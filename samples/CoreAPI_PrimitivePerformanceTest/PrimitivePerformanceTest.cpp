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


swApplication primitivePerformanceTest;
float lastTime=0;

#define MAX_POINT  786432
swPoint vertexArray[1024][768];
swColor colorArray[1024][768];


//-------------------------------------------------------------------------------------------
void InitApp(){
	for(int i=0;i<1024;i++){
		for(int j=0;j<768;j++){
			vertexArray[i][j].x=i;
			vertexArray[i][j].y=j;
			colorArray[i][j].r=swMathRandomFloat(0,1);
			colorArray[i][j].g=swMathRandomFloat(0,1);
			colorArray[i][j].b=swMathRandomFloat(0,1);
			colorArray[i][j].a=swMathRandomFloat(0,1);
		}
	}

}


//-------------------------------------------------------------------------------------------
void GameLoop(){ 

	swGraphicsBeginScene();

	int maxNumber=0;

	glGetIntegerv(GL_MAX_ELEMENTS_VERTICES,&maxNumber);  

	swGraphicsSetColor0(1,1,1,0);

	float current=swSystemGetElapsedSeconds();
	swLoggerLog("dTime =%f\n",1.0f/(current-lastTime));
	lastTime=current;

	swGraphicsSetColor1(&SWCOLOR_RED);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

		glVertexPointer(2, GL_FLOAT, sizeof(swPoint), vertexArray);
		glColorPointer(4, GL_FLOAT, sizeof(swColor), colorArray);
		glDrawArrays(GL_POINTS, 0, MAX_POINT);

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	swGraphicsEndScene();
}





//-------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{ 


	//Application Settings
	primitivePerformanceTest.hInstance=hInstance;
	primitivePerformanceTest.fullScreen=false;
	primitivePerformanceTest.cursor=true;
	primitivePerformanceTest.width=1024;
	primitivePerformanceTest.height=768;
	primitivePerformanceTest.title="Primitive Performance Test";
	primitivePerformanceTest.path="resource";
	primitivePerformanceTest.appRun=GameLoop;

	//Application Execution
	swEngineInit(&primitivePerformanceTest);
	InitApp();
	swEngineRun();
	swEngineExit();

	return 0;
}