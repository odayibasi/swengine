#ifndef VEC2_H
#define VEC2_H
#include "Base.h"

typedef struct _Vec2{
	float index[2];
}Vec2;



void vec2Set(Vec2 *v,float f0, float f1);
void vec2Copy(Vec2 *v1, Vec2 *v2);
void vec2Add(Vec2 *result,Vec2 *v1, Vec2 *v2);
void vec2Mult(Vec2 *result,Vec2 *v1, float a);
void vec2Normalize(Vec2 *result,Vec2 *v);

#endif