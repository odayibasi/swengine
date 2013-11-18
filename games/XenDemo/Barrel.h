#ifndef XEN_BARREL_H
#define XEN_BARREL_H


#include "../../include/SWEngine.h"
#include "XenCommon.h"

typedef struct _xenBarrel{
	int			bodyID;
	int         dispID;
	int         execID;
	int			layer;
	bool		bEnabled;
	bool		hasShadow;
	swRect		target;
	float		rot;
	bool        slowMotion;
	int         hitCount;
	xenUserData userData;
}xenBarrel;


xenBarrel*	barrelCreate(int layer, float x, float y,bool slowMotion);


#endif