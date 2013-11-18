#include "SWAudioIn.h"

int bufferList=-1;
int sourceList=-1;
int bufferIDCounter=0;
int sourceIDCounter=0;

#define SWAUDIOSOURCE_HSNOBFFER "HasNo Buffer"
#define SWAUDIOSOURCE_INITIAL   "Initial"
#define SWAUDIOSOURCE_PLAYING   "Playing"
#define SWAUDIOSOURCE_PAUSE     "Pause"
#define SWAUDIOSOURCE_STOP      "Stop"


//-------------------------------------------------------------------------------------------
DllExport void swAudioInit(void){

	bufferList=swLinkedListCreate();
	sourceList=swLinkedListCreate();

	ALCdevice* pDevice = alcOpenDevice(NULL);
	if (pDevice){
		ALCcontext* pContext = alcCreateContext(pDevice, NULL);
		alcMakeContextCurrent(pContext);
		swAudioLoaderInit();
	}
}


//-------------------------------------------------------------------------------------------
DllExport void swAudioDeInit(void){

	ALCcontext *pContext = alcGetCurrentContext();
	ALCdevice *pDevice = alcGetContextsDevice(pContext);

	alcMakeContextCurrent(NULL);
	alcDestroyContext(pContext);
	alcCloseDevice(pDevice);
	swLinkedListDestroy(bufferList);
	swLinkedListDestroy(sourceList);
	swAudioLoaderDeInit();
}

//-------------------------------------------------------------------------------------------
DllExport void swAudioUpdate(void){


	AudioSource *aS=(AudioSource*)swLinkedListGetFirst(sourceList);
	while(aS!=NULL){
	  	
		if( aS->aBuffer!=NULL){
			AudioBuffer *aB=aS->aBuffer;
			if(aS->state==SW_AUDIO_SOURCE_STATE_PLAYING && aB->type==SW_AUDIO_BUFFER_TYPE_OGG_STREAM){
				aS->iBuffersProcessed = 0;
				alGetSourcei(aS->oalSourceID, AL_BUFFERS_PROCESSED, &aS->iBuffersProcessed);
				aS->iTotalBuffersProcessed+=aS->iBuffersProcessed;

				// For each processed buffer, remove it from the Source Queue, read next chunk of audio
				// data from disk, fill buffer with new data, and add it to the Source Queue
				while (aS->iBuffersProcessed){
					// Remove the Buffer from the Queue.  (uiBuffer contains the Buffer ID for the unqueued Buffer)
					aB->oalBufferID = 0;
					alSourceUnqueueBuffers(aS->oalSourceID, 1, &aB->oalBufferID);
					swAudioLoaderLoadOggStream(aS->oalSourceID,&aB->oalBufferID,aB);
					aS->iBuffersProcessed--;
				}

				// Check the status of the Source.  If it is not playing, then playback was completed,
				// or the Source was starved of audio data, and needs to be restarted.
				alGetSourcei(aS->oalSourceID, AL_SOURCE_STATE, &aS->iState);
				if (aS->iState != AL_PLAYING){
					// If there are Buffers in the Source Queue then the Source was starved of audio
					// data, so needs to be restarted (because there is more audio data to play)
					alGetSourcei(aS->oalSourceID, AL_BUFFERS_QUEUED, &aS->iQueuedBuffers);
					if (aS->iQueuedBuffers){
						alSourcePlay(aS->oalSourceID);
					}else{
						free(aB->pDecodeBuffer);
						swAudioLoaderCreateOggFileStream(aB->fsFullPath,aB);
						swAudioBindSourceAndBuffer(aS->id,aB->id);
					}
				}
			}else if(aS->state==SW_AUDIO_SOURCE_STATE_PLAYING && aB->type!=SW_AUDIO_BUFFER_TYPE_OGG_STREAM){
				alGetSourcei(aS->oalSourceID, AL_SOURCE_STATE, &aS->iState);
				if (aS->iState != AL_PLAYING){
					aS->state=SW_AUDIO_SOURCE_STATE_STOP;
					alSourceStop(aS->oalSourceID);
				}
			}
		}//end if Buffer NULL
		aS=(AudioSource*)swLinkedListGetNext(sourceList);
	}
}


