#include "../../include/SWEngine.h"

#pragma comment (lib,"../../lib/SWUtil.lib")    
#pragma comment (lib,"../../lib/SWTypes.lib")    
#pragma comment (lib,"../../lib/SWCore.lib")    
#pragma comment (lib,"../../lib/SWEngine.lib")    
#pragma comment (lib,"../../lib/SWGame.lib")    
#pragma comment (lib,"../../lib/SWGui.lib")    
#pragma comment (lib,"../../lib/SWServices.lib")    

swApplication metaballApp2;

typedef struct _Metaball{
	swRect target;
	int    xModifierID;
	int    imgID;
}Metaball;

Metaball mb1,mb2;

//-------------------------------------------------------------------------------------------
void reflectMetaballEffect(Metaball *mb){
	swGraphicsSetColor0(1,1,1,0.45);
	swGraphicsRenderImg0(mb->imgID,&mb->target);
}

//-------------------------------------------------------------------------------------------
void GameLoop(){ 
	swValueModifierExecute(mb1.xModifierID,0.015);	
	swValueModifierExecute(mb2.xModifierID,0.015);	

	swGraphicsBeginScene();
		swGraphicsSetBlendingMode(SW_BLENDING_MODE_ADDITIVE);
		swGraphicsSetBgColor0(0,0,0);
		reflectMetaballEffect(&mb1);
		reflectMetaballEffect(&mb2);
	swGraphicsEndScene();
}

//-------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{ 
	//Application Settings
	metaballApp2.hInstance=hInstance;
	metaballApp2.fullScreen=false;
	metaballApp2.cursor=true;
	metaballApp2.width=800;
	metaballApp2.height=600;
	metaballApp2.title="Metaball2";
	metaballApp2.path="\\rsc\\Metaball2\\";
	metaballApp2.appRun=GameLoop;

	//Application Execution
	swEngineInit(&metaballApp2);

	//Metaball1
	swRectSet(&mb1.target,100,250,256,256);
	mb1.xModifierID=swValueModifierCreate(SW_VALUE_MODIFIER_010_LOOP,&mb1.target.x,100,600,100,0);
	mb1.imgID=swGraphicsCreateImg("Ball1.tga");

	//Metaball2
	swRectSet(&mb2.target,600,250,256,256);
	mb2.xModifierID=swValueModifierCreate(SW_VALUE_MODIFIER_010_LOOP,&mb2.target.x,100,600,100,0);
	mb2.imgID=swGraphicsCreateImg("Ball1.tga");

	swEngineRun();
	swEngineExit();

	return 0;
}


