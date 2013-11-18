#include "../../include/SWEngine.h"

#pragma comment (lib,"../../lib/SWUtil.lib")    
#pragma comment (lib,"../../lib/SWTypes.lib")    
#pragma comment (lib,"../../lib/SWCore.lib")    
#pragma comment (lib,"../../lib/SWEngine.lib")    


swApplication glowFXApp;
int imgID,imgID2;
swRect target={200,200,32,32};
swRect target2={260,240,128,128};

//-------------------------------------------------------------------------------------------
void GameLoop(){ 

	swGraphicsBeginScene();

	//Background
	swGraphicsSetBgColor0(0,0,0);

		//BlendingMode
		swGraphicsSetBlendingMode(SW_BLENDING_MODE_ADDITIVE);

		//Draw Image
		swGraphicsSetColor0(1,1,1,0.4);
		swGraphicsRenderImg0(imgID,&target);
		swGraphicsRenderImg0(imgID2,&target2);
	swGraphicsEndScene();

}





//-------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{ 


	//Application Settings
	glowFXApp.hInstance=hInstance;
	glowFXApp.fullScreen=false;
	glowFXApp.cursor=true;
	glowFXApp.width=800;
	glowFXApp.height=600;
	glowFXApp.title="Glow FX";
	glowFXApp.path="\\rsc\\GlowFX\\";
	glowFXApp.appRun=GameLoop;

	//Application Execution
	swEngineInit(&glowFXApp);

	//Init My Application
	imgID=swGraphicsCreateImg("Glow1.tga");
	imgID2=swGraphicsCreateImg("Yz.tga");

	swEngineRun();
	swEngineExit();

	return 0;
}