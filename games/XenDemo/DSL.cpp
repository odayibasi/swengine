#include "../../include/SWEngine.h"
#include "DSL.h"
#include "Turret.h"
#include "Barrel.h"
#include "SolidItems.h"
#include "NeonItems.h"
#include "CargoBox.h"
#include "Defender.h"
#include "Platform.h"
#include "BgTiles.h"
#include "Elevator.h"
#include "PhysBoundary.h"
#include "RefPoint.h"
#include "Claw.h"
#include "Hud.h"


extern		int labelID;
extern      int hutID;
extern		int fenceID;
extern      int doorID;
extern      int airventID;
extern      int clawOthersID;
extern      int clawPitID;
extern		int particleLitID;
extern      int img7D8ID;
extern      int img7D8Party;
extern		int img7D8Symbol;


swArg		dslArgs[1];
swArg		xyArgs[2];
swArg		cXcYArgs[2];
swArg		xywhArgs[4];
swArg		xycXdX[4];
swArg		xycX[3];


#define		DSL_EXECUTE_LVL "include"
#define		DSL_TURRET_CREATION "turret"
#define		DSL_CLAW_CREATION "claw"
#define		DSL_HUD_CREATION "hud"
#define		DSL_GRAY_BARREL_CREATION "grayBarrel"
#define		DSL_ORNG_BARREL_CREATION "orngBarrel"
#define		DSL_ORNG_BARREL_CLONEX_CREATION "barrelCloneX"
#define		DSL_HUT_CREATION "hut"
#define		DSL_FENCE_CREATION "fence"
#define		DSL_LABEL_CREATION "label"
#define		DSL_DOOR_CREATION "door"
#define		DSL_CLAWOTHERS_CREATION "clawOthers"
#define		DSL_AIRVENT_CREATION "airvent"
#define		DSL_CLAWPIT_CREATION "clawPit"
#define		DSL_NEON7D8_CREATION "neon7d8"
#define		DSL_CARGOBOX_CREATION "cargoBox"
#define		DSL_CARGOBOX_CLONEX_CREATION "cargoBoxCloneX"
#define		DSL_DEFENDER_CREATION "defender"
#define		DSL_PLATFORM_CREATION "platform"
#define		DSL_ELEVATOR_CREATION "elevator"
#define		DSL_PHYSBOUNDARY_CREATION "physBoundary"
#define		DSL_REFPOINT "refPoint"
#define		DSL_BGWALL_CREATION "bgWall"
#define		DSL_COLUMN_CREATION "column"
#define		DSL_EDGEWALL_X_CREATION "edgeX"
#define		DSL_EDGEWALL_Y_CREATION "edgeY"


//-------------------------------------------------------------------------------------------
void dslExecuteLvlWithDSL(int countArgs,swArg* argS){
	char filename[MAX_CHAR_DLS_CMD];
	swStringCopy(filename,argS[0].arg.sVal);
	dslExecuterExecuteLevel(filename);
}


//-------------------------------------------------------------------------------------------
void dslXY(int countArgs,swArg* argS,swPoint *point){
	swPoint p=refPointGet();
	float x=argS[0].arg.fVal+p.x;
	float y=argS[1].arg.fVal+p.y;
	point->x=x;
	point->y=y;
}


//-------------------------------------------------------------------------------------------
void dslCreateTurret(int countArgs,swArg* argS){
	swPoint p;
	dslXY(countArgs,argS,&p);
	turretCreate(7,p.x,p.y);
}

//-------------------------------------------------------------------------------------------
void dslCreateGrayBarrel(int countArgs,swArg* argS){
	swPoint p;
	dslXY(countArgs,argS,&p);
	barrelCreate(1,p.x,p.y,true);
}


//-------------------------------------------------------------------------------------------
void dslCreateOrangeBarrel(int countArgs,swArg* argS){
	swPoint p;
	dslXY(countArgs,argS,&p);
	barrelCreate(1,p.x,p.y,false);
}


