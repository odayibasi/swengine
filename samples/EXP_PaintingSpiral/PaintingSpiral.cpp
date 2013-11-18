#include "../../include/SWEngine.h"
#include <math.h>

#pragma comment (lib,"../../lib/SWUtil.lib")    
#pragma comment (lib,"../../lib/SWTypes.lib")    
#pragma comment (lib,"../../lib/SWCore.lib")    
#pragma comment (lib,"../../lib/SWEngine.lib")    


swApplication paintingSpiralApp;
swPoint center={400,300};
swRect	screenRect={0,0,800,600};
int rendTargID=-1;
int imgID=-1;
int timerID;
float radious=1;
float angle=0;
float dx,dy;


//-------------------------------------------------------------------------------------------
void paintSpiral(void *obj){
	radious+=0.5;
	angle=angle+5;
	dx=swMathCos(angle)*radious;
	dy=swMathSin(angle)*radious;
}


//-------------------------------------------------------------------------------------------
void GameLoop(){ //This function triggered when 1 frame process end Independent Time


	//Display Scene	
	swGraphicsBeginScene();

	//Active Rendering Target
	swGraphicsSetRenderingTarget(rendTargID);	

	swGraphicsSetBlendingMode(SW_BLENDING_MODE_ADDITIVE);
	swGraphicsSetBgColor0(0.0f,0.0f,0.0f);
	swGraphicsSetColor0(swMathRandomFloat(0,1),swMathRandomFloat(0,1),swMathRandomFloat(0,1),0.6);
	swGraphicsRenderPoint0(center.x+dx,center.y+dy,swMathRandomFloat(3,7));

	if(!swIntersectionRectAndPoint2(&screenRect,center.x+dx,center.y+dy)){
		swTimerStop(timerID);
	}



	//Active FrameBuffer	
	swGraphicsSetRenderingTarget(SW_RENDERING_TARGET_DEFAULT);
	swGraphicsSetBgColor0(0.0f,0.0f,0.0f);
	swGraphicsSetColor0(1,1,1,0.5);
	swGraphicsRenderImg0(imgID,&screenRect);




	swGraphicsEndScene();
}


//-------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{ 

	//Application Settings
	paintingSpiralApp.hInstance=hInstance;
	paintingSpiralApp.fullScreen=false;
	paintingSpiralApp.cursor=true;
	paintingSpiralApp.width=800;
	paintingSpiralApp.height=600;
	paintingSpiralApp.title="Painting Sprial";
	paintingSpiralApp.path="resource";
	paintingSpiralApp.appRun=GameLoop;

	//Application Execution
	//Init SWEngine
	swEngineInit(&paintingSpiralApp);

	//Init My Application
	timerID=swTimerCreate(0.05f,NULL,paintSpiral);


	rendTargID=swGraphicsCreateRenderingTarget(800,600,3); //Define New RenderingTarget 
	imgID=swGraphicsRenderingTargetGetImgID(rendTargID); //Get ImgID  

	swEngineRun();
	swEngineExit();

	return 0;
}