#ifndef PARTICLESYSMANAGER_H
#define PARTICLESYSMANAGER_H

#include "Base.h"
#include "ParticleSystem.h"


ParticleSystem* particleSystemManagerCreate();
void particleSystemManagerExecute();
void particleSystemManagerDisplay();
void particleSystemManagerInit();

#endif