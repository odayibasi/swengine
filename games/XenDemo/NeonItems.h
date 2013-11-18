#ifndef XEN_NEONITEM_H
#define XEN_NEONITEM_H
#include "../../include/SWEngine.h"


typedef struct _xenNeonItem{
	int     dispID;
	int     execID;
	int		imgID;
	swRect	target;
	swColor color;
	bool	bEnabled;
	float	lastTime;
	float	sleepTime;
}neonItem;

neonItem* neonItemCreate(int imgID,float x,float y,float w,float h);
neonItem* neonItemCreate1(int imgID,float x,float y,float w,float h,float startTime,float sleepTime);
neonItem* neonItemCreate2(int imgID,
						  float x,float y,float w,float h,
						  float r,float g,float b,float a,
						  float startTime,float sleepTime);



#endif