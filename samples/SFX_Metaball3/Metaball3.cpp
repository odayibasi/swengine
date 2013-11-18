#pragma comment (lib,"opengl32.lib")      

#include "../../include/SWEngine.h"
#include <gl/GL.h>

#pragma comment (lib,"../../lib/SWUtil.lib")    
#pragma comment (lib,"../../lib/SWTypes.lib")    
#pragma comment (lib,"../../lib/SWCore.lib")    
#pragma comment (lib,"../../lib/SWEngine.lib")    
#pragma comment (lib,"../../lib/SWGame.lib")    
#pragma comment (lib,"../../lib/SWGui.lib")    
#pragma comment (lib,"../../lib/SWServices.lib")    

swApplication metaballApp3;

typedef struct _Metaball{
	swRect target;
	int    xModifierID;
	int    imgID;
}Metaball;

Metaball mb1,mb2,mb3;


int windowID=-1;
int windowTexID=-1;
swRect window={0,0,800,600};

//-------------------------------------------------------------------------------------------
void reflectMetaballEffect(Metaball *mb){
	swGraphicsSetColor0(1,1,1,0.45);
	swGraphicsRenderImg0(mb->imgID,&mb->target);
}

//-------------------------------------------------------------------------------------------
void GameLoop(){ 
	swValueModifierExecute(mb1.xModifierID,0.015);	
	swValueModifierExecute(mb2.xModifierID,0.015);	
	swValueModifierExecute(mb3.xModifierID,0.015);	

	swGraphicsBeginScene();

		//Active Rendering Target
		swGraphicsSetRenderingTarget(windowID);		
		swGraphicsClearRenderingTarget();
		swGraphicsSetBgColor1(0,0,0,0.5);
		swGraphicsSetBlendingMode(SW_BLENDING_MODE_ADDITIVE);
		reflectMetaballEffect(&mb1);
		reflectMetaballEffect(&mb2);
		reflectMetaballEffect(&mb3);

		//FrameBuffer Active 
		swGraphicsSetRenderingTarget(SW_RENDERING_TARGET_DEFAULT);
		swGraphicsSetBgColor0(0,0,0);
		swGraphicsSetBlendingMode(SW_BLENDING_MODE_NONE);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER,0.5f);
		swGraphicsSetColor0(1,1,1,1);
		swGraphicsRenderImg0(windowTexID,&window);
		glDisable(GL_ALPHA_TEST);
		

		
	swGraphicsEndScene();
}

//-------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{ 
	//Application Settings
	metaballApp3.hInstance=hInstance;
	metaballApp3.fullScreen=false;
	metaballApp3.cursor=true;
	metaballApp3.width=800;
	metaballApp3.height=600;
	metaballApp3.title="Metaball3";
	metaballApp3.path="\\rsc\\Metaball3\\";
	metaballApp3.appRun=GameLoop;

	//Application Execution
	swEngineInit(&metaballApp3);

	//Metaball1
	swRectSet(&mb1.target,200,250,256,256);
	mb1.xModifierID=swValueModifierCreate(SW_VALUE_MODIFIER_010_LOOP,&mb1.target.x,200,400,200,0);
	mb1.imgID=swGraphicsCreateImg("Ball4.tga");

	//Metaball2
	swRectSet(&mb2.target,400,250,236,256);
	mb2.xModifierID=swValueModifierCreate(SW_VALUE_MODIFIER_010_LOOP,&mb2.target.x,200,400,200,0);
	mb2.imgID=swGraphicsCreateImg("Blobs.tga");


	//Metaball3
	swRectSet(&mb3.target,300,150,256,256);
	mb3.xModifierID=swValueModifierCreate(SW_VALUE_MODIFIER_010_LOOP,&mb3.target.y,150,350,100,0);
	mb3.imgID=swGraphicsCreateImg("Ball3.tga");


	//RenderingTarget
	windowID=swGraphicsCreateRenderingTarget(800,600,4); //Define New RenderingTarget 
	windowTexID=swGraphicsRenderingTargetGetImgID(windowID);	


	swEngineRun();
	swEngineExit();

	return 0;
}


