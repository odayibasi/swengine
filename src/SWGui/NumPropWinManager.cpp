#include "SWGuiIn.h"



char *numPropRscFullPath;
int   numPropWinList=-1;
int   numPropWinIDCounter=0;

char   logoPath[512];
char   fontPath[512];
char   iconSetPath[512];


int   numPropUpBtnNormalTexID=-1;
int   numPropUpBtnMOverTexID=-1;
int   numPropUpBtnPressedTexID=-1;


int   numPropDownBtnNormalTexID=-1;
int   numPropDownBtnMOverTexID=-1;
int   numPropDownBtnPressedTexID=-1;


int   numPropWinLogoID=-1;
int   numPropWinFontID=-1;
int   numPropWinIconSetID=-1;

NumPropWin *numPropWinSelected=NULL;

//-------------------------------------------------------------------------------------------
DllExport void swNumPropWinSetPath(char *path){
	numPropRscFullPath=path;
	strcpy(logoPath,path);
	strcat(logoPath,"logo.tga");
 	numPropWinLogoID=swGraphicsCreateImg(logoPath);

	strcpy(fontPath,path);
	strcat(fontPath,"font.tga");
	numPropWinFontID=swGraphicsCreateFont(fontPath);

	strcpy(iconSetPath,path);
	strcat(iconSetPath,"IconSet.tga");
	numPropWinIconSetID=swGraphicsCreateImg(iconSetPath);

	swNumPropWinSetIconID(numPropWinIconSetID);
	swNumPropTitleBarSetLogo(numPropWinLogoID);
	swNumPropTitleBarSetFont(numPropWinFontID);
	swPropComponentSetFont(numPropWinFontID);
	swNumPropSetFont(numPropWinFontID);

}


//-------------------------------------------------------------------------------------------
DllExport void swNumPropWinSetDependency(int logoID,int fontID,int iconSetID){
	numPropWinLogoID=logoID;
	numPropWinFontID=fontID;
	numPropWinIconSetID=iconSetID;
	swNumPropWinSetIconID(numPropWinIconSetID);
	swNumPropTitleBarSetLogo(numPropWinLogoID);
	swNumPropTitleBarSetFont(numPropWinFontID);
	swPropComponentSetFont(numPropWinFontID);
	swNumPropSetFont(numPropWinFontID);

}



//-------------------------------------------------------------------------------------------
void swNumPropertyWinManagerDisplay(void *obj){
	NumPropWin *win=(NumPropWin *)swLinkedListGetFirst(numPropWinList);
	while(win!=NULL){
		if(win->bVisible)
			swNumPropWinDisplay(win);
		win=(NumPropWin *)swLinkedListGetNext(numPropWinList);
	}

	if(numPropWinSelected!=NULL)
		swNumPropWinDisplay(numPropWinSelected);
}


//-------------------------------------------------------------------------------------------
void swNumPropertyWinManagerInput(void *obj,swKeyboardState *keybState,swMouseState *mousState){
	NumPropWin *win=(NumPropWin *)swLinkedListGetFirst(numPropWinList);
	while(win!=NULL){
		if(win->bVisible)
		swNumPropWinInput(win,keybState,mousState);		
		win=(NumPropWin *)swLinkedListGetNext(numPropWinList);
	}

	
	numPropWinSelected=NULL;
	win=(NumPropWin *)swLinkedListGetFirst(numPropWinList);
	while(win!=NULL){
		if(win->bVisible && win->titleBar.bSelected && numPropWinSelected==NULL){
			numPropWinSelected=win;
		}else{
			win->titleBar.bSelected=false;
		}
		win=(NumPropWin *)swLinkedListGetNext(numPropWinList);
	}

    

}


//-------------------------------------------------------------------------------------------
void swNumPropWinManagerInit(){
	numPropWinList=swLinkedListCreate();
	swDispManagerAdd(swNumPropertyWinManagerDisplay,NULL,NULL,NULL,NULL);
	swInteractionManagerAdd(swNumPropertyWinManagerInput,NULL,NULL);
}

//-------------------------------------------------------------------------------------------
void swNumPropWinManagerDeInit(){
	swLinkedListDestroy(numPropWinList);
}	





