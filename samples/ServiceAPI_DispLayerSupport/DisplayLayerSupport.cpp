#include "Entity.h"

swApplication dispLayerSupport;
Defender      *defender=NULL;
#define       MIN_X 100
#define       MAX_X 700




//-------------------------------------------------------------------------------------------
void GameLoop(){ 
	swGraphicsBeginScene();
		swGraphicsSetBgColor2(&SWCOLOR_GRAY);
		swDispManagerExecute();
	swGraphicsEndScene();
}




//-------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{ 


	//Application Settings
	dispLayerSupport.hInstance=hInstance;
	dispLayerSupport.fullScreen=false;
	dispLayerSupport.cursor=true;
	dispLayerSupport.width=800;
	dispLayerSupport.height=600;
	dispLayerSupport.title="Layer Support";
	dispLayerSupport.path="\\rsc\\DispLayerSupport\\";
	dispLayerSupport.appRun=GameLoop;

	//Application Execution
	swEngineInit(&dispLayerSupport);

	//Init My Application
	swDispManagerSetLayerCount(3);
	xenInit();
	xenCreate();
	defenderInit();
	defender=defenderCreate();

	swEngineRun();
	swEngineExit();

	return 0;
}