#include "SWGuiIn.h"


int logoTexID=-1;
int tbFontID=-1;


//-------------------------------------------------------------------------------------------
void swNumPropTitleBarSetLogo(int logoID){
   logoTexID=logoID;
}

//-------------------------------------------------------------------------------------------
void swNumPropTitleBarSetFont(int fontID){
  tbFontID=fontID;
}

//-------------------------------------------------------------------------------------------
void swNumPropTitleBarDisplayLogo(swRect *tbarLayout){
	
	swBlendingMode mode=swGraphicsGetBlendingMode();
	swGraphicsSetBlendingMode(SW_BLENDING_MODE_SOLID);
	swGraphicsSetColor0(1,1,1,1);
	swRect logoRect;
	logoRect.x=tbarLayout->x+2.5f;
	logoRect.y=tbarLayout->y+2.5f;
	logoRect.w=20;
	logoRect.h=20;
	swGraphicsRenderImg0(logoTexID,&logoRect);
	swGraphicsSetBlendingMode(SW_BLENDING_MODE_NONE);

}



//-------------------------------------------------------------------------------------------
void swNumPropTitleBarDisplayTitle(swRect *tbarLayout,char *title){

	swBlendingMode mode=swGraphicsGetBlendingMode();
	swGraphicsSetBlendingMode(SW_BLENDING_MODE_ADDITIVE);
	swGraphicsSetColor0(1,1,1,0.5);
	float x0=tbarLayout->x+25;
	float y0=tbarLayout->y+2.5f;
	swGraphicsRenderText(tbFontID,0,12,x0,y0,0,"%s",title);
	swGraphicsSetBlendingMode(SW_BLENDING_MODE_NONE);

}


//-------------------------------------------------------------------------------------------
void swNumPropTitleBarUpdateCloseBtnPos(swRect *tbarLayout,NumPropTitleBarButton *btn){
	btn->rect.x=swRectXPlusW(tbarLayout)-22.5f;
	btn->rect.y=tbarLayout->y+2.5f;
}

//-------------------------------------------------------------------------------------------
void swNumPropTitleBarExpandBtnPos(swRect *tbarLayout,NumPropTitleBarButton *btn){
	btn->rect.x=swRectXPlusW(tbarLayout)-45;
	btn->rect.y=tbarLayout->y+2.5f;
}


//-------------------------------------------------------------------------------------------
void swNumPropTitleBarTransparentBtnPos(swRect *tbarLayout,NumPropTitleBarButton *btn){
	btn->rect.x=swRectXPlusW(tbarLayout)-67.5f;
	btn->rect.y=tbarLayout->y+2.5f;
}

//-------------------------------------------------------------------------------------------
void swNumPropTitleBarDisplay(NumPropTitleBar *titleBar){
	swGraphicsSetColor0(0.0f,0.3f,0.9f,1.0f);
	swGraphicsRenderSolidRect2(&titleBar->rect);
	swGraphicsSetColor0(0.3f,0.3f,0.7f,1.0f);
	swGraphicsRenderLineRect2(&titleBar->rect,2);


	swNumPropTitleBarDisplayLogo(&titleBar->rect);
	swNumPropTitleBarDisplayTitle(&titleBar->rect,titleBar->name);
	
	
	titleBar->closeBtn.rect.x=swRectXPlusW(&titleBar->rect)-NUMPROP_BTN_SIZE-2.5f;
	titleBar->closeBtn.rect.y=titleBar->rect.y+2.5f;
	swNumPropTitleBarBtnDisplay(&titleBar->closeBtn);

	titleBar->iconifyBtn.rect.x=swRectXPlusW(&titleBar->rect)-(NUMPROP_BTN_SIZE+2.5f)*2;
	titleBar->iconifyBtn.rect.y=titleBar->rect.y+2.5f;
	swNumPropTitleBarBtnDisplay(&titleBar->iconifyBtn);
	
}


//-------------------------------------------------------------------------------------------
void swNumPropTitleBarInput(NumPropTitleBar *titleBar, swKeyboardState *keybState,swMouseState *mousState){
	
	bool inTitleBar=swIntersectionRectAndPoint2(&titleBar->rect,mousState->x,mousState->y);
	swNumPropTitleBarBtnInput(&titleBar->closeBtn,keybState,mousState);
	swNumPropTitleBarBtnInput(&titleBar->iconifyBtn,keybState,mousState);
	swNumPropTitleBarBtnInput(&titleBar->transpBtn,keybState,mousState);
	

	//Dragging
	if(!titleBar->dragStart){
		titleBar->dragStart=inTitleBar && mousState->btnLEFT;
	}else if(titleBar->dragStart && mousState->btnLEFT){
		titleBar->bDragging=true;	
	}else if(titleBar->dragStart && !mousState->btnLEFT){
		titleBar->bDragging=false;
		titleBar->dragStart=false;
	}

	//Selection
	if(inTitleBar && mousState->btnLEFT && !titleBar->prevMouseLBState){
		titleBar->bSelected=true;
	}

	if(!inTitleBar && mousState->btnLEFT && !titleBar->prevMouseLBState){
		titleBar->bSelected=false;
	}



	titleBar->prevMouseLBState=mousState->btnLEFT;
}