//-------------------------------------------------------------------------------------------
AudioSource* swAudioGetSource(int sourceID){
	AudioSource *audioSource=(AudioSource*)swLinkedListGetFirst(sourceList);
	while(audioSource!=NULL){
		if(audioSource->id==sourceID){
			return  audioSource;
		}
		audioSource=(AudioSource*)swLinkedListGetNext(sourceList);
	}
	return NULL;
}

//-------------------------------------------------------------------------------------------
AudioBuffer* swAudioGetBuffer(int bufferID){
	AudioBuffer *audioBuffer=(AudioBuffer*)swLinkedListGetFirst(bufferList);
	while(audioBuffer!=NULL){
		if(audioBuffer->id==bufferID){
			return  audioBuffer;
		}
		audioBuffer=(AudioBuffer*)swLinkedListGetNext(bufferList);
	}
	return NULL;
}


//-------------------------------------------------------------------------------------------
DllExport int  swAudioCreateBuffer(char *path, swAudioBufferType bufferType){
	//FullPath creation
	char fsFullPath[MAX_PATH];
	swStringCopy(fsFullPath,swFileSystemGetResourcePath());
	swStringConcat1(fsFullPath,path);

	AudioBuffer* aBuffer=(AudioBuffer*)malloc(sizeof(AudioBuffer));
	aBuffer->type=bufferType;
	alGenBuffers( 1, &aBuffer->oalBufferID);
	swLinkedListAdd(bufferList,aBuffer);
	aBuffer->id=bufferIDCounter++;
	swStringCopy(aBuffer->fsFullPath,fsFullPath);
	switch(bufferType){
		case SW_AUDIO_BUFFER_TYPE_WAV:
			 swAudioLoaderLoadWav(fsFullPath,aBuffer->oalBufferID);
			 break;
		case SW_AUDIO_BUFFER_TYPE_OGG:
			swAudioLoaderLoadOgg(fsFullPath,aBuffer);
			break;
		case SW_AUDIO_BUFFER_TYPE_OGG_STREAM:
			alGenBuffers( NUMBUFFERS, aBuffer->streamBuffers);
			swAudioLoaderCreateOggFileStream(fsFullPath,aBuffer);
			break;
	}

	return aBuffer->id;
}




//-------------------------------------------------------------------------------------------
DllExport void swAudioDestroyBuffer(int bufferID){
	AudioBuffer *aBuffer=swAudioGetBuffer(bufferID);
	alDeleteBuffers(1, &aBuffer->oalBufferID);
	swLinkedListDel(bufferList,aBuffer);
}



//Source
//-------------------------------------------------------------------------------------------
DllExport int    swAudioCreateSource(){
	AudioSource* aSource=(AudioSource*)malloc(sizeof(AudioSource));
	aSource->aBuffer=NULL;
	aSource->state=SW_AUDIO_SOURCE_STATE_NOBUFFER;
	alGenSources(1, &aSource->oalSourceID);
	swLinkedListAdd(sourceList,aSource);
	aSource->id=sourceIDCounter++;
	return aSource->id;
}

//-------------------------------------------------------------------------------------------
DllExport void   swAudioDestroySource(int sourceID){
	AudioSource* aSource=swAudioGetSource(sourceID);
	alDeleteSources(1,&aSource->oalSourceID);
	swLinkedListDel(sourceList, aSource);
}


