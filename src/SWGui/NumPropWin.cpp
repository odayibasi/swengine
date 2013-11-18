#include "SWGuiIn.h"


int   numPropSetIconID=-1;



//-------------------------------------------------------------------------------------------
DllExport void  swNumPropWinSetVisible(int winID,bool bVisible){
	NumPropWin *win=swNumPropWinGet(winID);
	win->bVisible=bVisible;
}


//-------------------------------------------------------------------------------------------
void  swNumPropWinClose(void *obj){
	NumPropWin *win=(NumPropWin*)obj;
	win->bVisible=false;
}

//-------------------------------------------------------------------------------------------
void  swNumPropWinIconfy(void *obj){
	NumPropWin *win=(NumPropWin*)obj;
	win->bCollapse=!win->bCollapse;
}


//-------------------------------------------------------------------------------------------
void  swNumPropWinSetIconID(int iconID){
	numPropSetIconID=iconID;
}


//-------------------------------------------------------------------------------------------
DllExport void  swNumPropWinSetCollapse(int winID,bool bCollapse){
	NumPropWin *win=swNumPropWinGet(winID);
	win->bCollapse=bCollapse;

}

//-------------------------------------------------------------------------------------------
DllExport void  swNumPropWinSetLocation(int winID,float x,float y){
	NumPropWin *win=swNumPropWinGet(winID);
	win->rect.x=x;
	win->rect.y=y;
}


//-------------------------------------------------------------------------------------------
DllExport void  swNumPropWinSetWidth(int winID,float width){
    NumPropWin *win=swNumPropWinGet(winID);
	win->rect.w=width;
}


//-------------------------------------------------------------------------------------------
DllExport void  swNumPropWinSetVisibleProp(int winID,int visibleProp){
	NumPropWin *win=swNumPropWinGet(winID);
	win->propPanel.visbProp=visibleProp;
}

//-------------------------------------------------------------------------------------------
DllExport void swNumPropWinAddEnum(int winID,char *name,int *iVal,int enumStringList){
	NumPropWin *win=swNumPropWinGet(winID);
	PropComponent *propComp=(PropComponent *)malloc(sizeof(PropComponent));
	propComp->type=PROP_COMP_NUM;
	propComp->rect.x=win->rect.x;
	propComp->rect.y=0;
	propComp->rect.w=win->rect.w;
	propComp->rect.h=NUMPROP_BTN_SIZE;

	NumPropComponent *prop=&propComp->np;
	prop->propModel.name=name;
	prop->propModel.type=NUMPROP_TYPE_ENUM;
	prop->propModel.ep.iVal=iVal;
	prop->propModel.ep.iMin=0;
	prop->propModel.ep.iMax=swLinkedListSize(enumStringList)-1;
	prop->propModel.ep.iDelta=1;
	prop->propModel.ep.enumStrList=enumStringList;


	swRect norm,mover,pressed;
	int    iconSet=numPropSetIconID;

	//Inc
	swMathSourceCalculate(&norm,20,14,0,0);
	swMathSourceCalculate(&mover,20,14,1,0);
	swMathSourceCalculate(&pressed,20,14,9,0);
	swNumPropControlBtnInit(&prop->incButton,&prop->propModel,NUMPROP_EVNT_TYPE_INC,iconSet,&norm,&mover,&pressed);


	//Dec
	swMathSourceCalculate(&norm,20,14,2,0);
	swMathSourceCalculate(&mover,20,14,3,0);
	swMathSourceCalculate(&pressed,20,14,11,0);
	swNumPropControlBtnInit(&prop->decButton,&prop->propModel,NUMPROP_EVNT_TYPE_DEC,iconSet,&norm,&mover,&pressed);

	swLinkedListAdd(win->propPanel.iPropList,propComp);
	win->propPanel.propOfCompSelect.ip.iMax=swLinkedListSize(win->propPanel.iPropList)-win->propPanel.visbProp;
}


