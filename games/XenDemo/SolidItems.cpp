#include "SolidItems.h"


extern  bool	xenShadowActive;
swPoint			wpSolidItem={0,0};

//-------------------------------------------------------------------------------------------
void solidItemPrepareShadow(swRect *rT,swRect rS){
	float dX=0;
	float dY=0;
	float dW=8;
	float dH=8;

	rT->x=rS.x+dX; rT->y=rS.y+dY; rT->w=rS.w+dW; rT->h=rS.h+dH; 
}



//-------------------------------------------------------------------------------------------
void solidItemRenderWithParams(swColor color,xenSolidItem *item,swRect target){

	swGraphicsSetColor1(&color);
	if(item->animID==-1){ //Image
		swGraphicsRenderImg4(item->imgsprID,&target,item->rot,&wpSolidItem);
	}else{
		int index=swAnimatorGetIndex(item->animID);
		swGraphicsRenderSprite4(item->imgsprID,index,&target,item->rot,&wpSolidItem);
	}
}


//-------------------------------------------------------------------------------------------
void solidItemRender(xenSolidItem *solidItem){
	solidItemRenderWithParams(SWCOLOR_WHITE,solidItem,solidItem->target);
}

//-------------------------------------------------------------------------------------------
void renderSolidItemShadow(xenSolidItem *solidItem){

	swColor shdColor={0,0,0,0.5};
	swRect  shdRect;

	solidItemPrepareShadow(&shdRect,solidItem->target);
	solidItemRenderWithParams(shdColor,solidItem,shdRect);
}

//-------------------------------------------------------------------------------------------
void solidItemDisplay(void *obj){
	xenSolidItem* item=(xenSolidItem*)obj; 
	swGraphicsSetBlendingMode(SW_BLENDING_MODE_SOLID);
	if(xenShadowActive && item->hasShadow)
		renderSolidItemShadow(item);
	solidItemRender(item);
}


//-------------------------------------------------------------------------------------------
void solidItemDestroy(void *obj){
	xenSolidItem* item=(xenSolidItem*)obj; 
	swDispManagerDel(item->dispID);
	if(item->animID!=-1) swAnimatorDestroy(item->animID);
	if(item->bodyID!=-1) swPhysBodyDestroy(item->bodyID);
}



//-------------------------------------------------------------------------------------------
xenSolidItem* solidItemCreate(int imgsprID,int layer,float x,float y,float w,float h,bool bHasShadow){
	xenSolidItem* item=(xenSolidItem*)malloc(sizeof(xenSolidItem)); 
	item->imgsprID=imgsprID;
	item->layer=layer;
	item->bEnabled=true;
	item->hasShadow=bHasShadow;
	item->animID=-1;
	item->bodyID=-1;
	item->rot=0;
	swRectSet(&item->target,x,y,w,h);
	item->dispID=swDispManagerAdd(solidItemDisplay,item,&item->bEnabled,&item->target,&item->layer);
	swDestroyManagerAdd(solidItemDestroy,item);
	return item;
}


//-------------------------------------------------------------------------------------------
xenSolidItem* solidItemCreateWithAnims(int imgsprID,int layer,float x,float y,float w,float h,float sleepTime, bool hasShadow){
	xenSolidItem* item=solidItemCreate(imgsprID,layer,x,y,w,h,hasShadow);
	item->animID=swAnimatorCreate(swGraphicsGetCountOfImgInSprite(imgsprID),sleepTime);
	swAnimatorSetExecutionMode(item->animID,SW_ANIMATOR_EXEC_FORWARD_LOOP);
	return item;
}


//-------------------------------------------------------------------------------------------
xenSolidItem* solidItemCreateWithBody(int imgsprID,int layer,float x,float y,float w,float h,bool bHasShadow){
	xenSolidItem* item=solidItemCreate(imgsprID,layer,x,y,w,h,bHasShadow);
	swPhysBodyDefSetPos(x,y);
	swPhysBodyDefSetRectShapeType(w,h);
	swPhysBodyDefSetDensity(1.0f);
	swPhysBodyDefSetPosListener(&item->target.x,&item->target.y);
	swPhysBodyDefSetAngleListener(&item->rot);
	item->bodyID=swPhysBodyCreate();
	return item;
}



//-------------------------------------------------------------------------------------------
xenSolidItem* solidItemCreateFixedBody(int imgsprID,int layer,float x,float y,float w,float h,bool bHasShadow){
	xenSolidItem* item=solidItemCreate(imgsprID,layer,x,y,w,h,bHasShadow);
	swPhysBodyDefSetPos(x,y);
	swPhysBodyDefSetRectShapeType(w,h);
	swPhysBodyDefSetDensity(0);
	swPhysBodyDefSetFilterGroupIndex(-4);
	swPhysBodyDefSetPosListener(&item->target.x,&item->target.y);
	swPhysBodyDefSetAngleListener(&item->rot);
	item->bodyID=swPhysBodyCreate();
	return item;
}

