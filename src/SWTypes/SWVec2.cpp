#include "SWTypesIn.h"
#include <math.h>


swVec2 vec2Result;

//----------------------------------------------------------------
DllExport swVec2* swVec2Create(float x,float y){
	return swPointCreate(x,y);
}

//----------------------------------------------------------------
DllExport void swVec2Destroy(swVec2 *v){
	swPointDestroy(v);
}

//----------------------------------------------------------------
DllExport void swVec2Set(swVec2 *v,float x,float y){
	swPointSet(v,x,y);
}

//----------------------------------------------------------------
DllExport void swVec2Copy(swVec2 *copy,swVec2 *real){
	swPointCopy(copy,real);
}

//----------------------------------------------------------------
DllExport swVec2* swVec2Clone(swVec2 *real){
	return swPointClone(real);
}

//----------------------------------------------------------------
DllExport bool swVec2Equals(swVec2 *v1,swVec2 *v2){
	return swPointEquals(v1,v2);
}

//----------------------------------------------------------------
DllExport swVec2* swVec2Add(swVec2 *v1,swVec2 *v2){
	vec2Result.x=v1->x+v2->x;
	vec2Result.y=v1->y+v2->y;
	return &vec2Result;
}

//----------------------------------------------------------------
DllExport swVec2* swVec2Sub(swVec2 *v1,swVec2 *v2){
	vec2Result.x=v1->x-v2->x;
	vec2Result.y=v1->y-v2->y;
	return &vec2Result;
}

//----------------------------------------------------------------
DllExport swVec2* swVec2Mult(swVec2 *v,float val){
	vec2Result.x=v->x*val;
	vec2Result.y=v->y*val;
	return &vec2Result;
}



//----------------------------------------------------------------
DllExport swVec2* swVec2Div(swVec2 *v,float val){
	vec2Result.x=v->x/val;
	vec2Result.y=v->y/val;
	return &vec2Result;
}


//----------------------------------------------------------------
DllExport float swVec2Dot(swVec2 *v1,swVec2 *v2){
	float result=v1->x*v2->x+v1->y*v2->y;
	return result;
}


//----------------------------------------------------------------
DllExport float swVec2Length(swVec2 *v){
	float result=sqrt(v->x*v->x+v->y*v->y);
	return result;
}

//----------------------------------------------------------------
DllExport float swVec2Angle(swVec2 *v1,swVec2 *v2){
	float dotV1V2=swVec2Dot(v1,v2);
	float magV1=swVec2Length(v1);
	float magV2=swVec2Length(v2);
	float angle=acos(dotV1V2/(magV1*magV2));
    return angle;
}


//----------------------------------------------------------------
DllExport swVec2* swVec2Normal(swVec2 *v){
	float length=swVec2Length(v);
	float oneOverLenght = (1.0f/length);
	vec2Result.x=oneOverLenght*v->x;
	vec2Result.y=oneOverLenght*v->y;	
	return &vec2Result;
}


//----------------------------------------------------------------
DllExport swVec2* swVec2Abs(swVec2 *v){
	vec2Result.x=abs(v->x);
	vec2Result.y=abs(v->y);
	return &vec2Result;
}

//-------------------------------------------------------
DllExport swVec2* swVec2Reflect(swVec2 *normal,swVec2 *light){
	swVec2 v0;	
	float dotValue=swVec2Dot(normal,light);
	swVec2Copy(&v0,swVec2Mult(normal,dotValue*2));
	swVec2Copy(&vec2Result,swVec2Sub(&v0,light));
	return &vec2Result;
}

//-------------------------------------------------------
DllExport swVec2* swVec2CrossX(swVec2 *v,float s){
	vec2Result.x=-s*v->y;
	vec2Result.y= s*v->x;
	return &vec2Result;
}


//-------------------------------------------------------
DllExport swVec2* swVec2CrossY(swVec2 *v,float s){
	vec2Result.x= s*v->y;
	vec2Result.y=-s*v->x;
	return &vec2Result;
}

//-------------------------------------------------------
DllExport swVec2* swVec2MultMat22(swMat22 *m, swVec2 *v){
	vec2Result.x=m->index[0]*v->x+m->index[2]*v->y;
	vec2Result.y=m->index[1]*v->y+m->index[3]*v->y;
	return &vec2Result;
}

