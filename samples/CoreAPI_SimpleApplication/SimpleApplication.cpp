#include "../../include/SWEngine.h"
#include "resource.h"
#pragma comment (lib,"../../lib/SWEngine.lib")    
    
swApplication simpleApplication;

//-------------------------------------------------------------------------------------------
void GameLoop(){ 

	//Input Handling
	//Process Input 
	//Process System & AI
	//Rendering
}



//-------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{ 


	//Application Settings
	simpleApplication.hInstance=hInstance;
	simpleApplication.fullScreen=false;
	simpleApplication.cursor=true;
	simpleApplication.width=800;
	simpleApplication.height=600;
	simpleApplication.title="Simple Application";
	simpleApplication.path="resource";
	simpleApplication.appRun=GameLoop;

	//Application Execution
	swEngineInit(&simpleApplication);
	swEngineRun();
	swEngineExit();

	return 0;
}
