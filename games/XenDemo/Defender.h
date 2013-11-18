#ifndef XEN_DEFENDER_H
#define XEN_DEFENDER_H
#include "../../include/SWEngine.h"
#include "XenCommon.h"

typedef enum _xenDefenderState{
	XEN_DEFENDER_STATE_AVOID,
	XEN_DEFENDER_STATE_FIRE,
	XEN_DEFENDER_STATE_ROTATE,
}xenDefenderState;


typedef struct _xenDefender{
	int					dispID;
	int					execID;
	bool                bLive;
	int					layer;
	int					timerID;
	swRect				target;
	swRect				*source;
	int					animatorID;
	int					spriteID;
	int					avoidAnimatorID;
	int					rotateAnimatorID;
	int					fireAnimatorID;
	xenDefenderState	state;
	int                 bodyID;
	xenUserData			userData;
	float				lastFireTime;
	int					hitCount;
}xenDefender;


xenDefender*	defenderCreate();
void			defenderSetPos(xenDefender *defender,float x, float y);
void			defenderSetTarget(swRect *target);



#endif