#include "PostProcessingFX.h"


bool bSlowMotionActive=false;
extern  int gameLoopTimerID;


//-------------------------------------------------------------------------------------------
void slowMotionExit(void *obj){
	swTimerUpdateDelaySeconds(gameLoopTimerID,0.016f);
	fullSceenFXSetActive(FULLSCREEN_FX_NONE);
	bSlowMotionActive=false;
}


//-------------------------------------------------------------------------------------------
void slowMotionEnter(){
	bSlowMotionActive=true;
	swTimerUpdateDelaySeconds(gameLoopTimerID,0.1f);
	fullSceenFXSetActive(FULLSCREEN_FX_GRAYSCALED);	
	swScheduledManagerAdd1(slowMotionExit,NULL,3.0f);
}