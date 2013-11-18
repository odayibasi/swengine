#include "../../include/SWEngine.h"

typedef struct _edgeWall{
	float  rot;
	swRect target;
	int    dispID;
}edgeWall;

int			edgeWallLayer=9;
bool		edgeWallIsVisible=true;
extern int	edgeWallImgID;

//-------------------------------------------------------------------------------------------
void renderEdgeWall(void *obj){
	edgeWall *wall=(edgeWall *)obj;
	swGraphicsSetBlendingMode(SW_BLENDING_MODE_NONE);
	swGraphicsSetColor1(&SWCOLOR_WHITE);
	swGraphicsRenderImg1(edgeWallImgID,&wall->target,wall->rot);
}


//-------------------------------------------------------------------------------------------
void destroyEdgeWall(void *obj){
	edgeWall *wall=(edgeWall *)obj;
	swDispManagerDel(wall->dispID);
	free(wall);
}


//-------------------------------------------------------------------------------------------
void setEdgeWall(edgeWall *wall, int x,int y){
	swRectSet(&wall->target,x,y,32,32);
	wall->dispID=swDispManagerAdd(renderEdgeWall,wall,&edgeWallIsVisible,&wall->target,&edgeWallLayer);
	swDestroyManagerAdd(destroyEdgeWall,wall);
}



//-------------------------------------------------------------------------------------------
void edgeWallCreateXAxis(float x,float y,int count){
	for(int i=0;i<count;i++){
		edgeWall *wall=(edgeWall *)malloc(sizeof(edgeWall));
		wall->rot=0;
		setEdgeWall(wall,x+i*32,y);
	}
}

//-------------------------------------------------------------------------------------------
void edgeWallCreateYAxis(float x,float y,int count){
	for(int i=0;i<count;i++){
		edgeWall *wall=(edgeWall *)malloc(sizeof(edgeWall));
		wall->rot=90;	
		setEdgeWall(wall,x,y+i*32);
	}
}
