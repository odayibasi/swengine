#ifndef SWGUI_IN_H
#define SWGUI_IN_H


#include "../../include/SWGui.h"

#pragma comment (lib,"../../lib/SWTypes.lib")   
#pragma comment (lib,"../../lib/SWUtil.lib")   
#pragma comment (lib,"../../lib/SWCore.lib")  
#pragma comment (lib,"../../lib/SWServices.lib")  



//Cursor
void swCursorInit();
void swCursorDeInit();




//Property
typedef struct _IntPropModel{
	int *iVal;
	int iMin;
	int iMax;
	int iDelta;
}IntPropModel;


typedef struct _EnumPropModel{
	int *iVal;
	int iMin;
	int iMax;
	int iDelta;
	int enumStrList;
}EnumPropModel;


typedef struct _FloatPropModel{
	float *fVal;
	float fMin;
	float fMax;
	float fDelta;
}FloatPropModel;


typedef struct _DoublePropModel{
	double *dVal;
	double dMin;
	double dMax;
	double dDelta;
}DoublePropModel;



typedef enum _eNumPropType{
	NUMPROP_TYPE_ENUM,
	NUMPROP_TYPE_INT,
	NUMPROP_TYPE_FLOAT,
	NUMPROP_TYPE_DOUBLE,
}eNumPropType;


typedef struct _PropModel{
	char		*name;
	eNumPropType	 type;
	union{
		EnumPropModel	ep;
		IntPropModel	ip;
		FloatPropModel  fp;
		DoublePropModel dp;
	};
}PropModel;



typedef enum _eNumPropEvntType{
	NUMPROP_EVNT_TYPE_INC,
	NUMPROP_EVNT_TYPE_DEC,
}eNumPropEvntType;

typedef struct _NumPropControlButton{
	swRect				rect;
	swRect				*source;
	bool				prevMouseLBState;
    bool             firstPressed;
	bool             sleepPressed;
	bool				continuesPressed;
	float				mouseStateChangedTime;
	float				mouseProcessEffectTime;
	PropModel			*propModel;
    int                 iconSetID;
	swRect				normSource;
	swRect				moverSource;
	swRect				pressedSource;
	eNumPropEvntType	type;
}NumPropControlButton;


typedef struct _NumPropComponent{
	NumPropControlButton incButton;
	NumPropControlButton decButton;
	PropModel propModel;
}NumPropComponent;


typedef struct _StructPropComponent{
	bool              bMousOver;
	void                 *numStruct;    
}StructPropComponent;


typedef enum ePropCompType{
	PROP_COMP_NUM,
	PROP_COMP_STRUCT,
}ePropCompType;

typedef struct _PropComponent{
	swRect           rect;
	ePropCompType	 type;
	union{
		NumPropComponent	np;
		StructPropComponent  sp;
	};
}PropComponent;


typedef struct _NumPropTitleBarButton{
	swRect				rect;
	swRect              *source;
	bool             bMouseOver;
	int                 iconSetID;
	swRect              normalSource;
	swRect              mouseOverSource;
	bool				prevMouseLBState;
	void                (*callback)(void *); 
    void                *obj;
}NumPropTitleBarButton;


typedef struct _NumPropTitleBar{
	swRect					rect;
	char					*name;
	NumPropTitleBarButton	transpBtn;
	NumPropTitleBarButton	iconifyBtn;
	NumPropTitleBarButton	closeBtn;
	bool				    dragStart;
	bool                 bDragging;
	bool                 bSelected;
	bool					prevMouseLBState;

}NumPropTitleBar;


typedef struct _NumPropPanel{
	PropModel				propOfCompSelect;
	swRect					rect;
	NumPropControlButton    upBtn;
	NumPropControlButton    downBtn;
	int                     iPropList;
	int                     visbProp;
	int                     iPropIndex;
}NumPropPanel;


typedef struct _NumPropWin{
	int                     id;
	bool                 bVisible;
	bool                 bTransparent;
	bool                 bCollapse;
	swRect					rect;
	NumPropTitleBar			titleBar;
	NumPropPanel            propPanel;
}NumPropWin;



