#include "../../include/SWEngine.h"
#include "Items.h"

extern int sprPlatformID;

//-------------------------------------------------------------------------------------------
void platformDisplay(dwPlatform *plt){
	swGraphicsSetBlendingMode(SW_BLENDING_MODE_SOLID);
	swGraphicsRenderImg0(sprPlatformID,&plt->target);
}

//-------------------------------------------------------------------------------------------
dwPlatform* platformCreate(float x,float y){
	dwPlatform *platform=(dwPlatform*)malloc(sizeof(dwPlatform)); 

	//Display Register
	platform->target.w=128; 
	platform->target.h=24;

	return platform;
}



