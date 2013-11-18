#ifndef PARTICLE_H
#define PARTICLE_H

#include "Vec2.h"
#include "Base.h"


typedef struct _Particle{
	Vec2	vecLocation;
	Vec2	vecVelocity;

	float	fGravity;
	float	fRadialAccel;
	float	fTangentialAccel;

	float	fSpin;
	float	fSpinDelta;

	float	fSize;
	float	fSizeDelta;

	swColor	colColor;		// + alpha
	swColor colColorDelta;

	float	fAge;
	float	fTerminalAge;
}Particle;



#endif