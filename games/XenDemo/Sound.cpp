#include "../../include/SWEngine.h"
#include "Sound.h"

#define XEN_MAX_SOUND_SOURCE 20


extern int clawWpnSoundBufferID;
extern int clawWpnCollideSoundBufferID;
extern int barrelExplodeSoundBufferID; 

int  arryOfSoundSource[XEN_MAX_SOUND_SOURCE];

//-------------------------------------------------------------------------------------------
void soundInit(){
	for(int i=0;i<XEN_MAX_SOUND_SOURCE;i++){
		arryOfSoundSource[i]=swAudioCreateSource();
	}
}


//-------------------------------------------------------------------------------------------
void soundDeInit(){

}

//-------------------------------------------------------------------------------------------
int soundGetFreeSource(){
	for(int i=0;i<XEN_MAX_SOUND_SOURCE;i++){
		int sourceID=arryOfSoundSource[i];
		switch(swAudioGetSourceState(sourceID)){
			case SW_AUDIO_SOURCE_STATE_INITIAL:
			case SW_AUDIO_SOURCE_STATE_NOBUFFER:
			case SW_AUDIO_SOURCE_STATE_STOP:
				return sourceID;
			default:
				break;
		}
	}
	return -1;
}


//-------------------------------------------------------------------------------------------
void soundPlay(xenSoundType type){

	int sourceID=soundGetFreeSource();
	if(sourceID==-1)
		return;

	switch(type){
		case SOUND_OF_CLAW_WEAPON_BULLET_SHOT:
			swAudioSetSourceGain(sourceID,0.1);
			swAudioBindSourceAndBuffer(sourceID,clawWpnSoundBufferID);
			swAudioPlaySource(sourceID);
			break;
		case SOUND_OF_CLAW_WEAPON_BULLET_COLLIDE:
			swAudioSetSourceGain(sourceID,0.1);
			swAudioBindSourceAndBuffer(sourceID,clawWpnCollideSoundBufferID);
			swAudioPlaySource(sourceID);			
			break;
		case SOUND_OF_BARREL_EXPLODE:
			swAudioSetSourceGain(sourceID,0.1);
			swAudioBindSourceAndBuffer(sourceID,barrelExplodeSoundBufferID);
			swAudioPlaySource(sourceID);			
		default:
			break;
	}
}