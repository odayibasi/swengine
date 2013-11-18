#include "LaserGate.h"
#include "MoleculerDecompose.h"
#include "RefPoint.h"


#define		DSL_LASERGATE_CREATION "laserGate"
swArg		laserGateArgs[2];

#define		DSL_LASERGATE_SWITCHER_CREATION "laserGateSwitcher"
swArg		laserGateSwitcherArgs[1];


xenLaserGateSwitcher *activeLaserGateSwitcher;

extern int laserHoseID;
extern int particleLitID;
int laserGateLayer=7;
swPoint lgWP={0,0};



//-------------------------------------------------------------------------------------------
void laserGateEditorInit(xenLaserGate *eg,float x){

	int winHose1=swNumPropWinCreate("WinHose1",x,100,300,3);
	swNumPropWinAddFloat(winHose1,"x",&eg->hose1.rect.x,0,FLT_MAX,1);	
	swNumPropWinAddFloat(winHose1,"y",&eg->hose1.rect.y,0,FLT_MAX,1);	
	swNumPropWinAddFloat(winHose1,"r",&eg->hose1.rot,0,360,1);	
	swNumPropWinSetVisible(winHose1,true);

	int winHose2=swNumPropWinCreate("WinHose2",x,300,300,3);
	swNumPropWinAddFloat(winHose2,"x",&eg->hose2.rect.x,0,FLT_MAX,1);	
	swNumPropWinAddFloat(winHose2,"y",&eg->hose2.rect.y,0,FLT_MAX,1);	
	swNumPropWinAddFloat(winHose2,"r",&eg->hose2.rot,0,360,1);	
	swNumPropWinSetVisible(winHose2,true);


	int winLaser=swNumPropWinCreate("WinLaser",x+400,200,300,6);
	swNumPropWinAddFloat(winLaser,"x",&eg->elec.rect.x,0,FLT_MAX,1);	
	swNumPropWinAddFloat(winLaser,"y",&eg->elec.rect.y,0,FLT_MAX,1);	
	swNumPropWinAddFloat(winLaser,"r",&eg->elec.rot,0,360,1);	
	swNumPropWinAddInt(winLaser,"c",&eg->countElec,0,150,1);	
	swNumPropWinAddFloat(winLaser,"xD",&eg->xDeltaElec,-5,5,0.5);	
	swNumPropWinAddFloat(winLaser,"yD",&eg->yDeltaElec,0,20,0.5);	
	swNumPropWinSetVisible(winLaser,true);
}



//-------------------------------------------------------------------------------------------
void laserGateDisplay(void *obj){
	xenLaserGate *eg=(xenLaserGate*)obj;

	swGraphicsSetBlendingMode(SW_BLENDING_MODE_SOLID);
	swGraphicsSetColor1(&SWCOLOR_WHITE);
	swGraphicsRenderImg4(laserHoseID,&eg->hose1.rect,eg->hose1.rot,&lgWP);
	swGraphicsRenderImg4(laserHoseID,&eg->hose2.rect,eg->hose2.rot,&lgWP);

	if(eg->isExecute){	
		swGraphicsSetBlendingMode(SW_BLENDING_MODE_ADDITIVE);
		swGraphicsSetColor0(0,0.4,0.8,0.5);
		for(int i=0;i<eg->countElec;i++){
			swRect rect;
			swRect eRect=eg->elec.rect;
			swRectSet(&rect,eRect.x+i*eg->xDeltaElec,eRect.y+i*eg->yDeltaElec,eRect.w,eRect.h);
			swGraphicsRenderImg1(particleLitID,&rect,eg->elec.rot);
		}
	}else{
		eg->isExecute=eg->isExecute;
	}
}

//-------------------------------------------------------------------------------------------
void laserGateDestroy(void *obj){
	xenLaserGate *eg=(xenLaserGate*)obj;
	swDispManagerDel(eg->dispID);
	swPhysBodyDestroy(eg->hose1.bodyID);
	swPhysBodyDestroy(eg->hose2.bodyID);
	free(eg);
}




//-------------------------------------------------------------------------------------------
xenLaserGate* laserGateCreate(){
	xenLaserGate *eg=(xenLaserGate*)malloc(sizeof(xenLaserGate));
	eg->dispID=swDispManagerAdd(laserGateDisplay,eg,NULL,NULL,&laserGateLayer);
	swDestroyManagerAdd(laserGateDestroy,eg);
	return eg;
}



//-------------------------------------------------------------------------------------------
void laserGateHoseBodyCreate(lsrOrientation *orx){
	swPhysBodyDefSetPos(orx->rect.x,orx->rect.y);
	swPhysBodyDefSetAngle(orx->rot);
	swPhysBodyDefSetRectShapeType(orx->rect.w,orx->rect.h);
	swPhysBodyDefSetDensity(0);
	swPhysBodyDefSetPosListener(&orx->rect.x,&orx->rect.y);
	swPhysBodyDefSetAngleListener(&orx->rot);
	orx->bodyID=swPhysBodyCreate();
}


