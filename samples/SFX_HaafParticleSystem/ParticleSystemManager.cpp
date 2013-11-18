#include "ParticleSystemManager.h"	
#include <assert.h>

#define MAX_PARTICLESYSTEM 100

ParticleSystem   particleSystemS[MAX_PARTICLESYSTEM];

//-----------------------------------------------------------------
void particleSystemManagerInit(){
	for(int i=0;i<MAX_PARTICLESYSTEM;i++){
		ParticleSystem *pS=&particleSystemS[i];
		pS->fAge=-2;
	}
}




//-----------------------------------------------------------------
ParticleSystem* particleSystemManagerCreate(){
	int i;	
	for(i=0;i<MAX_PARTICLESYSTEM;i++){
		if(particleSystemS[i].fAge==-2)
			particleSystemSetDefault(&particleSystemS[i]);
		return particleSystemS;
	}
	assert (TRUE);
}



//-----------------------------------------------------------------
void particleSystemManagerExecute(){	
	int i;	
	ParticleSystem *pS;	

	for(i=0;i<MAX_PARTICLESYSTEM;i++){
		pS=&particleSystemS[i];
		if(particleSystemIsAlive(pS)){
			particleSystemIncAge(pS);
			particleSystemGenerateNewParticles(pS);
			particleSystemKillIsLifeEnd(pS);
		}
		particleSystemExecute(pS);
	}
}

//-----------------------------------------------------------------
void particleSystemManagerDisplay(){	
	int i;	
	ParticleSystem *pS;	
	for(i=0;i<MAX_PARTICLESYSTEM;i++){
		pS=&particleSystemS[i];
		particleSystemDisplay(pS);
	}
}

