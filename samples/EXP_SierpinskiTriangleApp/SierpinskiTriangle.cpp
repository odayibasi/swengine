#include "../../include/SWEngine.h"

#pragma comment (lib,"../../lib/SWUtil.lib")    
#pragma comment (lib,"../../lib/SWTypes.lib")    
#pragma comment (lib,"../../lib/SWCore.lib")    
#pragma comment (lib,"../../lib/SWEngine.lib")    


swApplication sierpinskiTriangle;
bool bDrawed=false;

//-------------------------------------------------------------------------------------------
void GameLoop(){ 


	if(!bDrawed){
		swGraphicsBeginScene();
		swGraphicsSetColor1(&SWCOLOR_WHITE);

		//Draw Sierpinski Triangle
		swPoint pointS[3]={{50,50},{400,500},{750,50}};
		int index=swMathRandomInt(0,2);
		swPoint p=pointS[index];
		swGraphicsRenderPoint1(&p,2);
		for(int i=0;i<5000;i++){
			index=swMathRandomInt(0,2);
			p.x=(p.x+pointS[index].x)/2;
			p.y=(p.y+pointS[index].y)/2;
			swGraphicsRenderPoint1(&p,2);
		}
		swGraphicsEndScene();
		bDrawed=true;
	}
}


//-------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{ 


	//Application Settings
	sierpinskiTriangle.hInstance=hInstance;
	sierpinskiTriangle.fullScreen=false;
	sierpinskiTriangle.cursor=true;
	sierpinskiTriangle.width=800;
	sierpinskiTriangle.height=600;
	sierpinskiTriangle.title="Sierpinski Triangle";
	sierpinskiTriangle.path="resource";
	sierpinskiTriangle.appRun=GameLoop;

	//Application Execution
	swEngineInit(&sierpinskiTriangle);
	swEngineRun();
	swEngineExit();

	return 0;
}