//-------------------------------------------------------------------------------------------
void dslCreateCloneBarrel(int countArgs,swArg* argS){
	swPoint p=refPointGet();
	float x=argS[0].arg.fVal+p.x;
	float y=argS[1].arg.fVal+p.y;
	int   xCount=argS[2].arg.iVal;
	float dx=argS[3].arg.fVal;

	for(int i=0;i<xCount;i++){
		barrelCreate(1,x+(i*dx),y,false);			
	}
}


//-------------------------------------------------------------------------------------------
void dslHutCreate(int countArgs,swArg* argS){
	swPoint p;
	dslXY(countArgs,argS,&p);
	solidItemCreate(hutID,1,p.x,p.y,160,80,false);
}

//-------------------------------------------------------------------------------------------
void dslFenceCreate(int countArgs,swArg* argS){
	swPoint p=refPointGet();
	float x=argS[0].arg.fVal+p.x;
	float y=argS[1].arg.fVal+p.y;
	int   c=argS[2].arg.iVal;
	for(int i=0;i<c;i++)
		solidItemCreate(fenceID,3,x+32*i,y,32,32,false);
}


//-------------------------------------------------------------------------------------------
void dslLabelCreate(int countArgs,swArg* argS){
	swPoint p;
	dslXY(countArgs,argS,&p);
	solidItemCreate(labelID,1,p.x,p.y,64,16,false);
}


//-------------------------------------------------------------------------------------------
void dslDoorCreate(int countArgs,swArg* argS){
	swPoint p;
	dslXY(countArgs,argS,&p);
	solidItemCreate(doorID,1,p.x,p.y,64,54,false);
}


//-------------------------------------------------------------------------------------------
void dslClawOthersCreate(int countArgs,swArg* argS){
	swPoint p;
	dslXY(countArgs,argS,&p);
	solidItemCreate(clawOthersID,1,p.x,p.y,256,155,false);
}


//-------------------------------------------------------------------------------------------
void dslAirventCreate(int countArgs,swArg* argS){
	swPoint p=refPointGet();
	float x=argS[0].arg.fVal+p.x;
	float y=argS[1].arg.fVal+p.y;
	int   c=argS[2].arg.iVal;

	for(int i=0;i<c;i++)
		solidItemCreateWithAnims(airventID,1,x+400*i,y,64,64,0.05,false);
}

//-------------------------------------------------------------------------------------------
void dslClawPitCreate(int countArgs,swArg* argS){
	swPoint p;
	dslXY(countArgs,argS,&p);
	solidItemCreate(clawPitID,1,p.x,p.y,128,64,false);
	neonItemCreate2(particleLitID,p.x+5,  p.y+42,20.0f,20.0f,1.0f,0.0f,0.0f,0.4f,8.0f,0.5f);
	neonItemCreate2(particleLitID,p.x+106,p.y+42,20.0f,20.0f,1.0f,0.0f,0.0f,0.4f,8.5f,0.5f);
}


//-------------------------------------------------------------------------------------------
void dsl7D8Create(int countArgs,swArg* argS){
	swPoint p;
	dslXY(countArgs,argS,&p);

	//Neon 7D8 Party
	neonItemCreate(img7D8ID,p.x,p.y+210,128,64);
	neonItemCreate(img7D8Party,p.x+10,p.y,64,256);

	float startTime=8.0;

	neonItemCreate1(img7D8Symbol,p.x+50,p.y+20,64,64,startTime,0.5);	
	neonItemCreate1(img7D8Symbol,p.x+50,p.y+60,64,64,startTime+0.1,0.5);
	neonItemCreate1(img7D8Symbol,p.x+50,p.y+100,64,64,startTime+0.2,0.5);
	neonItemCreate1(img7D8Symbol,p.x+50,p.y+140,64,64,startTime+0.3,0.5);
	neonItemCreate1(img7D8Symbol,p.x+50,p.y+180,64,64,startTime+0.4,0.5);

}


