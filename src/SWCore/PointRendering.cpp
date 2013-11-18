#include "SWCoreIn.h"
#include <gl/gl.h>			// Header File For The OpenGL32 Library



//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsRenderPoint0(float x,float y,float size){
	glPointSize(size);
	glBegin(GL_POINTS);
	glVertex2f(x,y);
	glEnd();
}


//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsRenderPoint1(swPoint *point,float size){
	swGraphicsRenderPoint0(point->x,point->y,size);
}

