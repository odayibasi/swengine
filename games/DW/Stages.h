#ifndef DW_STAGES_H
#define DW_STAGES_H

#include <math.h>
#include "../../include/SWEngine.h"

typedef struct Actor{
	int			animIndex;
	swRect      target;
	float       rot;
	int         bindedPlatformID;
};

typedef struct Platform{
	int			animID;
	swRect		target;
	int			color;
}Platform;


void stageMainGuiInit();
void stageMainGuiExecute();
void stageMainGuiDeInit();

void stageLightInit();
void stageLightExecute();
void stageLightDeInit();

void stageTransitionLightToCrossingInit();
void stageTransitionLightToCrossingExecute();
void stageTransitionLightToCrossingDeInit();
void stageTransitionCrossingLayoutCentered();

void stageCrossingInit();
void stageCrossingExecute();
void stageCrossingDeInit();

void stageEndOfSceneInit();
void stageEndOfSceneExecute();
void stageEndOfSceneDeInit();

void bindActorToPlatform(Actor* act, Platform* plt);




#endif
