#include "../../include/SWEngine.h"

#pragma comment (lib,"../../lib/SWUtil.lib")    
#pragma comment (lib,"../../lib/SWTypes.lib")    
#pragma comment (lib,"../../lib/SWCore.lib")    
#pragma comment (lib,"../../lib/SWEngine.lib")    
#pragma comment (lib,"../../lib/SWGame.lib")    
#pragma comment (lib,"../../lib/SWGui.lib")    
#pragma comment (lib,"../../lib/SWServices.lib")    

swApplication metaballApp;

typedef struct _Metaball{
  float x,y;
  float mass;
  int   xModifierID;
}Metaball;

Metaball mb1,mb2;

//-------------------------------------------------------------------------------------------
void reflectMetaballEffect(Metaball *mb){

	float range=128;
	int x0=(int)(mb->x-range);
	int y0=(int)(mb->y-range);
	int x1=(int)(mb->x+range);
	int y1=(int)(mb->y+range);


	for(int x=x0;x<x1;x++){
		for(int y=y0;y<y1;y++){
			float xDist = (x - mb->x);
			float yDist = (y - mb->y);
			float xDistSq = xDist * xDist;
			float yDistSq = yDist * yDist;
			float g = mb->mass /(xDistSq + yDistSq);
			float cVal=swMathClampFloat(g,0,1);
			swGraphicsSetColor0(cVal,cVal,cVal,0.5f);
			swGraphicsRenderPoint0(x,y,1);
		}
	}
}

//-------------------------------------------------------------------------------------------
void GameLoop(){ 
	swValueModifierExecute(mb1.xModifierID,0.015);	
	swValueModifierExecute(mb2.xModifierID,0.015);	

	swGraphicsBeginScene();
		swGraphicsSetRenderingTarget(SW_RENDERING_TARGET_DEFAULT);	
		swGraphicsSetBlendingMode(SW_BLENDING_MODE_ADDITIVE);
		swGraphicsSetBgColor0(1,0,0);
		reflectMetaballEffect(&mb1);
		reflectMetaballEffect(&mb2);
	swGraphicsEndScene();
}

//-------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{ 
	//Application Settings
	metaballApp.hInstance=hInstance;
	metaballApp.fullScreen=false;
	metaballApp.cursor=true;
	metaballApp.width=400;
	metaballApp.height=300;
	metaballApp.title="Metaball";
	metaballApp.path="";
	metaballApp.appRun=GameLoop;

	//Application Execution
	swEngineInit(&metaballApp);

	//Metaball1
	mb1.x=100; mb1.y=150; mb1.mass=512;
	mb1.xModifierID=swValueModifierCreate(SW_VALUE_MODIFIER_010_LOOP,&mb1.x,100,300,100,0);

	//Metaball2
	mb2.x=300; mb2.y=150; mb2.mass=256;
	mb2.xModifierID=swValueModifierCreate(SW_VALUE_MODIFIER_010_LOOP,&mb2.x,100,300,100,0);

	swEngineRun();
	swEngineExit();

	return 0;
}


