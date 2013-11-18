#ifndef SWGUI_H
#define SWGUI_H


#include "SWTypes.h"
#include "SWUtil.h"
#include "SWCore.h"
#include "SWServices.h"




#ifndef DllExport
#define DllExport extern "C" __declspec(dllexport)
#endif


//GUI====================================================
DllExport void swGuiInit();
DllExport void swGuiDeInit();


//NUMPROP====================================================
DllExport void swNumPropWinSetPath(char *path);
DllExport void swNumPropWinSetDependency(int logoID,int fontID,int iconSetID);
DllExport int  swNumPropWinCreate(char *name,float x,float y,float w,int countVisbProp);
DllExport int  swNumPropPointWinCreate(char *name,float x,float y,swPoint *point);
DllExport int  swNumPropDimWinCreate(char *name,float x,float y,swDimension *dim);
DllExport int  swNumPropRectWinCreate(char *name,float x,float y,swRect *rect);
DllExport int  swNumPropColorWinCreate(char *name,float x,float y,swColor *color);
DllExport void swNumPropWinDestroy(int winID);
DllExport void swNumPropWinAddInt(int winID,char *name,int *iVal,int iMin,int iMax,int iInc);
DllExport void swNumPropWinAddFloat(int winID,char *name,float *fVal,float fMin,float fMax,float fInc);
DllExport void swNumPropWinAddDouble(int winID,char *name,double *dVal,double dMin,double dMax,double dInc);
DllExport void swNumPropWinAddEnum(int winID,char *name,int *iVal,int enumStringList);
DllExport void swNumPropWinAddSubWin(int winID,int subWinID);
DllExport void swNumPropWinSetVisible(int winID,bool bVisible);
DllExport void swNumPropWinSetCollapse(int winID,bool bCollapse);
DllExport void swNumPropWinSetLocation(int winID,float x,float y);
DllExport void swNumPropWinSetWidth(int winID,float width);
DllExport void swNumPropWinSetVisibleProp(int winID,int visibleProp);

//PALET====================================================
//CLOCK====================================================
DllExport void swClockInit(int fontID,int set,swColor color,float size,float x,float y,int layer);

//CONSOLE====================================================
DllExport void	swConsoleInit();
DllExport void	swConsoleDeInit();
DllExport void	swConsoleSetFont(int fontID,int set,swColor *color,float size);
DllExport void	swConsoleSetBgColor(swColor *color);
DllExport void	swConsoleSetPos(float x,float y);
DllExport void	swConsoleSetLayer(int layer);
DllExport void	swConsoleSetSize(float w,float h);
DllExport void	swConsoleSetVisible(bool bVisible);
DllExport void	swConsolePrint(char *string,...);
DllExport void	swConsoleClear();
DllExport void  swConsoleRegisterCommand(void(*cmdFunc)(int,swArg *cArgs),char *cmdName,int count,swArg *cArgs);







#endif