//-------------------------------------------------------------------------------------------
void laserGateSetDisp(xenLaserGate *eg,
						 float xHose1,float yHose1,float rotHose1,
						 float xHose2,float yHose2,float rotHose2,
						 float xLaser,float yLaser,float rotLaser, 
						 float countE,float xDelta,float yDelta){
	swRectSet(&eg->hose1.rect,xHose1,yHose1,50,50);
	eg->hose1.rot=rotHose1;
	swRectSet(&eg->hose2.rect,xHose2,yHose2,50,50);
	eg->hose2.rot=rotHose2;
	swRectSet(&eg->elec.rect,xLaser,yLaser,15,54);
	eg->elec.rot=rotLaser;
    eg->countElec=countE;
	eg->xDeltaElec=xDelta;
	eg->yDeltaElec=yDelta;

	laserGateHoseBodyCreate(&eg->hose1);						 
	laserGateHoseBodyCreate(&eg->hose2);


	float x0=swRectMidX(&eg->elec.rect);
	float y0=swRectMidY(&eg->elec.rect);
	float x1=swRectMidX(&eg->elec.rect)+eg->countElec*eg->xDeltaElec;
	float y1=swRectMidY(&eg->elec.rect)+eg->countElec*eg->yDeltaElec;


	moleculerDecomposerCreate(x0,y0,x1,y1,&eg->isExecute);


}


//-------------------------------------------------------------------------------------------
void laserGateSetDisp1(xenLaserGate *eg,float egX){
	laserGateSetDisp(eg,egX+50,82,180,egX+3,685,0,egX+20,63,0,60,0,10);
}

//-------------------------------------------------------------------------------------------
void laserGateSetDisp2(xenLaserGate *eg,float egX){
	laserGateSetDisp(eg,egX+45,80,202,egX-180,675,22,egX+8,63,20,60,-2.9,10);
}

//-------------------------------------------------------------------------------------------
void laserGateSetDisp3(xenLaserGate *eg,float egX){
	laserGateSetDisp(eg,egX+55,70,161,egX+215,685,338,egX+30,63,160,59,3.4f,10);
}



//-------------------------------------------------------------------------------------------
void executeLaserGateSwitcher(void *obj){
	xenLaserGateSwitcher* switcher=(xenLaserGateSwitcher*)obj;
	float sysTime=swSystemGetElapsedSeconds();
	if(sysTime-switcher->lastTime>switcher->sleepTime){
		xenLaserGate *eg=(xenLaserGate*)swLinkedListGetFirst(switcher->gateList);
		while(eg!=NULL){
			eg->isExecute=true;
			eg=(xenLaserGate*)swLinkedListGetNext(switcher->gateList);
		}

		switcher->index++;
		switcher->lastTime=sysTime;
		if(switcher->index>=swLinkedListSize(switcher->gateList)){
			switcher->index=0;
		}

		eg=(xenLaserGate *)swLinkedListGet(switcher->gateList,switcher->index);
		if(eg!=NULL){
			eg->isExecute=false;
		}
	}
}

//-------------------------------------------------------------------------------------------
void destroyLaserGateSwitcher(void *obj){
	xenLaserGateSwitcher* switcher=(xenLaserGateSwitcher*)obj;
	swExecManagerDel(switcher->execID);
	swLinkedListDestroy(switcher->gateList);
	free(switcher);
}


//-------------------------------------------------------------------------------------------
xenLaserGateSwitcher* laserGateSwitcherCreate(float sleepTime){
	xenLaserGateSwitcher* switcher=(xenLaserGateSwitcher*)malloc(sizeof(xenLaserGateSwitcher));
	switcher->sleepTime=sleepTime;
	switcher->index=0;
	switcher->gateList=swLinkedListCreate();
	switcher->execID=swExecManagerAdd(executeLaserGateSwitcher,switcher,NULL);
	swDestroyManagerAdd(destroyLaserGateSwitcher,switcher);
	return switcher;
}


//-------------------------------------------------------------------------------------------
void laserGateSwitcherAdd(xenLaserGateSwitcher *switcher,xenLaserGate *eg){
	swLinkedListAdd(switcher->gateList,eg);
}



//-------------------------------------------------------------------------------------------
void laserGateCreateWithDSL(int countArgs,swArg* argS){
	swPoint p=refPointGet();
	int   type=argS[0].arg.iVal;
	float x=argS[1].arg.fVal+p.x;
	xenLaserGate* eg=laserGateCreate();
	switch(type){
		case 1:
			laserGateSetDisp1(eg,x);
			break;
		case 2:
			laserGateSetDisp2(eg,x);
			break;
		case 3:
			laserGateSetDisp3(eg,x);
			break;
		default:
			laserGateSetDisp1(eg,x);
			break;
	}
	laserGateSwitcherAdd(activeLaserGateSwitcher,eg);
}


//-------------------------------------------------------------------------------------------
void laserGateSwitcherCreateWithDSL(int countArgs,swArg* argS){
	float sleeptTime=argS[0].arg.fVal;
	activeLaserGateSwitcher=laserGateSwitcherCreate(sleeptTime);
}


//-------------------------------------------------------------------------------------------
void laserGateInit(){
	//Single Creation
	laserGateArgs[0].type=SW_ARG_INT;
	laserGateArgs[1].type=SW_ARG_FLOAT;
	swDSLRegisterCommand(laserGateCreateWithDSL,DSL_LASERGATE_CREATION,2,laserGateArgs);

	//Clone Creation
	laserGateSwitcherArgs[0].type=SW_ARG_FLOAT;
	swDSLRegisterCommand(laserGateSwitcherCreateWithDSL,DSL_LASERGATE_SWITCHER_CREATION,1, laserGateSwitcherArgs);
}


//-------------------------------------------------------------------------------------------
void laserGateDeInit(){
	//Nothing Todo
}