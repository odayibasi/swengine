#include "../../include/SWEngine.h"

#pragma comment (lib,"../../lib/SWUtil.lib")    
#pragma comment (lib,"../../lib/SWTypes.lib")    
#pragma comment (lib,"../../lib/SWCore.lib")    
#pragma comment (lib,"../../lib/SWEngine.lib")    


//OpenGL
#include <gl/glew.h>		// Header File For The GLu32 Library
#include <gl/wglew.h>		// Header File For The GLu32 Library
#include <gl/gl.h>			// Header File For The OpenGL32 Library
#include <gl/glu.h>			// Header File For The GLu32 Library

#pragma comment (lib,"opengl32.lib")      
#pragma comment (lib,"glu32.lib")         
#pragma comment(lib, "glew32.lib")


swApplication animatedDrawing;
float lastTime=0;

#define CIRCLE_POINT 120
swPoint vertexArray[CIRCLE_POINT];
swColor colorArray[CIRCLE_POINT];

int changeEdgeIndex=0;
GLenum type=GL_POINTS;


//-------------------------------------------------------------------------------------------
void changeEdgeColor(void *obj){ 
	if(changeEdgeIndex<CIRCLE_POINT){
		colorArray[changeEdgeIndex].r=1;
		colorArray[changeEdgeIndex].g=0;
		colorArray[changeEdgeIndex].b=0;
		colorArray[changeEdgeIndex].a=0;
		changeEdgeIndex++;
	}else{
		glShadeModel(GL_SMOOTH);
		glHint(GL_POLYGON_SMOOTH_HINT,GL_NICEST);
		type=GL_POLYGON;
	}
}



//-------------------------------------------------------------------------------------------
void InitApp(){

	for(int i=0;i<CIRCLE_POINT;i++){
		colorArray[i].r=1;
		colorArray[i].g=1;
		colorArray[i].b=1;
		colorArray[i].a=1;
	}

	
	for(int i=0;i<CIRCLE_POINT;i++){
		float angle=360.0f/CIRCLE_POINT*i;
		float dx=swMathCos(angle)*200;
		float dy=swMathSin(angle)*200;
		vertexArray[i].x=300+dx;
		vertexArray[i].y=300+dy;
	}  


	int thirdTimer=swTimerCreate(0.02f,NULL,changeEdgeColor);
}


//-------------------------------------------------------------------------------------------
void GameLoop(){ 

	swGraphicsBeginScene();
		swGraphicsSetColor0(1,1,1,0);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);

			glHint(GL_POLYGON_SMOOTH_HINT,GL_NICEST);
			glVertexPointer(2, GL_FLOAT, 0, vertexArray);
			glColorPointer(4, GL_FLOAT, 0, colorArray);
			glDrawArrays(type, 0, CIRCLE_POINT);

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	swGraphicsEndScene();
}





//-------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{ 


	//Application Settings
	animatedDrawing.hInstance=hInstance;
	animatedDrawing.fullScreen=false;
	animatedDrawing.cursor=true;
	animatedDrawing.width=1024;
	animatedDrawing.height=768;
	animatedDrawing.title="Animated Drawing";
	animatedDrawing.path="resource";
	animatedDrawing.appRun=GameLoop;

	//Application Execution
	swEngineInit(&animatedDrawing);
	InitApp();
	swEngineRun();
	swEngineExit();

	return 0;
}