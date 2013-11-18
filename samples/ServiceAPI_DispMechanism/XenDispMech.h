#ifndef ACTOR_XEN_H
#define ACTOR_XEN_H

#include "../../include/SWEngine.h"

#pragma comment (lib,"../../lib/SWUtil.lib")    
#pragma comment (lib,"../../lib/SWTypes.lib")    
#pragma comment (lib,"../../lib/SWCore.lib")    
#pragma comment (lib,"../../lib/SWServices.lib")    
#pragma comment (lib,"../../lib/SWGame.lib")   
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


#endif
