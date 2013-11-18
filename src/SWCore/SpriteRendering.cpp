#include "SWCoreIn.h"
#include <gl/gl.h>			// Header File For The OpenGL32 Library


extern swPoint			defaultWeight;
extern swRect			defaultSource;


//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsRenderSprite0(int spriteID,int index,swRect *t){
	swGraphicsRenderSprite5(spriteID,index,t,&defaultSource,0,&defaultWeight);
}

//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsRenderSprite1(int spriteID,int index,swRect *t,float rot){
	swGraphicsRenderSprite5(spriteID,index,t,&defaultSource,rot,&defaultWeight);
}


//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsRenderSprite2(int spriteID,int index,swRect *t,swRect *s){
	swGraphicsRenderSprite5(spriteID,index,t,s,0,&defaultWeight);
}


//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsRenderSprite3(int spriteID,int index,swRect *t,swRect *s,float rot){
	swGraphicsRenderSprite5(spriteID,index,t,s,rot,&defaultWeight);
}


//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsRenderSprite4(int spriteID,int index,swRect *t,float  rot, swPoint *weight){
	swGraphicsRenderSprite5(spriteID,index,t,&defaultSource,rot,&defaultWeight);
}


//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsRenderSprite5(int spriteID,int index,swRect *t,swRect *s,float rot, swPoint *weight){
	float dX=-(t->w*weight->x+t->x);
	float dY=-(t->h*weight->y+t->y);

	glPushMatrix();
	Sprite *sprite=swSpriteGetById(spriteID);
	swGraphicsBindSprite(sprite,index);
	swGraphicsUpdateModelMatrix(-dX,-dY,rot);
	if(sprite->powerTwo){
		swGraphicsRenderImg1(dX+t->x,dY+t->y,t->w,t->h,s->x,s->y,s->w,s->h);
	}else{
		swGraphicsRenderImg2(dX+t->x,dY+t->y,t->w,t->h,s->x,s->y,s->w,s->h,(float)sprite->width,(float)sprite->height);
	}
	swGraphicsUnBindSprite(sprite);
	glPopMatrix();
}
