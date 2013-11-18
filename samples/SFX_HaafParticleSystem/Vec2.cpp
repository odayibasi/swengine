#include "Base.h"
#include "Vec2.h"
#include <math.h>


//-----------------------------------------------------------
void vec2Set(Vec2 *v,float f0, float f1){
	v->index[0]=f0;
	v->index[1]=f1;
}


//-------------------------------------------------------
void vec2Copy(Vec2 *v1, Vec2 *v2){
	for (int i=0;i<2;i++)
		v1->index[i] = v2->index[i];
}



//-------------------------------------------------------
void vec2Add(Vec2 *result,Vec2 *v1, Vec2 *v2){
	for (int i=0;i<2;i++)
		result->index[i]=v1->index[i] + v2->index[i];
}

//-------------------------------------------------------
void vec2Mult(Vec2 *result,Vec2 *v1, float a){
	for (int i=0;i<2;i++)
		result->index[i]=v1->index[i]*a;	

}


//-------------------------------------------------------
float vec2Length(Vec2 *v){
	return (float)sqrt(v->index[0]*v->index[0]+ v->index[1]*v->index[1]);
}

//-------------------------------------------------------
void vec2Normalize(Vec2 *result,Vec2 *v){
	float OneOverLength = (1/vec2Length(v));
	result->index[0]=OneOverLength*v->index[0];
	result->index[1]=OneOverLength*v->index[1];
}
