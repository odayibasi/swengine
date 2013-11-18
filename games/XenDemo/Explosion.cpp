#include "Explosion.h"
#include "Sound.h"

int			 explosionLayer=5;
#define		 EXPLOSION_MAX 5
xenExplosion explosionS[EXPLOSION_MAX];
int          explosionListenerList=-1;
int          explosionDispID=-1;
int          explosionExecID=-1;


typedef struct _ExpListener{
	void(*notify)(swExplosionEffect *);
}ExpListener;


//-------------------------------------------------------------------------------------------
xenExplosion* explosionGet(){ 
	for(int i=0;i<EXPLOSION_MAX;i++){
		if(!explosionS[i].bLive)
			return &explosionS[i];
	}
	return NULL;
}



//-------------------------------------------------------------------------------------------
void explosionDisplay(void *obj){ 
	for(int i=0;i<EXPLOSION_MAX;i++){
		xenExplosion *expl=&explosionS[i];
		if(expl->bLive){
			swGraphicsSetBlendingMode(SW_BLENDING_MODE_SOLID);
			swGraphicsSetColor1(expl->color);
			int index=swAnimatorGetIndex(expl->animID);
			swGraphicsRenderSprite0(expl->spriteID,index,&expl->target);
		}
	}
}


//-------------------------------------------------------------------------------------------
void explosionExecute(void *obj){ 
	for(int i=0;i<EXPLOSION_MAX;i++){
		xenExplosion *expl=&explosionS[i];
		if(expl->bLive){
			if(swAnimatorIsLastFrameActive(expl->animID)){
				expl->bLive=false;
			}
		
		}
	}
}

//-------------------------------------------------------------------------------------------
void explosionDeInit(void *obj){ 
	swDispManagerDel(explosionDispID);
	swExecManagerDel(explosionExecID);
	swLinkedListClear(explosionListenerList);
	swLinkedListDestroy(explosionListenerList);
}




//-------------------------------------------------------------------------------------------
void explosionInit(){ 
	for(int i=0;i<EXPLOSION_MAX;i++){
		xenExplosion *expl=&explosionS[i];
		expl->bLive=false;
	}

	explosionDispID=swDispManagerAdd(explosionDisplay,NULL,NULL,NULL,&explosionLayer);
	explosionExecID=swExecManagerAdd(explosionExecute,NULL,NULL);
	explosionListenerList=swLinkedListCreate();
	//swDestroyManagerAdd(explosionDeInit,NULL);
}

//-------------------------------------------------------------------------------------------
void explosionListenerAdd(void (*explosionListener)(swExplosionEffect *)){
	 ExpListener* listener=(ExpListener*)malloc(sizeof(ExpListener));
	 listener->notify=explosionListener;
	 swLinkedListAdd(explosionListenerList,listener);
}



//-------------------------------------------------------------------------------------------
void explosionListen(swExplosionEffect *e){ 
	void(*notify)(swExplosionEffect *);
	if(e->userData!=NULL){
	    ExpListener* listener=(ExpListener*)swLinkedListGetFirst(explosionListenerList);
		while(listener!=NULL){
			notify=listener->notify;
			listener=(ExpListener*)swLinkedListGetNext(explosionListenerList);
			(*notify)(e);
		}
	}
}




//-------------------------------------------------------------------------------------------
xenExplosion* explosionCreate(int spriteID,swRect target,float rot, swColor *color){ 
	xenExplosion *expl=explosionGet();
	if(expl==NULL)
		return NULL;

	expl->color=color;
	expl->bLive=true;
	expl->spriteID=spriteID;
	swRectSet(&expl->target,target.x,target.y,150,150);
	expl->animID=swAnimatorCreate(swGraphicsGetCountOfImgInSprite(spriteID),0.02);
	swAnimatorSetExecutionMode(expl->animID,SW_ANIMATOR_EXEC_FORWARD);

	swVec2 pos;
	swVec2Set(&pos,swRectMidX(&target),target.y);
	swPhysModelExplosion(pos,150,0.4,explosionListen);
	
	soundPlay(SOUND_OF_BARREL_EXPLODE);
	return expl;
}


