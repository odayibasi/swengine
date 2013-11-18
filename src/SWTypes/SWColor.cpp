#include "SWTypesIn.h"




//---------------------------------------------------------------
DllExport swColor* swColorCreate(float r,float g,float b,float a){
	swColor *color=(swColor*)malloc(sizeof(swColor));
	swColorSet(color,r,g,b,a);
	return color;
}

//---------------------------------------------------------------
DllExport void	swColorDestroy(swColor *color){
	free(color);
}

//----------------------------------------------------------------
DllExport void swColorSet(swColor *c,float r, float g,float b,float a){
	c->r=r;
	c->g=g;
	c->b=b;
	c->a=a;
}

//----------------------------------------------------------------
DllExport void swColorCopy(swColor *c1,swColor *c2){
	c1->r=c2->r;
	c1->g=c2->g;
	c1->b=c2->b;
	c1->a=c2->a;
}

//----------------------------------------------------------------
DllExport swColor* swColorClone(swColor *c){
	swColor* cloneObj=(swColor*)malloc(sizeof(swColor));
	swColorCopy(cloneObj,c);
	return cloneObj;
}


//----------------------------------------------------------------
DllExport bool swColorEquals(swColor *c1,swColor *c2){
	if(c1->r==c2->r && c1->g==c2->g && c1->b==c2->b && c1->a==c2->a) return true;
	return false;
}



