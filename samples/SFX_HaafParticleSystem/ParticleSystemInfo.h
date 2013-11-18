#ifndef PARTICLEINFO_H
#define PARTICLEINFO_H

#include "Base.h"



typedef struct _ParticleSystemInfo{
	int    	    sprite;    // texture + blend mode
	int			nEmission; // particles per sec
	float		fLifetime;

	float		fParticleLifeMin;
	float		fParticleLifeMax;

	float		fDirection;
	float		fSpread;
	BOOL		bRelative;

	float		fSpeedMin;
	float		fSpeedMax;

	float		fGravityMin;
	float		fGravityMax;

	float		fRadialAccelMin;
	float		fRadialAccelMax;

	float		fTangentialAccelMin;
	float		fTangentialAccelMax;

	float		fSizeStart;
	float		fSizeEnd;
	float		fSizeVar;

	float		fSpinStart;
	float		fSpinEnd;
	float		fSpinVar;

	swColor		colColorStart; // + alpha
	swColor		colColorEnd;
	float		fColorVar;
	float		fAlphaVar;
}ParticleSystemInfo;


#endif