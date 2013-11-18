#include "XenCull.h"

swApplication dispCullingApp;
int fontID=-1;


//-------------------------------------------------------------------------------------------
void GameLoop(){ 
	swGraphicsBeginScene();
	swGraphicsSetBgColor2(&SWCOLOR_GRAY);
	swDispManagerExecute();

	swGraphicsSetBlendingMode(SW_BLENDING_MODE_ADDITIVE);
	swGraphicsRenderText(fontID,2,25,200,240,0,"All Xen=%i Rendered Xen=%i",swDispManagerSizeOfAll(),	swDispManagerSizeOfRendered());
	swGraphicsEndScene();
}



//-------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{ 


	//Application Settings
	dispCullingApp.hInstance=hInstance;
	dispCullingApp.fullScreen=false;
	dispCullingApp.cursor=true;
	dispCullingApp.width=800;
	dispCullingApp.height=600;
	dispCullingApp.title="Culling";
	dispCullingApp.path="\\rsc\\DisplayCulling\\";
	dispCullingApp.appRun=GameLoop;

	//Application Execution
	swEngineInit(&dispCullingApp);

	//Init My Application
	swDispManagerSetCullRegion(0,0,700,500);

	fontID=swGraphicsCreateFont("Font.tga");
	xenInit();
	for(int i=0;i<25;i++){
		for(int j=0;j<25;j++){
			Xen *xen=xenCreate();
			xen->target.x=i*80;
			xen->target.y=j*120;
		}
	}


	swEngineRun();
	swEngineExit();

	return 0;
}
