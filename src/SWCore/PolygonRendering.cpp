#include "SWCoreIn.h"
#include <gl/gl.h>			// Header File For The OpenGL32 Library



//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsRenderSolidPolygon0(int count,swPoint *pointS){
	glBegin(GL_POLYGON);
	for(int i=0;i<count;i++)
		glVertex2f(pointS[i].x,pointS[i].y);
	glEnd();
}

//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsRenderSolidPolygon1(int pointLinkedListID){
	glBegin(GL_POLYGON);
	swPoint *p=(swPoint*)swLinkedListGetFirst(pointLinkedListID);
	while(p!=NULL){
		glVertex2f(p->x,p->y);
		p=(swPoint*)swLinkedListGetNext(pointLinkedListID);
	}
	glEnd();
}

//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsRenderSolidPolygon2(swPolygon *polygon){
	swGraphicsRenderSolidPolygon0(polygon->count,polygon->pointS);
}


//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsRenderLinePolygon0(int count,swPoint *pointS,float width){
	glLineWidth(width);
	glBegin(GL_LINE_LOOP);
	for(int i=0;i<count;i++)
		glVertex2f(pointS[i].x,pointS[i].y);
	glEnd();
}

//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsRenderLinePolygon1(int pointLinkedListID,float width){
	glBegin(GL_LINE_LOOP);
	swPoint *p=(swPoint*)swLinkedListGetFirst(pointLinkedListID);
	while(p!=NULL){
		glVertex2f(p->x,p->y);
		p=(swPoint*)swLinkedListGetNext(pointLinkedListID);
	}
	glEnd();
}

//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsRenderLinePolygon2(swPolygon *polygon,float width){
	swGraphicsRenderLinePolygon0(polygon->count,polygon->pointS,width);
}

//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsRenderPointPolygon0(int count,swPoint *pointS,float size){
	glPointSize(size);
	glBegin(GL_POINTS);
	for(int i=0;i<count;i++)
		glVertex2f(pointS[i].x,pointS[i].y);
	glEnd();
}

//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsRenderPointPolygon1(int pointLinkedListID,float size){
	glPointSize(size);
	glBegin(GL_POINTS);
	swPoint *p=(swPoint*)swLinkedListGetFirst(pointLinkedListID);
	while(p!=NULL){
		glVertex2f(p->x,p->y);
		p=(swPoint*)swLinkedListGetNext(pointLinkedListID);
	}
	glEnd();

}

//-------------------------------------------------------------------------------------------
DllExport void swGraphicsRenderPointPolygon2(swPolygon *polygon,float size){
	swGraphicsRenderPointPolygon0(polygon->count,polygon->pointS,size);
}
