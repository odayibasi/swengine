#include "NeonItems.h"


int neonItemLayer=2;

//-------------------------------------------------------------------------------------------
void neonItemDisplay(void *obj){
	neonItem* item=(neonItem*)obj; 
	swGraphicsSetBlendingMode(SW_BLENDING_MODE_ADDITIVE);
	swGraphicsSetColor1(&item->color);
	swGraphicsRenderImg0(item->imgID,&item->target);
}


//-------------------------------------------------------------------------------------------
void neonItemExecute(void *obj){
	neonItem* item=(neonItem*)obj; 
	float sysTime=swSystemGetElapsedSeconds();
	if (sysTime-item->lastTime>item->sleepTime){
		item->bEnabled=!item->bEnabled;
		item->lastTime=sysTime;
	}
}


//-------------------------------------------------------------------------------------------
void neonItemRegisterExecution(void *obj){
	neonItem* item=(neonItem*)obj; 
	item->execID=swExecManagerAdd(neonItemExecute,obj,NULL);
}



//-------------------------------------------------------------------------------------------
void neonItemDestroy(void *obj){
	neonItem* item=(neonItem*)obj; 
	if(item->execID!=-1) swExecManagerDel(item->execID);
	swDispManagerDel(item->dispID);
	free(item);
}


//-------------------------------------------------------------------------------------------
neonItem* neonItemCreate(int imgID,float x,float y,float w,float h){
	neonItem* item=(neonItem*)malloc(sizeof(neonItem)); 
	item->imgID=imgID;
	swRectSet(&item->target,x,y,w,h);
	swColorSet(&item->color,1,1,1,0.4);
	item->bEnabled=true;
	item->execID=-1;
	item->dispID=swDispManagerAdd(neonItemDisplay,item,&item->bEnabled,&item->target,&neonItemLayer);
	swDestroyManagerAdd(neonItemDestroy,item);
	return item;
}


//-------------------------------------------------------------------------------------------
neonItem* neonItemCreate1(int imgID,float x,float y,float w,float h,float startTime,float sleepTime){
	neonItem* item=neonItemCreate(imgID,x,y,w,h);
	item->lastTime=startTime;
	item->sleepTime=sleepTime;
	swScheduledManagerAdd0(neonItemRegisterExecution,item,startTime);
	return item;
}

//-------------------------------------------------------------------------------------------
neonItem* neonItemCreate2(int imgID,
								float x,float y,float w,float h,
								float r,float g,float b,float a,
								float startTime,float sleepTime){
	neonItem* item=neonItemCreate1(imgID,x,y,w,h,startTime,sleepTime);
	item->color.r=r;
	item->color.g=g;
	item->color.b=b;
	item->color.a=a;
	return item;
}
