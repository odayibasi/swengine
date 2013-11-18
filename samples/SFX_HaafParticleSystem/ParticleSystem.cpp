#include "Base.h"
#include "ParticleSystem.h"
#include <math.h>

#define REFRESH_TIME 0.0166

//------------------------------------------------------------
void particleSystemSetDefault(ParticleSystem *pS){
	vec2Set(&pS->vecLocation,0.0f,0.0f);
	vec2Set(&pS->vecPrevLocation,0.0f,0.0f);
	pS->fTx=pS->fTy=0;
	pS->fEmissionResidue=0;
	pS->nParticlesAlive=0;
	pS->fAge=0;
	pS->fUpdSpeed=REFRESH_TIME;
	pS->fResidue=0;
}

//------------------------------------------------------------
void particleSystemCheck(ParticleSystem *pS){
	int i;
	Particle *p;

	//Check Particle Age
	p=pS->particles;
	for(i=0;i<pS->nParticlesAlive;i++){
		p->fAge +=REFRESH_TIME;
		if(p->fAge >= p->fTerminalAge){
			pS->nParticlesAlive--;
			memcpy(p, &pS->particles[pS->nParticlesAlive], sizeof(Particle));
			i--;
			continue;
		}
		p++;
	}
}


//------------------------------------------------------------
void particleSystemUpdateAliveParticle(ParticleSystem *pS){
	int i;
	Particle *p;
	Vec2 vecAccel, vecAccel2;
	float ang;
	float deltaTime=REFRESH_TIME;

	p=pS->particles;
	for(i=0;i<pS->nParticlesAlive;i++){

		vecAccel.index[0] = p->vecLocation.index[0]-pS->vecLocation.index[0];
		vecAccel.index[1] = p->vecLocation.index[1]-pS->vecLocation.index[1];
		vec2Normalize(&vecAccel,&vecAccel);
		vec2Copy(&vecAccel2,&vecAccel);		
		vec2Mult(&vecAccel,&vecAccel,p->fRadialAccel);

		ang=vecAccel2.index[0];
		vecAccel2.index[0]=-vecAccel2.index[1];
		vecAccel2.index[1]=ang;

		vec2Mult(&vecAccel2,&vecAccel2,p->fTangentialAccel);
		p->vecVelocity.index[0]+=(vecAccel.index[0]+vecAccel2.index[0])*deltaTime;
		p->vecVelocity.index[1]+=(vecAccel.index[1]+vecAccel2.index[1])*deltaTime;
		p->vecVelocity.index[1]+=p->fGravity*deltaTime;

		vec2Add(&p->vecLocation,&p->vecLocation,&p->vecVelocity);
		p->fSpin+=p->fSpinDelta*deltaTime;


		p->fSpin += p->fSpinDelta*deltaTime;
		p->fSize += p->fSizeDelta*deltaTime;

		p->colColor.r += p->colColorDelta.r*deltaTime;
		p->colColor.g += p->colColorDelta.g*deltaTime;
		p->colColor.b += p->colColorDelta.b*deltaTime;
		p->colColor.a += p->colColorDelta.a*deltaTime;
		p++;

	}
}


//------------------------------------------------------------
void particleSystemGenerateNewParticles(ParticleSystem *pS){
	float fParticlesNeeded;
	float deltaTime;
	int nParticlesCreated;
	ParticleSystemInfo info;
	Particle *par;
	int i;
	float random;
	float ang;


	deltaTime=REFRESH_TIME;
	info=pS->info;
	fParticlesNeeded = info.nEmission*deltaTime + pS->fEmissionResidue;
	nParticlesCreated = (unsigned int)fParticlesNeeded;
	pS->fEmissionResidue=fParticlesNeeded-nParticlesCreated;
	par=&pS->particles[pS->nParticlesAlive];

	for(i=0; i<nParticlesCreated; i++)
	{
		if(pS->nParticlesAlive>=MAX_PARTICLES) break;

		par->fAge = 0.0f;
		par->fTerminalAge = swMathRandomFloat(info.fParticleLifeMin, info.fParticleLifeMax);



		random=swMathRandomFloat(0.0f, 1.0f);
		par->vecLocation.index[0] = pS->vecPrevLocation.index[0]+(pS->vecLocation.index[0]-pS->vecPrevLocation.index[0])*random;
		par->vecLocation.index[1] = pS->vecPrevLocation.index[1]+(pS->vecLocation.index[1]-pS->vecPrevLocation.index[1])*random;

		par->vecLocation.index[0] += swMathRandomFloat(-2.0f, 2.0f);
		par->vecLocation.index[1] += swMathRandomFloat(-2.0f, 2.0f);

		ang=info.fDirection-SW_MATH_PI/2+swMathRandomFloat(0,info.fSpread)-info.fSpread/2.0f;
		if(info.bRelative) ang +=swMathDegree(pS->vecPrevLocation.index[0],pS->vecPrevLocation.index[1],pS->vecLocation.index[0],pS->vecLocation.index[1])+SW_MATH_PI/2;
		par->vecVelocity.index[0] = cosf(ang); 
		par->vecVelocity.index[1] = sinf(ang);
		vec2Mult(&par->vecVelocity,&par->vecVelocity,swMathRandomFloat(info.fSpeedMin, info.fSpeedMax));

		par->fGravity = swMathRandomFloat(info.fGravityMin, info.fGravityMax);
		par->fRadialAccel = swMathRandomFloat(info.fRadialAccelMin, info.fRadialAccelMax);
		par->fTangentialAccel = swMathRandomFloat(info.fTangentialAccelMin, info.fTangentialAccelMax);

		par->fSize = swMathRandomFloat(info.fSizeStart, info.fSizeStart+(info.fSizeEnd-info.fSizeStart)*info.fSizeVar);
		par->fSizeDelta = (info.fSizeEnd-par->fSize) / par->fTerminalAge;

		par->fSpin = swMathRandomFloat(info.fSpinStart, info.fSpinStart+(info.fSpinEnd-info.fSpinStart)*info.fSpinVar);
		par->fSpinDelta = (info.fSpinEnd-par->fSpin) / par->fTerminalAge;

		par->colColor.r = swMathRandomFloat(info.colColorStart.r, info.colColorStart.r+(info.colColorEnd.r-info.colColorStart.r)*info.fColorVar);
		par->colColor.g = swMathRandomFloat(info.colColorStart.g, info.colColorStart.g+(info.colColorEnd.g-info.colColorStart.g)*info.fColorVar);
		par->colColor.b = swMathRandomFloat(info.colColorStart.b, info.colColorStart.b+(info.colColorEnd.b-info.colColorStart.b)*info.fColorVar);
		par->colColor.a = swMathRandomFloat(info.colColorStart.a, info.colColorStart.a+(info.colColorEnd.a-info.colColorStart.a)*info.fAlphaVar);

		par->colColorDelta.r = (info.colColorEnd.r-par->colColor.r) / par->fTerminalAge;
		par->colColorDelta.g = (info.colColorEnd.g-par->colColor.g) / par->fTerminalAge;
		par->colColorDelta.b = (info.colColorEnd.b-par->colColor.b) / par->fTerminalAge;
		par->colColorDelta.a = (info.colColorEnd.a-par->colColor.a) / par->fTerminalAge;

		pS->nParticlesAlive++;
		par++;
	}
}


