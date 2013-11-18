#include "../../include/SWEngine.h"
#pragma comment (lib,"../../lib/SWCore.lib")    
#pragma comment (lib,"../../lib/SWEngine.lib")    



swApplication listenMouseApp;
swKeyboardState keybState;
swMouseState    mousState;
int             fontID;
//-------------------------------------------------------------------------------------------
void GameLoop(){ 

	//Input Handling
	swInputListenKeyboard(&keybState);
	swInputListenMouse(&mousState);


	swGraphicsBeginScene();
		swGraphicsSetColor0(1,1,1,1);
		swGraphicsSetBlendingMode(SW_BLENDING_MODE_ADDITIVE);
		if(mousState.btnLEFT)
			swGraphicsRenderText(fontID,2,16,200,200,0,"Left Key Pressed");

		if(mousState.btnRIGHT)
			swGraphicsRenderText(fontID,2,16,200,220,0,"Right Key Pressed");

		if(mousState.btnMIDDLE)
			swGraphicsRenderText(fontID,2,16,200,240,0,"Middle Key Pressed");


		swGraphicsRenderText(fontID,2,16,200,260,0,"Mouse dx=%f dy=%f",mousState.dx,mousState.dy);
	swGraphicsEndScene();

	if(keybState.keyESCAPE){
		swEngineExit();
	}

	//Process System & AI
	//Rendering
}



//-------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{ 


	//Application Settings
	listenMouseApp.hInstance=hInstance;
	listenMouseApp.fullScreen=false;
	listenMouseApp.cursor=true;
	listenMouseApp.width=800;
	listenMouseApp.height=600;
	listenMouseApp.title="Listen Mouse";
	listenMouseApp.path="\\rsc\\ListenMouse\\";
	listenMouseApp.appRun=GameLoop;

	//Application Execution
	swEngineInit(&listenMouseApp);
	fontID=swGraphicsCreateFont("Font.tga");



	swEngineRun();
	swEngineExit();

	return 0;
}