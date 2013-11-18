#ifndef XEN_CLAW_WEAPON_H
#define XEN_CLAW_WEAPON_H

#include "../../include/SWEngine.h"
#include "XenCommon.h"


typedef enum _clawWeaponType{
	CLAW_WEAPON_BULLET,
	CLAW_WEAPON_ACID,
	CLAW_WEAPON_LASER,
	CLAW_WEAPON_LAW,
	CLAW_WEAPON_GUIDED,
	CLAW_WEAPON_GRAVITY,
	CLAW_WEAPON_MISKET,
	CLAW_WEAPON_CRISTAL,
}clawWeaponType;


typedef struct _clawWeapon{
	bool    bLive;
	bool    bDieOperation;
	swRect  target;
	float   rot;
	swPoint prevPos;
	float   prevRot;
	int     bodyID;
	int     imgID;	
	xenUserData userData;
}clawWeapon;




void clawWeaponInit();
void clawWeaponDeInit();
bool clawWeaponFire(swRect hand,swRect target);




#endif