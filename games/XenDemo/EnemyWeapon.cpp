#include "EnemyWeapon.h"
#include <float.h>



//Weapon
#define ENEMY_MAX_WPN 100


extern int	wpnEBullet;
int			enemyWpnLayer=5;
int			enemyWpnDispID=-1;
int         enemyWpnExecID=-1;


enemyWeapon enemyWeaponS[ENEMY_MAX_WPN];
swPoint     enemyWeaponWP={0,0};
float       enemyWpnBulletSpeed=10;

extern int	camID;




//-------------------------------------------------------------------------------------------
enemyWeapon* enemyWeaponGet(){ 
	for(int i=0;i<ENEMY_MAX_WPN;i++){
		if(!enemyWeaponS[i].bLive)
			return &enemyWeaponS[i];
	}
	return NULL;
}



//-------------------------------------------------------------------------------------------
void enemyWeaponCreateBullet(float x,float y,float rot,float xMult,float yMult){

		enemyWeapon *wpn=enemyWeaponGet();
		if(wpn==NULL)
			return;


		wpn->bLive=true;
		wpn->bDieOperation=false;
		swRectSet(&wpn->target,x,y,20,10);
		swPhysBodyDefSetPos(x,y);
		swPhysBodyDefSetAngle(rot);
		swPhysBodyDefSetRectShapeType(wpn->target.w,wpn->target.h-2);
		swPhysBodyDefSetDensity(1.0f);
		swPhysBodyDefSetFriction(2.0f);
		swPhysBodyDefSetRestitution(0.2);
		swPhysBodyDefSetBullet(true);		
		wpn->userData.type=XEN_ENEMY_WPN_BULLET;
		wpn->userData.obj=wpn;
		swPhysBodyDefSetUserData(&wpn->userData);
		swPhysBodyDefSetFilterGroupIndex(-5);
		swPhysBodyDefSetPosListener(&wpn->target.x,&wpn->target.y);
		swPhysBodyDefSetAngleListener(&wpn->rot);
		wpn->bodyID=swPhysBodyCreate();
		swPhysBodyWakeUp(wpn->bodyID);
		swPhysBodySetLinearVelocity1(wpn->bodyID,xMult*enemyWpnBulletSpeed,yMult*enemyWpnBulletSpeed);

		wpn->prevPos.x=FLT_MIN;
		wpn->prevPos.y=FLT_MIN;
		wpn->rot=FLT_MIN;


}

//-------------------------------------------------------------------------------------------
void enemyWeaponDisplay(void *obj){ 
	for(int i=0;i<ENEMY_MAX_WPN;i++){
		enemyWeapon *wpn=&enemyWeaponS[i];
		if(wpn->bLive){
			swGraphicsSetBlendingMode(SW_BLENDING_MODE_ADDITIVE);
			swGraphicsSetColor0(1,0.8,0.8,0.4);
			swGraphicsRenderImg4(wpnEBullet,&wpn->target,wpn->rot,&enemyWeaponWP);
		}
	}
}

//-------------------------------------------------------------------------------------------
bool isEnemyWeaponMoveless(enemyWeapon *wpn){
	return wpn->prevPos.x==wpn->target.x && wpn->prevPos.y==wpn->target.y && wpn->prevRot==wpn->rot;
}


//-------------------------------------------------------------------------------------------
bool isEnemyWeaponOutCullRegion(enemyWeapon *wpn){
	float x=swGraphicsGetCamPosX(camID);
	float y=swGraphicsGetCamPosY(camID);
	swRect cullRegion;
	swRectSet(&cullRegion,x,y,1024,800);
	return !swIntersectionRectAndRect(&cullRegion,&wpn->target);
}




//-------------------------------------------------------------------------------------------
void enemyWeaponExecute(void *obj){ 

	for(int i=0;i<ENEMY_MAX_WPN;i++){
		enemyWeapon *wpn=&enemyWeaponS[i];
		if(wpn->bLive){
			if(isEnemyWeaponMoveless(wpn) || isEnemyWeaponOutCullRegion(wpn) || wpn->bDieOperation){
				wpn->bLive=false;
				wpn->bDieOperation=false;
				swPhysBodyDestroy(wpn->bodyID);
			}
		}
	}


	for(int i=0;i<ENEMY_MAX_WPN;i++){
		enemyWeapon *wpn=&enemyWeaponS[i];
		if(wpn->bLive){
			wpn->prevPos.x=wpn->target.x;
			wpn->prevPos.y=wpn->target.y;
			wpn->prevRot=wpn->rot;
		}
	}
}



//-------------------------------------------------------------------------------------------
void enemyWeaponDeInit(){
	swDispManagerDel(enemyWpnDispID);
	swExecManagerDel(enemyWpnExecID);
}

//-------------------------------------------------------------------------------------------
void enemyWeaponInit(){ 
	for(int i=0;i<ENEMY_MAX_WPN;i++){
		enemyWeapon *wpn=&enemyWeaponS[i];
		wpn->bLive=false;
	}

	enemyWpnDispID=swDispManagerAdd(enemyWeaponDisplay,NULL,NULL,NULL,&enemyWpnLayer);
	enemyWpnExecID=swExecManagerAdd(enemyWeaponExecute,NULL,NULL);
}



//-------------------------------------------------------------------------------------------
void enemyWeaponFire(float sX,float sY,float tX,float tY){ 

	float dist=swMathDistance(sX,sY,tX,tY);
	float angle=swMathDegree(sX,sY,tX,tY);

	if(dist==0)
		return;

	float xMult=(tX-sX)/dist;
	float yMult=(tY-sY)/dist;
	enemyWeaponCreateBullet(sX,sY,angle,xMult,yMult);
}
