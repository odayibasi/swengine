#include "../../include/SWEngine.h"

#pragma comment (lib,"../../lib/SWUtil.lib")    
#pragma comment (lib,"../../lib/SWTypes.lib")    
#pragma comment (lib,"../../lib/SWCore.lib")    
#pragma comment (lib,"../../lib/SWEngine.lib")    


swApplication timeDepMoveApp;
swPoint elipsCenter={400,300};
swDimension elipsDim={300,100};
float rot2=0;
float rot3=0;



//-------------------------------------------------------------------------------------------
void rotateSecondElips(void *obj){ //This function triggered 0,05 seconds..
	rot2+=10;  
}

//-------------------------------------------------------------------------------------------
void rotateThirdElips(void *obj){ //This function triggered 1 seconds
	rot3-=10;
}


//-------------------------------------------------------------------------------------------
void GameLoop(){ //This function triggered when 1 frame process end Independent Time


	//Display Scene	
	swGraphicsBeginScene();

		//Background
		swGraphicsSetBgColor0(0.6f,0.6f,0.6f);

		//BlendingMode
		swGraphicsSetBlendingMode(SW_BLENDING_MODE_ADDITIVE);

		//Draw Elips
		swGraphicsSetColor0(0,1,0,0.5);
		swGraphicsRenderSolidElips2(&elipsCenter,&elipsDim,30,0);

		swGraphicsSetColor0(1,0,0,0.5);
		swGraphicsRenderSolidElips2(&elipsCenter,&elipsDim,30,60+rot2);

		swGraphicsSetColor0(0,0,1,0.5);
		swGraphicsRenderSolidElips2(&elipsCenter,&elipsDim,30,120+rot3);

	swGraphicsEndScene();
}


//-------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{ 

	//Application Settings
	timeDepMoveApp.hInstance=hInstance;
	timeDepMoveApp.fullScreen=false;
	timeDepMoveApp.cursor=true;
	timeDepMoveApp.width=800;
	timeDepMoveApp.height=600;
	timeDepMoveApp.title="Time Dependent Movement";
	timeDepMoveApp.path="resource";
	timeDepMoveApp.appRun=GameLoop;

	//Application Execution
	//Init SWEngine
	swEngineInit(&timeDepMoveApp);
	
	//Init My Application
	int secondTimer=swTimerCreate(0.05f,NULL,rotateSecondElips);
	int thirdTimer=swTimerCreate(1.0f,NULL,rotateThirdElips);


	swEngineRun();
	swEngineExit();

	return 0;
}