#include "XenVisible.h"


int spriteID=-1;

//-------------------------------------------------------------------------------------------
void xenInit(){
	spriteID=swGraphicsCreateSprite("XenRunning\\");
}


//-------------------------------------------------------------------------------------------
void xenDeInit(){
	swGraphicsDestroySprite(spriteID);
}

//-------------------------------------------------------------------------------------------
void xenDisplay(void *obj){
	Xen *xen=(Xen*)obj;
	//BlendingMode
	swGraphicsSetBlendingMode(SW_BLENDING_MODE_SOLID);

	//Draw Image
	swGraphicsSetColor0(1,1,1,1);
	swGraphicsRenderSprite0(spriteID,swAnimatorGetIndex(xen->animatorID),&xen->target);
}


//-------------------------------------------------------------------------------------------
Xen* xenCreate(){
	Xen* xen=(Xen*)malloc(sizeof(Xen));
	xen->animatorID=swAnimatorCreate(swGraphicsGetCountOfImgInSprite(spriteID),0.03f);
	swAnimatorSetExecutionMode(xen->animatorID,SW_ANIMATOR_EXEC_FORWARD_LOOP);
	swRectSet(&xen->target,200,200,124,150);
	swDispManagerAdd(xenDisplay,xen,&xen->bVisible,NULL,NULL);
	return xen;
}
//-------------------------------------------------------------------------------------------
void  xenDestroy(Xen *xen){
	swAnimatorDestroy(xen->animatorID);
	swDispManagerDel(xen->animatorID);
	free(xen);	
}







