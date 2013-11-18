#include "Defender.h"
#include "ObjParticle.h"
#include "Explosion.h"
#include "Hud.h"
#include "MoleculerDecompose.h"
#include "EnemyWeapon.h"
#include "Claw.h"
#include "RefPoint.h"


extern int	defenderAvoidID;
extern int	defenderRotateID;
extern int	defenderFireID;
extern bool xenShadowActive;

float   defenderMass=0;
swRect* defenderTarget=NULL; 


typedef struct xenDefenderPositionData{
   bool		xOutSideRange;
   bool		yOutSideRange;
   bool		wrongDirection;
   bool		returToRight;
   float	dX;
   float	dY;
};


extern int explosionID;

//-------------------------------------------------------------------------------------------
void defenderSetTarget(swRect *target){
	defenderTarget=target;
}


//-------------------------------------------------------------------------------------------
void defenderMoleculerDecompose(void *obj){
	xenDefender *defender=(xenDefender*)obj;
	int index=swAnimatorGetIndex(defender->animatorID);
	objParticleGenerate(&defender->target,10,10,defender->spriteID,defender->animatorID,0,0.5,0.1f,10);
	defender->bLive=false;
}



//-------------------------------------------------------------------------------------------
void defendeRenderWithParams(swColor color,xenDefender *defender,swRect target){

	//Draw Image
	swGraphicsSetColor1(&color);
	int animIndex=swAnimatorGetIndex(defender->animatorID);
	swGraphicsRenderSprite2(defender->spriteID,animIndex,&target,defender->source);


}


//-------------------------------------------------------------------------------------------
void defendePrepareShadow(swRect *rT,swRect rS){
	float dX=5;
	float dY=5;
	float dW=15;
	float dH=15;

	rT->x=rS.x+dX; rT->y=rS.y+dY; rT->w=rS.w+dW; rT->h=rS.h+dH; 
}


//-------------------------------------------------------------------------------------------
void defenderRender(xenDefender *defender){
	defendeRenderWithParams(SWCOLOR_WHITE,defender,defender->target);
}

//-------------------------------------------------------------------------------------------
void defenderRenderShadow(xenDefender *defender){

	swColor shdColor={0,0,0,0.5};
	swRect  shdRect;

	defendePrepareShadow(&shdRect,defender->target);
	defendeRenderWithParams(shdColor,defender,shdRect);
}



//-------------------------------------------------------------------------------------------
void defenderDisplay(void *obj){
	xenDefender *defender=(xenDefender*)obj; 
	swGraphicsSetBlendingMode(SW_BLENDING_MODE_SOLID);
	if(xenShadowActive)
		defenderRenderShadow(defender);
	defenderRender(defender);
}


//-------------------------------------------------------------------------------------------
void defenderApplyToForce(xenDefender *defender, float xMultiplier,float yMultiplier){
	swVec2 pos;
	pos.x=swRectMidX(&defender->target); pos.y=swRectMidY(&defender->target);
	swVec2 force;
	force.x=defenderMass*xMultiplier; 
	force.y=defenderMass*yMultiplier;
	swPhysBodyApplyForce(defender->bodyID,force,pos);
}


//-------------------------------------------------------------------------------------------
bool defenderIsAvoidMode(xenDefender *defender){
	float sX=swRectMidX(&defender->target);
	float tX=swRectMidX(defenderTarget);
	float range=1000;
	return !swMathIsInRangeFloat(tX-sX,-range,range);    
}

//-------------------------------------------------------------------------------------------
bool defenderIsLeftDirection(xenDefender *defender){
	return swRectEquals(defender->source,&SW_SPRITE_SOURCE_DEFAULT);
}


//-------------------------------------------------------------------------------------------
bool defenderIsRightDirection(xenDefender *defender){
	return swRectEquals(defender->source,&SW_SPRITE_SOURCE_MIRRORY);
}



