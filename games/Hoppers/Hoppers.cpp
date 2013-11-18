#include "Board.h"
#include "resource.h"



swApplication	hoppersGame;
swKeyboardState keybState;
swMouseState    mousState;
int             fontID=-1;

//Cursor
int             cursorID=-1;
int				cursorID2=-1;
swRect			cursorTarget={0,0,16,16};
swRect			cursorTarget2={0,0,20,20};



//Bg
int             bgID=-1;
swRect          bgTarget={0,0,400,400};

//Logo
int             logoID=-1;
swRect          logoTarget={320,20,45,40};
bool			bPrevMousState=false;

//Smile
int             smileOff,smileOn;
swRect			smileTarget={280,300,32,32};

//Upset
int             upsetOff,upsetOn;
swRect			upsetTarget={310,300,32,32};

//BigWin
int				bigWinOff,bigWinOn;
swRect			bigWinTarget={340,300,32,32};


//Reset
int             resetID;
swRect			resetTarget={100,100,40,40};


//Status
bool			bUpset=false;
bool			bSmile=false;
bool			bHighScore=false;


//Time;
float startTime=0;
float totalTime=200;
float elapsedTime=0;
float highScore=0;


Board	*table;
bool	 isFirstMove = true;


swMousBehaviourListener mousBListener;







//-------------------------------------------------------------------------------------------
void fillRedPieces(){
	for (int row = rowsWithPieceCount-1; row >= 0; row--){
		for (int col = 0; (col + row) < rowsWithPieceCount; col++){
			table->currentState[boardCellCount-row-1][boardCellCount-col-1].mode=CELL_MODE_RED;
		}
	}
}

//-------------------------------------------------------------------------------------------
void fillBluePieces(){
	for (int row = rowsWithPieceCount-1; row >= 0; row--){
		for (int col = 0; (col + row) < rowsWithPieceCount; col++){
			table->currentState[row][col].mode=CELL_MODE_BLUE;
		}
	}
}

//-------------------------------------------------------------------------------------------
void GameReset(){
	table = new Board;
	table->setNextTurnOnBoard(CELL_MODE_BLUE);
	fillBluePieces();
	fillRedPieces();
	isFirstMove=true;
	bSmile=false;
	bUpset=false;
	bHighScore=false;
	startTime=swSystemGetElapsedSeconds();
	totalTime=200;

}


//-------------------------------------------------------------------------------------------
void calculateScore(){

	float currentTime=swSystemGetElapsedSeconds();
	float dTime=currentTime-startTime;

	if(!bUpset && !bSmile){
		elapsedTime=totalTime-dTime;
	}


	if(elapsedTime<=0){
		bUpset=true;
		elapsedTime=0;
	}


	if(bSmile && elapsedTime>highScore){
		highScore=elapsedTime;
		bHighScore=true;
	}

}



//-------------------------------------------------------------------------------------------
void displayCursor(int x,int y){

	swGraphicsSetBlendingMode(SW_BLENDING_MODE_SOLID);
	swGraphicsSetColor0(1,1,1,1);
	cursorTarget.x=x-cursorTarget.w/2;
	cursorTarget.y=y-cursorTarget.h/2;
	swGraphicsRenderImg0(cursorID,&cursorTarget);
}



//-------------------------------------------------------------------------------------------
void displayBg(){
	swGraphicsSetColor0(1,1,1,1);
	swGraphicsRenderImg0(bgID,&bgTarget);
}



//-------------------------------------------------------------------------------------------
void displayLogo(){
	bool bIn=swIntersectionRectAndPoint2(&logoTarget,mousState.x,mousState.y);
	if(bIn){
		swRectSet(&logoTarget,315,15,55,50);
	}else{
		swRectSet(&logoTarget,320,20,45,40);
	}
	swGraphicsSetColor0(1,1,1,1);
	swGraphicsRenderImg0(logoID,&logoTarget);

	if(bIn && mousState.btnLEFT && !bPrevMousState)
		system("explorer http://www.skywar.org");
}

//-------------------------------------------------------------------------------------------
void displayControlPanel(){
	bool bIn=swIntersectionRectAndPoint2(&resetTarget,mousState.x,mousState.y);
	if(bIn){
		swRectSet(&resetTarget,17,312,32,32);
	}else{
		swRectSet(&resetTarget,20,315,25,25);
	}

	if(bIn && mousState.btnLEFT && !bPrevMousState)
		GameReset();

	swGraphicsSetBlendingMode(SW_BLENDING_MODE_NONE);
	if(bIn && mousState.btnLEFT)
		swGraphicsSetColor0(0.5,0.5,1.0,0);
	swGraphicsRenderImg0(resetID,&resetTarget);


	swGraphicsSetBlendingMode(SW_BLENDING_MODE_ADDITIVE);
	swGraphicsSetColor0(1,1,1,0.5);
	swGraphicsRenderText(fontID,1,12,20,312,0,"Reset");


}



