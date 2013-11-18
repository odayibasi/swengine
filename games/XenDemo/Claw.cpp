#include "Claw.h"
#include "ClawWeapon.h"
#include "Hud.h"
#include "MoleculerDecompose.h"
#include "SceneManager.h"
#include "PostProcessingFX.h"
#include "XenCommon.h"


extern  int camID;
extern  bool xenShadowActive;


extern	int clawBodySprID;
extern	int clawArmSprID;
extern	int clawHandSprID;
extern	int clawTargetImgID;
extern	int fontID;

swRect	clawBodyTarget={200,32,128,128};
swRect	clawArmTarget={400,200,256,256};
swRect	clawHandTarget={100,200,64,64};
swRect	clawTargetTarget={300,60,32,32};
swRect	clawBodyTargeHistory;
int		clawLayer=5;

int		clawBodyAnimID;
int		clawArmAnimID;
int		clawHandAnimID;

int		clawArmBodyLinkID;
int		clawHandArmLinkID;

int		clawBodyID;
float	clawMass;


xenUserData	clawUserData;


swPoint  clawBody_Arm_Connector_Pos={0.369000f,0.785000f};
swPoint  clawArm_Body_Connector_Pos={0.440000f,0.645000f};
swPoint  clawArm_Hand_Connector_Pos[21]={
	{0.555000f,0.300001f},
	{0.540000f,0.295000f},
	{0.515000f,0.285000f},
	{0.475000f,0.275000f},
	{0.425000f,0.270000f},
	{0.365000f,0.280000f},
	{0.305000f,0.305000f},
	{0.255000f,0.335000f},
	{0.205000f,0.382000f},
	{0.156000f,0.440000f},
	{0.130000f,0.525000f},
	{0.115000f,0.620000f},
	{0.130000f,0.690000f},
	{0.155000f,0.745000f},
	{0.185000f,0.790000f},
	{0.220000f,0.830000f},
	{0.255000f,0.845000f},
	{0.275000f,0.855000f},
	{0.300000f,0.860000f},
	{0.310000f,0.865000f},
	{0.320000f,0.865000f},
};


swPoint clawHand_Arm_Connector_Pos={0.14,0.86};


swPoint clawBodyWP={0,0};
swPoint clawArmWP={0,0};
swPoint wpClawHand={0,0};

float   rotClawHand=0;
float   rotClawTarget=0;
float   rotHClawTarget=0;
float   speedClaw=3.5f;
bool    clawInteractionActive=false;
bool    clawHangingOnAir=true;


swKeybBehaviourListener clawListener;
bool		clawPaused=false;
bool		clawLive=true;


int			clawCannonCount=999;
int			clawLaserCount=20;
int			clawLawCount=10;
int			clawGuidedCount=0;
int			clawSharapnelCount=0;
int			clawHammerCount=0;

eWpnType	clawActiveWpn=WPN_TYPE_NONE;
eBombType	clawActiveBomb=BOMB_TYPE_NONE;

clawData	clawUserDataObj;
bool		bClawLive=true;
bool		bClawGodMode=false;
extern int	particleLitID;
bool		bClawInMoleculerDecompose=false;

int			clawDispID;
int			clawExecID;
int			clawIntrID;


//-------------------------------------------------------------------------------------------
void clawDisplay(swColor c,swRect *rBody,swRect *rArm, swRect *rHand, swRect *rTarget){


	int bodyAnimIndex=swAnimatorGetIndex(clawBodyAnimID);
	int armAnimIndex=swAnimatorGetIndex(clawArmAnimID);
	int handAnimIndex=swAnimatorGetIndex(clawHandAnimID);


	swLinkerBind0(clawArmBodyLinkID,rBody,rArm);
	swLinkerBind2(clawHandArmLinkID,&SW_SPRITE_SOURCE_DEFAULT,rArm,&clawArmWP,0,armAnimIndex,&SW_SPRITE_SOURCE_DEFAULT,rHand,&wpClawHand,rotClawHand,0);

	swGraphicsSetBlendingMode(SW_BLENDING_MODE_SOLID);

	swGraphicsSetColor1(&c);
	swGraphicsRenderSprite4(clawHandSprID,handAnimIndex,rHand,rotClawHand,&wpClawHand);
	swGraphicsRenderSprite0(clawArmSprID,armAnimIndex,rArm);
	swGraphicsRenderSprite4(clawBodySprID,bodyAnimIndex,rBody,0,&clawBodyWP);
	swGraphicsRenderImg1(clawTargetImgID,rTarget,rotClawTarget);

	if(bClawInMoleculerDecompose){
		swGraphicsSetBlendingMode(SW_BLENDING_MODE_ADDITIVE);
		swGraphicsSetColor0(0,0.4,0.8,0.5);
		swGraphicsRenderImg0(particleLitID,rBody);
		bClawInMoleculerDecompose=false;
	}




}


