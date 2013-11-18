#include "SWGuiIn.h"



//-------------------------------------------------------------------------------------------
void swNumPropTitleBarBtnInit(NumPropTitleBarButton *btn,void (*callback)(void *),void *obj,int iconSetID,swRect *normalS,swRect *mOverS){
	btn->bMouseOver=false;
	btn->prevMouseLBState=false;
	btn->callback=callback;
	btn->obj=obj;
	btn->rect.w=NUMPROP_BTN_SIZE;
	btn->rect.h=NUMPROP_BTN_SIZE;
	btn->iconSetID=iconSetID;
	swRectCopy(&btn->normalSource,normalS);
	swRectCopy(&btn->mouseOverSource,mOverS);
	btn->source=&btn->normalSource;
}



//-------------------------------------------------------------------------------------------
void swNumPropTitleBarBtnDisplay(NumPropTitleBarButton *btn){
	
	swGraphicsSetBlendingMode(SW_BLENDING_MODE_SOLID);
	swGraphicsSetColor0(1,1,1,1);
	swGraphicsRenderImg2(btn->iconSetID,&btn->rect,btn->source);
	swGraphicsSetBlendingMode(SW_BLENDING_MODE_NONE);
	swGraphicsSetColor0(0,0,0,0.5);
	swGraphicsRenderLineRect2(&btn->rect,1);

}



//-------------------------------------------------------------------------------------------
void swNumPropTitleBarBtnInput(NumPropTitleBarButton *btn,swKeyboardState *keybState,swMouseState *mousState){
	btn->bMouseOver=swIntersectionRectAndPoint2(&btn->rect,mousState->x,mousState->y);
	if(btn->bMouseOver){
		btn->source=&btn->mouseOverSource;
	}else{
		btn->source=&btn->normalSource;
	}


	if(btn->bMouseOver && mousState->btnLEFT && !btn->prevMouseLBState){
		void(*callBFunc)(void *);
		callBFunc=btn->callback;
		(*callBFunc)(btn->obj);
	}
	btn->prevMouseLBState=mousState->btnLEFT;
}

