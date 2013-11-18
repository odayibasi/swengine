#include "../../include/SWEngine.h"

#pragma comment (lib,"../../lib/SWUtil.lib")    
#pragma comment (lib,"../../lib/SWTypes.lib")    
#pragma comment (lib,"../../lib/SWCore.lib")    
#pragma comment (lib,"../../lib/SWEngine.lib")   
#pragma comment (lib,"../../lib/SWGame.lib")   



swApplication animatorTestApp;
int spriteID=-1;
int animatorID=-1;


//Img1 Setting
swRect target1={200,200,125,154};
swKeyboardState keybState;

//-------------------------------------------------------------------------------------------
void GameLoop(){ 

	swInputListenKeyboard(&keybState);

	if(keybState.keyLEFT)
		swAnimatorSetExecutionMode(animatorID,SW_ANIMATOR_EXEC_BACKWARD_LOOP);
	else if(keybState.keyRIGHT)
		swAnimatorSetExecutionMode(animatorID,SW_ANIMATOR_EXEC_FORWARD_LOOP);
		

	if(keybState.key1)
		swAnimatorSetDelay(animatorID,0.01f);
	else if(keybState.key2)
		swAnimatorSetDelay(animatorID,0.02f);
	else if(keybState.key3)
		swAnimatorSetDelay(animatorID,0.03f);
	else if(keybState.key4)
		swAnimatorSetDelay(animatorID,0.04f);
	else if(keybState.key5)
		swAnimatorSetDelay(animatorID,0.05f);
	else if(keybState.key6)
		swAnimatorSetDelay(animatorID,0.06f);
	else if(keybState.key7)
		swAnimatorSetDelay(animatorID,0.07f);
	else if(keybState.key8)
		swAnimatorSetDelay(animatorID,0.08f);
	else if(keybState.key9)
		swAnimatorSetDelay(animatorID,0.09f);




	//Display	
	swGraphicsBeginScene();

	//Background
	swGraphicsSetBgColor2(&SWCOLOR_GRAY);

	//BlendingMode
	swGraphicsSetBlendingMode(SW_BLENDING_MODE_SOLID);

	//Draw Image
	swGraphicsSetColor0(1,1,1,1);
	swGraphicsRenderSprite0(spriteID,swAnimatorGetIndex(animatorID),&target1);
	swGraphicsEndScene();

}





//-------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{ 


	//Application Settings
	animatorTestApp.hInstance=hInstance;
	animatorTestApp.fullScreen=false;
	animatorTestApp.cursor=true;
	animatorTestApp.width=800;
	animatorTestApp.height=600;
	animatorTestApp.title="Animator Test";
	animatorTestApp.path="\\rsc\\AnimatorTest\\";
	animatorTestApp.appRun=GameLoop;

	//Application Execution
	swEngineInit(&animatorTestApp);

	//Init My Application
	spriteID=swGraphicsCreateSprite("XenRunning\\");
	animatorID=swAnimatorCreate(swGraphicsGetCountOfImgInSprite(spriteID),0.03f);
	swAnimatorSetExecutionMode(animatorID,SW_ANIMATOR_EXEC_BACKWARD_LOOP);

	swEngineRun();
	swEngineExit();

	return 0;
}