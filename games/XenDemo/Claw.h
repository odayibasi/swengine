#ifndef XEN_CLAW_H
#define XEN_CLAW_H


#include "../../include/SWEngine.h"


typedef struct _clawData{
	int health;
	int shield;
}clawData;

void	clawCreate();
void	clawSetEnabledInteraction(bool clawIntrActive);
swRect *clawGetRect();
swRect *clawGetHRect();
void	clawSetPos(float x, float y);
void	clawSetTargetPos(float x, float y);
void	clawSetHangingOnAir(bool hanging);


#endif
