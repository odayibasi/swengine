#include "../../include/SWEngine.h"

typedef struct xenColumnPart{
	int		dispID;
	swRect	target;
	swRect *source;
};

int  iLayerColumnPart=8;
bool bVisibleColumnPart=true;

extern int columnPartID;
extern int columnBlockID;

swRect halfColumnSource={0,0,1,0.5};


//-------------------------------------------------------------------------------------------
void displayColumnPart(void *obj){
	xenColumnPart *wall=(xenColumnPart *)obj;
	swGraphicsSetBlendingMode(SW_BLENDING_MODE_SOLID);

	//DrawImage
	swGraphicsSetColor1(&SWCOLOR_WHITE);
	swGraphicsRenderImg2(columnPartID,&wall->target,wall->source);
}


//-------------------------------------------------------------------------------------------
void destroyColumnPart(void *obj){
	xenColumnPart *cPart=(xenColumnPart *)obj;
	swDispManagerDel(cPart->dispID);
	free(cPart);
}


//-------------------------------------------------------------------------------------------
void displayColumnBlock(void *obj){
	xenColumnPart *wall=(xenColumnPart *)obj;
	swGraphicsSetBlendingMode(SW_BLENDING_MODE_SOLID);
	swGraphicsSetColor1(&SWCOLOR_WHITE);
	swGraphicsRenderImg2(columnBlockID,&wall->target,wall->source);
}


//-------------------------------------------------------------------------------------------
void destroyColumnBlock(void *obj){
	xenColumnPart *cPart=(xenColumnPart *)obj;	
	swDispManagerDel(cPart->dispID);
	free(cPart);
}



//-------------------------------------------------------------------------------------------
void columnPartSet(xenColumnPart *wall, float x,float y,float w, float h,swRect *source){
	swRectSet(&wall->target,x,y,w,h);
	wall->source=source;
	wall->dispID=swDispManagerAdd(displayColumnPart,wall,&bVisibleColumnPart,&wall->target,&iLayerColumnPart);
	swDestroyManagerAdd(destroyColumnPart,wall);
}


//-------------------------------------------------------------------------------------------
void columnBlockSet(xenColumnPart *wall, float x,float y,swRect *source){
	swRectSet(&wall->target,x,y,64,44);
	wall->source=source;
	wall->dispID=swDispManagerAdd(displayColumnBlock,wall,&bVisibleColumnPart,&wall->target,&iLayerColumnPart);
	swDestroyManagerAdd(destroyColumnBlock,wall);
}


//-------------------------------------------------------------------------------------------
void columnPartCreate(float x,float y,int count){
	for(int i=0;i<count;i++){
		xenColumnPart *wall=(xenColumnPart *)malloc(sizeof(xenColumnPart));
		columnPartSet(wall,x,y+64*i,64,64,&SW_SPRITE_SOURCE_DEFAULT);
	}

	xenColumnPart *wall=(xenColumnPart *)malloc(sizeof(xenColumnPart));
	columnPartSet(wall,x,y+64*count,64,32,&halfColumnSource);

	
	xenColumnPart *wallBottom=(xenColumnPart *)malloc(sizeof(xenColumnPart));
	columnBlockSet(wallBottom,x,y,&SW_SPRITE_SOURCE_MIRRORXY);

	xenColumnPart *wallTop=(xenColumnPart *)malloc(sizeof(xenColumnPart));
	columnBlockSet(wallTop,x,y+64*(count)-42,&SW_SPRITE_SOURCE_DEFAULT);

}
