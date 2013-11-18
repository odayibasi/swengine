#ifndef XEN_SOLIDITEMS_H
#define XEN_SOLIDITEMS_H
#include "../../include/SWEngine.h"
#include "XenCommon.h"


typedef struct _xenSolidItem{
	int    dispID;
	int    imgsprID;
	int    bodyID;
	int    layer;
	bool   bEnabled;
	bool   hasShadow;
	swRect target;
	float  rot;
	int    animID;
}xenSolidItem;

xenSolidItem* solidItemCreate(int imgsprID,int layer,float x,float y,float w,float h,bool bHasShadow);
xenSolidItem* solidItemCreateFixedBody(int imgsprID,int layer,float x,float y,float w,float h,bool bHasShadow);
xenSolidItem* solidItemCreateWithBody(int imgsprID,int layer,float x,float y,float w,float h,bool bHasShadow);
xenSolidItem* solidItemCreateWithBody1(int imgsprID,int layer,float x,float y,float w,float h,bool bHasShadow,xenUserDataType type);
xenSolidItem* solidItemCreateWithAnims(int imgsprID,int layer,float x,float y,float w,float h,float sleepTime, bool hasShadow);



#endif


