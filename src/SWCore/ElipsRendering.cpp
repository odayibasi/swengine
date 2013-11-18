#include "SWCoreIn.h"
#include <gl/gl.h>			// Header File For The OpenGL32 Library


extern swPoint			defaultWeight;

//-------------------------------------------------------------------------------------------
void swGraphicsRenderElips( int count, float x, float y, float w, float h,float dX,float dY){
	for(int i=0;i<count;i++){
		float angle=360*i/count;
		float dx=swMathCos(angle)*w/2;
		float dy=swMathSin(angle)*h/2;
		glVertex2f(x+dx+dX,y+dy+dY);
	}  
}


//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsRenderPointElips0(float x,float y,float w,float h,int count,float size){
	glPointSize(size);
	glBegin(GL_POINTS);
	swGraphicsRenderElips(count,x, y, w, h,0,0);
	glEnd();
}


//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsRenderPointElips1(swPoint *pos,swDimension *dim,int count,float size){
	swGraphicsRenderPointElips0(pos->x, pos->y, dim->w, dim->h,count,size);
}


//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsRenderPointElips2(swPoint *pos,swDimension *dim,int count,float size,float rot){
	swGraphicsRenderPointElips3(pos,dim,count,size,rot,&defaultWeight);
}


//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsRenderPointElips3(swPoint *pos,swDimension *dim,int count, float size,float rot,swPoint *weight){
	swGraphicsRenderPointElips4(pos->x,pos->y,dim->w,dim->h,count,size,rot,weight);	
}


//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsRenderPointElips4(float x,float y,float w, float h,int count, float size, float rot,swPoint *weight){
	float dX=-(w*(weight->x-0.5f)+x);
	float dY=-(h*(weight->y-0.5f)+y);

	glPushMatrix();
	swGraphicsUpdateModelMatrix(-dX,-dY,rot);
	glPointSize(size);
	glBegin(GL_POINTS);
	swGraphicsRenderElips(count, x, y, w, h,dX,dY);
	glEnd();
	glPopMatrix();


}


//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsRenderLineElips0(float x,float y,float w,float h,int count,float width){
	glLineWidth(width);
	glBegin(GL_LINE_LOOP);
	swGraphicsRenderElips(count,x, y, w, h,0,0);
	glEnd();
}


//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsRenderLineElips1(swPoint *pos,swDimension *dim,int count,float width){
	swGraphicsRenderLineElips0(pos->x, pos->y, dim->w, dim->h,count,width);
}

//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsRenderLineElips2(swPoint *pos,swDimension *dim,int count,float width,float rot){
	swGraphicsRenderLineElips3(pos,dim,count,width,rot,&defaultWeight);
}

//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsRenderLineElips3(swPoint *pos,swDimension *dim,int count, float width,float rot, swPoint *weight){
	swGraphicsRenderLineElips4(pos->x,pos->y,dim->w,dim->h,count,width,rot,weight);
}

//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsRenderLineElips4(float x,float y,float w, float h,int count, float width,float rot, swPoint *weight){
	float dX=-(w*(weight->x-0.5f)+x);
	float dY=-(h*(weight->y-0.5f)+y);

	glPushMatrix();
	swGraphicsUpdateModelMatrix(-dX,-dY,rot);
	glLineWidth(width);
	glBegin(GL_LINE_LOOP);
	swGraphicsRenderElips(count, x, y, w, h,dX,dY);
	glEnd();
	glPopMatrix();
}



//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsRenderSolidElips0(float x,float y,float w,float h,int count){
	glBegin(GL_POLYGON);
	swGraphicsRenderElips(count,x, y, w, h,0,0);
	glEnd();
}


//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsRenderSolidElips1(swPoint *pos,swDimension *dim,int count){
	swGraphicsRenderSolidElips0(pos->x,pos->y,dim->w,dim->h,count);
}


//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsRenderSolidElips2(swPoint *pos,swDimension *dim,int count,float rot){
	swGraphicsRenderSolidElips3(pos,dim,count,rot,&defaultWeight);
}


//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsRenderSolidElips3(swPoint *pos,swDimension *dim,int count, float rot, swPoint *weight){
	swGraphicsRenderSolidElips4(pos->x,pos->y,dim->w,dim->h,count,rot,weight);
}

//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsRenderSolidElips4(float x,float y,float w,float h,int count, float rot, swPoint *weight){

	float dX=-(w*(weight->x-0.5f)+x);
	float dY=-(h*(weight->y-0.5f)+y);

	glPushMatrix();
	swGraphicsUpdateModelMatrix(-dX,-dY,rot);
	glBegin(GL_POLYGON);
	swGraphicsRenderElips(count, x, y, w, h,dX,dY);
	glEnd();
	glPopMatrix();
}

