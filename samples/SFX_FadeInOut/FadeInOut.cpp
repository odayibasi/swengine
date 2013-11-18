#include "../../include/SWEngine.h"

#pragma comment (lib,"../../lib/SWUtil.lib")    
#pragma comment (lib,"../../lib/SWTypes.lib")    
#pragma comment (lib,"../../lib/SWCore.lib")    
#pragma comment (lib,"../../lib/SWEngine.lib")    
#pragma comment (lib,"../../lib/SWGame.lib")    
#pragma comment (lib,"../../lib/SWGui.lib")    
#pragma comment (lib,"../../lib/SWServices.lib")    


swApplication fadeInOutApp;

//
int logoID=-1;
swRect logoTarget={360,260,93,135};
int windowID=-1;
int windowTexID=-1;
swRect window={0,0,800,600};
float  alpha=0;
int    alphaModifier=-1;

//-------------------------------------------------------------------------------------------
void GameLoop(){ 


	swValueModifierExecute(alphaModifier,0.015);	
	swGraphicsBeginScene();

		//Active Rendering Target
		swGraphicsSetRenderingTarget(windowID);		
			swGraphicsSetBgColor0(0,0,0);
			swGraphicsSetColor0(1,1,1,0.5);
			swGraphicsRenderImg0(logoID,&logoTarget);
       
	   //FrameBuffer Active 
	   swGraphicsSetRenderingTarget(SW_RENDERING_TARGET_DEFAULT);	
			swGraphicsSetBgColor0(0,0,0);
			swGraphicsSetBlendingMode(SW_BLENDING_MODE_ADDITIVE);
			swGraphicsSetColor0(alpha,alpha,alpha,1);
			swGraphicsRenderImg0(windowTexID,&window);

	swGraphicsEndScene();


}





//-------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{ 


	//Application Settings
	fadeInOutApp.hInstance=hInstance;
	fadeInOutApp.fullScreen=false;
	fadeInOutApp.cursor=true;
	fadeInOutApp.width=800;
	fadeInOutApp.height=600;
	fadeInOutApp.title="FadeInOut";
	fadeInOutApp.path="\\rsc\\FadeInOut\\";
	fadeInOutApp.appRun=GameLoop;

	//Application Execution
	swEngineInit(&fadeInOutApp);

	//Init My Application
	logoID=swGraphicsCreateImg("swLogo.tga");
	windowID=swGraphicsCreateRenderingTarget(800,600,4); //Define New RenderingTarget 
	windowTexID=swGraphicsRenderingTargetGetImgID(windowID);	

	alphaModifier=swValueModifierCreate(SW_VALUE_MODIFIER_010_LOOP,&alpha,0,1,0.2,0);


	swEngineRun();
	swEngineExit();

	return 0;
}