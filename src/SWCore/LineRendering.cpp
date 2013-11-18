#include "SWCoreIn.h"
#include <gl/gl.h>			// Header File For The OpenGL32 Library


extern swPoint			defaultWeight;

//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsRenderLine0(float x0,float y0,float x1,float y1,float width){
	glLineWidth(width);
	glBegin(GL_LINES);
	glVertex2f(x0,y0);
	glVertex2f(x1,y1);
	glEnd();
}

//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsRenderLine1(swPoint *startP,swPoint *endP,float width){
	swGraphicsRenderLine0(startP->x,startP->y,endP->x,endP->y,width);
}


//-------------------------------------------------------------------------------------------
DllExport void swGraphicsRenderLine2(swPoint *startP,swPoint *endP,float width,float rot){
	swGraphicsRenderLine3(startP,endP,width,rot,&defaultWeight);
}


//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsRenderLine3(swPoint *startP,swPoint *endP,float width,float rot,swPoint *weight){

	float dX=-((endP->x-startP->x)*weight->x+startP->x);
	float dY=-((endP->y-startP->y)*weight->y+startP->y);

	glPushMatrix();
	swGraphicsUpdateModelMatrix(-dX,-dY,rot);
	swGraphicsRenderLine0(dX+startP->x,dY+startP->y,dX+endP->x,dY+endP->y,width);
	glPopMatrix();
}

