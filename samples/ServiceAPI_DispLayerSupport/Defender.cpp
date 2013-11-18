#include "Entity.h"


int spriteVoidID=-1;
int spriteRotID=-1;
int x0_x1_InterpolaterID;
int x1_x0_InterpolaterID;
int L3w_L1w_InterpolaterID;
int L3h_L1h_InterpolaterID;
int L1w_L3w_InterpolaterID;
int L1h_L3h_InterpolaterID;

//-------------------------------------------------------------------------------------------
void defenderInit(){
	spriteVoidID=swGraphicsCreateSprite("Defender\\DefenderAvoid\\");
	spriteRotID=swGraphicsCreateSprite("Defender\\DefenderRotate\\");
	x0_x1_InterpolaterID=swInterpolaterCreate(100.0f,650.0f,3.0f);
	x1_x0_InterpolaterID=swInterpolaterCreate(650.0,100.0,3.0);
	L3w_L1w_InterpolaterID=swInterpolaterCreate(128.0,64.0,2.0);
	L3h_L1h_InterpolaterID=swInterpolaterCreate(64.0,32.0,2.0);
	L1w_L3w_InterpolaterID=swInterpolaterCreate(64.0,128.0,2.0);
	L1h_L3h_InterpolaterID=swInterpolaterCreate(32.0,64.0,2.0);

}


//-------------------------------------------------------------------------------------------
void defenderDeInit(){
	swGraphicsDestroySprite(spriteVoidID);
	swGraphicsDestroySprite(spriteRotID);
}

//-------------------------------------------------------------------------------------------
void defenderDisplay(void *obj){
	Defender *defender=(Defender*)obj;
	//BlendingMode
	swGraphicsSetBlendingMode(SW_BLENDING_MODE_SOLID);

	//Draw Image
	swGraphicsSetColor0(1,1,1,1);
	swGraphicsRenderSprite2(defender->spriteID,swAnimatorGetIndex(defender->animatorID),&defender->target,&defender->source);
}