//-------------------------------------------------------------------------------------------
void dslCargoBoxCreate(int countArgs,swArg* argS){
	swPoint p;
	dslXY(countArgs,argS,&p);
	cargoBoxCreate(1,p.x,p.y);
}

//-------------------------------------------------------------------------------------------
void dslCargoBoxClone(int countArgs,swArg* argS){
	swPoint p=refPointGet();
	float x=argS[0].arg.fVal+p.x;
	float y=argS[1].arg.fVal+p.y;
	int   xCount=argS[2].arg.iVal;
	float dx=argS[3].arg.fVal;

	for(int i=0;i<xCount;i++){
		cargoBoxCreate(1,x+(i*dx),y);			
	}
}

//-------------------------------------------------------------------------------------------
void dslDefenderCreate(int countArgs,swArg* argS){
	swPoint p;
	dslXY(countArgs,argS,&p);
	xenDefender* defender=defenderCreate();
	defenderSetPos(defender,p.x,p.y);
}

//-------------------------------------------------------------------------------------------
void dslPlatformCreate(int countArgs,swArg* argS){
	swPoint p;
	dslXY(countArgs,argS,&p);
	platformCreate(p.x,p.y);
}



//-------------------------------------------------------------------------------------------
void dslElevatorCreate(int countArgs,swArg* argS){
	swPoint p;
	dslXY(countArgs,argS,&p);
	elevatorCreate(p.x,p.y);
}

//-------------------------------------------------------------------------------------------
void dslPhysBoundaryCreate(int countArgs,swArg* argS){
	swPoint p=refPointGet();
	float x=argS[0].arg.fVal+p.x;
	float y=argS[1].arg.fVal+p.y;
	float w=argS[2].arg.fVal;
	float h=argS[3].arg.fVal;
	physBoundaryCreate(x,y,w,h);
}

//-------------------------------------------------------------------------------------------
void dslRefPointSet(int countArgs,swArg* argS){
	float x=argS[0].arg.fVal;
	float y=argS[1].arg.fVal;
	refPointSet(x,y);
}


//-------------------------------------------------------------------------------------------
void dslClawCreate(int countArgs,swArg* argS){
	clawCreate();
}


//-------------------------------------------------------------------------------------------
void dslHUDCreate(int countArgs,swArg* argS){
	hudCreate();
}

//-------------------------------------------------------------------------------------------
void dslBgWallCreate(int countArgs,swArg* argS){

	int   cx=argS[0].arg.iVal;
	int   cy=argS[1].arg.iVal;

	for(int i=0;i<cx;i++){
		for(int j=0;j<cy;j++){
			bgWallCreate(i,j);
		}
	}
}


//-------------------------------------------------------------------------------------------
void dslColumnCreate(int countArgs,swArg* argS){
	float   x=argS[0].arg.fVal;
	float   dx=argS[1].arg.fVal;
	int		c=argS[2].arg.iVal;
	for(int i=0;i<c;i++){
		columnPartCreate(x+dx*i,32,11);
	}
}

//-------------------------------------------------------------------------------------------
void dslEdgeWallCreateXAxis(int countArgs,swArg* argS){
	swPoint p=refPointGet();
	float x=argS[0].arg.fVal+p.x;
	float y=argS[1].arg.fVal+p.y;
	int   c=argS[2].arg.iVal;
	edgeWallCreateXAxis(x,y,c);
}

//-------------------------------------------------------------------------------------------
void dslEdgeWallCreateYAxis(int countArgs,swArg* argS){
	swPoint p=refPointGet();
	float x=argS[0].arg.fVal+p.x;
	float y=argS[1].arg.fVal+p.y;
	int   c=argS[2].arg.iVal;
	edgeWallCreateYAxis(x,y,c);
}




