#include "../../include/SWEngine.h"

#pragma comment (lib,"../../lib/SWUtil.lib")    
#pragma comment (lib,"../../lib/SWTypes.lib")    
#pragma comment (lib,"../../lib/SWCore.lib")    
#pragma comment (lib,"../../lib/SWEngine.lib")    
#pragma comment (lib,"../../lib/SWGame.lib")    
#pragma comment (lib,"../../lib/SWGui.lib")    


swApplication interpolationApp;
float alpha=0;
int   interpID=-1;


//-------------------------------------------------------------------------------------------
void GameLoop(){ 

	swGraphicsBeginScene();


	//Background
	swGraphicsSetBgColor0(0.6f,0.6f,0.6f);


	//5gen
	swGraphicsSetColor0(0.3,0.2,0.8,alpha);
	swGraphicsSetBlendingMode(SW_BLENDING_MODE_SOLID);
	alpha=swInterpolaterGetValue(interpID);
	swGraphicsRenderSolidElips0(300,300,200,200,5);
	swGraphicsEndScene();

}





//-------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{ 


	//Application Settings
	interpolationApp.hInstance=hInstance;
	interpolationApp.fullScreen=false;
	interpolationApp.cursor=true;
	interpolationApp.width=800;
	interpolationApp.height=600;
	interpolationApp.title="Interpolation";
	interpolationApp.path="";
	interpolationApp.appRun=GameLoop;

	//Application Execution
	swEngineInit(&interpolationApp);
	
	//Init Application
	interpID=swInterpolaterCreate(0,1,10);
	swInterpolaterStart(interpID);

	swEngineRun();
	swEngineExit();

	return 0;
}