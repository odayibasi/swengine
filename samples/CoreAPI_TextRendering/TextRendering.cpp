#include "../../include/SWEngine.h"

#pragma comment (lib,"../../lib/SWUtil.lib")    
#pragma comment (lib,"../../lib/SWTypes.lib")    
#pragma comment (lib,"../../lib/SWCore.lib")    
#pragma comment (lib,"../../lib/SWEngine.lib")    


swApplication textRenderingApp;
int fontID;

//-------------------------------------------------------------------------------------------
void GameLoop(){ 

	swGraphicsBeginScene();

	//Background
	swGraphicsSetBgColor0(0,0,0.6);

	//BlendingMode
	swGraphicsSetBlendingMode(SW_BLENDING_MODE_ADDITIVE);

	//Draw Text
	swGraphicsSetColor0(1,0,0,1);
	swGraphicsRenderText(fontID,1,20,200,200,0,"Hello World");
	swGraphicsSetColor0(1,1,1,1);
	swGraphicsRenderText(fontID,0,16,200,240,0,"string=%s int=%i float=%1.1f ","SkyWar",5,10.0f);
	swGraphicsRenderText(fontID,1,20,300,250,0,"SkyWar");
	swGraphicsRenderText(fontID,1,20,300,250,30,"SkyWar");
	swGraphicsRenderText(fontID,1,20,300,250,40,"SkyWar");
	swGraphicsEndScene();

}





//-------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{ 


	//Application Settings
	textRenderingApp.hInstance=hInstance;
	textRenderingApp.fullScreen=false;
	textRenderingApp.cursor=true;
	textRenderingApp.width=800;
	textRenderingApp.height=600;
	textRenderingApp.title="Image Rendering";
	textRenderingApp.path="\\rsc\\TextRendering\\";
	textRenderingApp.appRun=GameLoop;

	//Application Execution
	swEngineInit(&textRenderingApp);

	//Init My Application
	fontID=swGraphicsCreateFont("Font.tga");

	swEngineRun();
	swEngineExit();

	return 0;
}