//-------------------------------------------------------------------------------------------
bool  defenderIsPositioningMode(xenDefender *defender,xenDefenderPositionData *data){

	bool isPostioningMode=false;

	//X Range Control
	float xRange=600;
	float tX=swRectMidX(defenderTarget);
	float sX=swRectMidX(&defender->target);
	data->dX=tX-sX;
	bool isInXRange=swMathIsInRangeFloat(data->dX,-xRange,xRange);
	if(!isInXRange){
		isPostioningMode=true;
		data->xOutSideRange=true;
	}else{
		data->xOutSideRange=false;
	}

	//Y Range Control
	float yRange=40;
	float tY=swRectMidY(defenderTarget);
	float sY=swRectMidY(&defender->target);
	data->dY=tY-sY;
	bool isInYRange=swMathIsInRangeFloat(data->dY,-yRange,yRange);
	if(!isInYRange){
		isPostioningMode=true;
		data->yOutSideRange=true;
	}else{
		data->yOutSideRange=false;
	}

	//Direction
	data->wrongDirection=false;
	if(data->dX>0 &&  defenderIsLeftDirection(defender)){
		isPostioningMode=true;
		data->wrongDirection=true;
		data->returToRight=true;
	}

	if(data->dX<=0 && defenderIsRightDirection(defender)){
		isPostioningMode=true;
		data->wrongDirection=true;
		data->returToRight=false;
	}


	return isPostioningMode;
}


//-------------------------------------------------------------------------------------------
void defenderRunAvoidMode(xenDefender *defender){
	defender->animatorID=defender->avoidAnimatorID;
	defender->spriteID=defenderAvoidID; 
}


//-------------------------------------------------------------------------------------------
void defenderRunPositioningMode(xenDefender *defender,xenDefenderPositionData *positioningData){

	//Animation Setting
	if(positioningData->wrongDirection){
		defender->animatorID=defender->rotateAnimatorID;
		defender->spriteID=defenderRotateID;
	}else{
		defender->animatorID=defender->avoidAnimatorID;
		defender->spriteID=defenderAvoidID; 
	}

	//Rotation Animation
	if(positioningData->wrongDirection){
		
		if(swAnimatorIsLastFrameActive(defender->rotateAnimatorID)){
			 swAnimatorSetIndex(defender->rotateAnimatorID,0);
			if(positioningData->returToRight) defender->source=&SW_SPRITE_SOURCE_MIRRORY;	
			else defender->source=&SW_SPRITE_SOURCE_DEFAULT;
		}

	}else{ //Poistioning Movement
			
		if(positioningData->yOutSideRange){
			int signYDirection=swMathSign(positioningData->dY);
			defenderApplyToForce(defender,0,signYDirection);
		}

		if(positioningData->xOutSideRange){
			int signXDirection=swMathSign(positioningData->dX);
			defenderApplyToForce(defender,signXDirection,0);
		}
	
	}




}


//-------------------------------------------------------------------------------------------
void defenderRunFightiningMode(xenDefender *defender){
	swPhysBodySetLinearVelocityX(defender->bodyID,0);
	swPhysBodySetLinearVelocityY(defender->bodyID,0);
	defender->animatorID=defender->fireAnimatorID;
	defender->spriteID=defenderFireID;

	float sysTime=swSystemGetElapsedSeconds();
	if(sysTime-defender->lastFireTime>0.2){

		float sX=swRectMidX(&defender->target);
		float sY=swRectMidY(&defender->target);

		if(defenderIsLeftDirection(defender)){
			enemyWeaponFire(sX,sY,sX-400,sY);
		}else if(defenderIsRightDirection(defender)){
			enemyWeaponFire(sX,sY,sX+400,sY);
		}

		defender->lastFireTime=sysTime;
	}
}





