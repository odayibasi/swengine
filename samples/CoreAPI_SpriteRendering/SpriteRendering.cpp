#include "../../include/SWEngine.h"

#pragma comment (lib,"../../lib/SWUtil.lib")    
#pragma comment (lib,"../../lib/SWTypes.lib")    
#pragma comment (lib,"../../lib/SWCore.lib")    
#pragma comment (lib,"../../lib/SWGame.lib")   
#pragma comment (lib,"../../lib/SWGui.lib")   
#pragma comment (lib,"../../lib/SWEngine.lib")   




swApplication spriteRenderingApp;
int spriteID;
int spriteID2;

int animatorID=-1;
int animatorID2=-1;

//Img1 Setting
swRect target1={200,200,125,150};
swRect target2={400,200,125,150};


//-------------------------------------------------------------------------------------------
void GameLoop(){ 


	swGraphicsBeginScene();

	//Background
	swGraphicsSetBgColor0(0.0f,0.0f,0.6f);

	//BlendingMode
	swGraphicsSetBlendingMode(SW_BLENDING_MODE_SOLID);



	//Draw Image
	int index=swAnimatorGetIndex(animatorID);
	swGraphicsSetColor0(1,1,1,1);
	swGraphicsRenderSprite0(spriteID,index,&target1);

	index=swAnimatorGetIndex(animatorID2);
	swGraphicsSetColor0(1,1,1,1);
	swGraphicsRenderSprite0(spriteID2,index,&target2);


   swGraphicsEndScene();

}





//-------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{ 


	//Application Settings
	spriteRenderingApp.hInstance=hInstance;
	spriteRenderingApp.fullScreen=false;
	spriteRenderingApp.cursor=true;
	spriteRenderingApp.width=800;
	spriteRenderingApp.height=600;
	spriteRenderingApp.title="Sprite Rendering";
	spriteRenderingApp.path="\\rsc\\SprRendering\\";
	spriteRenderingApp.appRun=GameLoop;

	//Application Execution
	swEngineInit(&spriteRenderingApp);

	//Init My Application
	//spriteID=swGraphicsCreateSprite("XenRunning\\");
	spriteID=swGraphicsCreateSprite("Smurfs\\");
	animatorID=swAnimatorCreate(swGraphicsGetCountOfImgInSprite(spriteID),0.1);
	swAnimatorSetExecutionMode(animatorID, SW_ANIMATOR_EXEC_FORWARD_LOOP);

	spriteID2=swGraphicsCreateSprite("XenRunning\\");
	animatorID2=swAnimatorCreate(swGraphicsGetCountOfImgInSprite(spriteID2),0.1);
	swAnimatorSetExecutionMode(animatorID2, SW_ANIMATOR_EXEC_FORWARD_LOOP);


	swEngineRun();
	swEngineExit();

	return 0;
}
