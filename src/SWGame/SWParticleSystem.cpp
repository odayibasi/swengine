#include "SWGameIn.h"


#define MAX_PARTICLES_IN_PS 500

typedef struct{
	bool          bAlive;
	swVec2		  vel;
	swPointSprite pSprite;
}swParticle;



typedef struct{
	int     id;
	int     pointSpriteID;
	float   pointSize;
	int     particleListID;
	int     nEmission;   //emitting particle count/per second
	int     fLifeTime;   //particle system life time


}swParticleSystem;


int psList=-1;
int psCounter=0;





//-------------------------------------------------------------
DllExport void  swParticleSystemInit(){
	psList=swLinkedListCreate();
}

//-------------------------------------------------------------
DllExport void  swParticleSystemDeInit(){
	psCounter=0;
	swLinkedListDestroy(psList);
}


//-------------------------------------------------------------
swParticleSystem* swParticleSystemGet(int id){
	swParticleSystem *ps=(swParticleSystem*)swLinkedListGetFirst(psList);
	while(ps!=NULL){
		if(ps->id==id)
			return ps;
		ps=(swParticleSystem*)swLinkedListGetNext(psList);
	}
	return NULL;
}


//-------------------------------------------------------------
DllExport void  swParticleSystemDestroy(int psID){
	swParticleSystem *ps=swParticleSystemGet(psID);
	swLinkedListDel(psList,ps);
}


//-------------------------------------------------------------
DllExport int   swParticleSystemCreate0(){
	swParticleSystem *ps=(swParticleSystem *)malloc(sizeof(swParticleSystem));
	ps->id=psCounter++;
	swLinkedListAdd(psList,ps);
	return ps->id;
}

//-------------------------------------------------------------
DllExport void swParticleSystemRender(int psID){
//swColor colors[MAX_PARTICLES_IN_PS];
//swPoint points(MAX_PARTICLES_IN_PS);
//int     renderCount=0;
//	
//  swParticleSystem *ps=swParticleSystemGet(psID);
//  for(int i=0;i<ps->maxParticleCount;i++){
//	swParticle p=ps->particleS[i];
//	if(p->bAlive){
//		swColorCopy(&colors[renderCount])
//		renderCount++;
//	}
//  }	
//
//
//
//  swGraphicsRenderPointSprite(ps->pointSpriteID,ps->pointSize,ps->count,ps->colorS,ps->pointS);
}



//-------------------------------------------------------------
DllExport void swParticleSystemUpdate(){
	swParticleSystem *ps=(swParticleSystem*)swLinkedListGetFirst(psList);
	while(ps!=NULL){
		swParticleSystemUpdateOne(ps);	
		ps=(swParticleSystem*)swLinkedListGetNext(psList);	
	}
}

