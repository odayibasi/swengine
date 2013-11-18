#ifndef SWAUDIOLOADER_H
#define SWAUDIOLOADER_H

#include <al/al.h>
#include <al/alc.h>
#include <al/efx.h>
#include <al/efx-creative.h>
#include <al/xram.h>
#include "CWaves.h"
#include "vorbisfile.h"
#include "../SWCoreIn.h"

#define NUMBUFFERS              (4)

typedef struct _AudioBuffer{
	int					id;
	swAudioBufferType	type;
	ALuint				oalBufferID;
	ALuint				streamBuffers[NUMBUFFERS];
	unsigned long		ulFrequency;
	unsigned long		ulFormat;
	unsigned long		ulChannels;
	unsigned long		ulBufferSize;
	unsigned long		ulBytesWritten;
	char				*pDecodeBuffer;
	OggVorbis_File		sOggVorbisFile;
	char				fsFullPath[MAX_PATH];
}AudioBuffer;



void swAudioLoaderInit();
void swAudioLoaderDeInit();
ALboolean swAudioLoaderLoadWav(const char *szWaveFile, ALuint uiBufferID);
ALboolean swAudioLoaderLoadOgg(const char *szOggFile, AudioBuffer *aB);
ALboolean swAudioLoaderLoadOggStream(ALuint oalSourceID, ALuint* oalBufferID, AudioBuffer *aB);
ALboolean swAudioLoaderCreateOggFileStream(const char *szOggFile, AudioBuffer *aBuffer);







#endif 
