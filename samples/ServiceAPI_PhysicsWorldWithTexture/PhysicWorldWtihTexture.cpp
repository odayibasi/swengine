#include "../../include/SWEngine.h"

#pragma comment (lib,"../../lib/SWUtil.lib")    
#pragma comment (lib,"../../lib/SWTypes.lib")    
#pragma comment (lib,"../../lib/SWCore.lib")    
#pragma comment (lib,"../../lib/SWServices.lib")   
#pragma comment (lib,"../../lib/SWEngine.lib")   




swApplication physicWorldApp;
swRect  groundRect={10,20,780,20};
swRect  boxRect={350,200,32,32};
swRect  boxRect2={350,150,32,32};

float   boxDegree=0;
float   boxDegree2=20;
swPoint cirPos={340,120};
float   cirRad=32;

swPoint defaultWeight={0,0};

int     imgID=-1;


//-------------------------------------------------------------------------------------------
void GameLoop(){ 

	swPhysWorldUpdate();

	swGraphicsBeginScene();

		//Render Ground
		swGraphicsSetColor0(0,0,1,0);
		swGraphicsRenderLineRect2(&groundRect,2);

		//Render Boxes	
		swGraphicsSetColor0(1,1,1,0);
		swGraphicsRenderImg4(imgID,&boxRect,boxDegree,&defaultWeight);
		swGraphicsRenderImg4(imgID,&boxRect2,boxDegree2,&defaultWeight);
		
		//Render Circle
		swGraphicsRenderPointElips0(cirPos.x,cirPos.y,cirRad,cirRad,60,2);


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


	//Ground
	swPhysBodyDefSetPos(groundRect.x,groundRect.y);
	swPhysBodyDefSetRectShapeType(groundRect.w,groundRect.h);
	int groundBodyID=swPhysBodyCreate();

	//Box Body
	swPhysBodyDefSetPos(boxRect.x,boxRect.y);
	swPhysBodyDefSetAngle(boxDegree);
	swPhysBodyDefSetPosListener(&boxRect.x,&boxRect.y);
	swPhysBodyDefSetAngleListener(&boxDegree);
	swPhysBodyDefSetRectShapeType(boxRect.w,boxRect.h);
	swPhysBodyDefSetDensity(1.0f);
	swPhysBodyDefSetFriction(10.0f);
	swPhysBodyDefSetRestitution(0.05f);
	int boxBodyID=swPhysBodyCreate();


	//Box Body
	swPhysBodyDefSetPos(boxRect2.x,boxRect2.y);
	swPhysBodyDefSetAngle(boxDegree2);
	swPhysBodyDefSetPosListener(&boxRect2.x,&boxRect2.y);
	swPhysBodyDefSetAngleListener(&boxDegree2);
	swPhysBodyDefSetRectShapeType(boxRect2.w,boxRect2.h);
	swPhysBodyDefSetDensity(1.0f);
	swPhysBodyDefSetFriction(3.0f);
	swPhysBodyDefSetRestitution(0.1f);
	int boxBodyID2=swPhysBodyCreate();

	//Circle Body
	swPhysBodyDefSetPos(cirPos.x,cirPos.y);
	swPhysBodyDefSetPosListener(&cirPos.x,&cirPos.y);
	swPhysBodyDefSetCircleShapeType(cirRad/2);
	swPhysBodyDefSetDensity(1.0f);
	swPhysBodyDefSetFriction(0.0f);
	swPhysBodyDefSetRestitution(0.9f);
	int cirBodyID=swPhysBodyCreate();



}



//-------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{ 
	//Application Settings
	physicWorldApp.hInstance=hInstance;
	physicWorldApp.fullScreen=false;
	physicWorldApp.cursor=true;
	physicWorldApp.width=800;
	physicWorldApp.height=600;
	physicWorldApp.title="Physics World With Texture";
	physicWorldApp.path="/rsc/PhysicsWorldWithTexture/";
	physicWorldApp.appRun=GameLoop;

	//Application Execution
	swEngineInit(&physicWorldApp);

	//InitApplication
	initPhysWorldApp();

	imgID=swGraphicsCreateImg("CargoBox.tga");
	swEngineRun();
	swEngineExit();

	return 0;
}