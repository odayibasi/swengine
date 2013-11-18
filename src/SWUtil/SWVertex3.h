#ifndef SWVERTEX3_H
#define SWVERTEX3_H

#include <windows.h>


typedef struct _Vertex3{
	float x,y,z;
}Vertex3;



void swVertex3Copy(Vertex3 *v1,Vertex3 *v2);
void swVertex3Set(Vertex3 *activeVertex3,float x, float y,float z);

#endif