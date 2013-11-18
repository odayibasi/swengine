#ifndef XEN_TURRET_H
#define XEN_TURRET_H

#include "../../include/SWEngine.h"
#include "XenCommon.h"

typedef struct _xenTurret{
	bool        bLive;
	int			bodyID;
	int         dispID;
	int         execID;
	int			layer;
	int         animID;
	bool		bEnabled;
	bool		hasShadow;
	swRect		target;
	float		rot;
	int         hitCount;
	xenUserData userData;
	int         lastAnimIndex;
}xenTurret;


xenTurret*	turretCreate(int layer, float x, float y);


#endif
