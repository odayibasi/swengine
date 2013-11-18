#include "SWGuiIn.h"


int		clockFontID;
int		clockFontSet;
swColor clockFontColor;
float	clockFontSize;
swPoint clockPos;
int     clockLayer;


//-------------------------------------------------------------------------------------------
void swClockDisplay(void *obj){
	swGraphicsSetBlendingMode(SW_BLENDING_MODE_ADDITIVE);
	swGraphicsSetColor1(&clockFontColor);
	swGraphicsRenderText(clockFontID,clockFontSet,clockFontSize,clockPos.x,clockPos.y,0,"%0.3f",swSystemGetElapsedSeconds());
}


//-------------------------------------------------------------------------------------------
DllExport void swClockInit(int fontID,int set,swColor color,float size,float x,float y,int layer){
	clockFontID=fontID;
	clockFontSet=set;
	clockFontColor=color;
	clockFontSize=size;
	clockPos.x=x;
	clockPos.y=y;
	clockLayer=layer;
	swDispManagerAdd(swClockDisplay,NULL,NULL,NULL,&clockLayer);
}