//-------------------------------------------------------------------------------------------
DllExport int  swNumPropWinCreate(char *name,float x,float y,float w,int countVisbProp){
	NumPropWin *win=(NumPropWin *)malloc(sizeof(NumPropWin));
	win->id=numPropWinIDCounter++;
	win->titleBar.name=name;
	
	win->rect.x=x;
	win->rect.y=y;
	win->rect.w=w;
	win->rect.h=(countVisbProp+3)*NUMPROP_COMP_HEIGHT;
	
	win->bVisible=false;
	win->bCollapse=false;
	win->bTransparent=false;

	//TitleBar
	win->titleBar.bSelected=false;
	win->titleBar.bDragging=false;
	win->titleBar.dragStart=false;

	swRect norm,mover,pressed;
	int    iconSet=numPropWinIconSetID;
	//CloseBtn
	swMathSourceCalculate(&norm,20,14,0,3);
	swMathSourceCalculate(&mover,20,14,1,3);
	swNumPropTitleBarBtnInit(&win->titleBar.closeBtn,swNumPropWinClose,win,iconSet,&norm,&mover);
	
	//Iconfy
	swMathSourceCalculate(&norm,20,14,4,3);
	swMathSourceCalculate(&mover,20,14,5,3);
	swNumPropTitleBarBtnInit(&win->titleBar.iconifyBtn,swNumPropWinIconfy,win,iconSet,&norm,&mover);


	//PropPanel
    win->propPanel.iPropList=swLinkedListCreate();
	win->propPanel.iPropIndex=0;
	win->propPanel.visbProp=countVisbProp;

	win->propPanel.rect.x=win->rect.x;
	win->propPanel.rect.y=win->rect.y;
	win->propPanel.rect.w=win->rect.w;
	win->propPanel.rect.h=win->rect.h-NUMPROP_COMP_HEIGHT;

	win->propPanel.propOfCompSelect.type=NUMPROP_TYPE_INT;
	win->propPanel.propOfCompSelect.name="X";
	win->propPanel.propOfCompSelect.ip.iVal=&win->propPanel.iPropIndex;
	win->propPanel.propOfCompSelect.ip.iDelta=1;
	win->propPanel.propOfCompSelect.ip.iMin=0;
	win->propPanel.propOfCompSelect.ip.iMax=0;


	//UpBtn
	swMathSourceCalculate(&norm,20,14,14,3);
	swMathSourceCalculate(&mover,20,14,15,3);
	swMathSourceCalculate(&pressed,20,14,11,2);
	swNumPropControlBtnInit(&win->propPanel.upBtn,&win->propPanel.propOfCompSelect,NUMPROP_EVNT_TYPE_DEC,iconSet
		,&norm,&mover,&pressed);


	//DownBtn
	swMathSourceCalculate(&norm,20,14,12,3);
	swMathSourceCalculate(&mover,20,14,13,3);
	swMathSourceCalculate(&pressed,20,14,7,2);
	swNumPropControlBtnInit(&win->propPanel.downBtn,&win->propPanel.propOfCompSelect,NUMPROP_EVNT_TYPE_INC,iconSet,&norm,&mover,&pressed);


	swLinkedListAdd(numPropWinList,win);
	return win->id;

}


//-------------------------------------------------------------------------------------------
DllExport int  swNumPropPointWinCreate(char *name,float x,float y,swPoint *point){
	int winID=swNumPropWinCreate(name,x,y,200,2);
	swNumPropWinAddFloat(winID,"PosX",&point->x,FLT_MIN,FLT_MAX,1);
	swNumPropWinAddFloat(winID,"PosY",&point->y,FLT_MIN,FLT_MAX,1);
	return winID;
}


//-------------------------------------------------------------------------------------------
DllExport int  swNumPropDimWinCreate(char *name,float x,float y,swDimension *dim){
	int winID=swNumPropWinCreate(name,x,y,200,2);
	swNumPropWinAddFloat(winID,"Width",&dim->w,FLT_MIN,FLT_MAX,1);
	swNumPropWinAddFloat(winID,"Height",&dim->h,FLT_MIN,FLT_MAX,1);
	return winID;
}


//-------------------------------------------------------------------------------------------
DllExport int  swNumPropRectWinCreate(char *name,float x,float y,swRect *rect){
	int winID=swNumPropWinCreate(name,x,y,300,4);
	swNumPropWinAddFloat(winID,"PosX",&rect->x,FLT_MIN,FLT_MAX,1);
	swNumPropWinAddFloat(winID,"PosY",&rect->y,FLT_MIN,FLT_MAX,1);
	swNumPropWinAddFloat(winID,"Width",&rect->w,FLT_MIN,FLT_MAX,1);
	swNumPropWinAddFloat(winID,"Height",&rect->h,FLT_MIN,FLT_MAX,1);
	return winID;
}


//-------------------------------------------------------------------------------------------
DllExport int  swNumPropColorWinCreate(char *name,float x,float y,swColor *color){
	int winID=swNumPropWinCreate(name,x,y,250,4);
	swNumPropWinAddFloat(winID,"Red",&color->r,0.0f,1.0f,0.05f);
	swNumPropWinAddFloat(winID,"Green",&color->g,0.0f,1.0f,0.05f);
	swNumPropWinAddFloat(winID,"Blue",&color->b,0.0f,1.0f,0.05f);
	swNumPropWinAddFloat(winID,"Alpha",&color->a,0.0f,1.0f,0.05f);
	return winID;
}



//-------------------------------------------------------------------------------------------
NumPropWin* swNumPropWinGet(int winID){
	NumPropWin *win=(NumPropWin *)swLinkedListGetFirst(numPropWinList);
	while(win!=NULL){
		if(win->id==winID){
			return win;
		}
		win=(NumPropWin *)swLinkedListGetNext(numPropWinList);
	}
	return NULL;
}


//-------------------------------------------------------------------------------------------
DllExport void swNumPropWinDestroy(int winID){
	NumPropWin *win=swNumPropWinGet(winID);
	swLinkedListDel(numPropWinList,win);
	free(win);
}