//-------------------------------------------------------------------------------------------
void defenderExecute(void *obj){
	Defender *defender=(Defender*)obj;
	switch(defender->state){

		//=======================================================================
		// STATE: MOVE X0 TO X1	
		//======================================================================

		case DefenderState_Move_X0_X1_Enter:
			swInterpolaterStart(x0_x1_InterpolaterID);
			defender->state=DefenderState_Move_X0_X1_Exec;
			break;

		case DefenderState_Move_X0_X1_Exec:
			defender->target.x=swInterpolaterGetValue(x0_x1_InterpolaterID);
			if(swInterpolaterIsFinished(x0_x1_InterpolaterID))
				defender->state=DefenderState_Move_X0_X1_Exit;
			break;

		case DefenderState_Move_X0_X1_Exit:
			defender->state=DefenderState_RotateLeft_Enter;
			break;

			//=======================================================================
			// STATE: ROTATE LEFT
			//=======================================================================

		case DefenderState_RotateLeft_Enter:
			defender->spriteID=spriteRotID;
			defender->animatorID=defender->rotateAnimatorID;
			swAnimatorSetIndex(defender->rotateAnimatorID,0);
			swAnimatorSetExecutionMode(defender->rotateAnimatorID,SW_ANIMATOR_EXEC_FORWARD);
			defender->state=DefenderState_RotateLeft_Exec;
			break;

		case DefenderState_RotateLeft_Exec:
			if(swAnimatorIsLastFrameActive(defender->animatorID)){
				defender->state=DefenderState_RotateLeft_Exit;
			}
			break;

		case DefenderState_RotateLeft_Exit:
			swAnimatorSetIndex(defender->rotateAnimatorID,0);
			swRectCopy(&defender->source,&SW_SPRITE_SOURCE_DEFAULT);
			defender->spriteID=spriteVoidID;
			defender->animatorID=defender->avoidAnimatorID;
			defender->state=DefenderState_SwitchLayer1_Enter;
			break;

			//=======================================================================
			// STATE: SWTICH LAYER 3 TO 1
			//=======================================================================

		case DefenderState_SwitchLayer1_Enter:
			swInterpolaterStart(L3w_L1w_InterpolaterID);
			swInterpolaterStart(L3h_L1h_InterpolaterID);
			defender->state=DefenderState_SwitchLayer1_Exec;
			break;

		case DefenderState_SwitchLayer1_Exec:
			defender->target.w=swInterpolaterGetValue(L3w_L1w_InterpolaterID);
			defender->target.h=swInterpolaterGetValue(L3h_L1h_InterpolaterID);
			if(swInterpolaterIsFinished(L3w_L1w_InterpolaterID) &&  swInterpolaterIsFinished(L3h_L1h_InterpolaterID))
				defender->state=DefenderState_SwitchLayer1_Exit;
			break;

		case DefenderState_SwitchLayer1_Exit:
			defender->layer=1;
			defender->state=DefenderState_Move_X1_X0_Enter;
			break;

			//=======================================================================
			// STATE: MOVE X1 TO X0	
			//=======================================================================
		case DefenderState_Move_X1_X0_Enter:
			swInterpolaterStart(x1_x0_InterpolaterID);
			defender->state=DefenderState_Move_X1_X0_Exec;
			break;

		case DefenderState_Move_X1_X0_Exec:
			defender->target.x=swInterpolaterGetValue(x1_x0_InterpolaterID);
			if(swInterpolaterIsFinished(x1_x0_InterpolaterID))
				defender->state=DefenderState_Move_X1_X0_Exit;
			break;

		case DefenderState_Move_X1_X0_Exit:
			defender->state=DefenderState_SwitchLayer3_Enter;
			break;


			//=======================================================================
			// STATE: SWTICH LAYER 1 TO 3
			//=======================================================================
		case DefenderState_SwitchLayer3_Enter:
			swInterpolaterStart(L1w_L3w_InterpolaterID);
			swInterpolaterStart(L1h_L3h_InterpolaterID);
			defender->state=DefenderState_SwitchLayer3_Exec;
			break;

		case DefenderState_SwitchLayer3_Exec:
			defender->target.w=swInterpolaterGetValue(L1w_L3w_InterpolaterID);
			defender->target.h=swInterpolaterGetValue(L1h_L3h_InterpolaterID);
			if(swInterpolaterIsFinished(L1w_L3w_InterpolaterID) &&  swInterpolaterIsFinished(L1h_L3h_InterpolaterID))
				defender->state=DefenderState_SwitchLayer3_Exit;
			break;

		case DefenderState_SwitchLayer3_Exit:
			defender->layer=3;
			defender->state=DefenderState_RotateRight_Enter;
			break;



			//=======================================================================
			// STATE: ROTATE RIGHT
			//=======================================================================
		case DefenderState_RotateRight_Enter:
			defender->spriteID=spriteRotID;
			defender->animatorID=defender->rotateAnimatorID;
			swAnimatorSetIndex(defender->rotateAnimatorID,0);
			swAnimatorSetExecutionMode(defender->rotateAnimatorID,SW_ANIMATOR_EXEC_FORWARD);
			defender->state=DefenderState_RotateRight_Exec;
			break;


		case DefenderState_RotateRight_Exec:
			if(swAnimatorIsLastFrameActive(defender->animatorID)){
				defender->state=DefenderState_RotateRight_Exit;
			}
			break;

		case DefenderState_RotateRight_Exit:
			defender->spriteID=spriteVoidID;
			defender->animatorID=defender->avoidAnimatorID;
			swRectCopy(&defender->source,&SW_SPRITE_SOURCE_MIRRORY);
			swAnimatorSetExecutionMode(defender->avoidAnimatorID,SW_ANIMATOR_EXEC_FORWARD_LOOP);
			defender->state=DefenderState_Move_X0_X1_Enter;
			break;
	}
}



//-------------------------------------------------------------------------------------------
Defender* defenderCreate(){
	Defender* defender=(Defender*)malloc(sizeof(Defender));
	defender->timerID=swTimerCreate(0.01f,defender,defenderExecute);
	swTimerStart(defender->timerID);
	swDispManagerAdd(defenderDisplay,defender,NULL,NULL,&defender->layer);
	defender->layer=3;
	defender->avoidAnimatorID=swAnimatorCreate(swGraphicsGetCountOfImgInSprite(spriteVoidID),0.03f);
	defender->rotateAnimatorID=swAnimatorCreate(swGraphicsGetCountOfImgInSprite(spriteRotID),0.03f);
	swRectSet(&defender->target,100,250,128,64);
	defender->state=DefenderState_RotateRight_Exit;
	return defender;
}

//-------------------------------------------------------------------------------------------
void  defenderDestroy(Defender *defender){
	swAnimatorDestroy(defender->animatorID);
	swDispManagerDel(defender->animatorID);
	free(defender);	
}



