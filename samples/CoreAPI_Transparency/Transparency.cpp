#include "../../include/SWEngine.h"

#pragma comment (lib,"../../lib/SWUtil.lib")    
#pragma comment (lib,"../../lib/SWTypes.lib")    
#pragma comment (lib,"../../lib/SWCore.lib")    
#pragma comment (lib,"../../lib/SWEngine.lib")    


swApplication transparencyApp;
swPoint elipsCenter={400,300};
swDimension elipsDim={300,100};


//-------------------------------------------------------------------------------------------
void GameLoop(){ 

	swGraphicsBeginScene();

	//Background
	swGraphicsSetBgColor0(0.6f,0.6f,0.6f);

	//BlendingMode
	swGraphicsSetBlendingMode(SW_BLENDING_MODE_ADDITIVE);

	//Draw Elips
	swGraphicsSetColor0(0,1,0,0.5);
	swGraphicsRenderSolidElips2(&elipsCenter,&elipsDim,30,0);

	swGraphicsSetColor0(1,0,0,0.5);
	swGraphicsRenderSolidElips2(&elipsCenter,&elipsDim,30,60);

	swGraphicsSetColor0(0,0,1,0.5);
	swGraphicsRenderSolidElips2(&elipsCenter,&elipsDim,30,120);

	swGraphicsEndScene();

}





//-------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{ 


	//Application Settings
	transparencyApp.hInstance=hInstance;
	transparencyApp.fullScreen=false;
	transparencyApp.cursor=true;
	transparencyApp.width=800;
	transparencyApp.height=600;
	transparencyApp.title="Transparency";
	transparencyApp.path="resource";
	transparencyApp.appRun=GameLoop;

	//Application Execution
	swEngineInit(&transparencyApp);
	swEngineRun();
	swEngineExit();

	return 0;
}