//-------------------------------------------------------------------------------------------
void defenderExecute(void *obj){
	xenDefenderPositionData positioningData;
	xenDefender *defender=(xenDefender*)obj;
	defenderApplyToForce(defender,0,2); // for gravity; 

	if(defenderIsAvoidMode(defender)){
		defenderRunAvoidMode(defender);
	}else if(defenderIsPositioningMode(defender,&positioningData)){
		defenderRunPositioningMode(defender,&positioningData);
	}else{
		defenderRunFightiningMode(defender);		
	}

	if(defender->hitCount>=20){
		explosionCreate(explosionID,defender->target,0,&SWCOLOR_WHITE);
		hudAddScore(5000);
		defender->bLive=false;
		swPhysBodyDestroy(defender->bodyID);
		defender->bodyID=-1;
	}

}


//-------------------------------------------------------------------------------------------
void  defenderDestroy(void *obj){
	xenDefender *defender=(xenDefender*)obj;
	swDispManagerDel(defender->dispID);
	swExecManagerDel(defender->execID);
	if(defender->bodyID!=-1) swPhysBodyDestroy(defender->bodyID);
	swAnimatorDestroy(defender->avoidAnimatorID);
	swAnimatorDestroy(defender->rotateAnimatorID);
	swAnimatorDestroy(defender->fireAnimatorID);
	free(defender);	
}


//-------------------------------------------------------------------------------------------
xenDefender* defenderCreate(){
	xenDefender* defender=(xenDefender*)malloc(sizeof(xenDefender));
	defender->dispID=swDispManagerAdd(defenderDisplay,defender,&defender->bLive,NULL,&defender->layer);
	defender->execID=swExecManagerAdd(defenderExecute,defender,&defender->bLive);
	defender->layer=3;
	defender->bLive=true;
	defender->source=&SW_SPRITE_SOURCE_DEFAULT;
	defender->avoidAnimatorID=swAnimatorCreate(swGraphicsGetCountOfImgInSprite(defenderAvoidID),0.02f);
	defender->rotateAnimatorID=swAnimatorCreate(swGraphicsGetCountOfImgInSprite(defenderRotateID),0.03f);
	defender->fireAnimatorID=swAnimatorCreate(swGraphicsGetCountOfImgInSprite(defenderFireID),0.01f);
	swRectSet(&defender->target,100,250,100,50);
	swAnimatorSetExecutionMode(defender->avoidAnimatorID,SW_ANIMATOR_EXEC_FORWARD_LOOP);
	swAnimatorSetExecutionMode(defender->rotateAnimatorID,SW_ANIMATOR_EXEC_FORWARD);
	swAnimatorSetExecutionMode(defender->fireAnimatorID,SW_ANIMATOR_EXEC_FORWARD_LOOP);

	defender->state=XEN_DEFENDER_STATE_AVOID;
	defender->animatorID=defender->avoidAnimatorID;
	defender->spriteID=defenderAvoidID;

	//Phys..
	defender->userData.obj=defender;
	defender->userData.type=XEN_DEFENDER;
	defender->hitCount=0;

	swPhysBodyDefSetUserData(&defender->userData);
	swPhysBodyDefSetPos(defender->target.x,defender->target.y);
	swPhysBodyDefSetRectShapeType(defender->target.w,defender->target.h);
	swPhysBodyDefSetDensity(1.0f);
	swPhysBodyDefSetFilterGroupIndex(-5);
	swPhysBodyDefSetFixedRotation(true);
	swPhysBodyDefSetPosListener(&defender->target.x,&defender->target.y);
	defender->bodyID=swPhysBodyCreate();
	defenderMass=swPhysBodyGetMass(defender->bodyID);

	swDestroyManagerAdd(defenderDestroy,defender);


	defenderSetTarget(clawGetRect());
	
	//Fire
	defender->lastFireTime=0;
	moleculerDecomposerAdd(&defender->bLive,&defender->target,defenderMoleculerDecompose,defender);



	return defender;
}


//-------------------------------------------------------------------------------------------
void defenderSetPos(xenDefender *defender,float x, float y){
	swPhysBodySetXForm1(defender->bodyID,x,y,0);
}