//-------------------------------------------------------------------------------------------
void displayResult(){

	swGraphicsSetColor0(1,1,1,1);
	if(bHighScore){
		swGraphicsRenderImg0(bigWinOn,&bigWinTarget);
	}else{
		swGraphicsRenderImg0(bigWinOff,&bigWinTarget);
	}

	if(bSmile){
		swGraphicsRenderImg0(smileOn,&smileTarget);
	}else{
		swGraphicsRenderImg0(smileOff,&smileTarget);
	}

	if(bUpset){
		swGraphicsRenderImg0(upsetOn,&upsetTarget);
	}else{
		swGraphicsRenderImg0(upsetOff,&upsetTarget);
	}

	swGraphicsSetBlendingMode(SW_BLENDING_MODE_ADDITIVE);
	swGraphicsSetColor0(1,1,1,0.5);
	swGraphicsRenderText(fontID,1,12,283,294,0,"Win");
	swGraphicsRenderText(fontID,1,12,311,294,0,"Lost");
	swGraphicsRenderText(fontID,1,12,345,294,0,"%3.2f",elapsedTime);

	swGraphicsRenderText(fontID,1,12,315,250,0,"%3.2f",highScore);

	swGraphicsSetColor0(1,0,0,1);
	swGraphicsRenderText(fontID,1,14,305,262,0,"HighScore");


}





//-------------------------------------------------------------------------------------------
void MouseReleased(float x,float y){
	Cell * oldSelected = table->getSelectedCell();
	table->selectCell(x,y);
	table->movePieceToSelectedIfSuitable(oldSelected);
	table->setDragging(false);
}



//-------------------------------------------------------------------------------------------
void MousePressed(float x,float y){
	table->selectCell(x,y);
	table->fillPossibleNextPieceCells();
}


//-------------------------------------------------------------------------------------------
void MouseDragging(float x,float y){
	table->setDragging(true);
	swGraphicsSetBlendingMode(SW_BLENDING_MODE_SOLID);
	swGraphicsSetColor0(1,1,1,1);
	cursorTarget2.x=x-cursorTarget2.w/2;
	cursorTarget2.y=y-cursorTarget2.h/2;
	swGraphicsRenderImg0(cursorID2,&cursorTarget2);

}


//-------------------------------------------------------------------------------------------
void MouseMoving(float x,float y){
}



//-------------------------------------------------------------------------------------------
void GameLoop(){ 

	float x,y;	
	//Input Process	
	swInputListenKeyboard(&keybState);
	swInputListenMouse(&mousState);
	swInteractionManagerExecute(&keybState,&mousState);
	x=mousState.x;
	y=mousState.y;


	if(!bSmile && !bUpset){
		if (table->getNextTurnOnBoard() == CELL_MODE_RED){
			table->discoverNextMovesInGivenDepth(level);
			table = table->findBestNextBoard(); 
			isFirstMove = false;
		} else if(mousState.btnLEFT){
			//table->selectCell(x,y);
			//table->fillPossibleNextPieceCells();

		} else if(mousState.btnRIGHT){
			//Cell * oldSelected = table->getSelectedCell();
			//table->selectCell(x,y);
			//table->movePieceToSelectedIfSuitable(oldSelected);
		}

		//AI
		table->refreshWinningFlags();
		if (table->getIsComputerWon() && !isFirstMove){
			bUpset=true;
		} else if (table->getIsPlayerWon() && !isFirstMove){
			bSmile=true;
		} else if (table->getNextTurnOnBoard() == CELL_MODE_RED){
		}
	}


	//Display
	swGraphicsBeginScene();
		displayBg();
		displayControlPanel();
		displayLogo();
		displayResult();
		calculateScore();
		table->draw();
		displayCursor(x,y);
		swMousBehaviourExecute(&mousState);
	swGraphicsEndScene();


	//Exit
	if(keybState.keyESCAPE){
		swEngineExit();
	}

	bPrevMousState=mousState.btnLEFT;

}




//-------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{
	//Application Settings
	hoppersGame.hInstance=hInstance;
	hoppersGame.fullScreen=false;
	hoppersGame.cursor=false;
	hoppersGame.icon=LoadIcon(hInstance, (LPCTSTR)IDI_ICON1);
	hoppersGame.width=400;
	hoppersGame.height=400;
	hoppersGame.title="Hoppers";
	hoppersGame.path="\\rsc\\Hoppers\\";
	hoppersGame.appRun=GameLoop;



	//Application Execution
	swEngineInit(&hoppersGame);

	GameReset();

	fontID=swGraphicsCreateFont("Font.tga");
	cursorID=swGraphicsCreateImg("Cursor.tga");
	bgID=swGraphicsCreateImg("Bg.tga");
	swGraphicsCreateImg("RedBtn.tga");
	cursorID2=swGraphicsCreateImg("BlueBtn.tga");

	logoID=swGraphicsCreateImg("SWLogo.tga");
	bigWinOff=swGraphicsCreateImg("BigWinOff.tga");
	bigWinOn=swGraphicsCreateImg("BigWinOn.tga");
	
	smileOff=swGraphicsCreateImg("SmileOff.tga");
	smileOn=swGraphicsCreateImg("SmileOn.tga");

	upsetOff=swGraphicsCreateImg("UpsetOff.tga");
	upsetOn=swGraphicsCreateImg("UpsetOn.tga");

	resetID=swGraphicsCreateImg("Reset.tga");

	mousBListener.dragging=MouseDragging;
	mousBListener.moving=MouseMoving;
	mousBListener.pressed=MousePressed;
	mousBListener.released=MouseReleased;
	swMousBehaviourAdd(&mousBListener);


	swEngineRun();
	swEngineExit();

	return 0;
}
