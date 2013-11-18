#include "../../include/SWEngine.h"

#pragma comment (lib,"../../lib/SWUtil.lib")    
#pragma comment (lib,"../../lib/SWTypes.lib")    
#pragma comment (lib,"../../lib/SWCore.lib")    
#pragma comment (lib,"../../lib/SWEngine.lib")    


swApplication rotationApp;
swPoint elipsCenter={400,300};
swDimension elipsDim={300,100};



//-------------------------------------------------------------------------------------------
void GameLoop(){ 

	swGraphicsBeginScene();

	//Background
	swGraphicsSetBgColor0(0.6f,0.6f,0.6f);

	//Draw Elips
	swGraphicsSetColor1(&SWCOLOR_GREEN);
	swGraphicsRenderSolidElips2(&elipsCenter,&elipsDim,30,0);

	swGraphicsSetColor1(&SWCOLOR_RED);
	swGraphicsRenderSolidElips2(&elipsCenter,&elipsDim,30,60);

	swGraphicsSetColor1(&SWCOLOR_BLUE);
	swGraphicsRenderSolidElips2(&elipsCenter,&elipsDim,30,120);

	swGraphicsEndScene();

}





//-------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{ 


	//Application Settings
	rotationApp.hInstance=hInstance;
	rotationApp.fullScreen=false;
	rotationApp.cursor=true;
	rotationApp.width=800;
	rotationApp.height=600;
	rotationApp.title="Rotation";
	rotationApp.path="resource";
	rotationApp.appRun=GameLoop;

	//Application Execution
	swEngineInit(&rotationApp);
	swEngineRun();
	swEngineExit();

	return 0;
}