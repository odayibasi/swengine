#ifndef XEN_ENEMY_WEAPON_H
#define XEN_ENEMY_WEAPON_H
#include "../../include/SWEngine.h"
#include "XenCommon.h"


typedef struct _enemyWeapon{
	bool    bLive;
	bool    bDieOperation;
	swRect  target;
	float   rot;
	swPoint prevPos;
	float   prevRot;
	int     bodyID;
	int     imgID;	
	xenUserData userData;
}enemyWeapon;


void enemyWeaponInit();
void enemyWeaponDeInit();
void enemyWeaponFire(float sX,float sY,float tX,float tY);


#endif