#include "XenShadow.h"

swApplication shadowApp;
Xen *xen=NULL;

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
	shadowApp.hInstance=hInstance;
	shadowApp.fullScreen=false;
	shadowApp.cursor=true;
	shadowApp.width=800;
	shadowApp.height=600;
	shadowApp.title="Shadow";
	shadowApp.path="\\rsc\\Shadow\\";
	shadowApp.appRun=GameLoop;

	//Application Execution
	swEngineInit(&shadowApp);

	//Init My Application
	xenInit();
	xen=xenCreate();
	swEngineRun();
	swEngineExit();

	return 0;
}