//-------------------------------------------------------------------------------------------
DllExport void swNumPropWinAddInt(int winID,char *name,int *iVal,int iMin,int iMax,int iInc){
	NumPropWin *win=swNumPropWinGet(winID);
	PropComponent *propComp=(PropComponent *)malloc(sizeof(PropComponent));
	propComp->type=PROP_COMP_NUM;
	propComp->rect.x=win->rect.x;
	propComp->rect.y=0;
	propComp->rect.w=win->rect.w;
	propComp->rect.h=NUMPROP_BTN_SIZE;

	NumPropComponent *prop=&propComp->np;
	prop->propModel.name=name;
	prop->propModel.type=NUMPROP_TYPE_INT;
	prop->propModel.ip.iVal=iVal;
	prop->propModel.ip.iMin=iMin;
	prop->propModel.ip.iMax=iMax;
	prop->propModel.ip.iDelta=iInc;

	swRect norm,mover,pressed;
	int    iconSet=numPropSetIconID;

	//Inc
	swMathSourceCalculate(&norm,20,14,0,0);
	swMathSourceCalculate(&mover,20,14,1,0);
	swMathSourceCalculate(&pressed,20,14,9,0);
	swNumPropControlBtnInit(&prop->incButton,&prop->propModel,NUMPROP_EVNT_TYPE_INC,iconSet,&norm,&mover,&pressed);


	//Dec
	swMathSourceCalculate(&norm,20,14,2,0);
	swMathSourceCalculate(&mover,20,14,3,0);
	swMathSourceCalculate(&pressed,20,14,11,0);
	swNumPropControlBtnInit(&prop->decButton,&prop->propModel,NUMPROP_EVNT_TYPE_DEC,iconSet,&norm,&mover,&pressed);

	swLinkedListAdd(win->propPanel.iPropList,propComp);
	win->propPanel.propOfCompSelect.ip.iMax=swLinkedListSize(win->propPanel.iPropList)-win->propPanel.visbProp;
}

//-------------------------------------------------------------------------------------------
DllExport void swNumPropWinAddFloat(int winID,char *name,float *fVal,float fMin,float fMax,float fInc){
	NumPropWin *win=swNumPropWinGet(winID);
	PropComponent *propComp=(PropComponent *)malloc(sizeof(PropComponent));
	propComp->type=PROP_COMP_NUM;
	propComp->rect.x=win->rect.x;
	propComp->rect.y=0;
	propComp->rect.w=win->rect.w;
	propComp->rect.h=NUMPROP_BTN_SIZE;
	
	NumPropComponent *prop=&propComp->np;
	prop->propModel.name=name;
	prop->propModel.type=NUMPROP_TYPE_FLOAT;
	prop->propModel.fp.fVal=fVal;
	prop->propModel.fp.fMin=fMin;
	prop->propModel.fp.fMax=fMax;
	prop->propModel.fp.fDelta=fInc;

	swRect norm,mover,pressed;
	int    iconSet=numPropSetIconID;

	//Inc
	swMathSourceCalculate(&norm,20,14,0,0);
	swMathSourceCalculate(&mover,20,14,1,0);
	swMathSourceCalculate(&pressed,20,14,9,0);
	swNumPropControlBtnInit(&prop->incButton,&prop->propModel,NUMPROP_EVNT_TYPE_INC,iconSet,&norm,&mover,&pressed);


	//Dec
	swMathSourceCalculate(&norm,20,14,2,0);
	swMathSourceCalculate(&mover,20,14,3,0);
	swMathSourceCalculate(&pressed,20,14,11,0);
	swNumPropControlBtnInit(&prop->decButton,&prop->propModel,NUMPROP_EVNT_TYPE_DEC,iconSet,&norm,&mover,&pressed);

	swLinkedListAdd(win->propPanel.iPropList,propComp);
	win->propPanel.propOfCompSelect.ip.iMax=swLinkedListSize(win->propPanel.iPropList)-win->propPanel.visbProp;

}