//-------------------------------------------------------------------------------------------
void prepareClawShadow(swRect *rT,swRect rS){
	float dX=5;
	float dY=5;
	float dW=15;
	float dH=15;

	rT->x=rS.x+dX; rT->y=rS.y+dY; rT->w=rS.w+dW; rT->h=rS.h+dH; 
}




//-------------------------------------------------------------------------------------------
void renderClaw(){
	clawDisplay(SWCOLOR_WHITE,&clawBodyTarget,&clawArmTarget,&clawHandTarget,&clawTargetTarget);
}

//-------------------------------------------------------------------------------------------
void renderClawShadow(){

	swColor shdColor={0,0,0,0.5};
	swRect  shdBody,shdArm,shdHand,shdTarget;

	prepareClawShadow(&shdBody,clawBodyTarget);
	prepareClawShadow(&shdArm,clawArmTarget);
	prepareClawShadow(&shdHand,clawHandTarget);
	prepareClawShadow(&shdTarget,clawTargetTarget);
	clawDisplay(shdColor,&shdBody,&shdArm,&shdHand,&shdTarget);
}



//-------------------------------------------------------------------------------------------
void renderClawShadow(void *obj){
	if(xenShadowActive)
		renderClawShadow();
	renderClaw();
}


//-------------------------------------------------------------------------------------------
void applyForceToClaw(float xMultiplier,float yMultiplier){

	swVec2 pos;
	pos.x=swRectMidX(&clawBodyTarget); pos.y=swRectMidY(&clawBodyTarget);
	swVec2 force;
	force.x=clawMass*xMultiplier; force.y=clawMass*yMultiplier;
	swPhysBodyApplyForce(clawBodyID,force,pos);
}


//-------------------------------------------------------------------------------------------
void executeClaw(void *obj){

	float dX,dY,dRot;

	if(clawHangingOnAir)
		applyForceToClaw(0,2);

	//Body
	dY=clawBodyTarget.y-clawBodyTargeHistory.y;
	if(dY>0) swAnimatorSetExecutionMode(clawBodyAnimID,SW_ANIMATOR_EXEC_FORWARD);
	else swAnimatorSetExecutionMode(clawBodyAnimID,SW_ANIMATOR_EXEC_BACKWARD);

	//Arm
	dY=clawTargetTarget.y-clawBodyTarget.y;
	if(dY>0) swAnimatorSetExecutionMode(clawArmAnimID,SW_ANIMATOR_EXEC_FORWARD);
	else swAnimatorSetExecutionMode(clawArmAnimID,SW_ANIMATOR_EXEC_BACKWARD);

	//Hand
	dY=clawTargetTarget.y-clawHandTarget.y;
	dX=clawTargetTarget.x-clawHandTarget.x;
	dRot=((int)(43+swMathDegree(0,0,dX,dY)))%360;
	rotClawHand=dRot;

	dRot=rotClawTarget-rotHClawTarget;
	if(dRot!=0){
		if(swAnimatorIsLastFrameActive(clawHandAnimID))
			swAnimatorSetIndex(clawHandAnimID,25);
		swAnimatorSetExecutionMode(clawHandAnimID,SW_ANIMATOR_EXEC_FORWARD);
	}else{
		swAnimatorSetExecutionMode(clawHandAnimID,SW_ANIMATOR_EXEC_BACKWARD);
	}


	//Target
	hudSetEnabled(clawTargetTarget.y>200 && clawBodyTarget.y>100);

	if(bClawGodMode){
		clawUserDataObj.health=100;
		clawUserDataObj.shield=100;
	}

	hudSetHealth(clawUserDataObj.health);
	hudSetShield(clawUserDataObj.shield);

	swGraphicsAddCamPosX(camID,clawBodyTarget.x-clawBodyTargeHistory.x);
	swDispManagerSetCullRegionPos(swGraphicsGetCamPosX(camID),swGraphicsGetCamPosY(camID));

	clawBodyTargeHistory=clawBodyTarget;
	rotHClawTarget=rotClawTarget;




	if(clawUserDataObj.health<=0 && bClawLive){
		bClawLive=false;
		scnMngrSetMode(SCENE_DEMO_LVL_PLAY_GAMEOVER);
	}
}


//-------------------------------------------------------------------------------------------
void listenKeyForClawMgt(swKeyEnum key){
	if(key==SWKEY_PAUSE){
		clawPaused=!clawPaused;
		xenDemoSetPaused(clawPaused);
	}

	if(key==SWKEY_G){
		bClawGodMode=!bClawGodMode;
	}
}


