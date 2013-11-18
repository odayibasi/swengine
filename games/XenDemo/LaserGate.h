#ifndef XEN_LASERGATE_H
#define XEN_LASERGATE_H


#include "../../include/SWEngine.h"


typedef struct _lsrOrientation{
	int    bodyID;
	swRect rect;
	float  rot;
}lsrOrientation;


typedef struct _xenLaserGate{
	int             dispID;
	lsrOrientation	hose1;
	lsrOrientation	hose2;
	lsrOrientation	elec;
	int				countElec;
	float			xDeltaElec;
	float			yDeltaElec;
	bool			isExecute;
}xenLaserGate;


typedef struct _xenLaserGateSwitcher{
	int   execID;
	int   gateList;
	float sleepTime;
	float lastTime;
	int   index;
}xenLaserGateSwitcher;


xenLaserGate* laserGateCreate();
void laserGateSetDisp(xenLaserGate *eg,
					  float xHose1,float yHose1,float rotHose1,
					  float xHose2,float yHose2,float rotHose2,
					  float xElect,float yElect,float rotElect, 
					  float countE,float xDelta,float yDelta);


void laserGateHoseBodyCreate(lsrOrientation *orx);


void laserGateSetDisp1(xenLaserGate *eg,float egX);
void laserGateSetDisp2(xenLaserGate *eg,float egX);
void laserGateSetDisp3(xenLaserGate *eg,float egX);

xenLaserGateSwitcher* laserGateSwitcherCreate(float sleepTime);
void laserGateSwitcherAdd(xenLaserGateSwitcher *switcher,xenLaserGate *eg);
void laserGateEditorInit(xenLaserGate *eg,float x);


void laserGateInit();
void laserGateDeInit();

#endif