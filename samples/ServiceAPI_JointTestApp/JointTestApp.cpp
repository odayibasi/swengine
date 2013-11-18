#include "../../include/SWEngine.h"

#pragma comment (lib,"../../lib/SWUtil.lib")    
#pragma comment (lib,"../../lib/SWTypes.lib")    
#pragma comment (lib,"../../lib/SWCore.lib")    
#pragma comment (lib,"../../lib/SWServices.lib")   
#pragma comment (lib,"../../lib/SWEngine.lib")   




swApplication jointTestApp;
swRect  groundRect={10,20,780,20};
swRect  boxRect2={350,150,100,100};

float   boxDegree2=20;
swPoint cirPos={340,300};
float   cirRad=50;

swPoint    defaultWeight={0,0};


//-------------------------------------------------------------------------------------------
void GameLoop(){ 

	swPhysWorldUpdate();
	swGraphicsBeginScene();
		swGraphicsSetColor0(0,0,1,0);
		swGraphicsRenderLineRect2(&groundRect,5);
		//swGraphicsRenderLineRect4(&boxRect,2,boxDegree,&defaultWeight);
		swGraphicsRenderLineRect4(&boxRect2,2,boxDegree2,&defaultWeight);
		swGraphicsRenderPointElips0(cirPos.x,cirPos.y,cirRad,cirRad,60,2);
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
	//swPhysRendererSetEnabled(SW_PHYS_RENDERED_CORESHAPES,true);
	//swPhysRendererSetEnabled(SW_PHYS_RENDERED_AABBs,true);
	//swPhysRendererSetEnabled(SW_PHYS_RENDERED_OBBs,true);
	//swPhysRendererSetEnabled(SW_PHYS_RENDERED_CENTEROFMASSES,true);
	//swPhysRendererSetEnabled(SW_PHYS_RENDERED_PAIRS,true);
	//swPhysRendererSetEnabled(SW_PHYS_RENDERED_STATISTICS,true);


	//Ground
	swPhysBodyDefSetPos(groundRect.x,groundRect.y);
	swPhysBodyDefSetRectShapeType(groundRect.w,groundRect.h);
	int groundBodyID=swPhysBodyCreate();


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

	swPoint p0={swRectMidX(&boxRect2),swRectMidY(&boxRect2)};	
	swPoint p1={cirPos.x,cirPos.y};	

	//swPhysDistJointCreate(boxBodyID2,p0,cirBodyID,p1,true);
	swPhysRevoJointCreate(cirBodyID,boxBodyID2,p0,10,90,true,10,0,true);

}



//-------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{ 
	//Application Settings
	jointTestApp.hInstance=hInstance;
	jointTestApp.fullScreen=false;
	jointTestApp.cursor=true;
	jointTestApp.width=800;
	jointTestApp.height=600;
	jointTestApp.title="Physics World With Box2D Default Renderer";
	jointTestApp.path="resource";
	jointTestApp.appRun=GameLoop;

	//Application Execution
	swEngineInit(&jointTestApp);

	//InitApplication
	initPhysWorldApp();


	swEngineRun();
	swEngineExit();

	return 0;
}