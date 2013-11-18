#include "XenDemoApp.h"


bool bLaserCollisionFX=false;


//-------------------------------------------------------------------------------------------
void laserCollisionExit(void *obj){
	//fullSceenFXSetActive(FULLSCREEN_FX_NONE);
	//bLaserCollisionFX=false;
}


//-------------------------------------------------------------------------------------------
void laserCollisionEnter(){
	//bLaserCollisionFX=true;
	//fullSceenFXSetActive(FULLSCREEN_FX_INVERTED);	
	//swScheduledManagerAdd1(laserCollisionExit,NULL,0.5f);
}
