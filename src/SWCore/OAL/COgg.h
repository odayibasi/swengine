#ifndef _COGG_H_
#define _COGG_H_


#include "AudioLoader.h"

#define STATIC_BUFFER_SIZE     32768       // 32 KB buffers



void initOggVorbis();
void deInitOggVorbis();
void openOggFileAndReadStructInfo(const char *szOggFile, AudioBuffer *aBuffer);
void allocBufferForOggDecoding(AudioBuffer *aBuffer);
unsigned long decodeOgg(AudioBuffer *aBuffer);
unsigned long decodeAllOgg(const char *szOggFile, AudioBuffer *aBuffer);



#endif