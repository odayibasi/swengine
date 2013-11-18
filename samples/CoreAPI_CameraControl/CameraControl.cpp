#include "../../include/SWEngine.h"

#pragma comment (lib,"../../lib/SWUtil.lib")    
#pragma comment (lib,"../../lib/SWTypes.lib")    
#pragma comment (lib,"../../lib/SWCore.lib")    
#pragma comment (lib,"../../lib/SWEngine.lib")    


swApplication camControlApp;
swPoint elipsCenter={400,300};
swDimension elipsDim={300,100};
swKeyboardState keybState;
swMouseState    mousState;
int             camID;


//-------------------------------------------------------------------------------------------
void GameLoop(){ 

	
	//Input Handling
	swInputListenKeyboard(&keybState);
	swInputListenMouse(&mousState);
	if(keybState.keyESCAPE){
		swEngineExit();
	}

	if(keybState.keyLEFT)
		swGraphicsAddCamPosX(camID,-2);
	
	if(keybState.keyRIGHT)
		swGraphicsAddCamPosX(camID,2);

	if(keybState.keyUP)
		swGraphicsAddCamPosY(camID,2);

	if(keybState.keyDOWN)
		swGraphicsAddCamPosY(camID,-2);


	if(keybState.key1)
		swGraphicsAddCamZoom(camID,0.1);

	if(keybState.key2)
		swGraphicsAddCamZoom(camID,-0.1);


	if(mousState.btnLEFT)
		swGraphicsAddCamRot(camID,2);
	
	if(mousState.btnRIGHT)
		swGraphicsAddCamRot(camID,-2);


	swGraphicsBeginScene();
		swGraphicsActiveCam(camID);

		//Background
		swGraphicsSetBgColor0(0.6f,0.6f,0.6f);

		//BlendingMode
		swGraphicsSetBlendingMode(SW_BLENDING_MODE_ADDITIVE);

		//Draw Elips
		swGraphicsSetColor0(0,1,0,0.5);
		swGraphicsRenderSolidElips2(&elipsCenter,&elipsDim,30,0);

		swGraphicsSetColor0(1,0,0,0.5);
		swGraphicsRenderSolidElips2(&elipsCenter,&elipsDim,30,60);

		swGraphicsSetColor0(0,0,1,0.5);
		swGraphicsRenderSolidElips2(&elipsCenter,&elipsDim,30,120);

	swGraphicsEndScene();

}





//-------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{ 


	//Application Settings
	camControlApp.hInstance=hInstance;
	camControlApp.fullScreen=false;
	camControlApp.cursor=true;
	camControlApp.width=800;
	camControlApp.height=600;
	camControlApp.title="Camera Control";
	camControlApp.path="";
	camControlApp.appRun=GameLoop;

	//Application Execution
	swEngineInit(&camControlApp);
	
	//Create Cam
	camID=swGraphicsCreateCam();

	swEngineRun();
	swEngineExit();

	return 0;
}