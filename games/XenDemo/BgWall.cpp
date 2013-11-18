#include "../../include/SWEngine.h"

typedef struct _bgWall{
   swRect  target;
   swRect *source;
   float   rot;
   int     dispID;
}bgWall;

//Display
extern int		bgWallImgID;
int				bgWallLayer=0;
bool			bgWallIsVisible=true;

//-------------------------------------------------------------------------------------------
void bgWallDisplay(void *obj){
	bgWall *wall=(bgWall *)obj;
	swGraphicsSetColor1(&SWCOLOR_WHITE);
	swGraphicsRenderImg3(bgWallImgID,&wall->target,wall->source,wall->rot);
}



//-------------------------------------------------------------------------------------------
void bgWallDestroy(void *obj){
	bgWall *wall=(bgWall *)obj;
	swDispManagerDel(wall->dispID);
	free(wall);
}



//-------------------------------------------------------------------------------------------
void bgWallSet(bgWall *wall, int x,int y,swRect *source, float rot){
	swRectSet(&wall->target,x,y,128,128);
	wall->source=source;
	wall->rot=rot;
	wall->dispID=swDispManagerAdd(bgWallDisplay,wall,&bgWallIsVisible,&wall->target,&bgWallLayer);
	swDestroyManagerAdd(bgWallDestroy,wall);
}

//-------------------------------------------------------------------------------------------
void bgWallCreate(int x,int y){
	
	bgWall *wall0=(bgWall *)malloc(sizeof(bgWall));
	bgWallSet(wall0,x*256,y*256,&SW_SPRITE_SOURCE_DEFAULT,90);

	bgWall *wall1=(bgWall *)malloc(sizeof(bgWall));
	bgWallSet(wall1,x*256,y*256+128,&SW_SPRITE_SOURCE_MIRRORX,270);

	bgWall *wall2=(bgWall *)malloc(sizeof(bgWall));
	bgWallSet(wall2,x*256+128,y*256,&SW_SPRITE_SOURCE_MIRRORX,90);

	bgWall *wall3=(bgWall *)malloc(sizeof(bgWall));
	bgWallSet(wall3,x*256+128,y*256+128,&SW_SPRITE_SOURCE_DEFAULT,270);
}
