#include "SWVertex3.h"

//----------------------------------------------------------------
void swVertex3Copy(Vertex3 *v1,Vertex3 *v2){
	v1->x=v2->x;
	v1->y=v2->y;
	v1->z=v2->z;
}

//----------------------------------------------------------------
void swVertex3Set(Vertex3 *activeVertex3,float x, float y,float z){
	activeVertex3->x=x;
	activeVertex3->y=y;
	activeVertex3->z=z;
}

