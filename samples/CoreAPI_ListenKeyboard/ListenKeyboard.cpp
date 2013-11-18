#include "../../include/SWEngine.h"
#pragma comment (lib,"../../lib/SWCore.lib")    
#pragma comment (lib,"../../lib/SWEngine.lib")    



swApplication listenKeybApp;
swKeyboardState state;

//-------------------------------------------------------------------------------------------
void GameLoop(){ 

	//Input Handling
	swInputListenKeyboard(&state);
	if(state.keyESCAPE){
		swEngineExit();
	}


	//Process Input 
	//Process System & AI
	//Rendering
}



//-------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{ 


	//Application Settings
	listenKeybApp.hInstance=hInstance;
	listenKeybApp.fullScreen=false;
	listenKeybApp.cursor=true;
	listenKeybApp.width=800;
	listenKeybApp.height=600;
	listenKeybApp.title="Listen Keyboard";
	listenKeybApp.path="resource";
	listenKeybApp.appRun=GameLoop;

	//Application Execution
	swEngineInit(&listenKeybApp);
	swEngineRun();
	swEngineExit();

	return 0;
}