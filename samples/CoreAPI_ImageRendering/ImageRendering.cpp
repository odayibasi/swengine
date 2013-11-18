#include "../../include/SWEngine.h"

#pragma comment (lib,"../../lib/SWUtil.lib")    
#pragma comment (lib,"../../lib/SWTypes.lib")    
#pragma comment (lib,"../../lib/SWCore.lib")    
#pragma comment (lib,"../../lib/SWEngine.lib")    


swApplication imgRenderingApp;
int tgaID;
int jpgID;
int pngID;
int bmpID;

swRect target1={100,100,100,100};
swRect target2={100,300,100,100};
swRect target3={100,500,100,100};
swRect target4={300,100,100,100};


//Img3 Setting
swRect source={1,1,-1,-1};
swPoint weight={0.5,0.5};

//-------------------------------------------------------------------------------------------
void GameLoop(){ 

	swGraphicsBeginScene();

	//Background
	swGraphicsSetBgColor0(0,0,0.6);

	//BlendingMode
	swGraphicsSetBlendingMode(SW_BLENDING_MODE_SOLID);

	//Draw Image
	swGraphicsSetColor0(1,1,1,1);
	swGraphicsRenderImg0(tgaID,&target1);
	swGraphicsRenderImg0(bmpID,&target2);
	swGraphicsRenderImg0(jpgID,&target3);
	swGraphicsRenderImg0(pngID,&target4);



	swGraphicsEndScene();

}





//-------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{ 


	//Application Settings
	imgRenderingApp.hInstance=hInstance;
	imgRenderingApp.fullScreen=false;
	imgRenderingApp.cursor=true;
	imgRenderingApp.width=800;
	imgRenderingApp.height=600;
	imgRenderingApp.title="Image Rendering";
	imgRenderingApp.path="\\rsc\\ImgRendering\\";
	imgRenderingApp.appRun=GameLoop;

	//Application Execution
	swEngineInit(&imgRenderingApp);

	//Init My Application
	tgaID=swGraphicsCreateImg("Smurf.tga");
	jpgID=swGraphicsCreateImg("Smurf.jpg");
	pngID=swGraphicsCreateImg("Smurf.png");
	bmpID=swGraphicsCreateImg("Smurf.bmp");

	swEngineRun();
	swEngineExit();

	return 0;
}