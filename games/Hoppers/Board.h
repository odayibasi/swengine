#ifndef BOARD_H
#define BOARD_H

#include "Hoppers.h"

class Board {
private:
	Cell  *selected;
	Cell  *possibleNextCells[MAX_MOVE_TYPES];
	Board **possibleNextBoards;
	CellMode nextTurnOnBoard;
	int  pieceCount;
	int  gradeOfGreatestMove;
	bool isPlayerWon;
	bool isComputerWon;
	bool isDragging;

	void initCells();
	void initNextBoards();
	void copyCells(const Cell state[][MAX_CELL_COUNT]);
	Cell* findEmptyUpLeftCell(Cell*);
	Cell* findEmptyUpRightCell(Cell*);
	Cell* findEmptyDownLeftCell(Cell*);
	Cell* findEmptyDownRightCell(Cell*);
	Cell* findEmptyUpCell(Cell*);
	Cell* findEmptyDownCell(Cell*);
	Cell* findEmptyLeftCell(Cell*);
	Cell* findEmptyRightCell(Cell*);
	Cell* findEmptyCellForMove(int, Cell *);
	int   evaluateBoardStateForRed(void);
	void  makeNextMove(Cell*, int, int, int);

public:	
	Board();	
	Cell currentState[MAX_CELL_COUNT][MAX_CELL_COUNT];
	void draw(void);
	void selectCell(float, float);
	void fillPossibleNextPieceCells(void);
	void movePieceToSelectedIfSuitable(Cell * oldSelected);
	void clearSelections(void);
	void refreshWinningFlags(void);
	void setNextTurnOnBoard(CellMode);
	void discoverNextMovesInGivenDepth(int);
	Cell* getSelectedCell(void);
	CellMode getNextTurnOnBoard(void);
	bool getIsComputerWon(void);
	bool getIsPlayerWon(void);
	void setDragging(bool bEnable);
	Board* findBestNextBoard(void);
};
#endif 