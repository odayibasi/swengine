#include "../../include/SWEngine.h"

#pragma comment (lib,"../../lib/SWUtil.lib")    
#pragma comment (lib,"../../lib/SWTypes.lib")    
#pragma comment (lib,"../../lib/SWCore.lib")    
#pragma comment (lib,"../../lib/SWEngine.lib")    


swApplication colouringApp;

//-------------------------------------------------------------------------------------------
void GameLoop(){ 

	swGraphicsBeginScene();

		//Background
		swGraphicsSetBgColor0(0.6f,0.6f,0.6f);

		//Draw Point
		swGraphicsSetColor0(1,0,0,0);
		swGraphicsRenderPoint0(25,25,5);
		
		swGraphicsSetColor1(&SWCOLOR_GREEN);
		swGraphicsRenderPoint0(50,50,10);

		swGraphicsSetColor1(&SWCOLOR_BLUE);
		swGraphicsRenderPoint0(100,100,20);

		//Draw Line
		swGraphicsSetColor1(&SWCOLOR_RED);
		swGraphicsRenderLine0(300,300,500,500,4);	

		swGraphicsSetColor1(&SWCOLOR_BLUE);
		swGraphicsRenderLine0(500,300,300,500,4);

		//DrawElips
		swGraphicsSetColor1(&SWCOLOR_GREEN);
		swGraphicsRenderSolidElips0(400,400,200,150,60);


		//DrawRect
		swGraphicsSetColor1(&SWCOLOR_BLACK);
		swGraphicsRenderLineRect0(400,100,100,100,2);

		//DrawPolygon
		swGraphicsSetColor1(&SWCOLOR_WHITE);
		swPoint pointS[3]={{600,100},{700,100},{650,150}};
		swGraphicsRenderLinePolygon0(3,pointS,2);	

	swGraphicsEndScene();

}





//-------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{ 


	//Application Settings
	colouringApp.hInstance=hInstance;
	colouringApp.fullScreen=false;
	colouringApp.cursor=true;
	colouringApp.width=800;
	colouringApp.height=600;
	colouringApp.title="Colouring";
	colouringApp.path="resource";
	colouringApp.appRun=GameLoop;

	//Application Execution
	swEngineInit(&colouringApp);
	swEngineRun();
	swEngineExit();

	return 0;
}