/*
 * Copyright (c) 2006, Creative Labs Inc.
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided
 * that the following conditions are met:
 * 
 *     * Redistributions of source code must retain the above copyright notice, this list of conditions and
 * 	     the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright notice, this list of conditions
 * 	     and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *     * Neither the name of Creative Labs Inc. nor the names of its contributors may be used to endorse or
 * 	     promote products derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "AudioLoader.h"
#include "COgg.h"





// Ogg Voribis DLL Handle
HINSTANCE g_hVorbisFileDLL = NULL;

// Functions
void InitVorbisFile();
void ShutdownVorbisFile();

void Swap(short &s1, short &s2);

size_t ov_read_func(void *ptr, size_t size, size_t nmemb, void *datasource);
int ov_seek_func(void *datasource, ogg_int64_t offset, int whence);
int ov_close_func(void *datasource);
long ov_tell_func(void *datasource);

// Function pointers
typedef int (*LPOVCLEAR)(OggVorbis_File *vf);
typedef long (*LPOVREAD)(OggVorbis_File *vf,char *buffer,int length,int bigendianp,int word,int sgned,int *bitstream);
typedef ogg_int64_t (*LPOVPCMTOTAL)(OggVorbis_File *vf,int i);
typedef vorbis_info * (*LPOVINFO)(OggVorbis_File *vf,int link);
typedef vorbis_comment * (*LPOVCOMMENT)(OggVorbis_File *vf,int link);
typedef int (*LPOVOPENCALLBACKS)(void *datasource, OggVorbis_File *vf,char *initial, long ibytes, ov_callbacks callbacks);

// Variables
LPOVCLEAR			fn_ov_clear = NULL;
LPOVREAD			fn_ov_read = NULL;
LPOVPCMTOTAL		fn_ov_pcm_total = NULL;
LPOVINFO			fn_ov_info = NULL;
LPOVCOMMENT			fn_ov_comment = NULL;
LPOVOPENCALLBACKS	fn_ov_open_callbacks = NULL;

bool g_bVorbisInit = false;



//----------------------------------------------------------------
void initOggVorbis(){
	InitVorbisFile();
	if(!g_bVorbisInit){
		swLoggerLog("Failed to find OggVorbis DLLs (vorbisfile.dll, ogg.dll, or vorbis.dll)\n");
		return;
	}
}


//----------------------------------------------------------------
void deInitOggVorbis(){
	if(g_bVorbisInit){
		ShutdownVorbisFile();
	}
}



//----------------------------------------------------------------
void openOggFileAndReadStructInfo(const char *szOggFile, AudioBuffer *aBuffer){
	// Open the OggVorbis file
	FILE *pOggVorbisFile = fopen(szOggFile,"rb");
	if (!pOggVorbisFile){
		return;
	}

	ov_callbacks	sCallbacks;
	vorbis_info		*psVorbisInfo;

	sCallbacks.read_func = ov_read_func;
	sCallbacks.seek_func = ov_seek_func;
	sCallbacks.close_func = ov_close_func;
	sCallbacks.tell_func = ov_tell_func;


	// Create an OggVorbis file stream
	if (fn_ov_open_callbacks(pOggVorbisFile, &aBuffer->sOggVorbisFile, NULL, 0, sCallbacks) == 0){
		// Get some information about the file (Channels, Format, and Frequency)
		psVorbisInfo = fn_ov_info(&aBuffer->sOggVorbisFile, -1);
		if (psVorbisInfo)
		{
			aBuffer->ulFrequency = psVorbisInfo->rate;
			aBuffer->ulChannels = psVorbisInfo->channels;
			if (psVorbisInfo->channels == 1)
			{
				aBuffer->ulFormat = AL_FORMAT_MONO16;
				// Set BufferSize to 250ms (Frequency * 2 (16bit) divided by 4 (quarter of a second))
				aBuffer->ulBufferSize = aBuffer->ulFrequency >> 1;
				// IMPORTANT : The Buffer Size must be an exact multiple of the BlockAlignment ...
				aBuffer->ulBufferSize -= (aBuffer->ulBufferSize % 2);
			}
			else if (psVorbisInfo->channels == 2)
			{
				aBuffer->ulFormat = AL_FORMAT_STEREO16;
				// Set BufferSize to 250ms (Frequency * 4 (16bit stereo) divided by 4 (quarter of a second))
				aBuffer->ulBufferSize = aBuffer->ulFrequency;
				// IMPORTANT : The Buffer Size must be an exact multiple of the BlockAlignment ...
				aBuffer->ulBufferSize -= (aBuffer->ulBufferSize % 4);
			}
			else if (psVorbisInfo->channels == 4)
			{
				aBuffer->ulFormat = alGetEnumValue("AL_FORMAT_QUAD16");
				// Set BufferSize to 250ms (Frequency * 8 (16bit 4-channel) divided by 4 (quarter of a second))
				aBuffer->ulBufferSize = aBuffer->ulFrequency * 2;
				// IMPORTANT : The Buffer Size must be an exact multiple of the BlockAlignment ...
				aBuffer->ulBufferSize -= (aBuffer->ulBufferSize % 8);
			}
			else if (psVorbisInfo->channels == 6)
			{
				aBuffer->ulFormat = alGetEnumValue("AL_FORMAT_51CHN16");
				// Set BufferSize to 250ms (Frequency * 12 (16bit 6-channel) divided by 4 (quarter of a second))
				aBuffer->ulBufferSize = aBuffer->ulFrequency * 3;
				// IMPORTANT : The Buffer Size must be an exact multiple of the BlockAlignment ...
				aBuffer->ulBufferSize -= (aBuffer->ulBufferSize % 12);
			}
		}
	}

}


//----------------------------------------------------------------
void allocBufferForOggDecoding(AudioBuffer *aBuffer){
	if (aBuffer->ulFormat != 0){
		// Allocate a buffer to be used to store decoded data for all Buffers
		aBuffer->pDecodeBuffer = (char*)malloc(aBuffer->ulBufferSize);
	}
}

//----------------------------------------------------------------
void InitVorbisFile(){	
	if (g_bVorbisInit)
		return;

	// Try and load Vorbis DLLs (VorbisFile.dll will load ogg.dll and vorbis.dll)
	g_hVorbisFileDLL = LoadLibrary("vorbisfile.dll");
	if (g_hVorbisFileDLL)
	{
		fn_ov_clear = (LPOVCLEAR)GetProcAddress(g_hVorbisFileDLL, "ov_clear");
		fn_ov_read = (LPOVREAD)GetProcAddress(g_hVorbisFileDLL, "ov_read");
		fn_ov_pcm_total = (LPOVPCMTOTAL)GetProcAddress(g_hVorbisFileDLL, "ov_pcm_total");
		fn_ov_info = (LPOVINFO)GetProcAddress(g_hVorbisFileDLL, "ov_info");
		fn_ov_comment = (LPOVCOMMENT)GetProcAddress(g_hVorbisFileDLL, "ov_comment");
		fn_ov_open_callbacks = (LPOVOPENCALLBACKS)GetProcAddress(g_hVorbisFileDLL, "ov_open_callbacks");

		if (fn_ov_clear && fn_ov_read && fn_ov_pcm_total && fn_ov_info &&
			fn_ov_comment && fn_ov_open_callbacks)
		{
			g_bVorbisInit = true;
		}
	}
}

//----------------------------------------------------------------
void ShutdownVorbisFile(){
	if (g_hVorbisFileDLL){
		FreeLibrary(g_hVorbisFileDLL);
		g_hVorbisFileDLL = NULL;
	}
	g_bVorbisInit = false;
}

//----------------------------------------------------------------
unsigned long DecodeOggVorbis(OggVorbis_File *psOggVorbisFile, char *pDecodeBuffer, unsigned long ulBufferSize, unsigned long ulChannels){
	
	int current_section;
	long lDecodeSize;
	unsigned long ulSamples;
	short *pSamples;

	unsigned long ulBytesDone = 0;
	while (1)
	{
		lDecodeSize = fn_ov_read(psOggVorbisFile, pDecodeBuffer + ulBytesDone, ulBufferSize - ulBytesDone, 0, 2, 1, &current_section);
		if (lDecodeSize > 0)
		{
			ulBytesDone += lDecodeSize;

			if (ulBytesDone >= ulBufferSize)
				break;
		}
		else
		{
			break;
		}
	}

	// Mono, Stereo and 4-Channel files decode into the same channel order as WAVEFORMATEXTENSIBLE,
	// however 6-Channels files need to be re-ordered
	if (ulChannels == 6)
	{		
		pSamples = (short*)pDecodeBuffer;
		for (ulSamples = 0; ulSamples < (ulBufferSize>>1); ulSamples+=6)
		{
			// WAVEFORMATEXTENSIBLE Order : FL, FR, FC, LFE, RL, RR
			// OggVorbis Order            : FL, FC, FR,  RL, RR, LFE
			Swap(pSamples[ulSamples+1], pSamples[ulSamples+2]);
			Swap(pSamples[ulSamples+3], pSamples[ulSamples+5]);
			Swap(pSamples[ulSamples+4], pSamples[ulSamples+5]);
		}
	}

	return ulBytesDone;
}




//----------------------------------------------------------------
void Swap(short &s1, short &s2){
	short sTemp = s1;
	s1 = s2;
	s2 = sTemp;
}

//----------------------------------------------------------------
size_t ov_read_func(void *ptr, size_t size, size_t nmemb, void *datasource){
	return fread(ptr, size, nmemb, (FILE*)datasource);
}

//----------------------------------------------------------------
int ov_seek_func(void *datasource, ogg_int64_t offset, int whence){
	return fseek((FILE*)datasource, (long)offset, whence);
}


//----------------------------------------------------------------
int ov_close_func(void *datasource){
   return fclose((FILE*)datasource);
}


//----------------------------------------------------------------
long ov_tell_func(void *datasource){
	return ftell((FILE*)datasource);
}

//----------------------------------------------------------------
unsigned long decodeOgg(AudioBuffer *aB){
	return DecodeOggVorbis(&aB->sOggVorbisFile, aB->pDecodeBuffer, aB->ulBufferSize, aB->ulChannels);
}


//----------------------------------------------------------------
unsigned long decodeAllOgg(const char *szOggFile, AudioBuffer *aB){
	

	openOggFileAndReadStructInfo(szOggFile,aB);	
	allocBufferForOggDecoding(aB);
	
	unsigned long totalBytes=0;
	do{
		aB->ulBytesWritten=decodeOgg(aB);
		totalBytes+=aB->ulBytesWritten;
	}while(aB->ulBytesWritten>0);
	free(aB->pDecodeBuffer);

	openOggFileAndReadStructInfo(szOggFile,aB);	

	aB->ulBufferSize=totalBytes;
	allocBufferForOggDecoding(aB);
	aB->ulBytesWritten=decodeOgg(aB);

	return aB->ulBytesWritten;
}
