#include "../../include/SWEngine.h"

//-------------------------------------------------------------------------------------------
void physBoundaryDestroy(void *obj){
	int iBodyID=(int)obj;
	swPhysBodyDestroy(iBodyID);

}

//-------------------------------------------------------------------------------------------
void physBoundaryCreate(float x,float y,float w,float h){
	swPhysBodyDefSetPos(x,y);
	swPhysBodyDefSetRectShapeType(w,h);
	int id=swPhysBodyCreate();
	swDestroyManagerAdd(physBoundaryDestroy,(void*)id);

}



