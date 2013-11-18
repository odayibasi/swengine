#ifndef SWAUDIO_IN_H
#define SWAUDIO_IN_H

#include "SWCoreIn.h"

#pragma comment (lib,"openal32.lib")   
#pragma comment (lib,"EFX-Util.lib")   


#include <al/al.h>
#include <al/alc.h>
#include <al/efx.h>
#include <al/efx-creative.h>
#include <al/xram.h>
#include "oal/AudioLoader.h"


typedef struct _AudioSource{
   int id;
   ALuint oalSourceID;
   AudioBuffer *aBuffer;
   int iBuffersProcessed, iTotalBuffersProcessed, iQueuedBuffers;
   ALint iState;
   swAudioSourceState state;
}AudioSource;




#endif