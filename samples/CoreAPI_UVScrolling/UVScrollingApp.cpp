#include "../../include/SWEngine.h"

#pragma comment (lib,"../../lib/SWUtil.lib")    
#pragma comment (lib,"../../lib/SWTypes.lib")    
#pragma comment (lib,"../../lib/SWCore.lib")    
#pragma comment (lib,"../../lib/SWEngine.lib")    


swApplication uvScrollingApp;
int bgScrollImgID,defenderImgID;

//Img1 Setting
swRect target={0,0,1024,256};
swRect target2={200,200,64,32};
swRect source={0,0,1,1};
int  timerID=-1;



//-------------------------------------------------------------------------------------------
void UScrolling(void *obj){ 

	source.x+=0.1;
	if(source.x>=1.0)
		source.x=0;

}


//-------------------------------------------------------------------------------------------
void VScrolling(void *obj){ 

	source.y+=0.01;
	if(source.y>=1.0)
		source.y=0;

}


//-------------------------------------------------------------------------------------------
void GameLoop(){ 

	swGraphicsBeginScene();

	//Background
	swGraphicsSetBgColor0(0,0,0.6);

	//BlendingMode
	swGraphicsSetBlendingMode(SW_BLENDING_MODE_SOLID);

	//Draw BgScrolling Img
	swGraphicsSetColor0(1,1,1,1);
	swGraphicsRenderImg2(bgScrollImgID,&target,&source);	
	swGraphicsRenderImg2(defenderImgID,&target2,&SW_SPRITE_SOURCE_MIRRORY);

	swGraphicsEndScene();

}



//-------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd){ 

	//Application Settings
	uvScrollingApp.hInstance=hInstance;
	uvScrollingApp.fullScreen=false;
	uvScrollingApp.cursor=true;
	uvScrollingApp.width=800;
	uvScrollingApp.height=600;
	uvScrollingApp.title="UVScrolling";
	uvScrollingApp.path="\\rsc\\UVScrolling\\";
	uvScrollingApp.appRun=GameLoop;

	//Application Execution
	swEngineInit(&uvScrollingApp);

	timerID=swTimerCreate(0.2,NULL,UScrolling);
	swTimerStart(timerID);

	//Init My Application
	bgScrollImgID=swGraphicsCreateImg("mountBg.tga");
	defenderImgID=swGraphicsCreateImg("defender.tga");
	swGraphicsSetImgUVScrollable(bgScrollImgID,true);
	swEngineRun();
	swEngineExit();

	return 0;
}