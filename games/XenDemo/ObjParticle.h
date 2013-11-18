#ifndef XEN_OBJPARTICLE_H
#define XEN_OBJPARTICLE_H

#include "../../include/SWEngine.h"


void objParticleInit();
void objParticleGenerate(swRect *target,int wSlice,int hSlice,int imgID,int index,float rot,float posSpeed,float scaleSpeed,float rotSpeed);


#endif