const static float NUMPROP_COMP_HEIGHT=25.0f;
const static float NUMPROP_BTN_SIZE=20.0f;


//TitleBar
void swNumPropTitleBarSetLogo(int logoID);
void swNumPropTitleBarSetFont(int fontID);
void swNumPropTitleBarInput(NumPropTitleBar *titleBar, swKeyboardState *keybState,swMouseState *mousState);
void swNumPropTitleBarDisplay(NumPropTitleBar *titleBar);



//TitleBar Button
void swNumPropTitleBarBtnInit(NumPropTitleBarButton *btn,void (*callback)(void *),void *obj,int iconSetID,swRect *normalS,swRect *mOverS);
void swNumPropTitleBarBtnDisplay(NumPropTitleBarButton *btn);
void swNumPropTitleBarBtnInput(NumPropTitleBarButton *btn,swKeyboardState *keybState,swMouseState *mousState);


//NumberPropControlButton
void swNumPropControlBtnInit(NumPropControlButton *btn,PropModel *prop,eNumPropEvntType type,int iconSetID,swRect *norm,swRect * mover,swRect *pressed);
void swNumPropControlBtnDisplay(NumPropControlButton *btn);
void swNumPropControlBtnInput(NumPropControlButton *btn,swKeyboardState *keybState,swMouseState *mousState);


//PropComponent
void swPropComponentSetFont(int fontID);
void swPropComponentDisplay(PropComponent *propComp);
void swPropComponentInput(PropComponent *propComp,swKeyboardState *keybState,swMouseState *mousState);

//NumProperty
void swNumPropProcess(PropModel *prop,eNumPropEvntType type);
void swNumPropDisplay(PropModel *prop,float x,float y);
void swNumPropSetFont(int fontID);

//NumPropPanel
void swNumPropPanelInput(NumPropPanel *panel,swKeyboardState *keybState,swMouseState *mousState);
void swNumPropPanelDisplay(NumPropPanel *panel);


//NumPropWin
void  swNumPropWinSetIconID(int iconID);
void  swNumPropWinDisplay(NumPropWin *win);
void swNumPropWinInput(NumPropWin *win,swKeyboardState *keybState, swMouseState *mousState);
void  swNumPropWinClose(void *obj);
void  swNumPropWinIconfy(void *obj);
void  swNumPropWinTransparent(void *obj);


//NumPropWinManager
void swNumPropWinManagerInit();
void swNumPropWinManagerDeInit();
NumPropWin* swNumPropWinGet(int winID);

//Widget
void	swWidgetManagerInit();
void   swWidgetManagerDeInit();


//class swWidget{
//
//public:
//	swWidget();
//	~swWidget();
//	bool equals(int id);
//	
//	int  getId();
//	bool isEnabled();
//	bool isVisible();
//	eWidget getType();
//	swRect* getTarget();
//	
//	void setId(int id);
//	void setEnabled(bool bEnabled);
//	void setVisible(bool bEnabled);
//	void setType(eWidget type);
//	void setSize(float w, float h);
//	void setPos(float w,float h);
//
//	virtual void display()=0;
//	virtual void mouseMoving(float x,float y)=0;
//	void mousePressed(float x,float y);
//	void mouseReleased(float x,float y);
//	void mouseDragging(float x,float y);
//
//
//private:
//	int		id;
//	eWidget type;
//	bool	bEnabled;
//	bool	bVisible;
//
//protected:
//	swRect  rTarget;
//};
//
//

//
//
//
//
////ImgButton
//class swImgButton: public swWidget{
//
//public:
//	swImgButton();
//	~swImgButton();
//	void setImgs(int normTex,int mOverTex,int pressTex);
//	void display();
//	void mouseMoving(float x,float y);
//
//private:
//	int     activeTexID;
//	int		normTexID;
//	int		mOverTexID;
//	int		pressTexID;
//};
//







#endif


