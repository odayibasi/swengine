#include "SWTypesIn.h"

//----------------------------------------------------------------
DllExport swDimension* swDimensionCreate(float w,float h){
	swDimension *dimension=(swDimension*)malloc(sizeof(swDimension));
	swDimensionSet(dimension,w,h);
	return dimension;
}

//----------------------------------------------------------------
DllExport void swDimensionDestroy(swDimension *dimension){
	free(dimension);
}

//----------------------------------------------------------------
DllExport void swDimensionSet(swDimension *dimension, float w, float h){
	dimension->w=w;
	dimension->h=h;
}

//----------------------------------------------------------------
DllExport void swDimensionCopy(swDimension *copy,swDimension *real){
	copy->w=real->w;
	copy->h=real->h;
}

//----------------------------------------------------------------
DllExport swDimension* swDimensionClone(swDimension *real){
	swDimension *cloneObj=(swDimension*)malloc(sizeof(swDimension));
	swDimensionCopy(cloneObj,real);
	return cloneObj;
}

//----------------------------------------------------------------
DllExport bool swDimensionEquals(swDimension *dimension1,swDimension *dimension2){
	if(dimension1->w==dimension2->h && dimension1->w==dimension2->h) return true;
	return false;
}

