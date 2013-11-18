#include "../../include/SWEngine.h"

#pragma comment (lib,"../../lib/SWUtil.lib")    
#pragma comment (lib,"../../lib/SWTypes.lib")    
#pragma comment (lib,"../../lib/SWCore.lib")    
#pragma comment (lib,"../../lib/SWEngine.lib")    


swApplication imgRenderingApp;
int imgID;

//Icon Setting
swRect target={200,200,20,20};
swRect source={0,0,1,1};
int    xIndex=3;
int    yIndex=3;
int    timerID=-1;

const static int XGRID_SIZE=20;
const static int YGRID_SIZE=14;



//-------------------------------------------------------------------------------------------
void switchIcon(void *obj){ //This function triggered 0,05 seconds..
	xIndex++;
	if(xIndex==XGRID_SIZE){
		xIndex=0;
		yIndex++;
	}

	if(yIndex==YGRID_SIZE){
		yIndex=0;
	}
}




//-------------------------------------------------------------------------------------------
void GameLoop(){ 

	swGraphicsBeginScene();

		//Background
		swGraphicsSetBgColor0(0,0,0.6);

		//BlendingMode
		swGraphicsSetBlendingMode(SW_BLENDING_MODE_ADDITIVE);
		swMathSourceCalculate(&source,XGRID_SIZE,YGRID_SIZE,xIndex,yIndex);

		//Draw Image
		swGraphicsSetColor0(1,1,1,0.5);
		swGraphicsRenderImg2(imgID,&target,&source);

	swGraphicsEndScene();

}


//-------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{ 


	//Application Settings
	imgRenderingApp.hInstance=hInstance;
	imgRenderingApp.fullScreen=false;
	imgRenderingApp.cursor=true;
	imgRenderingApp.width=400;
	imgRenderingApp.height=300;
	imgRenderingApp.title="Image Clipping";
	imgRenderingApp.path="\\rsc\\IconSetAccess\\";
	imgRenderingApp.appRun=GameLoop;

	//Application Execution
	swEngineInit(&imgRenderingApp);

	//Init My Application
 	imgID=swGraphicsCreateImg("IconSet.tga");
	timerID=swTimerCreate(0.2f,NULL,switchIcon);
	swEngineRun();
	swEngineExit();

	return 0;
}