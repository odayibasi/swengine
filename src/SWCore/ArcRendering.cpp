#include "SWCoreIn.h"
#include <gl/gl.h>			// Header File For The OpenGL32 Library


//-------------------------------------------------------------------------------------------
void swGraphicsRenderArcs( int count, float x, float y, float w, float h,float dX,float dY, float startAngle, float stopAngle){

	float delta=stopAngle-startAngle;

	glVertex2f(x+dX,y+dY);
	for(int i=0;i<count;i++){
		float angle=startAngle+delta*i/count;
		float dx=swMathCos(angle)*w/2;
		float dy=swMathSin(angle)*h/2;
		glVertex2f(x+dx+dX,y+dy+dY);
	}  
	glVertex2f(x+dX,y+dY);
}


//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsRenderPointArcs(float x,float y,float w, float h,int count, float size, float rot,swPoint *weight,float startAngle,float stopAngle){

	float dX=-(w*(weight->x-0.5f)+x);
	float dY=-(h*(weight->y-0.5f)+y);

	glPushMatrix();
	swGraphicsUpdateModelMatrix(-dX,-dY,rot);
	glPointSize(size);
	glBegin(GL_POINTS);
	swGraphicsRenderArcs(count, x, y, w, h,dX,dY,startAngle,stopAngle);
	glEnd();
	glPopMatrix();

}

//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsRenderLineArcs(float x,float y,float w, float h,int count, float width,float rot, swPoint *weight, float startAngle,float stopAngle){

	float dX=-(w*(weight->x-0.5f)+x);
	float dY=-(h*(weight->y-0.5f)+y);

	glPushMatrix();
	swGraphicsUpdateModelMatrix(-dX,-dY,rot);
	glLineWidth(width);
	glBegin(GL_LINE_LOOP);
	swGraphicsRenderArcs(count, x, y, w, h,dX,dY,startAngle,stopAngle);
	glEnd();
	glPopMatrix();

}

//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsRenderSolidArcs0(float x,float y,float w,float h,int count,float startAngle,float stopAngle){
	glBegin(GL_POLYGON);
	swGraphicsRenderArcs(count,x, y, w, h,0,0,startAngle,stopAngle);
	glEnd();
}



//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsRenderSolidArcs4(float x,float y,float w,float h,int count, float rot, swPoint *weight, float startAngle,float stopAngle){
	float dX=-(w*(weight->x-0.5f)+x);
	float dY=-(h*(weight->y-0.5f)+y);

	glPushMatrix();
	swGraphicsUpdateModelMatrix(-dX,-dY,rot);
	glBegin(GL_POLYGON);
	swGraphicsRenderArcs(count, x, y, w, h,dX,dY,startAngle,stopAngle);
	glEnd();
	glPopMatrix();

}
