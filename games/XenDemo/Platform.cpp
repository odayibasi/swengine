#include "../../include/SWEngine.h"
#include "Platform.h"

extern int platformID;

//-------------------------------------------------------------------------------------------
void platformDisplay(void *obj){
	xenPlatform *platform=(xenPlatform*)obj; 
	swGraphicsSetBlendingMode(SW_BLENDING_MODE_SOLID);
	swGraphicsRenderImg0(platformID,&platform->target);
}

//-------------------------------------------------------------------------------------------
void platformDestroy(void *obj){
	xenPlatform *platform=(xenPlatform*)obj; 
	swDispManagerDel(platform->dispID);
	swPhysBodyDestroy(platform->bodyID);
	free(platform);
}

//-------------------------------------------------------------------------------------------
void platformCreate(float x,float y){
	xenPlatform *platform=(xenPlatform*)malloc(sizeof(xenPlatform)); 

	//Display Register
	platform->layer=1;
	platform->target.w=128; 
	platform->target.h=24;
	platform->dispID=swDispManagerAdd(platformDisplay,platform,NULL,&platform->target,&platform->layer);

	//Phys Register
	swPhysBodyDefSetPos(x,y);
	swPhysBodyDefSetRectShapeType(platform->target.w,platform->target.h);
	swPhysBodyDefSetDensity(0);
	swPhysBodyDefSetFilterGroupIndex(-4);
	swPhysBodyDefSetPosListener(&platform->target.x,&platform->target.y);
	platform->bodyID=swPhysBodyCreate();

	//Destroy Register
	swDestroyManagerAdd(platformDestroy,platform);
}



