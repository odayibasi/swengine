//SWEngine
#include "../../include/SWEngine.h"

#pragma comment (lib,"../../lib/SWUtil.lib")    
#pragma comment (lib,"../../lib/SWTypes.lib")    
#pragma comment (lib,"../../lib/SWCore.lib")    
#pragma comment (lib,"../../lib/SWEngine.lib")    


swApplication pointSpriteApp;
int pointSpriteID=-1;

swPoint pointS[3];
swColor colorS[3];



//-------------------------------------------------------------------------------------------
void GameLoop(){ 

	swGraphicsBeginScene();
	swGraphicsSetBlendingMode(SW_BLENDING_MODE_ADDITIVE_ACCORDING2_ALPHA);
	swGraphicsRenderPointSprite0(pointSpriteID,60,3,colorS,pointS);
	swGraphicsEndScene();

}


//-------------------------------------------------------------------------------------------
void GameInit(){ 
    pointSpriteID=swGraphicsCreatePointSprite("particleX.tga");
	pointS[0].x=100; pointS[0].y=100;
	colorS[0].r=0.2; colorS[0].g=0.8; colorS[0].b=0.8; colorS[0].a=0.5;

	pointS[1].x=300; pointS[1].y=300;
	colorS[1].r=0.8; colorS[1].g=0.8; colorS[1].b=0.8; colorS[1].a=1;

	pointS[2].x=500; pointS[2].y=500;
	colorS[2].r=1.0; colorS[2].g=0.1; colorS[2].b=0.1; colorS[2].a=1;


}


//-------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{ 


	//Application Settings
	pointSpriteApp.hInstance=hInstance;
	pointSpriteApp.fullScreen=false;
	pointSpriteApp.cursor=true;
	pointSpriteApp.width=800;
	pointSpriteApp.height=600;
	pointSpriteApp.title="Point Sprite";
	pointSpriteApp.path="\\rsc\\PointSprites\\";
	pointSpriteApp.appRun=GameLoop;


	//Application Execution
	swEngineInit(&pointSpriteApp);
	GameInit();	
	swEngineRun();
	swEngineExit();

	return 0;
}