#include "../../include/SWEngine.h"
#include <math.h>

#pragma comment (lib,"../../lib/SWUtil.lib")    
#pragma comment (lib,"../../lib/SWTypes.lib")    
#pragma comment (lib,"../../lib/SWCore.lib")    
#pragma comment (lib,"../../lib/SWEngine.lib")    


swApplication simplePlotApp;
bool bDrawed=false;
int screenWidth=800;
int screenHeight=600;


//-------------------------------------------------------------------------------------------
void GameLoop(){ 

	double G=6.67e-11; //Test for e writing 10^-11 

	if(!bDrawed){

		double A,B,C,D,x;

		A=(screenWidth-200)/4;
		B=100;
		C=(screenHeight-200)/2;
		D=C;

		swGraphicsBeginScene();
		swGraphicsSetColor1(&SWCOLOR_WHITE);

		for(double x=0;x<4.0;x+=0.005){
				double fx=exp(-x)*cos(2*SW_MATH_PI*x);
				swGraphicsRenderPoint0(A*x+B,C*fx+D,2);
		}
		swGraphicsEndScene();
		bDrawed=true;
	}
}

//-------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{ 


	//Application Settings
	simplePlotApp.hInstance=hInstance;
	simplePlotApp.fullScreen=false;
	simplePlotApp.cursor=true;
	simplePlotApp.width=800;
	simplePlotApp.height=600;
	simplePlotApp.title="Simple Dots";
	simplePlotApp.path="resource";
	simplePlotApp.appRun=GameLoop;

	//Application Execution
	swEngineInit(&simplePlotApp);
	swEngineRun();
	swEngineExit();

	return 0;
}