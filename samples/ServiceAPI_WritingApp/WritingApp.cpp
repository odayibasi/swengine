#include "../../include/SWEngine.h"

#pragma comment (lib,"../../lib/SWUtil.lib")    
#pragma comment (lib,"../../lib/SWTypes.lib")    
#pragma comment (lib,"../../lib/SWCore.lib")    
#pragma comment (lib,"../../lib/SWServices.lib")   
#pragma comment (lib,"../../lib/SWEngine.lib")   


swApplication writingApp;
int fontID;
char str[99];
int  char_counter=0;
swKeyboardState keybState;
swKeybBehaviourListener keyListener;

//-------------------------------------------------------------------------------------------
void listenKeybForWriting(char c){
	if(char_counter<99){
		str[char_counter]=c;
		str[char_counter+1]='\0';
		char_counter++;
	}
}


//-------------------------------------------------------------------------------------------
void GameLoop(){ 

	swInputListenKeyboard(&keybState);
	swKeybBehaviourExecute(&keybState);

	swGraphicsBeginScene();

		//Background
		swGraphicsSetBgColor0(0,0,0.6);

		//BlendingMode
		swGraphicsSetBlendingMode(SW_BLENDING_MODE_ADDITIVE);

		//Draw Text
		swGraphicsSetColor0(1,0,0,1);
		swGraphicsRenderText(fontID,1,20,200,200,0,str);
	swGraphicsEndScene();
}





//-------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{ 


	//Application Settings
	writingApp.hInstance=hInstance;
	writingApp.fullScreen=false;
	writingApp.cursor=true;
	writingApp.width=800;
	writingApp.height=600;
	writingApp.title="Writing App";
	writingApp.path="\\rsc\\WritingApp\\";
	writingApp.appRun=GameLoop;

	//Application Execution
	swEngineInit(&writingApp);


	//Init My Application
	fontID=swGraphicsCreateFont("Font.tga");
	keyListener.typed=listenKeybForWriting;
	keyListener.pressed=NULL;
	keyListener.released=NULL;
	swKeybBehaviourAdd(&keyListener);

	swEngineRun();
	swEngineExit();

	return 0;
}