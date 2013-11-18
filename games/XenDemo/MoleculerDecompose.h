#ifndef XEN_MOLECULER_DECOMPOSE_H
#define XEN_MOLECULER_DECOMPOSE_H


#include "../../include/SWEngine.h"

void moleculerDecomposeInit();
void moleculerDecomposerCreate(float x0,float y0,float x1,float y1,bool *bEnabled);
void moleculerDecomposerAdd(bool *bLive,swRect *target,void (*moleculerDecompose)(void*),void *obj);






#endif