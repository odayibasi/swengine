#include "SWTypesIn.h"


//----------------------------------------------------------------
DllExport swPoint* swPointCreate(float x,float y){
	swPoint *point=(swPoint*)malloc(sizeof(swPoint));
	swPointSet(point,x,y);
	return point;
}

//----------------------------------------------------------------
DllExport void swPointDestroy(swPoint *point){
	free(point);
}

//----------------------------------------------------------------
DllExport void swPointSet(swPoint *point, float x, float y){
	point->x=x;
	point->y=y;
}

//----------------------------------------------------------------
DllExport void swPointCopy(swPoint *copy,swPoint *real){
	copy->x=real->x;
	copy->y=real->y;
}

//----------------------------------------------------------------
DllExport swPoint* swPointClone(swPoint *real){
	swPoint *cloneObj=(swPoint*)malloc(sizeof(swPoint));
	swPointCopy(cloneObj,real);
	return cloneObj;
}

//----------------------------------------------------------------
DllExport bool swPointEquals(swPoint *point1,swPoint *point2){
	if(point1->x==point2->x && point1->y==point2->y) return true;
	return false;
}

