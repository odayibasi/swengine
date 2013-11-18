#include "SWGuiIn.h"


//-------------------------------------------------------------------------------------------
void swNumPropControlBtnInit(NumPropControlButton *btn,PropModel *prop,eNumPropEvntType type,int iconSetID,swRect *norm,swRect * mover,swRect *pressed){
	btn->iconSetID=iconSetID;
	swRectCopy(&btn->normSource,norm);
	swRectCopy(&btn->moverSource,mover);
	swRectCopy(&btn->pressedSource,pressed);
	btn->source=&btn->normSource;
	btn->mouseProcessEffectTime=0;
	btn->mouseStateChangedTime=0;
	btn->firstPressed=false;
	btn->sleepPressed=false;
	btn->continuesPressed=false;
	btn->prevMouseLBState=false;
	btn->type=type;
	btn->propModel=prop;
	btn->rect.w=NUMPROP_BTN_SIZE;
	btn->rect.h=NUMPROP_BTN_SIZE;
}



//-------------------------------------------------------------------------------------------
void swNumPropControlBtnDisplay(NumPropControlButton *btn){
	swGraphicsSetBlendingMode(SW_BLENDING_MODE_SOLID);
	swGraphicsSetColor0(1,1,1,1.0);
	swGraphicsRenderImg2(btn->iconSetID,&btn->rect,btn->source);
	swGraphicsSetBlendingMode(SW_BLENDING_MODE_NONE);
	swGraphicsSetColor0(0,0,0,0.5);
	swGraphicsRenderLineRect2(&btn->rect,1);
}



//-------------------------------------------------------------------------------------------
void swNumPropControlBtnInput(NumPropControlButton *btn,swKeyboardState *keybState,swMouseState *mousState){
	bool bMouseOver=swIntersectionRectAndPoint2(&btn->rect,mousState->x,mousState->y);
	if(bMouseOver){
		btn->source=&btn->moverSource;
	}else{
		btn->source=&btn->normSource;
	}

	bool bPressed=false;
	if(bMouseOver && mousState->btnLEFT){
		btn->source=&btn->pressedSource;
		bPressed=true;
	}else{
		btn->firstPressed=false;
		btn->sleepPressed=false;
	}

	if(!btn->prevMouseLBState && bPressed){
		swNumPropProcess(btn->propModel,btn->type);
		btn->firstPressed=true;
		btn->mouseStateChangedTime=swSystemGetElapsedSeconds();
	}

	if(btn->firstPressed){
		float dSleep=swSystemGetElapsedSeconds()-btn->mouseStateChangedTime;
		if(dSleep>1){
			swNumPropProcess(btn->propModel,btn->type);
			btn->firstPressed=false;
			btn->sleepPressed=true;
		}
	}

	if(btn->sleepPressed){
		float dWait=swSystemGetElapsedSeconds()-btn->mouseProcessEffectTime;
		if(dWait>0.02){
			swNumPropProcess(btn->propModel,btn->type);
			btn->mouseProcessEffectTime=swSystemGetElapsedSeconds();
		}
	}

	btn->prevMouseLBState=bPressed;
}
