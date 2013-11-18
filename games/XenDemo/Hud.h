#ifndef XEN_HUD_H
#define XEN_HUD_H

#include "../../include/SWEngine.h"

//InClaw GUI
typedef enum _eWpnType{
	WPN_TYPE_NONE,
	WPN_TYPE_CANNON,
	WPN_TYPE_LASER,
	WPN_TYPE_LAW,
}eWpnType;

typedef enum _eBombType{
	BOMB_TYPE_NONE,
	BOMB_TYPE_GUIDEDMISSILE,
	BOMB_TYPE_SHARAPNEL,
	BOMB_TYPE_HAMMER,
}eBombType;

typedef enum _eCockpitMode{
	COCKPIT_TYPE_NORMAL,
	COCKPIT_TYPE_COLLISION,
	COCKPIT_TYPE_EXPLOSION,
}eCockpitMode;

void hudCreate();
void hudDisplay(void *obj);
void hudSetEnabled(bool bActive);
void hudSetTransparent(bool bEnabled);
void hudEnd();
void hudSetWeaponType(eWpnType WpnType);
void hudSetBombType(eBombType BombType);
void hudAddScore(int Score);
void hudSetBombCount(eBombType bombType,int count);
void hudSetWeaponCount(eWpnType wpnType,int count);
void hudXenCockpitMode(eCockpitMode cockpitType);
void hudSetShield(int Shield);
void hudSetHealth(int Health);


#endif