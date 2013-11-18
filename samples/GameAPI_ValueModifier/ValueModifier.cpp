#include "../../include/SWEngine.h"

#pragma comment (lib,"../../lib/SWUtil.lib")    
#pragma comment (lib,"../../lib/SWTypes.lib")    
#pragma comment (lib,"../../lib/SWCore.lib")    
#pragma comment (lib,"../../lib/SWEngine.lib")    
#pragma comment (lib,"../../lib/SWGame.lib")    
#pragma comment (lib,"../../lib/SWGui.lib")    


swApplication loopApp;
float alpha=0;
float x=100;
int   alphaLoopID=-1;
int   xLoopID=-1;



//-------------------------------------------------------------------------------------------
void GameLoop(){ 

	swGraphicsBeginScene();


	//Background
	swGraphicsSetBgColor0(0.6f,0.6f,0.6f);


	//5gen
	swValueModifierExecute(xLoopID,0.15f);
	swValueModifierExecute(alphaLoopID,0.15f);
	swGraphicsSetColor0(0.3,0.2,0.8,alpha);
	swGraphicsSetBlendingMode(SW_BLENDING_MODE_SOLID);
	swGraphicsRenderSolidElips0(x,300,200,200,5);
	swGraphicsEndScene();

}





//-------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{ 


	//Application Settings
	loopApp.hInstance=hInstance;
	loopApp.fullScreen=false;
	loopApp.cursor=true;
	loopApp.width=800;
	loopApp.height=600;
	loopApp.title="Loop Value Modifier";
	loopApp.path="";
	loopApp.appRun=GameLoop;

	//Application Execution
	swEngineInit(&loopApp);

	//Init Application
	alphaLoopID=swValueModifierCreate(SW_VALUE_MODIFIER_010_LOOP,&alpha,0,1,0.05,0);
	xLoopID=swValueModifierCreate(SW_VALUE_MODIFIER_01_LOOP,&x,100,600,20,0);

	swEngineRun();
	swEngineExit();

	return 0;
}