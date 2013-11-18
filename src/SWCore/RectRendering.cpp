#include "SWCoreIn.h"
#include <gl/gl.h>			// Header File For The OpenGL32 Library


extern swPoint			defaultWeight;

//-------------------------------------------------------------------------------------------
void swGraphicsRenderRect( float x, float y, float w, float h ){
	glVertex2f(x,y);
	glVertex2f(x+w,y);
	glVertex2f(x+w,y+h);
	glVertex2f(x,y+h);
}


//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsRenderPointRect0(float x,float y,float w,float h,float size){
	glPointSize(size);
	glBegin(GL_POINTS);
	swGraphicsRenderRect(x, y, w, h);
	glEnd();
}



//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsRenderPointRect1(swPoint *pos,swDimension *dim,float size){
	swGraphicsRenderPointRect0(pos->x,pos->y,dim->w,dim->h,size);
}

//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsRenderPointRect2(swRect *rect,float size){
	swGraphicsRenderPointRect0(rect->x,rect->y,rect->w,rect->h,size);
}


//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsRenderPointRect3(swRect *rect,float size,float rot){
	swGraphicsRenderPointRect4(rect,size,rot,&defaultWeight);
}


//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsRenderPointRect4(swRect *rect,float size,float rot,swPoint *weight){
	float dX=-(rect->w*weight->x+rect->x);
	float dY=-(rect->h*weight->y+rect->y);

	glPushMatrix();
	swGraphicsUpdateModelMatrix(-dX,-dY,rot);
	swGraphicsRenderPointRect0(dX+rect->x,dY+rect->y,rect->w,rect->h,size);
	glPopMatrix();
}

//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsRenderLineRect0(float x,float y,float w,float h,float width){
	glLineWidth(width);
	glBegin(GL_LINE_LOOP);
	swGraphicsRenderRect(x, y, w, h);
	glEnd();
}


//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsRenderLineRect1(swPoint *pos,swDimension *dim,float width){
	swGraphicsRenderLineRect0(pos->x,pos->y,dim->w,dim->h,width);
}


//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsRenderLineRect2(swRect *rect,float width){
	swGraphicsRenderLineRect0(rect->x,rect->y,rect->w,rect->h,width);
}


//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsRenderLineRect3(swRect *rect,float width,float rot){
	swGraphicsRenderLineRect4(rect,width,rot,&defaultWeight);
}


//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsRenderLineRect4(swRect *rect,float width,float rot,swPoint *weight){
	float dX=-(rect->w*weight->x+rect->x);
	float dY=-(rect->h*weight->y+rect->y);

	glPushMatrix();
	swGraphicsUpdateModelMatrix(-dX,-dY,rot);
	swGraphicsRenderLineRect0(dX+rect->x,dY+rect->y,rect->w,rect->h,width);
	glPopMatrix();
}


//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsRenderSolidRect0(float x,float y,float w,float h){
	glBegin(GL_QUADS);
	swGraphicsRenderRect(x, y, w, h);
	glEnd();

}


//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsRenderSolidRect1(swPoint *pos,swDimension *dim){
	swGraphicsRenderSolidRect0(pos->x,pos->y,dim->w,dim->h);
}


//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsRenderSolidRect2(swRect *rect){
	swGraphicsRenderSolidRect0(rect->x,rect->y,rect->w,rect->h);
}


//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsRenderSolidRect3(swRect *rect,float rot){
	swGraphicsRenderSolidRect4(rect,rot,&defaultWeight);
}


//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsRenderSolidRect4(swRect *rect,float rot,swPoint *weight){
	float dX=-(rect->w*weight->x+rect->x);
	float dY=-(rect->h*weight->y+rect->y);

	glPushMatrix();
	swGraphicsUpdateModelMatrix(-dX,-dY,rot);
	swGraphicsRenderSolidRect0(dX+rect->x,dY+rect->y,rect->w,rect->h);
	glPopMatrix();
}

