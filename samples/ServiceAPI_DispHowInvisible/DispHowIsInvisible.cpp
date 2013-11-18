#include "XenVisible.h"

swApplication dispHowIsInvisible;
Xen *xen=NULL;
swKeyboardState keybState;
int fontID=-1;

//-------------------------------------------------------------------------------------------
void GameLoop(){ 
	
	swInputListenKeyboard(&keybState);
	if(keybState.keyS)
		xen->bVisible=true;
	else if(keybState.keyH)
		xen->bVisible=false;



		swGraphicsBeginScene();
			swGraphicsSetBgColor2(&SWCOLOR_GRAY);
			swDispManagerExecute();
			swGraphicsSetColor1(&SWCOLOR_WHITE);
			swGraphicsSetBlendingMode(SW_BLENDING_MODE_ADDITIVE);
			swGraphicsRenderText(fontID,0,25,200,540,0,"KeyS=Show keyH=Hide");
		swGraphicsEndScene();
}



//-------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{ 


	//Application Settings
	dispHowIsInvisible.hInstance=hInstance;
	dispHowIsInvisible.fullScreen=false;
	dispHowIsInvisible.cursor=true;
	dispHowIsInvisible.width=800;
	dispHowIsInvisible.height=600;
	dispHowIsInvisible.title="Hide Item";
	dispHowIsInvisible.path="\\rsc\\DisplayHowIsInvisible\\";
	dispHowIsInvisible.appRun=GameLoop;

	//Application Execution
	swEngineInit(&dispHowIsInvisible);

	//Init My Application
	xenInit();
	xen=xenCreate();
	fontID=swGraphicsCreateFont("Font.tga");
	swEngineRun();
	swEngineExit();

	return 0;
}