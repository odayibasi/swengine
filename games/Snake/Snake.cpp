#include "../../include/SWEngine.h"

#pragma comment (lib,"../../lib/SWUtil.lib")    
#pragma comment (lib,"../../lib/SWTypes.lib")    
#pragma comment (lib,"../../lib/SWCore.lib")    
#pragma comment (lib,"../../lib/SWEngine.lib")    



swApplication snakeApp;

enum Direction{
   NORTH,
   SOUTH,
   EASTH,
   WEST
};

struct Snake{
   Direction direction;
   int nodeListID;
};

Snake snake;
swPoint bonus={3,3};


#define GRID_X  100
#define GRID_Y  100
#define GRID_HOLE_COUNT 20
#define GRID_HOLE_SIZE  16


swKeyboardState keybState;
int timerID=-1;
int fontID=-1;
int score=0;
float speed=0.4f;

void GameOver();
void GameReset();
void GameLoop();


//-------------------------------------------------------------------------------------------
void addSnakeNode(float x,float y){
	swPoint *node=swPointCreate(x,y);
	swLinkedListAdd(snake.nodeListID,node);
}

//-------------------------------------------------------------------------------------------
void displayNode(swPoint *node){
	swGraphicsRenderLineRect0(node->x*GRID_HOLE_SIZE+GRID_X,node->y*GRID_HOLE_SIZE+GRID_Y,GRID_HOLE_SIZE,GRID_HOLE_SIZE,2);
}

//-------------------------------------------------------------------------------------------
bool isRequestLocCollideSnake(swPoint requestLoc){
	swPoint *node=(swPoint*)swLinkedListGetFirst(snake.nodeListID);
	while(node!=NULL){
		if(swPointEquals(node,&requestLoc)){
			return true;
		}
		node=(swPoint*)swLinkedListGetNext(snake.nodeListID);
	}
	return false;
}

//-------------------------------------------------------------------------------------------
bool isRequestLocCollideWall(swPoint requestLoc){
	if(requestLoc.x==-1||requestLoc.y==-1||requestLoc.x==GRID_HOLE_COUNT|| requestLoc.y==GRID_HOLE_COUNT){
		return true;
	}
	return false;
}

//-------------------------------------------------------------------------------------------
bool isRequestLocCollideBonus(swPoint requestLoc){
	if(swPointEquals(&bonus,&requestLoc)){
		return true;
	}
	return false;
}

//-------------------------------------------------------------------------------------------
void processRequestLoc(swPoint *requestLoc){
	swPoint *head=(swPoint*)swLinkedListGetFirst(snake.nodeListID);
	switch(snake.direction){
		case NORTH:
			requestLoc->x=head->x;
			requestLoc->y=head->y+1;
			break;

		case SOUTH:
			requestLoc->x=head->x;
			requestLoc->y=head->y-1;
			break;

		case WEST:
			requestLoc->x=head->x-1;
			requestLoc->y=head->y;
			break;

		case EASTH:
			requestLoc->x=head->x+1;
			requestLoc->y=head->y;
			break;

		default:
			break;
	}


}




//-------------------------------------------------------------------------------------------
void moveSnake(void *obj){
	
	//Process Request Head Location
	swPoint requestLoc;
	processRequestLoc(&requestLoc);
	if(isRequestLocCollideSnake(requestLoc)||isRequestLocCollideWall(requestLoc)){
		GameOver();
		return;
	}

	if(isRequestLocCollideBonus(requestLoc)){
		addSnakeNode(0,0);
		score+=1000;
		speed-=0.02;
		swTimerUpdateDelaySeconds(timerID,speed);
		bonus.x=swMathRandomInt(0,19);
		bonus.y=swMathRandomInt(0,19);
	}


	//Move All Node To RequestLoc
	swPoint *node=(swPoint*)swLinkedListGetFirst(snake.nodeListID);
	swPoint temp;
	while(node!=NULL){
		swPointCopy(&temp,node);
		swPointCopy(node,&requestLoc);
		swPointCopy(&requestLoc,&temp);
		node=(swPoint*)swLinkedListGetNext(snake.nodeListID);
	}	
}



//-------------------------------------------------------------------------------------------
void GameOver(){ 
	swTimerStop(timerID);
}

//-------------------------------------------------------------------------------------------
void GameReset(){ 

}


//-------------------------------------------------------------------------------------------
void GameLoop(){ 

	//Input Handling
	swInputListenKeyboard(&keybState);
	if(keybState.keyESCAPE){
		swEngineExit();
	}


	if(keybState.keyLEFT)
		snake.direction=WEST;
	else if(keybState.keyRIGHT)
		snake.direction=EASTH;
	else if(keybState.keyUP)
		snake.direction=NORTH;
	else if(keybState.keyDOWN)
		snake.direction=SOUTH;

	//Display Scene
	swGraphicsBeginScene();
		swGraphicsSetBgColor0(0,0,0.0);
		
		//Display Grids
		swGraphicsSetColor0(1,0,0,1);
		swGraphicsSetColor0(1,1,1,1);
		for(int i=0;i<GRID_HOLE_COUNT+1;i++){ //i=X axis
			float x=GRID_X+i*GRID_HOLE_SIZE;
			float y0=GRID_Y;
			float y1=GRID_Y+GRID_HOLE_SIZE*GRID_HOLE_COUNT;
			swGraphicsRenderLine0(x,y0,x,y1,2);
		}//X axis


		for(int i=0;i<GRID_HOLE_COUNT+1;i++){   //Y axis
			float y=GRID_Y+i*GRID_HOLE_SIZE;
			float x0=GRID_X;
			float x1=GRID_X+GRID_HOLE_COUNT*GRID_HOLE_SIZE;
			swGraphicsRenderLine0(x0,y,x1,y,2);
		}

		//Display Bonus
		swGraphicsSetColor0(0,1,0,0);
		displayNode(&bonus);

		//Display Snake
		swPoint *node=(swPoint*)swLinkedListGetFirst(snake.nodeListID);
		swGraphicsSetColor0(1,0,0,0);
		while(node!=NULL){
			displayNode(node);
			node=(swPoint*)swLinkedListGetNext(snake.nodeListID);
		}

		//DisplayScore
		swGraphicsSetBlendingMode(SW_BLENDING_MODE_ADDITIVE);
		swGraphicsSetColor0(1,1,1,0);
		swGraphicsRenderText(fontID,1,20,550,250,0,"Score=%i",score);
		

	swGraphicsEndScene();

}





//-------------------------------------------------------------------------------------------
void initApp(){ 

	

	//Snake
	snake.nodeListID=swLinkedListCreate();
	snake.direction=NORTH;
	addSnakeNode(10,10);
	addSnakeNode(10,9);
	addSnakeNode(10,8);

	//Timer for moving
	timerID=swTimerCreate(0.4,NULL,moveSnake);

	//FontCreate
	fontID=swGraphicsCreateFont("Font.tga");

}


//-------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{ 


	//Application Settings
	snakeApp.hInstance=hInstance;
	snakeApp.fullScreen=false;
	snakeApp.cursor=true;
	snakeApp.width=800;
	snakeApp.height=600;
	snakeApp.title="Snake";
	snakeApp.path="\\rsc\\Snake\\";
	snakeApp.appRun=GameLoop;

	//Application Execution
	swEngineInit(&snakeApp);

	//Init My Application
	initApp();
	swEngineRun();
	return 0;
}
