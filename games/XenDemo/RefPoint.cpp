#include "../../include/SWEngine.h"

swPoint     refPoint={0,0};


//-------------------------------------------------------------------------------------------
swPoint refPointGet(){
	return refPoint;
}

//-------------------------------------------------------------------------------------------
void refPointSet(float x,float y){
	refPoint.x=x;
	refPoint.y=y;
}