//-------------------------------------------------------------------------------------------
int clawGetActiveWpnCount(){
	switch(clawActiveWpn){
		case WPN_TYPE_CANNON:
			return clawCannonCount;
		case WPN_TYPE_LASER:
			return clawLaserCount;
		case WPN_TYPE_LAW:
			return clawLawCount;
	}
	return 0;
}


//-------------------------------------------------------------------------------------------
void clawSelectAnotherWeapon(){
	if(clawCannonCount>0){
		clawActiveWpn=WPN_TYPE_CANNON;
		hudSetWeaponType(clawActiveWpn);
	}else if(clawLaserCount>0){
		clawActiveWpn=WPN_TYPE_LASER;
		hudSetWeaponType(clawActiveWpn);
	}else if(clawLawCount>0){
		clawActiveWpn=WPN_TYPE_LAW;
		hudSetWeaponType(clawActiveWpn);
	}else{
		clawActiveWpn=WPN_TYPE_NONE;
		hudSetWeaponType(clawActiveWpn);
	}
}



//-------------------------------------------------------------------------------------------
void clawDecreaseAndUpdateActiveWpnCount(){
	switch(clawActiveWpn){
		case WPN_TYPE_CANNON:
			clawCannonCount--;
			hudSetWeaponCount(WPN_TYPE_CANNON,clawCannonCount);
			break;
		case WPN_TYPE_LASER:
			clawLaserCount--;
			hudSetWeaponCount(WPN_TYPE_LASER,clawLaserCount);			
			break;
		case WPN_TYPE_LAW:
			clawLawCount--;
			hudSetWeaponCount(WPN_TYPE_LAW,clawLawCount);			
			break;
		default:
			break;
	}
}




//-------------------------------------------------------------------------------------------
void listenKeybAndMousForClawMgt(void *obj,swKeyboardState *keybState, swMouseState *mousState){

	swVec2 velocity={0,0};
	
	if(keybState->keyZ){
		fullSceenFXSetActive(FULLSCREEN_FX_NONE);
	}else if(keybState->keyX){
		fullSceenFXSetActive(FULLSCREEN_FX_GRAYSCALED);
	}else if(keybState->keyC){
		fullSceenFXSetActive(FULLSCREEN_FX_SHARPEN);
	}else if(keybState->keyV){
		fullSceenFXSetActive(FULLSCREEN_FX_DIOGNALBLUR);
	}else if(keybState->keyB){
		fullSceenFXSetActive(FULLSCREEN_FX_MULTIPLIER);
	}else if(keybState->keyN){
		fullSceenFXSetActive(FULLSCREEN_FX_INVERTED);
	}else if(keybState->keyM){
		fullSceenFXSetActive(FULLSCREEN_FX_EMBOSSS);
	}else if(keybState->keyQ){
		shockWaveEnter(clawTargetTarget.x,clawTargetTarget.y);
	}

	if(keybState->keyW){
		velocity.y=speedClaw;
	}

	if(keybState->keyS){
		velocity.y=-speedClaw;
	}

	if(keybState->keyA){
		velocity.x=-speedClaw;
	}

	if(keybState->keyD){
		velocity.x=speedClaw;
	}

	if(keybState->key1){
		clawActiveWpn=WPN_TYPE_CANNON;
		hudSetWeaponType(clawActiveWpn);
	}else if(keybState->key2){
		clawActiveWpn=WPN_TYPE_LASER;
		hudSetWeaponType(clawActiveWpn);
	}else if(keybState->key3){
		clawActiveWpn=WPN_TYPE_LAW;
		hudSetWeaponType(clawActiveWpn);
	}

	if(keybState->key4){
		clawActiveBomb=BOMB_TYPE_GUIDEDMISSILE;
		hudSetBombType(clawActiveBomb);
	}else if(keybState->key5){
		clawActiveBomb=BOMB_TYPE_SHARAPNEL;
		hudSetBombType(clawActiveBomb);
	}else if(keybState->key6){
		clawActiveBomb=BOMB_TYPE_HAMMER;
		hudSetBombType(clawActiveBomb);
	}


	//Update Velocity
	swPhysBodySetLinearVelocity(clawBodyID,velocity);

	//Target Control
	clawTargetTarget.x=mousState->x-clawTargetTarget.w/2+swGraphicsGetCamPosX(camID);
	clawTargetTarget.y=mousState->y-clawTargetTarget.h/2+swGraphicsGetCamPosY(camID);

	if(mousState->btnLEFT){	
		if(clawGetActiveWpnCount()>0){
			rotClawTarget+=15;
			bool bSuccess=clawWeaponFire(clawHandTarget,clawTargetTarget);
			if(bSuccess) clawDecreaseAndUpdateActiveWpnCount();
		}else{
			clawSelectAnotherWeapon();	
		}
	}
}