//-------------------------------------------------------------------------------------------
void dslInit(){
	dslArgs[0].type=SW_ARG_STRING;

	xyArgs[0].type=SW_ARG_FLOAT;
	xyArgs[1].type=SW_ARG_FLOAT;

	cXcYArgs[0].type=SW_ARG_INT;
	cXcYArgs[1].type=SW_ARG_INT;


	xywhArgs[0].type=SW_ARG_FLOAT;
	xywhArgs[1].type=SW_ARG_FLOAT;
	xywhArgs[2].type=SW_ARG_FLOAT;
	xywhArgs[3].type=SW_ARG_FLOAT;

	
	xycXdX[0].type=SW_ARG_FLOAT;
	xycXdX[1].type=SW_ARG_FLOAT;
	xycXdX[2].type=SW_ARG_INT;
	xycXdX[3].type=SW_ARG_FLOAT;

	xycX[0].type=SW_ARG_FLOAT;
	xycX[1].type=SW_ARG_FLOAT;
	xycX[2].type=SW_ARG_INT;

	swDSLRegisterCommand(dslExecuteLvlWithDSL,DSL_EXECUTE_LVL,1,dslArgs);
	swDSLRegisterCommand(dslRefPointSet,DSL_REFPOINT,2,xyArgs);
	swDSLRegisterCommand(dslClawCreate,DSL_CLAW_CREATION,2,xyArgs);
	swDSLRegisterCommand(dslHUDCreate,DSL_HUD_CREATION,2,xyArgs);
	swDSLRegisterCommand(dslBgWallCreate,DSL_BGWALL_CREATION,2,cXcYArgs);
	swDSLRegisterCommand(dslCreateTurret,DSL_TURRET_CREATION,2,xyArgs);
	swDSLRegisterCommand(dslCreateGrayBarrel,DSL_GRAY_BARREL_CREATION,2,xyArgs);
	swDSLRegisterCommand(dslCreateOrangeBarrel,DSL_ORNG_BARREL_CREATION,2,xyArgs);
	swDSLRegisterCommand(dslHutCreate,DSL_HUT_CREATION,2,xyArgs);
	swDSLRegisterCommand(dslLabelCreate,DSL_LABEL_CREATION,2,xyArgs);
	swDSLRegisterCommand(dslDoorCreate,DSL_DOOR_CREATION,2,xyArgs);
	swDSLRegisterCommand(dslClawOthersCreate,DSL_CLAWOTHERS_CREATION,2,xyArgs);
	swDSLRegisterCommand(dslClawPitCreate,DSL_CLAWPIT_CREATION,2,xyArgs);
	swDSLRegisterCommand(dsl7D8Create,DSL_NEON7D8_CREATION,2,xyArgs);
	swDSLRegisterCommand(dslCargoBoxCreate,DSL_CARGOBOX_CREATION,2,xyArgs);
	swDSLRegisterCommand(dslDefenderCreate,DSL_DEFENDER_CREATION,2,xyArgs);
	swDSLRegisterCommand(dslPlatformCreate,DSL_PLATFORM_CREATION,2,xyArgs);
	swDSLRegisterCommand(dslElevatorCreate,DSL_ELEVATOR_CREATION,2,xyArgs);
	swDSLRegisterCommand(dslCreateCloneBarrel,DSL_ORNG_BARREL_CLONEX_CREATION,4, xycXdX);
	swDSLRegisterCommand(dslFenceCreate,DSL_FENCE_CREATION,3,xycX);
	swDSLRegisterCommand(dslAirventCreate,DSL_AIRVENT_CREATION,3,xycX);
	swDSLRegisterCommand(dslCargoBoxClone,DSL_CARGOBOX_CLONEX_CREATION,4, xycXdX);
	swDSLRegisterCommand(dslPhysBoundaryCreate,DSL_PHYSBOUNDARY_CREATION,4,xywhArgs);
	swDSLRegisterCommand(dslColumnCreate,DSL_COLUMN_CREATION,3,xycX);
	swDSLRegisterCommand(dslEdgeWallCreateXAxis,DSL_EDGEWALL_X_CREATION,3,xycX);
	swDSLRegisterCommand(dslEdgeWallCreateYAxis,DSL_EDGEWALL_Y_CREATION,3,xycX);


}
