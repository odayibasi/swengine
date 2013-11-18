#include "../../include/SWEngine.h"

extern      int elevatorPartID;
extern		int elevatorID;

typedef struct _Elevator{
	int dispID;
	int execID;
    int vModifierID;
	swPoint pos;
	swRect  movPart;
	bool  bWait;
	float lastTimeOfWait;
	int   layer;
}Elevator;


//-------------------------------------------------------------------------------------------
void elevatorDisplay(void *obj){
	swRect target;
	Elevator *e=(Elevator*)obj;
	swGraphicsSetBlendingMode(SW_BLENDING_MODE_SOLID);
	swGraphicsSetColor1(&SWCOLOR_WHITE);
	for(int i=0;i<50;i++){
		swRectSet(&target,e->pos.x,e->pos.y+i*15,20,20);
		swGraphicsRenderImg0(elevatorPartID,&target);
	}
	swGraphicsRenderImg0(elevatorID,&e->movPart);
}


//-------------------------------------------------------------------------------------------
void elevatorExecute(void *obj){
	Elevator *e=(Elevator*)obj;
	if(!e->bWait){
		swValueModifierExecute(e->vModifierID,0.016f);
	}

	float systemTime=swSystemGetElapsedSeconds();
	if(e->bWait && systemTime-e->lastTimeOfWait>1.0){
		e->bWait=false;
		e->lastTimeOfWait=systemTime;
	}


	if(!e->bWait && systemTime-e->lastTimeOfWait>2.0 && (e->pos.y>=425 || e->pos.y<=-10)){
		e->bWait=true;
		e->lastTimeOfWait=systemTime;
	}
}


//-------------------------------------------------------------------------------------------
void elevatorDestroy(void *obj){
	Elevator *e=(Elevator*)obj;
	swDispManagerDel(e->dispID);
	swExecManagerDel(e->execID);
	swValueModifierDestroy(e->vModifierID);
	free(e);
}


//-------------------------------------------------------------------------------------------
void elevatorCreate(float x,float y){
	Elevator *e=(Elevator*)malloc(sizeof(Elevator));
	e->pos.x=x;
	e->pos.y=y;
	e->movPart.x=x-45;
	e->movPart.y=470;
	e->movPart.w=74;
	e->movPart.h=134;
	e->layer=1;
	
	e->vModifierID=swValueModifierCreate(SW_VALUE_MODIFIER_010_LOOP,&e->movPart.y,-10,425,50,0);			   
	e->execID=swExecManagerAdd(elevatorExecute,e,NULL);
	e->dispID=swDispManagerAdd(elevatorDisplay,e,NULL,NULL,&e->layer);
	swDestroyManagerAdd(elevatorDestroy,e);
}




