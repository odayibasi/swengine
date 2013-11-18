#include "SWCoreIn.h"
#include <gl/gl.h>			// Header File For The OpenGL32 Library


extern swPoint			defaultWeight;
extern swRect			defaultSource;

//-------------------------------------------------------------------------------------------
void swGraphicsRenderImg1(float tx, float ty, float tw, float th,float sx, float sy, float sw, float sh){

	glBegin(GL_QUADS);
	glTexCoord2f(sx,sy);
	glVertex2f(tx,ty);
	glTexCoord2f(sx+sw,sy);
	glVertex2f(tx+tw,ty);
	glTexCoord2f(sx+sw,sy+sh);
	glVertex2f(tx+tw,ty+th);
	glTexCoord2f(sx,sy+sh);
	glVertex2f(tx,ty+th);
	glEnd();
}


//-------------------------------------------------------------------------------------------
void swGraphicsRenderImg2(float tx, float ty, float tw, float th,float sx, float sy, float sw, float sh,float sW,float sH){

	glBegin(GL_QUADS);
	glTexCoord2f(sx*sW,sy*sH);
	glVertex2f(tx,ty);
	glTexCoord2f((sx+sw)*sW,sy*sH);
	glVertex2f(tx+tw,ty);
	glTexCoord2f((sx+sw)*sW,(sy+sh)*sH);
	glVertex2f(tx+tw,ty+th);
	glTexCoord2f(sx*sW,(sy+sh)*sH);
	glVertex2f(tx,ty+th);
	glEnd();
}


//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsRenderImg0(int imgID,swRect *t){
	swGraphicsRenderImg5(imgID,t,&defaultSource,0,&defaultWeight);
}

//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsRenderImg1(int imgID,swRect *t,float rot){
	swGraphicsRenderImg5(imgID,t,&defaultSource,rot,&defaultWeight);
}


//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsRenderImg2(int imgID,swRect *t,swRect *s){
	swGraphicsRenderImg5(imgID,t,s,0,&defaultWeight);
}

//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsRenderImg3(int imgID,swRect *t,swRect *s,float rot){
	swGraphicsRenderImg5(imgID,t,s,rot,&defaultWeight);
}


//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsRenderImg4(int imgID,swRect *t,float rot, swPoint *weight){
	swGraphicsRenderImg5(imgID,t,&defaultSource,rot,weight);
}



//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsRenderImg5(int imgID,swRect *t,swRect *s,float rot, swPoint *weight){
	swGraphicsRenderSprite5(imgID,0,t,s,rot,weight);
}