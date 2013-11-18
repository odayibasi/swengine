#include "DWApp.h"

swRect             mousTarget={0,0,50,50}; 


int					camID;
extern int			mouseID;
swApplication		dwApp;
swKeyboardState		keybState;
swMouseState		mousState;

void (*activeFunc)(void)=NULL;





//-------------------------------------------------------------------------------------------
void dwAppInit(){ 

	//Init My Application
	camID=swGraphicsCreateCam();

	//Manager Init
	resourceManagerInit();

	activeFunc = stageMainGuiInit;
	//activeFunc=stageEndOfSceneInit;

}



//-------------------------------------------------------------------------------------------
void dwAppLoop()
{

	//Game Loop
	swInputListenKeyboard(&keybState);
	swInputListenMouse(&mousState);
	swKeybBehaviourExecute(&keybState);
	swMousBehaviourExecute(&mousState);

	swGraphicsBeginScene();
	swGraphicsActiveCam(camID);
		swGraphicsSetBgColor2(&SWCOLOR_BLACK);
		if(activeFunc!=NULL )(*activeFunc)();

    swGraphicsActiveCam(SW_CAM_DEFAULT);
	swGraphicsSetBlendingMode(SW_BLENDING_MODE_SOLID);
	swGraphicsSetColor1(&SWCOLOR_WHITE);
	mousTarget.x=mousState.x-mousTarget.w/2; mousTarget.y=mousState.y-mousTarget.h/2;
	swGraphicsRenderImg0(mouseID,&mousTarget);

	swGraphicsEndScene();

	if(keybState.keyESCAPE){
		exit(0);
	}


}



//-------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{ 
	srand(time(NULL));
	//Application Settings
	dwApp.hInstance=hInstance;
	dwApp.fullScreen=true;
	dwApp.cursor=false;
	dwApp.width=1024;
	dwApp.height=768;
	dwApp.title="DreamWalker";
	dwApp.path="\\rsc\\DW\\";
	dwApp.appRun=dwAppLoop;

	//Application Execution
	swEngineInit(&dwApp);
	dwAppInit();
	swEngineRun();
	swEngineExit();

	return 0;
}

