#include "AudioLoader.h"
#include "COgg.h"


static CWaves *g_pWaveLoader = NULL;


//----------------------------------------------------------------
void swAudioLoaderInit(){
	g_pWaveLoader = new CWaves();
	initOggVorbis();
}

//----------------------------------------------------------------
void swAudioLoaderDeInit(){
	if (g_pWaveLoader){
		delete g_pWaveLoader;
		g_pWaveLoader = NULL;
	}

	deInitOggVorbis();
}

//----------------------------------------------------------------
ALboolean swAudioLoaderLoadWav(const char *szWaveFile, ALuint uiBufferID){
	WAVEID			WaveID;
	ALint			iDataSize, iFrequency;
	ALenum			eBufferFormat;
	ALchar			*pData;
	ALboolean		bReturn;

	bReturn = AL_FALSE;
	if (g_pWaveLoader){
		if (SUCCEEDED(g_pWaveLoader->LoadWaveFile(szWaveFile, &WaveID))){
			if ((SUCCEEDED(g_pWaveLoader->GetWaveSize(WaveID, (unsigned long*)&iDataSize))) &&
				(SUCCEEDED(g_pWaveLoader->GetWaveData(WaveID, (void**)&pData))) &&
				(SUCCEEDED(g_pWaveLoader->GetWaveFrequency(WaveID, (unsigned long*)&iFrequency))) &&
				(SUCCEEDED(g_pWaveLoader->GetWaveALBufferFormat(WaveID, &alGetEnumValue, (unsigned long*)&eBufferFormat))))
			{

				alGetError();
				alBufferData(uiBufferID, eBufferFormat, pData, iDataSize, iFrequency);
				if (alGetError() == AL_NO_ERROR)
					bReturn = AL_TRUE;

				g_pWaveLoader->DeleteWaveFile(WaveID);
			}
		}
	}

	return  bReturn;
}


//----------------------------------------------------------------
ALboolean swAudioLoaderLoadOgg(const char *szOggFile, AudioBuffer *aB){
	aB->ulBytesWritten = decodeAllOgg(szOggFile,aB);
	if (aB->ulBytesWritten){
		alBufferData(aB->oalBufferID, aB->ulFormat, aB->pDecodeBuffer, aB->ulBytesWritten, aB->ulFrequency);
	}
	return  AL_TRUE;
}


//----------------------------------------------------------------
ALboolean swAudioLoaderCreateOggFileStream(const char *szOggFile, AudioBuffer *aBuffer){
	openOggFileAndReadStructInfo(szOggFile,aBuffer);
	allocBufferForOggDecoding(aBuffer);
	return AL_TRUE;
}


//----------------------------------------------------------------
ALboolean swAudioLoaderLoadOggStream(ALuint oalSourceID, ALuint* oalBufferID, AudioBuffer *aB){
	aB->ulBytesWritten = decodeOgg(aB);
	if (aB->ulBytesWritten){
		alBufferData((*oalBufferID), aB->ulFormat, aB->pDecodeBuffer, aB->ulBytesWritten, aB->ulFrequency);
		alSourceQueueBuffers(oalSourceID, 1, oalBufferID);
	}
	return AL_TRUE;
}

