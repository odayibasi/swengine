#include "../../include/SWEngine.h"

#pragma comment (lib,"../../lib/SWUtil.lib")    
#pragma comment (lib,"../../lib/SWTypes.lib")    
#pragma comment (lib,"../../lib/SWCore.lib")    
#pragma comment (lib,"../../lib/SWServices.lib")   
#pragma comment (lib,"../../lib/SWEngine.lib")   




swApplication physicWorldAppWithBox2DRenderer;
swRect  groundRect={10,20,780,20};
swRect  boxRect={350,200,50,50};
swRect  boxRect2={350,150,40,40};

float   boxDegree=0;
float   boxDegree2=20;
swPoint cirPos={340,120};
float   cirRad=5;

swPoint    defaultWeight={0,0};


//-------------------------------------------------------------------------------------------
void GameLoop(){ 

	swPhysWorldUpdate();
	swGraphicsBeginScene();
		swPhysRendererExecute();
	swGraphicsEndScene();

}

//-------------------------------------------------------------------------------------------
void initPhysWorldApp(){

	//Physics
	swRect  aabb={0,0,800,600};
	swVec2  grav={0,-1000};
	bool    sleep=true;

	//World
	swPhysWorldCreate(&aabb,&grav,sleep);


	//Configure Phys Renderer
	swPhysRendererSetEnabled(SW_PHYS_RENDERED_SHAPE,true);
	swPhysRendererSetEnabled(SW_PHYS_RENDERED_JOINTS,true);
	swPhysRendererSetEnabled(SW_PHYS_RENDERED_CORESHAPES,true);
	//swPhysRendererSetEnabled(SW_PHYS_RENDERED_AABBs,true);
	//swPhysRendererSetEnabled(SW_PHYS_RENDERED_OBBs,true);
	swPhysRendererSetEnabled(SW_PHYS_RENDERED_CENTEROFMASSES,true);
	swPhysRendererSetEnabled(SW_PHYS_RENDERED_PAIRS,true);
	//swPhysRendererSetEnabled(SW_PHYS_RENDERED_STATISTICS,true);


	//Ground
	swPhysBodyDefSetPos(groundRect.x,groundRect.y);
	swPhysBodyDefSetRectShapeType(groundRect.w,groundRect.h);
	int groundBodyID=swPhysBodyCreate();

	//Box Body
	swPhysBodyDefSetPos(boxRect.x,boxRect.y);
	swPhysBodyDefSetRectShapeType(boxRect.w,boxRect.h);
	swPhysBodyDefSetAngle(boxDegree);
	swPhysBodyDefSetDensity(1.0f);
	swPhysBodyDefSetFriction(2.0f);
	swPhysBodyDefSetRestitution(0.05f);
	swPhysBodyDefSetPosListener(&boxRect.x,&boxRect.y);
	swPhysBodyDefSetAngleListener(&boxDegree);
	int boxBodyID=swPhysBodyCreate();

	//Box Body
	swPhysBodyDefSetPos(boxRect2.x,boxRect2.y);
	swPhysBodyDefSetRectShapeType(boxRect2.w,boxRect2.h);
	swPhysBodyDefSetAngle(boxDegree2);
	swPhysBodyDefSetDensity(1.0f);
	swPhysBodyDefSetFriction(0.3f);
	swPhysBodyDefSetRestitution(0.1f);
	swPhysBodyDefSetPosListener(&boxRect2.x,&boxRect2.y);
	swPhysBodyDefSetAngleListener(&boxDegree2);
	int boxBodyID2=swPhysBodyCreate();

	//Circle Body
	swPhysBodyDefSetPos(cirPos.x,cirPos.y);
	swPhysBodyDefSetCircleShapeType(cirRad/2);
	swPhysBodyDefSetDensity(1.0f);
	swPhysBodyDefSetFriction(0.0f);
	swPhysBodyDefSetRestitution(0.9f);
	swPhysBodyDefSetPosListener(&cirPos.x,&cirPos.y);
	int cirBodyID=swPhysBodyCreate();

}



//-------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{ 
	//Application Settings
	physicWorldAppWithBox2DRenderer.hInstance=hInstance;
	physicWorldAppWithBox2DRenderer.fullScreen=false;
	physicWorldAppWithBox2DRenderer.cursor=true;
	physicWorldAppWithBox2DRenderer.width=800;
	physicWorldAppWithBox2DRenderer.height=600;
	physicWorldAppWithBox2DRenderer.title="Physics World With Box2D Default Renderer";
	physicWorldAppWithBox2DRenderer.path="resource";
	physicWorldAppWithBox2DRenderer.appRun=GameLoop;

	//Application Execution
	swEngineInit(&physicWorldAppWithBox2DRenderer);

	//InitApplication
	initPhysWorldApp();
	

	swEngineRun();
	swEngineExit();

	return 0;
}