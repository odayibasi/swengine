#include "../../include/SWEngine.h"

#pragma comment (lib,"../../lib/SWUtil.lib")    
#pragma comment (lib,"../../lib/SWTypes.lib")    
#pragma comment (lib,"../../lib/SWCore.lib")    
#pragma comment (lib,"../../lib/SWServices.lib")   
#pragma comment (lib,"../../lib/SWEngine.lib")   


swApplication simpleBreakOutPhys;
swRect  rectFloor={0,0,800,50};
swRect  rectCeil= {0,550,800,50};
swRect  rectLWall={0,50,50,500};
swRect  rectRWall={750,50,50,500};

swPoint ballCenter={300,300};
float   ballRadious=10;

swPoint defaultWeight={0,0};


//-------------------------------------------------------------------------------------------
void GameLoop(){ 

	swPhysWorldUpdate();

	swGraphicsBeginScene();
		swGraphicsSetColor0(0,0,1,0);
		swGraphicsRenderLineRect2(&rectFloor,1);
		swGraphicsRenderLineRect2(&rectCeil,1);
		swGraphicsRenderLineRect2(&rectLWall,1);
		swGraphicsRenderLineRect2(&rectRWall,1);
	swGraphicsRenderSolidElips0(ballCenter.x,ballCenter.y,ballRadious,ballRadious,60);
	swGraphicsEndScene();

}

//-------------------------------------------------------------------------------------------
void initPhysWorldApp(){

	//Physics
	swRect  aabb={0,0,800,600};
	swVec2  grav={0,0};
	bool    sleep=true;

	//World
	swPhysWorldCreate(&aabb,&grav,sleep);

	//Walls
	swPhysBodyDefSetPos(rectFloor.x,rectFloor.y);
	swPhysBodyDefSetRectShapeType(rectFloor.w,rectFloor.h);
	swPhysBodyCreate();

	swPhysBodyDefSetPos(rectCeil.x,rectCeil.y);
	swPhysBodyDefSetRectShapeType(rectCeil.w,rectCeil.h);
	swPhysBodyCreate();

	swPhysBodyDefSetPos(rectLWall.x,rectLWall.y);
	swPhysBodyDefSetRectShapeType(rectLWall.w,rectLWall.h);
	swPhysBodyCreate();

	swPhysBodyDefSetPos(rectRWall.x,rectRWall.y);
	swPhysBodyDefSetRectShapeType(rectRWall.w,rectRWall.h);
	swPhysBodyCreate();


	//Circle Body
	swPhysBodyDefSetPos(ballCenter.x,ballCenter.y);
	swPhysBodyDefSetCircleShapeType(ballRadious/2);
	swPhysBodyDefSetDensity(1.0f);
	swPhysBodyDefSetFriction(0.0f);
	swPhysBodyDefSetRestitution(1.0f);
	swPhysBodyDefSetPosListener(&ballCenter.x,&ballCenter.y);
	int ballBodyID=swPhysBodyCreate();
	swPhysBodySetLinearVelocity1(ballBodyID,100,200);
	
}



//-------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{ 
	//Application Settings
	simpleBreakOutPhys.hInstance=hInstance;
	simpleBreakOutPhys.fullScreen=false;
	simpleBreakOutPhys.cursor=true;
	simpleBreakOutPhys.width=800;
	simpleBreakOutPhys.height=600;
	simpleBreakOutPhys.title="BreakOut Physics";
	simpleBreakOutPhys.path="resource";
	simpleBreakOutPhys.appRun=GameLoop;

	//Application Execution
	swEngineInit(&simpleBreakOutPhys);

	//InitApplication
	initPhysWorldApp();

	swEngineRun();
	swEngineExit();

	return 0;
}