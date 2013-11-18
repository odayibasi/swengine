#include "Stages.h"


extern int imgYouDiedID;
extern int imgEndOfSceneBgID;
extern int imgEndOfSceneExitID;

swRect rectEndOfSceneBg={0,128,1024,512};
swRect rectYouDied={375,225,512,256};
swRect rectEndOfSceneExit={700,35,256,32};


extern void (*activeFunc)(void);

float fadeValue=0;
float endOfTimeLastUpdate=0;
float endOfFadeDelay=0.2;

int   iExitBtnState=0;    //0-None  1-Wait 2-Display 
float fExitBtnWaitStartTime=0;

extern int endOfSceneSourceID;
extern int endOfSceneBufferID;
extern int menuBgBufferID;


extern swMouseState mousState;


//---------------------------------------------------------------------------------
void playJoyfulMusic() {
	swAudioStopSource(endOfSceneSourceID);
	swAudioSetSourceGain(endOfSceneSourceID,5);
	swAudioSetSourceLoop(endOfSceneSourceID,true);
	swAudioBindSourceAndBuffer(endOfSceneSourceID,menuBgBufferID);
	swAudioPlaySource(endOfSceneSourceID);
}


//---------------------------------------------------------------------------------
void playDramaticMusic() {
	swAudioSetSourceGain(endOfSceneSourceID,5);
	swAudioSetSourceLoop(endOfSceneSourceID,false);
	swAudioBindSourceAndBuffer(endOfSceneSourceID,endOfSceneBufferID);
	swAudioPlaySource(endOfSceneSourceID);
}


//---------------------------------------------------------------------------------
void stageEndOfSceneInit(){
	playDramaticMusic();
	activeFunc=stageEndOfSceneExecute;
}




//---------------------------------------------------------------------------------
void stageEndOfSceneExecute(){

	float currentTime=swSystemGetElapsedSeconds();
	if(currentTime-endOfTimeLastUpdate>endOfFadeDelay){
      fadeValue+=0.05;
	  endOfTimeLastUpdate=currentTime;	
	}

	swGraphicsSetBlendingMode(SW_BLENDING_MODE_SOLID);
	swGraphicsSetColor1(&SWCOLOR_WHITE);
	swGraphicsRenderImg0(imgEndOfSceneBgID,&rectEndOfSceneBg);

	if(fadeValue>=1){
		fadeValue=1;
		if(iExitBtnState==0){
			fExitBtnWaitStartTime=currentTime;
			iExitBtnState=1;
		}	
	}




	if(iExitBtnState==1 && currentTime-fExitBtnWaitStartTime>3.5){
		iExitBtnState=2;
		playJoyfulMusic();

	}

	swGraphicsSetColor0(1,1,1,fadeValue);
	swGraphicsRenderImg0(imgYouDiedID,&rectYouDied);


   

	if(swIntersectionRectAndPoint2(&rectEndOfSceneExit,mousState.x,mousState.y) && iExitBtnState==2){
			swGraphicsSetColor1(&SWCOLOR_GREEN);
			swGraphicsRenderImg0(imgEndOfSceneExitID,&rectEndOfSceneExit);
			if(mousState.btnLEFT) exit(0);
	}else if(iExitBtnState==2){
			swGraphicsSetColor1(&SWCOLOR_WHITE);
			swGraphicsRenderImg0(imgEndOfSceneExitID,&rectEndOfSceneExit);
	}
   





}


//---------------------------------------------------------------------------------
void stageEndOfSceneDeInit(){

}

