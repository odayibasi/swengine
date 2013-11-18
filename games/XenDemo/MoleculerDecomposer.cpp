#include "MoleculerDecompose.h"



typedef struct xenMoleculerDecomposer{
	swPoint pointA;
	swPoint pointB;
	bool    *bEnabled;
};

typedef struct xenMoleculerDecomposerTarget{
	bool* bLive;
    swRect *rect;
	void *obj;
	void (*moleculerDecompose)(void*);
};



int mDecomposerList=-1;
int mDecomposerTargetList=-1;
int mDecomposerLayer=8;



//-------------------------------------------------------------------------------------------
void moleculerDecomposeExecute(void *obj){
	xenMoleculerDecomposer* c=(xenMoleculerDecomposer*)swLinkedListGetFirst(mDecomposerList);
	while(c!=NULL){
		swPoint a=c->pointA;
		swPoint b=c->pointB;
		bool bEnable=*c->bEnabled;
		c=(xenMoleculerDecomposer*)swLinkedListGetNext(mDecomposerList);
		if(bEnable){
			xenMoleculerDecomposerTarget* t=(xenMoleculerDecomposerTarget*)swLinkedListGetFirst(mDecomposerTargetList);
			while(t!=NULL){
				if(*t->bLive && swIntersectionRectAndLine(t->rect,&a,&b)){
					(*t->moleculerDecompose)(t->obj);
				}
				t=(xenMoleculerDecomposerTarget*)swLinkedListGetNext(mDecomposerTargetList);
			}//end of while
		}//end of if
	}//end of while
}



//-------------------------------------------------------------------------------------------
void moleculerDecomposeDisplay(void *obj){

	swGraphicsSetBlendingMode(SW_BLENDING_MODE_NONE);
	swGraphicsSetColor1(&SWCOLOR_RED);
	xenMoleculerDecomposer* c=(xenMoleculerDecomposer*)swLinkedListGetFirst(mDecomposerList);
	while(c!=NULL){
		swPoint a=c->pointA;
		swPoint b=c->pointB;
		bool bEnable=*c->bEnabled;
		if(bEnable){
			swGraphicsRenderLine1(&a,&b,3);
		}//end of if
		c=(xenMoleculerDecomposer*)swLinkedListGetNext(mDecomposerList);
	}//end of while

	xenMoleculerDecomposerTarget* t=(xenMoleculerDecomposerTarget*)swLinkedListGetFirst(mDecomposerTargetList);
	while(t!=NULL){
		if(t->bLive){
			swGraphicsRenderLineRect2(t->rect,3);
		}
		t=(xenMoleculerDecomposerTarget*)swLinkedListGetNext(mDecomposerTargetList);
	}//end of while
}



//-------------------------------------------------------------------------------------------
void moleculerDecomposeInit(){
	mDecomposerList=swLinkedListCreate();
	mDecomposerTargetList=swLinkedListCreate();
	swExecManagerAdd(moleculerDecomposeExecute,NULL,NULL);
}



//-------------------------------------------------------------------------------------------
void moleculerDecomposerCreate(float x0,float y0,float x1,float y1,bool *bEnabled){
	xenMoleculerDecomposer* c=(xenMoleculerDecomposer*)malloc(sizeof(xenMoleculerDecomposer));
	c->bEnabled=bEnabled;
	c->pointA.x=x0;
	c->pointA.y=y0;
	c->pointB.x=x1;
	c->pointB.y=y1;
	swLinkedListAdd(mDecomposerList,c);
}


//-------------------------------------------------------------------------------------------
void moleculerDecomposerAdd(bool *bLive,swRect *target,void (*moleculerDecompose)(void*),void *obj){
	xenMoleculerDecomposerTarget * t=(xenMoleculerDecomposerTarget*)malloc(sizeof(xenMoleculerDecomposerTarget));
	t->bLive=bLive;
	t->rect=target;
	t->moleculerDecompose=moleculerDecompose;
	t->obj=obj;
	swLinkedListAdd(mDecomposerTargetList,t);
}