#include "../../include/SWEngine.h"

#pragma comment (lib,"../../lib/SWUtil.lib")    
#pragma comment (lib,"../../lib/SWTypes.lib")    
#pragma comment (lib,"../../lib/SWCore.lib")    
#pragma comment (lib,"../../lib/SWGui.lib")    
#pragma comment (lib,"../../lib/SWServices.lib")    
#pragma comment (lib,"../../lib/SWEngine.lib")    


swApplication   dispCursorApp;
swKeyboardState keybState;
swMouseState    mousState;

//-------------------------------------------------------------------------------------------
void GameLoop(){ 

	swInputListenKeyboard(&keybState);
	swInputListenMouse(&mousState);
	swInteractionManagerExecute(&keybState,&mousState);
		swGraphicsBeginScene();
			//Draw Cursor
			swGraphicsSetColor0(1,1,1,0);
			swGraphicsRenderPoint0(mousState.x,mousState.y,10);
		swGraphicsEndScene();
}


//-------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{ 

	//Application Settings
	dispCursorApp.hInstance=hInstance;
	dispCursorApp.fullScreen=false;
	dispCursorApp.cursor=false;
	dispCursorApp.width=800;
	dispCursorApp.height=600;
	dispCursorApp.title="Display Cursor";
	dispCursorApp.path="";
	dispCursorApp.appRun=GameLoop;

	//Application Execution
	swEngineInit(&dispCursorApp);
	swEngineRun();
	swEngineExit();

	return 0;
}