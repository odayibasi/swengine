#include "SWCoreIn.h"



//----------------------------------------------------------------
void swVectorSet(Vec4 *v,float f0, float f1,float f2,float f3){
	v->index[0]=f0;
	v->index[1]=f1;
	v->index[2]=f2;
	v->index[3]=f3;
}


//----------------------------------------------------------------
void swVectorCopy(Vec4 *v1, Vec4 *v2){
	int i;
	for (i=0;i<4;i++)
		v1->index[i] = v2->index[i];
}


//----------------------------------------------------------------
Vec4* swVectorClone(Vec4 *v){
	Vec4 *vClone=(Vec4*)malloc(sizeof(Vec4));
	swVectorCopy(vClone,v);
	return vClone;
}

//----------------------------------------------------------------
bool swVectorEquals(Vec4 *v1,Vec4 *v2){
	int i;
	for (i=0;i<4;i++){
		if(v1->index[i] != v2->index[i]){
			return false;
		}
	}
	return true;
}