//------------------------------------------------------------
void particleSystemExecute(ParticleSystem *pS){

	particleSystemCheck(pS);
	particleSystemUpdateAliveParticle(pS);
	vec2Copy(&pS->vecPrevLocation,&pS->vecLocation);

}


//------------------------------------------------------------
void particleSystemDisplay(ParticleSystem *pS){
	int i;
	Particle *par=pS->particles;
	swRect target;
	float rot;

	swGraphicsSetBlendingMode(SW_BLENDING_MODE_ADDITIVE_ACCORDING2_ALPHA);
	for(i=0; i<pS->nParticlesAlive; i++)
	{
			swRectSet(&target,par->vecLocation.index[0]+pS->fTx,par->vecLocation.index[1]+pS->fTy,par->fSize,par->fSize);
		rot=par->fSpin*par->fAge;


		swGraphicsSetColor1(&par->colColor);
		swGraphicsRenderImg1(pS->info.sprite,&target,rot);
		par++;
	}



}

//------------------------------------------------------------
void particleSystemFire(ParticleSystem *pS){
	pS->fAge=0.0f;
}

//------------------------------------------------------------
void particleSystemStop(ParticleSystem *pS, BOOL bKillParticles){
	pS->fAge=-2.0f;
	if(bKillParticles){
		pS->nParticlesAlive=0;
	}
}


//------------------------------------------------------------
void particleSystemMoveTo(ParticleSystem *pS,float x, float y, BOOL bMoveParticle){

	int i;
	float dx,dy;

	if(bMoveParticle)
	{
		dx=x-pS->vecLocation.index[0];
		dy=y-pS->vecLocation.index[1];

		for(i=0;i<pS->nParticlesAlive;i++)
		{
			pS->particles[i].vecLocation.index[0] += dx;
			pS->particles[i].vecLocation.index[1] += dy;
		}

		pS->vecPrevLocation.index[0]=pS->vecPrevLocation.index[0] + dx;
		pS->vecPrevLocation.index[1]=pS->vecPrevLocation.index[1] + dy;
	}
	else
	{

		pS->vecPrevLocation.index[0]=pS->vecLocation.index[0];
		pS->vecPrevLocation.index[1]=pS->vecLocation.index[1];
	}

	pS->vecLocation.index[0]=x;
	pS->vecLocation.index[1]=y;

}


//------------------------------------------------------------
void particleSystemFireAt(ParticleSystem *pS,float x, float y){
	particleSystemStop(pS,TRUE); 
	particleSystemMoveTo(pS,x,y,TRUE);
	particleSystemFire(pS);
}

//------------------------------------------------------------
BOOL particleSystemIsAlive(ParticleSystem *pS){
	return pS->fAge>=0;
}


//------------------------------------------------------------
void particleSystemIncAge(ParticleSystem *pS){
	pS->fAge+=REFRESH_TIME;
}


//------------------------------------------------------------
void particleSystemKillIsLifeEnd(ParticleSystem *pS){
	if(pS->info.fLifetime==-1){ //continues
		return;
	}

	if(pS->fAge>=pS->info.fLifetime){ 
		particleSystemStop(pS,FALSE);
	}
}


