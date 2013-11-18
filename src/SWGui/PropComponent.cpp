#include "SWGuiIn.h"

int propFontID=-1;


//-------------------------------------------------------------------------------------------
void swPropComponentSetFont(int fontID){
	propFontID=fontID;
}



//-------------------------------------------------------------------------------------------
void swNumPropComponentDisplay(NumPropComponent *numPropComp,swRect *rect){

	  numPropComp->incButton.rect.x=swRectXPlusW(rect)-(numPropComp->incButton.rect.w+2.5f)*2;
	  numPropComp->incButton.rect.y=rect->y+2.5f;

	  numPropComp->decButton.rect.x=rect->x+2.5f;
	  numPropComp->decButton.rect.y=rect->y+2.5f;

      swNumPropControlBtnDisplay(&numPropComp->incButton);
	  swNumPropControlBtnDisplay(&numPropComp->decButton);
	  
	  
	  float x0=swRectXPlusW(&numPropComp->decButton.rect)+5.0f;
	  float y0=rect->y+2.5f;
	  swNumPropDisplay(&numPropComp->propModel,x0,y0);
}


//-------------------------------------------------------------------------------------------
void swStructPropComponentDisplay(StructPropComponent *structPropComp,swRect *rect){
    NumPropWin *win=(NumPropWin*)structPropComp->numStruct;
	
	swGraphicsSetBlendingMode(SW_BLENDING_MODE_ADDITIVE);
	
	if(structPropComp->bMousOver)
		swGraphicsSetColor0(1,0,0,0.5);
	else{
		swGraphicsSetColor0(1,1,1,0.5);
	}

	float x0=rect->x+15;
	float y0=rect->y;

	swGraphicsRenderText(propFontID,0,12,x0,y0,0,win->titleBar.name);
	swGraphicsSetBlendingMode(SW_BLENDING_MODE_NONE);	
}


//-------------------------------------------------------------------------------------------
void swPropComponentDisplay(PropComponent *propComp){
	if(propComp->type==PROP_COMP_NUM){
		swNumPropComponentDisplay(&propComp->np,&propComp->rect);
	}else if(propComp->type==PROP_COMP_STRUCT){
		swStructPropComponentDisplay(&propComp->sp,&propComp->rect);
	}
}


//-------------------------------------------------------------------------------------------
void swPropComponentInput(PropComponent *propComp,swKeyboardState *keybState,swMouseState *mousState){
	if(propComp->type==PROP_COMP_NUM){
		swNumPropControlBtnInput(&propComp->np.incButton,keybState,mousState);
		swNumPropControlBtnInput(&propComp->np.decButton,keybState,mousState);
	}else if(propComp->type==PROP_COMP_STRUCT){
        propComp->sp.bMousOver=swIntersectionRectAndPoint2(&propComp->rect,mousState->x,mousState->y);
		if(propComp->sp.bMousOver && mousState->btnLEFT){
			NumPropWin *win=(NumPropWin*)propComp->sp.numStruct;
			win->bVisible=true;
		}
	}
}