//-------------------------------------------------------------------------------------------
DllExport void swNumPropWinAddDouble(int winID,char *name,double *dVal,double dMin,double dMax,double dInc){
	NumPropWin *win=swNumPropWinGet(winID);
	PropComponent *propComp=(PropComponent *)malloc(sizeof(PropComponent));
	propComp->type=PROP_COMP_NUM;
	propComp->rect.x=win->rect.x;
	propComp->rect.y=0;
	propComp->rect.w=win->rect.w;
	propComp->rect.h=NUMPROP_BTN_SIZE;

	NumPropComponent *prop=&propComp->np;
	prop->propModel.name=name;
	prop->propModel.type=NUMPROP_TYPE_DOUBLE;
	prop->propModel.dp.dVal=dVal;
	prop->propModel.dp.dMin=dMin;
	prop->propModel.dp.dMax=dMax;
	prop->propModel.dp.dDelta=dInc;

	swRect norm,mover,pressed;
	int    iconSet=numPropSetIconID;

	//Inc
	swMathSourceCalculate(&norm,20,14,0,0);
	swMathSourceCalculate(&mover,20,14,1,0);
	swMathSourceCalculate(&pressed,20,14,9,0);
	swNumPropControlBtnInit(&prop->incButton,&prop->propModel,NUMPROP_EVNT_TYPE_INC,iconSet,&norm,&mover,&pressed);


	//Dec
	swMathSourceCalculate(&norm,20,14,2,0);
	swMathSourceCalculate(&mover,20,14,3,0);
	swMathSourceCalculate(&pressed,20,14,11,0);
	swNumPropControlBtnInit(&prop->decButton,&prop->propModel,NUMPROP_EVNT_TYPE_DEC,iconSet,&norm,&mover,&pressed);

	swLinkedListAdd(win->propPanel.iPropList,propComp);
	win->propPanel.propOfCompSelect.ip.iMax=swLinkedListSize(win->propPanel.iPropList)-win->propPanel.visbProp;

}


//-------------------------------------------------------------------------------------------
DllExport void swNumPropWinAddSubWin(int winID,int subWinID){
	NumPropWin *win=swNumPropWinGet(winID);
	NumPropWin *subWin=swNumPropWinGet(subWinID);

	PropComponent *propComp=(PropComponent *)malloc(sizeof(PropComponent));
	propComp->type=PROP_COMP_STRUCT;
	propComp->sp.numStruct=subWin;
	propComp->sp.bMousOver=false;

	propComp->rect.x=win->rect.x;
	propComp->rect.y=0;
	propComp->rect.w=win->rect.w;
	propComp->rect.h=NUMPROP_BTN_SIZE;

	swLinkedListAdd(win->propPanel.iPropList,propComp);
	win->propPanel.propOfCompSelect.ip.iMax=swLinkedListSize(win->propPanel.iPropList)-win->propPanel.visbProp;
}



//-------------------------------------------------------------------------------------------
void swNumPropWinDisplay(NumPropWin *win){

	
	win->propPanel.rect.x=win->rect.x;
	win->propPanel.rect.y=win->rect.y;
	win->propPanel.rect.w=win->rect.w;
	win->propPanel.rect.h=(win->propPanel.visbProp+2)*NUMPROP_COMP_HEIGHT;

	win->titleBar.rect.x=win->propPanel.rect.x;
	win->titleBar.rect.y=swRectYPlusH(&win->propPanel.rect);
	win->titleBar.rect.w=win->rect.w;
	win->titleBar.rect.h=NUMPROP_COMP_HEIGHT;


	if(win->bCollapse){
		swNumPropTitleBarDisplay(&win->titleBar);
		if(win->titleBar.bSelected)
			swGraphicsSetColor0(0.7f,0.3f,0.3f,1.0f);
		else
			swGraphicsSetColor0(0.3f,0.3f,0.7f,1.0f);
		swGraphicsRenderLineRect2(&win->titleBar.rect,2);
	}else{

		swGraphicsSetColor0(0.7f,0.7f,0.7f,1.0f);
		swGraphicsRenderSolidRect2(&win->rect);
		swNumPropTitleBarDisplay(&win->titleBar);		
		swNumPropPanelDisplay(&win->propPanel);

		if(win->titleBar.bSelected)
			swGraphicsSetColor0(0.7f,0.3f,0.3f,1.0f);
		else
			swGraphicsSetColor0(0.3f,0.3f,0.7f,1.0f);
		swGraphicsRenderLineRect2(&win->rect,2);
	}

}



//-------------------------------------------------------------------------------------------
void swNumPropWinInput(NumPropWin *win,swKeyboardState *keybState, swMouseState *mousState){
	
	if(win->titleBar.bDragging && win->titleBar.bSelected){
		win->rect.x+=mousState->dx;
		win->rect.y-=mousState->dy;
	}
	
	swNumPropPanelInput(&win->propPanel,keybState,mousState);    
	swNumPropTitleBarInput(&win->titleBar,keybState,mousState);

}
