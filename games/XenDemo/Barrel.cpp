#include "Barrel.h"
#include "Hud.h"
#include "Explosion.h"
#include "PostProcessingFX.h"


extern bool xenShadowActive;
extern int	fontID;
extern int	explosionID;

extern	int	barrelID;
extern  int	barrelSlowMotionID;
swPoint		barrelWP={0,0};




//-------------------------------------------------------------------------------------------
void barrelRenderWithParams(swColor color,xenBarrel *barrel,swRect target){

	int imgID;
	if(barrel->slowMotion)
		imgID=barrelSlowMotionID;
	else
		imgID=barrelID;
		
	swGraphicsSetColor1(&color);
	swGraphicsRenderImg4(imgID,&target,barrel->rot,&barrelWP);

}


//-------------------------------------------------------------------------------------------
void barrelPrepareShadow(swRect *rT,swRect rS){
	float dX=0;
	float dY=0;
	float dW=8;
	float dH=8;

	rT->x=rS.x+dX; rT->y=rS.y+dY; rT->w=rS.w+dW; rT->h=rS.h+dH; 
}


//-------------------------------------------------------------------------------------------
void barrelRender(xenBarrel *barrel){
	barrelRenderWithParams(SWCOLOR_WHITE,barrel,barrel->target);
}

//-------------------------------------------------------------------------------------------
void barrelRenderShadow(xenBarrel *barrel){

	swColor shdColor={0,0,0,0.5};
	swRect  shdRect;

	barrelPrepareShadow(&shdRect,barrel->target);
	barrelRenderWithParams(shdColor,barrel,shdRect);
}



//-------------------------------------------------------------------------------------------
void displayBarrel(void *obj){
	xenBarrel *barrel=(xenBarrel*)obj; 
	swGraphicsSetBlendingMode(SW_BLENDING_MODE_SOLID);
	if(xenShadowActive)
		barrelRenderShadow(barrel);
	barrelRender(barrel);
}

//-------------------------------------------------------------------------------------------
void barrelExecute(void *obj){
	xenBarrel*barrel=(xenBarrel*)obj;
	if(barrel->hitCount>=5){
		swPhysBodyDestroy(barrel->bodyID);
		barrel->bodyID=-1;
		barrel->bEnabled=false;
		explosionCreate(explosionID,barrel->target,barrel->rot,&SWCOLOR_WHITE);
		hudAddScore(1000);
		if(barrel->slowMotion) slowMotionEnter();
		else shockWaveEnter(swRectMidX(&barrel->target),swRectMidY(&barrel->target));
					
	}
}


//-------------------------------------------------------------------------------------------
void barrelExplode(void *obj){
	xenBarrel*barrel=(xenBarrel*)obj;
	barrel->hitCount=10;
}

//-------------------------------------------------------------------------------------------
void barrelExplodeWithWaitTime(xenBarrel *barrel,float waitTime){
	swScheduledManagerAdd1(barrelExplode,barrel,waitTime);
}


//-------------------------------------------------------------------------------------------
void barrelExplosionListen(swExplosionEffect *e){ 
	xenUserData *userData=(xenUserData*)e->userData;
	if(userData->type==XEN_BARREL){
		if(e->dist<32){
			xenBarrel *barrel=(xenBarrel*)userData->obj;
			barrelExplodeWithWaitTime(barrel,0.1f);
		}
	}
}



//-------------------------------------------------------------------------------------------
void barrelDestroy(void *obj){
	xenBarrel*barrel=(xenBarrel*)obj;
	swDispManagerDel(barrel->dispID);
	swExecManagerDel(barrel->execID);
	if(barrel->bodyID!=-1) swPhysBodyDestroy(barrel->bodyID);
	free(barrel);
}



//-------------------------------------------------------------------------------------------
xenBarrel*	barrelCreate(int layer, float x, float y,bool slowMotion){
	xenBarrel* barrel=(xenBarrel*)malloc(sizeof(xenBarrel));
	
	//Barrel Set Disp Properties And Register
	barrel->layer=layer;
	barrel->bEnabled=true;
	barrel->hasShadow=true;
	barrel->rot=0;
	barrel->slowMotion=slowMotion;
	swRectSet(&barrel->target,x,y,25,25);
	barrel->dispID=swDispManagerAdd(displayBarrel,barrel,&barrel->bEnabled,&barrel->target,&barrel->layer);
	
	//Register Exec Manager
	barrel->execID=swExecManagerAdd(barrelExecute,barrel,&barrel->bEnabled);

	//Physics Objects Create And Register
	barrel->userData.obj=barrel;
	barrel->userData.type=XEN_BARREL;
	barrel->hitCount=0;
	swPhysBodyDefSetUserData(&barrel->userData);
	swPhysBodyDefSetPos(x,y);
	swPhysBodyDefSetRectShapeType(25,25);
	swPhysBodyDefSetDensity(1.0f);
	swPhysBodyDefSetPosListener(&barrel->target.x,&barrel->target.y);
	swPhysBodyDefSetAngleListener(&barrel->rot);
	barrel->bodyID=swPhysBodyCreate();
	explosionListenerAdd(barrelExplosionListen); //TODO

	//Register DestroyManager
	swDestroyManagerAdd(barrelDestroy,barrel);
	
	//Return Barrel
	return barrel;
}
