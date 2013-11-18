#include "Board.h"


//-------------------------------------------------------------------------------------------
Board::Board() {

	this->pieceCount = (rowsWithPieceCount * rowsWithPieceCount + rowsWithPieceCount) / 2;
	this->gradeOfGreatestMove = -1;
	this->selected = NULL;
	initCells();
	initNextBoards();
}


//-------------------------------------------------------------------------------------------
void Board::initCells(){

	for(int i = 0; i < boardCellCount; i++){
		for(int j=0; j < boardCellCount; j++){
			this->currentState[i][j].mode = CELL_MODE_EMPTY;
			this->currentState[i][j].xCellIndex = i;
			this->currentState[i][j].yCellIndex = j;
			this->currentState[i][j].center.x = BOARD_X+CELL_RADIOUS*i-CELL_RADIOUS*j;
			this->currentState[i][j].center.y = BOARD_Y+CELL_RADIOUS*i+CELL_RADIOUS*j;
		}
	}
}

//-------------------------------------------------------------------------------------------
void Board::copyCells(const Cell parentState[][MAX_CELL_COUNT]){

	for(int i = 0; i < boardCellCount; i++){
		for(int j=0; j < boardCellCount; j++){
			this->currentState[i][j].mode = parentState[i][j].mode;
			this->currentState[i][j].xCellIndex = parentState[i][j].xCellIndex;
			this->currentState[i][j].yCellIndex = parentState[i][j].yCellIndex;
			this->currentState[i][j].center.x = BOARD_X+CELL_RADIOUS*i-CELL_RADIOUS*j;
			this->currentState[i][j].center.y = BOARD_Y+CELL_RADIOUS*i+CELL_RADIOUS*j;
		}
	}
}

//-------------------------------------------------------------------------------------------
void Board::initNextBoards(){

	possibleNextBoards = new Board * [8 * pieceCount];
	for (int i = 0; i < MAX_MOVE_TYPES * pieceCount; i++) {
		this->possibleNextBoards[i]= NULL;
	}
}


//-------------------------------------------------------------------------------------------
void Board::setNextTurnOnBoard(CellMode  nextTurnOnBoard){

	this->nextTurnOnBoard = nextTurnOnBoard;
}

//-------------------------------------------------------------------------------------------
CellMode Board::getNextTurnOnBoard(void){

	return this->nextTurnOnBoard;
}

//-------------------------------------------------------------------------------------------
void Board::clearSelections(void){

	for (int move = 0; move < MAX_MOVE_TYPES; move++){
		possibleNextCells[move]=NULL;
	}
	selected = NULL;
}

//-------------------------------------------------------------------------------------------
Cell* Board::getSelectedCell(void){

	return selected;
}

//-------------------------------------------------------------------------------------------
bool Board::getIsComputerWon(void){

	return isComputerWon;
}

//-------------------------------------------------------------------------------------------
bool Board::getIsPlayerWon(void){

	return isPlayerWon;
}
//-------------------------------------------------------------------------------------------
void Board::refreshWinningFlags() {

	this->isPlayerWon = true;
	this->isComputerWon = true;
	for (int row = 0; row < boardCellCount; row++){
		for (int col = 0; col < boardCellCount; col++) {
			if (currentState[row][col].mode == CELL_MODE_EMPTY){
				if (row + col < rowsWithPieceCount) {
					this->isComputerWon = false;
				} else if (row + col >= (2 * boardCellCount - rowsWithPieceCount - 1)) {
					this->isPlayerWon = false;
				}
			}
		}
	}
}

//-------------------------------------------------------------------------------------------
int Board::evaluateBoardStateForRed() {

	int min, max;
	int value=0;
	for (int i=0; i<boardCellCount; i++) {
		for (int j=0; j<boardCellCount; j++) {
			if (currentState[i][j].mode == CELL_MODE_RED) {
				int x=boardCellCount-i;
				int y=boardCellCount-j;
				min = x > y ? y : x;
				max = x < y ? y : x;
				value += 2 * min*(boardCellCount) + max;
			}
			if (currentState[i][j].mode == CELL_MODE_BLUE) {

				min = i > j ? j : i;
				max = i < j ? j : i;
				value -= min*(boardCellCount) + max;
			}
		}
	}
	return value;
}

//-------------------------------------------------------------------------------------------
Cell* Board::findEmptyUpLeftCell(Cell *selected) {

	int row = selected->xCellIndex;
	int col = selected->yCellIndex;
	Cell *emptyCell = NULL;

	if (row != 0 && col != 0) {
		emptyCell = &currentState[row-1][col-1];
		if (emptyCell->mode != CELL_MODE_EMPTY) {
			return findEmptyUpLeftCell(emptyCell);
		}
	}
	return emptyCell;
}

