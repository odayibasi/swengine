#include "SWEngineIn.h"


bool bSWEngineExitFlag=false;
swApplication *swApp=NULL;




//-------------------------------------------------------------------------------------------
DllExport void swEngineExit(){
	bSWEngineExitFlag=true;
}



//-------------------------------------------------------------------------------------------
DllExport bool swEngineInit(swApplication *app){
	
	swApp=app;
	swWindowInit(app->hInstance,app->icon);
	swWindowSetCloseListener(swEngineExit);
	HWND hwnd=swWindowCreate(app->title,app->width,app->height,app->fullScreen,app->cursor);
	if(hwnd==NULL)
		return false;

	if(!swWindowSetUpPixelFormat(swWindowGetDC(),32,0,0,0))
		return false;

	swFileSystemInit();
	swFileSystemSetResourcePath(app->path);


	swGraphicsInit();
	swAudioInit();
	swInputInit();
	swSystemInit();
	swTimerInit();
	swDestroyManagerInit();
	swScheduledManagerInit();
	swDispManagerInit();
	swExecManagerInit();
	swInteractionManagerInit();
	swKeybBehaviourInit();
	swMousBehaviourInit();
	swDSLInit();
	swPersistManagerInit();
	swConsoleInit();
	swAnimatorInit();
	swLinkerInit();
	swInterpolaterInit();
	swValueModifierInit();
	swGuiInit();
	return true;
}


//-------------------------------------------------------------------------------------------
DllExport void swEngineRun(){
void (*ptAppFuncRun)();	
	MSG Msg;
	while(!bSWEngineExitFlag){
		if(!swWindowPeekMsg(&Msg) && swWindowIsActive()){
			swSystemUpdate();
			swTimerTick(swSystemGetElapsedSeconds());
		    swAudioUpdate();
			ptAppFuncRun=swApp->appRun;
			(*ptAppFuncRun)();
		}
	}

	//ExitEngine
	swGuiDeInit();
	swLinkerDeInit();
	swAnimatorDeInit();
	swInterpolaterDeInit();
	swValueModifierDeInit();
	swConsoleDeInit();
	swDSLDeInit();
	swPersistManagerDeInit();
	swMousBehaviourDeInit();
	swKeybBehaviourDeInit();
	swInteractionManagerDeInit();
	swScheduledManagerDeInit();
	swExecManagerDeInit();
	swDispManagerDeInit();
	swDestroyManagerDeInit();
	swTimerDeInit();
	swInputDeInit();
	swAudioInit();
	swGraphicsDeInit();
	swWindowDeInit(); 
	exit(0);

}


