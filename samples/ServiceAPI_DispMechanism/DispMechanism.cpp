#include "XenDispMech.h"

swApplication dispMechanismApp;

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
	dispMechanismApp.hInstance=hInstance;
	dispMechanismApp.fullScreen=false;
	dispMechanismApp.cursor=true;
	dispMechanismApp.width=800;
	dispMechanismApp.height=600;
	dispMechanismApp.title="Display Mechanism";
	dispMechanismApp.path="\\rsc\\DisplayMechanism\\";
	dispMechanismApp.appRun=GameLoop;

	//Application Execution
	swEngineInit(&dispMechanismApp);

	//Init My Application
	xenInit();
	xenCreate();


	swEngineRun();
	swEngineExit();

	return 0;
}