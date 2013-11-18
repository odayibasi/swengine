#include "../../include/SWEngine.h"

#pragma comment (lib,"../../lib/SWUtil.lib")    
#pragma comment (lib,"../../lib/SWTypes.lib")    
#pragma comment (lib,"../../lib/SWCore.lib")    
#pragma comment (lib,"../../lib/SWEngine.lib")    


swApplication primitifRendering;

//-------------------------------------------------------------------------------------------
void GameLoop(){ 

	swGraphicsBeginScene();
		swGraphicsSetColor0(1,1,1,0);
		
        //Draw Point
		swGraphicsRenderPoint0(25,25,5);
		swGraphicsRenderPoint0(50,50,10);
		swGraphicsRenderPoint0(100,100,20);

		//Draw Line
		swGraphicsRenderLine0(300,300,500,500,4);	
		swGraphicsRenderLine0(500,300,300,500,4);
		
		//DrawElips
		swGraphicsRenderSolidElips0(400,400,200,150,60);
		

		//DrawArcs
		swGraphicsRenderSolidArcs0(700,400,200,150,4,0,50);



		//DrawRect
		swGraphicsRenderLineRect0(400,100,100,100,2);

		//DrawPolygon
		swPoint pointS[3]={{600,100},{700,100},{650,150}};
		swGraphicsRenderLinePolygon0(3,pointS,2);	

	swGraphicsEndScene();

}





//-------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{ 


	//Application Settings
	primitifRendering.hInstance=hInstance;
	primitifRendering.fullScreen=false;
	primitifRendering.cursor=true;
	primitifRendering.width=800;
	primitifRendering.height=600;
	primitifRendering.title="Primitive Rendering";
	primitifRendering.path="resource";
	primitifRendering.appRun=GameLoop;

	//Application Execution
	swEngineInit(&primitifRendering);
	swEngineRun();
	swEngineExit();

	return 0;
}