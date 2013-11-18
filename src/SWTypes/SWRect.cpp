#include "SWTypesIn.h"

//---------------------------------------------------------------
DllExport swRect* swRectCreate(float x,float y,float w,float h){
	swRect *rect=(swRect*)malloc(sizeof(swRect));
	swRectSet(rect,x,y,w,h);
	return rect;
}

//---------------------------------------------------------------
DllExport void	swRectDestroy(swRect *rect){
   free(rect);
}

//---------------------------------------------------------------
DllExport void swRectSet(swRect *r,float posX,float posY, float width, float height){
	r->x=posX;
	r->y=posY;
	r->w=width;
	r->h=height;
}

//----------------------------------------------------------------
DllExport void swRectCopy(swRect *r1,swRect *r2){
	r1->x=r2->x;
	r1->y=r2->y;
	r1->w=r2->w;
	r1->h=r2->h;
}

//----------------------------------------------------------------
DllExport swRect* swRectClone(swRect *r){
	swRect *cloneObj=(swRect*)malloc(sizeof(swRect));
	swRectCopy(cloneObj,r);
	return cloneObj;
}

//----------------------------------------------------------------
DllExport bool swRectEquals(swRect *r1,swRect *r2){
	if(r1->x==r2->x && r1->y==r2->y && r1->w==r2->w && r1->h==r2->h) return true;
	return false;
}


//----------------------------------------------------------------
DllExport float	swRectMidX(swRect *rect){
	return rect->x+rect->w/2;	
}

//----------------------------------------------------------------
DllExport float	swRectMidY(swRect *rect){
	return rect->y+rect->h/2;
}


//----------------------------------------------------------------
DllExport float	swRectYPlusH(swRect *rect){
	return rect->y+rect->h;
}

//----------------------------------------------------------------
DllExport float	swRectXPlusW(swRect *rect){
	return rect->x+rect->w;
}


