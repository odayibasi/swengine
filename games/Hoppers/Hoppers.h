#ifndef HOPPERS_H
#define HOPPERS_H

#include "../../include/SWEngine.h"

#pragma comment (lib,"../../lib/SWTypes.lib")    
#pragma comment (lib,"../../lib/SWUtil.lib")    
#pragma comment (lib,"../../lib/SWCore.lib")    
#pragma comment (lib,"../../lib/SWServices.lib")    
#pragma comment (lib,"../../lib/SWGame.lib")    
#pragma comment (lib,"../../lib/SWGui.lib")    
#pragma comment (lib,"../../lib/SWEngine.lib")    

typedef enum _CellMode{
	CELL_MODE_EMPTY,
	CELL_MODE_BLUE,
	CELL_MODE_RED,
}CellMode;

typedef struct _Cell{
	int      xCellIndex;
	int      yCellIndex;
	swPoint  center;
	CellMode mode;  
}Cell;

#define  BOARD_X			200
#define  BOARD_Y			40
#define  CELL_RADIOUS		20    
#define  MAX_CELL_COUNT		25
#define  UP_LEFT_MOVE		0
#define  UP_MOVE			1
#define  UP_RIGHT_MOVE		2
#define  RIGHT_MOVE			3
#define  DOWN_RIGHT_MOVE	4
#define  DOWN_MOVE			5
#define  DOWN_LEFT_MOVE		6
#define  LEFT_MOVE			7
#define  MAX_MOVE_TYPES		8

static int	boardCellCount = 8;
static int	rowsWithPieceCount = 3;
static int	level = 2;
static int  redBtnID=2;
static int  blueBtnID=3;






//-------------------------------------------------------------------------------------------
static void CellDisplay(Cell *cell,swColor *outLineColor,int outLineWidth){

	swPoint pTop,pLeft,pRight,pBottom,pCenter;
	swDimension dim={CELL_RADIOUS,CELL_RADIOUS};
	int x=cell->xCellIndex;
	int y=cell->yCellIndex;

	swPointCopy(&pCenter,&cell->center);
	swPointSet(&pTop,pCenter.x,pCenter.y+CELL_RADIOUS);
	swPointSet(&pBottom,pCenter.x,pCenter.y-CELL_RADIOUS);
	swPointSet(&pLeft,pCenter.x-CELL_RADIOUS,pCenter.y);
	swPointSet(&pRight,pCenter.x+CELL_RADIOUS,pCenter.y);

	//Display Cell
	swGraphicsSetColor1(outLineColor);
	swGraphicsRenderLine1(&pLeft,&pTop,outLineWidth);
	swGraphicsRenderLine1(&pTop,&pRight,outLineWidth);
	swGraphicsRenderLine1(&pRight,&pBottom,outLineWidth);
	swGraphicsRenderLine1(&pBottom,&pLeft,outLineWidth);


	swRect btnTarget;
	swRectSet(&btnTarget,pCenter.x-dim.w/2,pCenter.y-dim.h/2,dim.w,dim.h);
	swGraphicsSetBlendingMode(SW_BLENDING_MODE_SOLID);
	swGraphicsSetColor0(1,1,1,1);

	switch(cell->mode){
			case CELL_MODE_BLUE:
				swGraphicsRenderImg0(blueBtnID,&btnTarget);
				break;
			case CELL_MODE_RED:
				swGraphicsRenderImg0(redBtnID,&btnTarget);
				break;
			default:
				break;			
	}
}


#endif 