//-------------------------------------------------------------------------------------------
Cell* Board::findEmptyUpRightCell(Cell *selected) {

	int row = selected->xCellIndex;
	int col = selected->yCellIndex;
	Cell *emptyCell = NULL;

	if (row != 0 && col != (boardCellCount - 1)) {
		emptyCell = &currentState[row-1][col+1];
		if (emptyCell->mode != CELL_MODE_EMPTY) {
			return findEmptyUpRightCell(emptyCell);
		}
	}
	return emptyCell;
}

//-------------------------------------------------------------------------------------------
Cell* Board::findEmptyDownLeftCell(Cell *selected) {

	int row = selected->xCellIndex;
	int col = selected->yCellIndex;
	Cell *emptyCell = NULL;

	if (col != 0 && row != (boardCellCount - 1)) {
		emptyCell = &currentState[row+1][col-1];
		if (emptyCell->mode != CELL_MODE_EMPTY) {
			return findEmptyDownLeftCell(emptyCell);
		}
	}
	return emptyCell;
}

//-------------------------------------------------------------------------------------------
Cell* Board::findEmptyDownRightCell(Cell *selected) {

	int row = selected->xCellIndex;
	int col = selected->yCellIndex;
	Cell *emptyCell = NULL;

	if (col != (boardCellCount - 1) && row != (boardCellCount - 1)) {
		emptyCell = &currentState[row+1][col+1];
		if (emptyCell->mode != CELL_MODE_EMPTY) {
			return findEmptyDownRightCell(emptyCell);
		}
	}
	return emptyCell;
}

//-------------------------------------------------------------------------------------------
Cell* Board::findEmptyUpCell(Cell *selected) {

	int row = selected->xCellIndex;
	int col = selected->yCellIndex;
	Cell *emptyCell = NULL;

	if (row != 0) {
		emptyCell = &currentState[row-1][col];
		if (emptyCell->mode != CELL_MODE_EMPTY) {
			return findEmptyUpCell(emptyCell);
		}
	}
	return emptyCell;
}

//-------------------------------------------------------------------------------------------
Cell* Board::findEmptyDownCell(Cell *selected) {

	int row = selected->xCellIndex;
	int col = selected->yCellIndex;
	Cell *emptyCell = NULL;

	if (row != (boardCellCount - 1)) {
		emptyCell = &currentState[row+1][col];
		if (emptyCell->mode != CELL_MODE_EMPTY) {
			return findEmptyDownCell(emptyCell);
		}
	}
	return emptyCell;
}

//-------------------------------------------------------------------------------------------
Cell* Board::findEmptyRightCell(Cell *selected) {

	int row = selected->xCellIndex;
	int col = selected->yCellIndex;
	Cell *emptyCell = NULL;

	if (col != (boardCellCount - 1)) {
		emptyCell = &currentState[row][col+1];
		if (emptyCell->mode != CELL_MODE_EMPTY) {
			return findEmptyRightCell(emptyCell);
		}
	}
	return emptyCell;
}

//-------------------------------------------------------------------------------------------
Cell* Board::findEmptyLeftCell(Cell *selected) {

	int row = selected->xCellIndex;
	int col = selected->yCellIndex;
	Cell *emptyCell = NULL;

	if (col != 0) {
		emptyCell = &currentState[row][col-1];
		if (emptyCell->mode != CELL_MODE_EMPTY) {
			return findEmptyLeftCell(emptyCell);
		}
	}
	return emptyCell;
}


//-------------------------------------------------------------------------------------------
Cell* Board::findEmptyCellForMove(int move, Cell *selectedCell) {

	Cell *emptyCell = NULL;
	switch (move) {
		case UP_LEFT_MOVE : 
			emptyCell = findEmptyUpLeftCell(selectedCell);
			break;
		case UP_MOVE : 
			emptyCell = findEmptyUpCell(selectedCell);
			break;
		case UP_RIGHT_MOVE : 
			emptyCell = findEmptyUpRightCell(selectedCell);
			break;
		case RIGHT_MOVE : 
			emptyCell = findEmptyRightCell(selectedCell);
			break;
		case DOWN_RIGHT_MOVE : 
			emptyCell = findEmptyDownRightCell(selectedCell);
			break;
		case DOWN_MOVE : 
			emptyCell = findEmptyDownCell(selectedCell);
			break;
		case DOWN_LEFT_MOVE : 
			emptyCell = findEmptyDownLeftCell(selectedCell);
			break;
		case LEFT_MOVE : 
			emptyCell = findEmptyLeftCell(selectedCell);
			break;
	}
	return emptyCell;
}

//-------------------------------------------------------------------------------------------
void Board::makeNextMove(Cell *selectedCell, int move, int depth, int moveCount) {

	Cell *emptyCell = findEmptyCellForMove(move,selectedCell);

	if (emptyCell != NULL) {
		Board *nextBoard = new Board;
		nextBoard->copyCells(currentState);
		nextBoard->currentState[selectedCell->xCellIndex][selectedCell->yCellIndex].mode = CELL_MODE_EMPTY;
		nextBoard->currentState[emptyCell->xCellIndex][emptyCell->yCellIndex].mode = nextTurnOnBoard;
		nextBoard->setNextTurnOnBoard(nextTurnOnBoard == CELL_MODE_BLUE ? CELL_MODE_RED : CELL_MODE_BLUE);
		nextBoard->discoverNextMovesInGivenDepth(depth);
		this->possibleNextBoards[moveCount*MAX_MOVE_TYPES+move] = nextBoard;
	} else {
		this->possibleNextBoards[moveCount*MAX_MOVE_TYPES+move] = NULL;
	}
}