//-------------------------------------------------------------------------------------------
DllExport void   swAudioBindSourceAndBuffer(int sourceID,int bufferID){
	AudioSource* aS=swAudioGetSource(sourceID); 
	AudioBuffer* aB=swAudioGetBuffer(bufferID);
	if(aB->type==SW_AUDIO_BUFFER_TYPE_OGG_STREAM){
		for (int iLoop = 0; iLoop < NUMBUFFERS; iLoop++)
			swAudioLoaderLoadOggStream(aS->oalSourceID,&aB->streamBuffers[iLoop],aB);
	}else{
		alSourcei(aS->oalSourceID, AL_BUFFER, aB->oalBufferID);
	}
	aS->state=SW_AUDIO_SOURCE_STATE_INITIAL;
	aS->aBuffer=aB;
}

//-------------------------------------------------------------------------------------------
DllExport void   swAudioPlaySource(int sourceID){
    AudioSource *source=swAudioGetSource(sourceID);
	alSourcePlay(source->oalSourceID);
	source->state=SW_AUDIO_SOURCE_STATE_PLAYING;
}


//-------------------------------------------------------------------------------------------
DllExport void   swAudioPauseSource(int sourceID){
	AudioSource *source=swAudioGetSource(sourceID);
	alSourcePause(source->oalSourceID);
	source->state=SW_AUDIO_SOURCE_STATE_PAUSE;
}


//-------------------------------------------------------------------------------------------
DllExport void   swAudioStopSource(int sourceID){
	AudioSource *source=swAudioGetSource(sourceID);
	alSourceStop(source->oalSourceID);
	source->state=SW_AUDIO_SOURCE_STATE_STOP;
}


//-------------------------------------------------------------------------------------------
DllExport void   swAudioRewindSource(int sourceID){
	AudioSource *source=swAudioGetSource(sourceID);
	alSourceRewind(source->oalSourceID);
}


//-------------------------------------------------------------------------------------------
DllExport void   swAudioSetSourcePosition(int sourceID,float x,float y,float z){
	AudioSource *source=swAudioGetSource(sourceID);
	alSource3f(source->oalSourceID,AL_POSITION,x,y,z);
}

//-------------------------------------------------------------------------------------------
DllExport swAudioSourceState swAudioGetSourceState(int sourceID){
	AudioSource *source=swAudioGetSource(sourceID);
	return source->state;
}


//-------------------------------------------------------------------------------------------
DllExport char* swAudioGetSourceStateText(int sourceID){
	switch(swAudioGetSourceState(sourceID)){
		case SW_AUDIO_SOURCE_STATE_NOBUFFER:
			return SWAUDIOSOURCE_HSNOBFFER;
		case SW_AUDIO_SOURCE_STATE_INITIAL:
			return SWAUDIOSOURCE_INITIAL;
		case SW_AUDIO_SOURCE_STATE_PLAYING:
			return SWAUDIOSOURCE_PLAYING;
		case SW_AUDIO_SOURCE_STATE_PAUSE:
			return SWAUDIOSOURCE_PAUSE;
		case SW_AUDIO_SOURCE_STATE_STOP:
			return SWAUDIOSOURCE_STOP;
		default:
			return SWAUDIOSOURCE_HSNOBFFER;
	}//end switch
}

//-------------------------------------------------------------------------------------------
DllExport void	swAudioSetSourceLoop(int sourceID,bool loop){
	AudioSource *source=swAudioGetSource(sourceID);
	alSourcei (source->oalSourceID,AL_LOOPING,loop);
}


//-------------------------------------------------------------------------------------------
DllExport void	swAudioSetSourcePitch(int sourceID,float pitch){
	AudioSource *source=swAudioGetSource(sourceID);
	alSourcef (source->oalSourceID,AL_PITCH,pitch);
}


//-------------------------------------------------------------------------------------------
DllExport void	swAudioSetSourceGain(int sourceID,float gain){
	AudioSource *source=swAudioGetSource(sourceID);
	alSourcef (source->oalSourceID,AL_GAIN,gain);
}




//Listener
//-------------------------------------------------------------------------------------------
DllExport void  swAudioSetListenerPosition(float x,float y,float z){
	alListener3f(AL_POSITION,x,y,z);
}




