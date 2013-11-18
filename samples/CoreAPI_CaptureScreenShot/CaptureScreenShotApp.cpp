#include "../../include/SWEngine.h"

#pragma comment (lib,"../../lib/SWUtil.lib")    
#pragma comment (lib,"../../lib/SWTypes.lib")    
#pragma comment (lib,"../../lib/SWCore.lib")    
#pragma comment (lib,"../../lib/SWEngine.lib")    


swApplication captureSSApp;
int renderCount=0;

//-------------------------------------------------------------------------------------------
void GameLoop(){ 



	swGraphicsBeginScene();
		swGraphicsSetColor0(1,1,1,0);

		//Draw Line
		swGraphicsRenderLine0(300,300,500,500,4);	
		swGraphicsRenderLine0(500,300,300,500,4);

		//DrawElips
		swGraphicsRenderSolidElips0(400,400,200,150,60);


		//DrawRect
		swGraphicsRenderLineRect0(400,100,100,100,2);

		//DrawPolygon
		swPoint pointS[3]={{600,100},{700,100},{650,150}};
		swGraphicsRenderLinePolygon0(3,pointS,2);	

		renderCount++;
		if(renderCount==5){
		    swSystemCaptureScreen("xx.tga",SW_IMGTYPE_TGA);    
		}


	swGraphicsEndScene();

}





//-------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{ 


	//Application Settings
	captureSSApp.hInstance=hInstance;
	captureSSApp.fullScreen=false;
	captureSSApp.cursor=true;
	captureSSApp.width=800;
	captureSSApp.height=600;
	captureSSApp.title="Capture Rendering";
	captureSSApp.path="\\rsc\\CaptureScreen\\";
	captureSSApp.appRun=GameLoop;

	//Application Execution
	swEngineInit(&captureSSApp);
	swEngineRun();
	swEngineExit();

	return 0;
}