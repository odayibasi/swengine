#include "../../include/SWEngine.h"
#include "MoleculerDecompose.h"
#include "ObjParticle.h"
#include "CargoBox.h"

extern bool xenShadowActive;
extern int	cargoBoxID;
swPoint		cargoBoxWP={0,0};


//-------------------------------------------------------------------------------------------
void cargoBoxRenderWithParams(swColor color,xenCargoBox *cargoBox,swRect target){
	swGraphicsSetColor1(&color);
	swGraphicsRenderImg4(cargoBoxID,&target,cargoBox->rot,&cargoBoxWP);
}


//-------------------------------------------------------------------------------------------
void cargoBoxPrepareShadow(swRect *rT,swRect rS){
	float dX=0;
	float dY=0;
	float dW=8;
	float dH=8;
	rT->x=rS.x+dX; rT->y=rS.y+dY; rT->w=rS.w+dW; rT->h=rS.h+dH; 
}

//-------------------------------------------------------------------------------------------
void cargoBoxRender(xenCargoBox *cargoBox){
	cargoBoxRenderWithParams(SWCOLOR_WHITE,cargoBox,cargoBox->target);
}

//-------------------------------------------------------------------------------------------
void cargoBoxRenderShadow(xenCargoBox *cargoBox){
	swColor shdColor={0,0,0,0.5};
	swRect  shdRect;
	cargoBoxPrepareShadow(&shdRect,cargoBox->target);
	cargoBoxRenderWithParams(shdColor,cargoBox,shdRect);
}



//-------------------------------------------------------------------------------------------
void cargoBoxDisplay(void *obj){
	xenCargoBox *cargoBox=(xenCargoBox*)obj; 
	swGraphicsSetBlendingMode(SW_BLENDING_MODE_SOLID);
	if(xenShadowActive)
		cargoBoxRenderShadow(cargoBox);
	cargoBoxRender(cargoBox);
}




//-------------------------------------------------------------------------------------------
void cargoBoxDecomposeMolecules(void *obj){
	xenCargoBox *cargoBox=(xenCargoBox*)obj;
	objParticleGenerate(&cargoBox->target,5,5,cargoBoxID,0,cargoBox->rot,0.5,0.05f,10);
	cargoBox->bEnabled=false;
}


//-------------------------------------------------------------------------------------------
void cargoBoxDestroy(void *obj){
	xenCargoBox *cargoBox=(xenCargoBox*)obj;
	swDispManagerDel(cargoBox->dispID);
	swPhysBodyDestroy(cargoBox->bodyID);
	free(cargoBox);
}



//-------------------------------------------------------------------------------------------
xenCargoBox*cargoBoxCreate(int layer, float x, float y){
	xenCargoBox* cargoBox=(xenCargoBox*)malloc(sizeof(xenCargoBox));
	cargoBox->layer=layer;
	cargoBox->bEnabled=true;
	cargoBox->rot=0;
	swRectSet(&cargoBox->target,x,y,32,32);
	cargoBox->dispID=swDispManagerAdd(cargoBoxDisplay,cargoBox,&cargoBox->bEnabled,&cargoBox->target,&cargoBox->layer);
	moleculerDecomposerAdd(&cargoBox->bEnabled,&cargoBox->target,cargoBoxDecomposeMolecules,cargoBox);

	//Register Physics
	swPhysBodyDefSetPos(x,y);
	swPhysBodyDefSetRectShapeType(32,32);
	swPhysBodyDefSetDensity(1.0f);
	swPhysBodyDefSetPosListener(&cargoBox->target.x,&cargoBox->target.y);
	swPhysBodyDefSetAngleListener(&cargoBox->rot);
	cargoBox->bodyID=swPhysBodyCreate();
	
	//Register Destroy Manager
	swDestroyManagerAdd(cargoBoxDestroy,cargoBox);

	return cargoBox;
}



