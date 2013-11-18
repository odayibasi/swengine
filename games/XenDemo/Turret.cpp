#include "Turret.h"
#include "EnemyWeapon.h"
#include "Explosion.h"
#include "Hud.h"


extern bool xenShadowActive;
extern int	turretSpriteID;
extern int	turretSlowMotionID;
extern int	fontID;


swPoint		turret_WP={0,0};
float turret_FireTable[12][4]={
	{20, -30, 500,-100},
	{20, -30, 300,-100},
	{0,	 -30, 100,-300},
	{-10,-30,-150,-300},
	{ -5,-10,-450, -50},
	{ 3, -2, -600, -50},
	{ 3, -2, -650, -50},
	{ 3, -2, -750, -50},
	{ 3, -2, -750, -50},
	{ 3, -2, -750, -50},
	{ 3, -2, -750, -50},
};

extern int explosionID;



//-------------------------------------------------------------------------------------------
void turretRenderWithParams(swColor color,xenTurret *turret,swRect target){
	swGraphicsSetColor1(&color);
	int index=swAnimatorGetIndex(turret->animID);
	swGraphicsRenderSprite4(turretSpriteID,index,&target,turret->rot,&turret_WP);

}


//-------------------------------------------------------------------------------------------
void turretPrepareShadow(swRect *rT,swRect rS){
	float dX=0;
	float dY=0;
	float dW=8;
	float dH=8;

	rT->x=rS.x+dX; rT->y=rS.y+dY; rT->w=rS.w+dW; rT->h=rS.h+dH; 
}


//-------------------------------------------------------------------------------------------
void turretRender(xenTurret *turret){
	turretRenderWithParams(SWCOLOR_WHITE,turret,turret->target);
}

//-------------------------------------------------------------------------------------------
void turretRenderShadow(xenTurret *turret){

	swColor shdColor={0,0,0,0.5};
	swRect  shdRect;

	turretPrepareShadow(&shdRect,turret->target);
	turretRenderWithParams(shdColor,turret,shdRect);
}



//-------------------------------------------------------------------------------------------
void turretDisplay(void *obj){
	xenTurret *turret=(xenTurret*)obj; 
	swGraphicsSetBlendingMode(SW_BLENDING_MODE_SOLID);
	if(xenShadowActive)
		turretRenderShadow(turret);
	turretRender(turret);
}

//-------------------------------------------------------------------------------------------
void turretExecute(void *obj){
	xenTurret *turret=(xenTurret*)obj; 
	int index=swAnimatorGetIndex(turret->animID);
	if(index!=turret->lastAnimIndex){
		turret->lastAnimIndex=index;
		float sX=swRectMidX(&turret->target)+turret_FireTable[index][0];
		float sY=swRectMidY(&turret->target)+turret_FireTable[index][1];
		enemyWeaponFire(sX,sY,sX+turret_FireTable[index][2],turret_FireTable[index][3]);
	}


	if(turret->hitCount>=10){
		explosionCreate(explosionID,turret->target,0,&SWCOLOR_WHITE);
		hudAddScore(4000);
		turret->bEnabled=false;
		swPhysBodyDestroy(turret->bodyID);
	}
}


//-------------------------------------------------------------------------------------------
void turretDestroy(void *obj){
	xenTurret *turret=(xenTurret*)obj; 
	swDispManagerDel(turret->dispID);
	swExecManagerDel(turret->execID);
	swAnimatorDestroy(turret->animID);
	free(turret);
}


//-------------------------------------------------------------------------------------------
xenTurret*	turretCreate(int layer, float x, float y){
	xenTurret* turret=(xenTurret*)malloc(sizeof(xenTurret));
	turret->layer=layer;
	turret->bEnabled=true;
	turret->hasShadow=true;
	turret->rot=0;
	turret->animID=swAnimatorCreate(swGraphicsGetCountOfImgInSprite(turretSpriteID),0.25);
	swAnimatorSetExecutionMode(turret->animID,SW_ANIMATOR_EXEC_FORWARD_LOOP);
	swRectSet(&turret->target,x,y,70,70);
	turret->dispID=swDispManagerAdd(turretDisplay,turret,&turret->bEnabled,&turret->target,&turret->layer);
	turret->execID=swExecManagerAdd(turretExecute,turret,&turret->bEnabled);

	//Register Phys
	turret->userData.obj=turret;
	turret->userData.type=XEN_TURRET;
	turret->hitCount=0;
	swPhysBodyDefSetUserData(&turret->userData);
	swPhysBodyDefSetPos(x,y);
	swPhysBodyDefSetRectShapeType(turret->target.w,turret->target.h);
	swPhysBodyDefSetDensity(0);
	turret->bodyID=swPhysBodyCreate();

	//Register DestroyManager
	swDestroyManagerAdd(turretDestroy,turret);

	return turret;
}
