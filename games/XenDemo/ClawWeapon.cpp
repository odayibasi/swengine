#include "ClawWeapon.h"
#include "Hud.h"
#include "Sound.h"


//WeaponIcon
extern int bulletIcon;
extern int acidIcon;
extern int lawIcon;
extern int laserIcon;
extern int gravityIcon;
extern int guidedIcon;
extern int misketIcon;
extern int cristalIcon;

int				clawWpnDispID;
int				clawWpnExecID;


int				clawActiveWpnImgID;
int				clawWpnLayer=5;
extern eWpnType clawActiveWpn;		



//Weapon
extern int	wpnBullet;
float		clawWpnBulletFireWaitTime=0.1;
float		clawWpnBulletSpeed=10;

#define		CLAW_MAX_WPN 50
clawWeapon	clawWeaponS[CLAW_MAX_WPN];
float		clawLastFireTime=0; 
swPoint		clawWeaponWP={0,0};

extern int	camID;

//-------------------------------------------------------------------------------------------
clawWeapon* clawWeaponGet(){ 
	for(int i=0;i<CLAW_MAX_WPN;i++){
		if(!clawWeaponS[i].bLive)
			return &clawWeaponS[i];
	}
	return NULL;
}



//-------------------------------------------------------------------------------------------
bool clawWeaponCreateBullet(float x,float y,float rot,float xMult,float yMult){

	float sysTime=swSystemGetElapsedSeconds();
	if(sysTime-clawLastFireTime>clawWpnBulletFireWaitTime){	
		clawWeapon *wpn=clawWeaponGet();
		if(wpn==NULL)
			return false;

		wpn->bLive=true;
		wpn->bDieOperation=false;
		swRectSet(&wpn->target,0,0,10,10);
		swPhysBodyDefSetPos(x,y);
		swPhysBodyDefSetAngle(rot);
		swPhysBodyDefSetRectShapeType(wpn->target.w,wpn->target.h-2);
		swPhysBodyDefSetDensity(1.0f);
		swPhysBodyDefSetFriction(2.0f);
		swPhysBodyDefSetRestitution(0.2);
		swPhysBodyDefSetBullet(true);
		
		wpn->userData.type=XEN_CLAW_WPN_BULLET;
		wpn->userData.obj=wpn;
		swPhysBodyDefSetUserData(&wpn->userData);
		swPhysBodyDefSetFilterGroupIndex(-4);
		swPhysBodyDefSetPosListener(&wpn->target.x,&wpn->target.y);
		swPhysBodyDefSetAngleListener(&wpn->rot);
		wpn->bodyID=swPhysBodyCreate();
		swPhysBodyWakeUp(wpn->bodyID);
		swPhysBodySetLinearVelocity1(wpn->bodyID,xMult*clawWpnBulletSpeed,yMult*clawWpnBulletSpeed);
		clawLastFireTime=sysTime;
		soundPlay(SOUND_OF_CLAW_WEAPON_BULLET_SHOT);
		return true;
	}
	return false;
}

//-------------------------------------------------------------------------------------------
void clawWeaponDisplay(void *obj){ 
	for(int i=0;i<CLAW_MAX_WPN;i++){
		clawWeapon *wpn=&clawWeaponS[i];
		if(wpn->bLive){
			swGraphicsSetBlendingMode(SW_BLENDING_MODE_SOLID);
			swGraphicsRenderImg4(clawActiveWpnImgID,&wpn->target,wpn->rot,&clawWeaponWP);
		}
	}
}

//-------------------------------------------------------------------------------------------
bool isClawWeaponMoveless(clawWeapon *wpn){
	return wpn->prevPos.x==wpn->target.x && wpn->prevPos.y==wpn->target.y && wpn->prevRot==wpn->rot;
}


//-------------------------------------------------------------------------------------------
bool isClawWeaponOutCullRegion(clawWeapon *wpn){
	float x=swGraphicsGetCamPosX(camID);
	float y=swGraphicsGetCamPosY(camID);
	swRect cullRegion;
	swRectSet(&cullRegion,x,y,1024,800);
	return !swIntersectionRectAndRect(&cullRegion,&wpn->target);
}




//-------------------------------------------------------------------------------------------
void clawWeaponExecute(void *obj){ 

	for(int i=0;i<CLAW_MAX_WPN;i++){
		clawWeapon *wpn=&clawWeaponS[i];
		if(wpn->bLive){
			if(isClawWeaponMoveless(wpn) || isClawWeaponOutCullRegion(wpn) || wpn->bDieOperation){
				wpn->bLive=false;
				wpn->bDieOperation=false;
				swPhysBodyDestroy(wpn->bodyID);
			}
		}
	}


	for(int i=0;i<CLAW_MAX_WPN;i++){
		clawWeapon *wpn=&clawWeaponS[i];
		if(wpn->bLive){
			wpn->prevPos.x=wpn->target.x;
			wpn->prevPos.y=wpn->target.y;
			wpn->prevRot=wpn->rot;
		}
	}
}


//-------------------------------------------------------------------------------------------
bool clawWeaponFire(swRect hand,swRect target){ 

	float hX=swRectMidX(&hand);
	float hY=swRectMidY(&hand);
	float tX=swRectMidX(&target);
	float tY=swRectMidY(&target);
	float dist=swMathDistance(hX,hY,tX,tY);
	float angle=swMathDegree(hX,hY,tX,tY);

	if(dist==0)
		return false;

	float xMult=(tX-hX)/dist;
	float yMult=(tY-hY)/dist;
	
	switch(clawActiveWpn){
		case WPN_TYPE_CANNON:
			return clawWeaponCreateBullet(hX,hY,angle,xMult,yMult);
		default:
			return false;
	}
}



//-------------------------------------------------------------------------------------------
void clawWeaponDeInit(){
	swDispManagerDel(clawWpnDispID);
	swExecManagerDel(clawWpnExecID);
}


//-------------------------------------------------------------------------------------------
void clawWeaponInit(){ 
	for(int i=0;i<CLAW_MAX_WPN;i++){
		clawWeapon *wpn=&clawWeaponS[i];
		wpn->bLive=false;
	}

	clawWpnDispID=swDispManagerAdd(clawWeaponDisplay,NULL,NULL,NULL,&clawWpnLayer);
	clawWpnExecID=swExecManagerAdd(clawWeaponExecute,NULL,NULL);
	clawActiveWpnImgID=wpnBullet;


}

