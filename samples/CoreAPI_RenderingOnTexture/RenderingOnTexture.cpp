#include "../../include/SWEngine.h"

#pragma comment (lib,"../../lib/SWUtil.lib")    
#pragma comment (lib,"../../lib/SWTypes.lib")    
#pragma comment (lib,"../../lib/SWCore.lib")    
#pragma comment (lib,"../../lib/SWEngine.lib")    


swApplication rendOnTexApp;
swPoint elipsCenter={400,300};
swDimension elipsDim={300,100};
float rot2=0;
float rot3=0;

int rendTargID=-1;
int imgID=-1;
swRect rect={0,0,200,150};
swRect rect2={100,100,300,300};
swRect rect3={250,150,400,400};



//-------------------------------------------------------------------------------------------
void rotateSecondElips(void *obj){ //This function triggered 0,05 seconds..
	rot2+=10;  
}

//-------------------------------------------------------------------------------------------
void rotateThirdElips(void *obj){ //This function triggered 1 seconds
	rot3-=10;
}


//-------------------------------------------------------------------------------------------
void GameLoop(){ //This function triggered when 1 frame process end Independent Time


	//Display Scene	
	swGraphicsBeginScene();

		//Active Rendering Target
		swGraphicsSetRenderingTarget(rendTargID);	
		swGraphicsClearRenderingTarget();
			
		//Background
		swGraphicsSetBgColor0(0.6f,0.6f,0.6f);
		
		//BlendingMode
		swGraphicsSetBlendingMode(SW_BLENDING_MODE_ADDITIVE);

		//Draw Elips
		swGraphicsSetColor0(0,1,0,0.5);
		swGraphicsRenderSolidElips2(&elipsCenter,&elipsDim,30,0);

		swGraphicsSetColor0(1,0,0,0.5);
		swGraphicsRenderSolidElips2(&elipsCenter,&elipsDim,30,60+rot2);

		swGraphicsSetColor0(0,0,1,0.5);
		swGraphicsRenderSolidElips2(&elipsCenter,&elipsDim,30,120+rot3);


		//Active FrameBuffer	
		swGraphicsSetRenderingTarget(SW_RENDERING_TARGET_DEFAULT);
		swGraphicsSetBgColor0(0.6f,0.6f,0.6f);
		swGraphicsSetColor0(1,1,1,1);
		swGraphicsRenderImg0(imgID,&rect);
		swGraphicsRenderImg0(imgID,&rect2);
		swGraphicsRenderImg0(imgID,&rect3);



	swGraphicsEndScene();
}


//-------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{ 

	//Application Settings
	rendOnTexApp.hInstance=hInstance;
	rendOnTexApp.fullScreen=false;
	rendOnTexApp.cursor=true;
	rendOnTexApp.width=800;
	rendOnTexApp.height=600;
	rendOnTexApp.title="Rendering On Texture";
	rendOnTexApp.path="resource";
	rendOnTexApp.appRun=GameLoop;

	//Application Execution
	//Init SWEngine
	swEngineInit(&rendOnTexApp);

	//Init My Application
	int secondTimer=swTimerCreate(0.05f,NULL,rotateSecondElips);
	int thirdTimer=swTimerCreate(1.0f,NULL,rotateThirdElips);
	
	
	rendTargID=swGraphicsCreateRenderingTarget(400,300,3); //Define New RenderingTarget 
	imgID=swGraphicsRenderingTargetGetImgID(rendTargID); //Get ImgID  

	swEngineRun();
	swEngineExit();

	return 0;
}