//-------------------------------------------------------------------------------------------
void decomposeClaw(void *obj){
	if(clawUserDataObj.shield>0){
		clawUserDataObj.shield--;
	}else if(clawUserDataObj.health>0){
		clawUserDataObj.health--;
	}
	bClawInMoleculerDecompose=true;
}


//-------------------------------------------------------------------------------------------
void clawDestroy(void *obj){
	swAnimatorDestroy(clawBodyAnimID);
	swAnimatorDestroy(clawArmAnimID);
	swAnimatorDestroy(clawHandAnimID);
	
	swLinkerDestroy(clawArmBodyLinkID);
	swLinkerDestroy(clawHandArmLinkID);

	swPhysBodyDestroy(clawBodyID);
	swDispManagerDel(clawDispID);

	clawSetEnabledInteraction(false);
	swInteractionManagerDel(clawIntrID);
	swExecManagerDel(clawExecID);
	swKeybBehaviourDel(&clawListener);

}


//-------------------------------------------------------------------------------------------
void clawCreate(){
	clawBodyAnimID=swAnimatorCreate(swGraphicsGetCountOfImgInSprite(clawBodySprID),0.02f);
	clawArmAnimID=swAnimatorCreate(swGraphicsGetCountOfImgInSprite(clawArmSprID),0.02f);
	clawHandAnimID=swAnimatorCreate(swGraphicsGetCountOfImgInSprite(clawHandSprID),0.02f);

	clawArmBodyLinkID=swLinkerCreate(&clawBody_Arm_Connector_Pos,&clawArm_Body_Connector_Pos);
	clawHandArmLinkID=swLinkerCreate(clawArm_Hand_Connector_Pos,&clawHand_Arm_Connector_Pos);

	//Phys..
	clawUserDataObj.health=100;
	clawUserDataObj.shield=100;
	clawUserData.obj=&clawUserDataObj;
	clawUserData.type=XEN_CLAW;

	swPhysBodyDefSetUserData(&clawUserData);
	swPhysBodyDefSetFilterGroupIndex(-4);
	swPhysBodyDefSetPos(clawBodyTarget.x,clawBodyTarget.y);
	swPhysBodyDefSetRectShapeType(clawBodyTarget.w,clawBodyTarget.h+40);
	swPhysBodyDefSetDensity(1.0f);
	swPhysBodyDefSetFixedRotation(true);
	swPhysBodyDefSetPosListener(&clawBodyTarget.x,&clawBodyTarget.y);
	clawBodyID=swPhysBodyCreate();
	clawMass=swPhysBodyGetMass(clawBodyID);
	clawBodyTargeHistory=clawBodyTarget;



	clawDispID=swDispManagerAdd(renderClawShadow,NULL,NULL,NULL,&clawLayer);	
	clawIntrID=swInteractionManagerAdd(listenKeybAndMousForClawMgt,NULL,&clawInteractionActive);
	clawExecID=swExecManagerAdd(executeClaw,NULL,NULL);
	

	//KeyListener
	clawListener.typed=NULL;
	clawListener.pressed=listenKeyForClawMgt;
	clawListener.released=NULL;
	swKeybBehaviourAdd(&clawListener);
	moleculerDecomposerAdd(&clawLive,&clawBodyTarget,decomposeClaw,NULL);


	hudSetWeaponCount(WPN_TYPE_CANNON,clawCannonCount);
	hudSetWeaponCount(WPN_TYPE_LASER,clawLaserCount);
	hudSetWeaponCount(WPN_TYPE_LAW,clawLawCount);

	hudSetBombCount(BOMB_TYPE_GUIDEDMISSILE,clawGuidedCount);
	hudSetBombCount(BOMB_TYPE_SHARAPNEL,clawSharapnelCount);
	hudSetBombCount(BOMB_TYPE_HAMMER,clawHammerCount);

	swDestroyManagerAdd(clawDestroy,NULL);

}



//-------------------------------------------------------------------------------------------
void clawSetEnabledInteraction(bool clawIntrActive){	
	clawInteractionActive=clawIntrActive;
}

//-------------------------------------------------------------------------------------------
void clawSetHangingOnAir(bool hanging){
	clawHangingOnAir=hanging;
}

//-------------------------------------------------------------------------------------------
void clawSetPos(float x, float y){
	swPhysBodySetXForm1(clawBodyID,x,y,0);
}

//-------------------------------------------------------------------------------------------
void clawSetTargetPos(float x, float y){
	clawTargetTarget.x=x; clawTargetTarget.y=y; 
}


//-------------------------------------------------------------------------------------------
swRect *clawGetRect(){
	return &clawBodyTarget;
}

//-------------------------------------------------------------------------------------------
swRect *clawGetHRect(){
	return &clawBodyTargeHistory;
}

