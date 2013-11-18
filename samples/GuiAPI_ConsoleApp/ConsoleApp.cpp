#include "../../include/SWEngine.h"

#pragma comment (lib,"../../lib/SWUtil.lib")    
#pragma comment (lib,"../../lib/SWTypes.lib")    
#pragma comment (lib,"../../lib/SWCore.lib")    
#pragma comment (lib,"../../lib/SWServices.lib")   
#pragma comment (lib,"../../lib/SWGame.lib")    
#pragma comment (lib,"../../lib/SWGui.lib")    
#pragma comment (lib,"../../lib/SWEngine.lib")   


swApplication consoleApp;
swKeyboardState keybState;
swMouseState mousState;
swPoint      point={300,400};
bool		 bVisb=true;


//-------------------------------------------------------------------------------------------
void GameLoop(){ 

	//Listen Input
	swInputListenKeyboard(&keybState);
	swInputListenMouse(&mousState);

	//Execute Services
	swKeybBehaviourExecute(&keybState);
	swInteractionManagerExecute(&keybState,&mousState);


	swGraphicsBeginScene();

		//Background
		swGraphicsSetBgColor0(0,0,0.6);
		swDispManagerExecute();
		if(bVisb){
			swGraphicsSetColor1(&SWCOLOR_RED);
			swGraphicsRenderPoint1(&point,20);
		}
	swGraphicsEndScene();
}


//-------------------------------------------------------------------------------------------
void ExitApp(int countArgs,swArg* argS){
	swEngineExit();
}

//-------------------------------------------------------------------------------------------
void MoveItem(int countArgs,swArg* argS){
	point.x=argS[0].arg.fVal;
	point.y=argS[1].arg.fVal;
	swConsolePrint("Item move to x=%0.0f y=%0.0f position",point.x,point.y);
}


//-------------------------------------------------------------------------------------------
void VisbItem(int countArgs,swArg* argS){
	bVisb=argS[0].arg.bVal;
	if(bVisb)
		swConsolePrint("Item show");
	else
		swConsolePrint("Item hide");
}


//-------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{ 


	//Application Settings
	consoleApp.hInstance=hInstance;
	consoleApp.fullScreen=false;
	consoleApp.cursor=true;
	consoleApp.width=800;
	consoleApp.height=600;
	consoleApp.title="Console App";
	consoleApp.path="\\rsc\\ConsoleApp\\";
	consoleApp.appRun=GameLoop;

	//Application Execution
	swEngineInit(&consoleApp);



	//Init My Application
	swDispManagerSetLayerCount(11);
	swKeybBehaviourSetTypedSleepTime(0.15);

	int fontID=swGraphicsCreateFont("Font.tga");

	swConsoleSetBgColor(&SWCOLOR_BLACK);
	swConsoleSetFont(fontID,1,&SWCOLOR_WHITE,12);
	swConsoleSetLayer(10);
	swConsoleSetPos(100,100);
	swConsoleSetSize(600,200);
	swConsoleSetVisible(true);

	swDSLRegisterCommand(ExitApp,"exit",0,NULL);


	swArg argS[2];
	argS[0].type=SW_ARG_FLOAT;
	argS[1].type=SW_ARG_FLOAT;
	swDSLRegisterCommand(MoveItem,"move",2,argS);


	swArg argS2[2];
	argS2[0].type=SW_ARG_BOOL;
	swDSLRegisterCommand(VisbItem,"visb",1,argS2);

	swEngineRun();
	swEngineExit();

	return 0;
}