//-------------------------------------------------------------------------------------------
void Board::discoverNextMovesInGivenDepth(int depth) {

	if (depth == 0) {
		return;
	}
	depth--;

	Cell *selectedCell = NULL;
	int  moveCount = 0;

	for (int row = 0; row < boardCellCount; row++) {
		for (int col = 0; col < boardCellCount; col++) {
			selectedCell = &currentState[row][col];
			if (selectedCell->mode == nextTurnOnBoard) {
				for (int move = 0; move < MAX_MOVE_TYPES; move++) {
					makeNextMove(selectedCell, move, depth, moveCount);
				}
				moveCount++;
			} else continue;
		}
	}
}


//-------------------------------------------------------------------------------------------
void Board::fillPossibleNextPieceCells(void) {


	for (int move = 0; move < MAX_MOVE_TYPES; move++){
		possibleNextCells[move] = NULL;
		if (selected != NULL && selected->mode == nextTurnOnBoard && selected->xCellIndex >= 0 && selected->yCellIndex >= 0) {
			possibleNextCells[move] = findEmptyCellForMove(move, selected);
		} 
	}
}

//-------------------------------------------------------------------------------------------
void Board::selectCell(float x,float y){

	selected=NULL;
	swPoint selPoint;
	swPointSet(&selPoint,x,y);
	for(int i=0; i<boardCellCount; i++){
		for(int j=0; j<boardCellCount; j++){
			if(swIntersectionCircleAndPoint(&currentState[i][j].center,CELL_RADIOUS,&selPoint)){
				selected = &currentState[i][j];
			}
		}
	}
}



//-------------------------------------------------------------------------------------------
void Board::movePieceToSelectedIfSuitable(Cell * oldSelected){

	if (getSelectedCell() != NULL && getSelectedCell() != oldSelected){
		for (int move = 0; move < MAX_MOVE_TYPES; move++){
			if (getSelectedCell()  == possibleNextCells[move]){
				oldSelected->mode = CELL_MODE_EMPTY;
				getSelectedCell()->mode = nextTurnOnBoard;
				setNextTurnOnBoard(CELL_MODE_RED);
				break;
			}
		}
	}
}

//-------------------------------------------------------------------------------------------
void Board::setDragging(bool bEnabled) {
	isDragging=bEnabled;
}


//-------------------------------------------------------------------------------------------
void Board::draw(void) {
Cell temp;

	if(selected!=NULL){
		temp.xCellIndex=selected->xCellIndex;
		temp.yCellIndex=selected->yCellIndex;
		temp.center.x=selected->center.x;
		temp.center.y=selected->center.y;
		if(isDragging) temp.mode=CELL_MODE_EMPTY;
		else temp.mode=CELL_MODE_BLUE;
	}

	for(int i=0; i<boardCellCount; i++){
		for(int j=0;j<boardCellCount;j++){		
			Cell *cell=&currentState[i][j];
			if((selected==NULL) || (selected!=NULL && selected!=cell)){
				CellDisplay(cell,&SWCOLOR_WHITE,2);
			}
		}
	}

	if(selected!=NULL && selected->mode == nextTurnOnBoard){
     	CellDisplay(&temp,&SWCOLOR_RED,3);
		for (int move = 0; move < MAX_MOVE_TYPES; move++){
			if(possibleNextCells[move]!=NULL){
				CellDisplay(possibleNextCells[move],&SWCOLOR_GREEN,3);
			}
		}
	}
}


//-------------------------------------------------------------------------------------------
Board* Board::findBestNextBoard() {

	Board *child = NULL;
	Board *grandChild = NULL;
	int gradeMax = 0 - 2 * boardCellCount * boardCellCount *  boardCellCount * boardCellCount;
	int turnMultiplier = nextTurnOnBoard == CELL_MODE_RED ? 1 : -1;

	for (int i=0; i < pieceCount*MAX_MOVE_TYPES; i++) {
		if (possibleNextBoards[i] == NULL) {
			continue;
		} else {
			grandChild = possibleNextBoards[i]->findBestNextBoard();
			int maxGrandGrade = grandChild->gradeOfGreatestMove * turnMultiplier;
			if (maxGrandGrade > gradeMax) {
				gradeMax = maxGrandGrade;
				child = possibleNextBoards[i];
			}
		}
	}

	if (gradeOfGreatestMove == -1 && grandChild == NULL) {
		this->gradeOfGreatestMove = evaluateBoardStateForRed();
		child = this;	
	} else {
		this->gradeOfGreatestMove = child->gradeOfGreatestMove;
	}

	child->clearSelections();
	return child;
}
