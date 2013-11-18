#ifndef PARTICLESYS_H
#define PARTICLESYS_H

#include "Base.h"
#include "ParticleSystemInfo.h"
#include "Particle.h"


#define MAX_PARTICLES	1000

typedef struct _ParticleSystem{

	ParticleSystemInfo  info;

	float				fUpdSpeed;
	float				fResidue;

	float				fAge;
	float				fEmissionResidue;

	Vec2				vecPrevLocation;
	Vec2				vecLocation;
	float				fTx, fTy;

	int					nParticlesAlive;
	swRect				rectBoundingBox;
	BOOL				bUpdateBoundingBox;

	Particle			particles[MAX_PARTICLES];

}ParticleSystem;



void particleSystemFireAt(ParticleSystem *pS,float x, float y);
void particleSystemMoveTo(ParticleSystem *pS,float x, float y, bool bMoveParticle);
void particleSystemStop(ParticleSystem *pS, BOOL bKillParticles);
void particleSystemFire(ParticleSystem *pS);
void particleSystemDisplay(ParticleSystem *pS);
void particleSystemExecute(ParticleSystem *pS);
void particleSystemGenerateNewParticles(ParticleSystem *pS);
void particleSystemUpdateAliveParticle(ParticleSystem *pS);
void particleSystemCheck(ParticleSystem *pS);
void particleSystemSetDefault(ParticleSystem *pS);
BOOL particleSystemIsAlive(ParticleSystem *pS);
void particleSystemIncAge(ParticleSystem *pS);
void particleSystemKillIsLifeEnd(ParticleSystem *pS);

#endif