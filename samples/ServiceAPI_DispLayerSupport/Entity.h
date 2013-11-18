#ifndef ENTITY_H
#define ENTITY_H

#include "../../include/SWEngine.h"

#pragma comment (lib,"../../lib/SWUtil.lib")    
#pragma comment (lib,"../../lib/SWTypes.lib")    
#pragma comment (lib,"../../lib/SWCore.lib")    
#pragma comment (lib,"../../lib/SWServices.lib")    
#pragma comment (lib,"../../lib/SWGame.lib")   
#pragma comment (lib,"../../lib/SWGui.lib")   
#pragma comment (lib,"../../lib/SWEngine.lib")   


typedef struct _Xen{
	bool  bVisible;
	int      layer;
	swRect   target;
	int      animatorID;
}Xen;


void  xenInit();
void  xenDeInit();
Xen*  xenCreate();
void  xenDestroy(Xen *xen);



typedef enum _DefenderState{
 DefenderState_Move_X0_X1_Enter,
 DefenderState_Move_X0_X1_Exec,
 DefenderState_Move_X0_X1_Exit,
 DefenderState_RotateLeft_Enter,
 DefenderState_RotateLeft_Exec,
 DefenderState_RotateLeft_Exit,
 DefenderState_SwitchLayer1_Enter,
 DefenderState_SwitchLayer1_Exec,
 DefenderState_SwitchLayer1_Exit,
 DefenderState_Move_X1_X0_Enter,
 DefenderState_Move_X1_X0_Exec,
 DefenderState_Move_X1_X0_Exit,
 DefenderState_SwitchLayer3_Enter,
 DefenderState_SwitchLayer3_Exec,
 DefenderState_SwitchLayer3_Exit,
 DefenderState_RotateRight_Enter,
 DefenderState_RotateRight_Exec,
 DefenderState_RotateRight_Exit,
}DefenderState;


typedef struct _Defender{
	int      layer;
	int      timerID;
	swRect   target;
	swRect	 source;
	int      animatorID;
	int      spriteID;
	DefenderState state;
	int      avoidAnimatorID;
	int      rotateAnimatorID;
}Defender;

void		defenderInit();
void		defenderDeInit();
Defender*	defenderCreate();
void		defenderDestroy(Defender *defender);
void  	    defenderMoveTo(Defender *defender,float x, float y);





#endif
