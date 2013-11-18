#ifndef XEN_EXPLOSION_H
#define XEN_EXPLOSION_H


#include "../../include/SWEngine.h"
#include "XenCommon.h"

typedef struct _xenExplosion{
	int         spriteID;
	int         animID;
	swRect		target;
	bool        bLive;
	swColor*	color;
}xenExplosion;

void			explosionInit();
xenExplosion*	explosionCreate(int spriteID,swRect target,float rot, swColor *color);
void			explosionListenerAdd(void (*explosionListener)(swExplosionEffect *));


#endif