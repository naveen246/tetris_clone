
#include "board.h"

Board::Board(Pieces *pPieces, int pScreenHeight){
	mScreenHeight = pScreenHeight;
	mPieces = pPieces;
	initBoard();
}

//initialize the board with free positions
void Board::initBoard(){
	for(int i = 0; i < BOARD_WIDTH; i++){
		for(int j = 0; j < BOARD_HEIGHT; j++){
			mBoard[i][j] = POS_FREE;
		}
	}
}

/*delete a line of the board by moving all above lines down
pY : vertical position in blocks of the line to delete*/
void Board::deleteLine(int pY){
	for(int j = pY; j > 0; j--){
		for(int i = 0; i < BOARD_WIDTH; i++){
			mBoard[i][j] = mBoard[i][j - 1];
		}
	}
}

//takes horizontal position in blocks and returns horizontal position in pixels
int Board::getXPosInPixels(int pPos){
	return  ( ( BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH / 2)) ) + (pPos * BLOCK_SIZE) );
}

//takes vertical position in blocks and returns vertical position in pixels
int Board::getYPosInPixels(int pPos){
	return ( (mScreenHeight - (BLOCK_SIZE * BOARD_HEIGHT)) + (pPos * BLOCK_SIZE) );
}


bool Board::isFreeBlock(int pX, int pY){
	return mBoard[pX][pY] == POS_FREE;
}


bool Board::isPossibleMovement(int pX, int pY, int pPiece, int pRotation){
	for(int i1 = pX, i2 = 0; i1 < pX + PIECE_BLOCKS; i1++, i2++){
		for(int j1 = pY, j2 = 0; j1 < pY + PIECE_BLOCKS; j1++, j2++){
			// Check if the piece is outside the limits of the board
			if(i1 < 0 || i1 >= BOARD_WIDTH || j1 >= BOARD_HEIGHT){
				if(mPieces->getBlockType(pPiece, pRotation, j2, i2) != 0){
					return false;
				}
			}
			// Check if the piece have collisioned with a block already stored in the map
			if(j1 >= 0){
				if(mPieces->getBlockType(pPiece, pRotation, j2, i2) != 0 && !isFreeBlock(i1, j1)){
					return false;
				}
			}
		}
	}
	return true;
}

//store a piece in the board by filling the blocks
void Board::storePiece(int pX, int pY, int pPiece, int pRotation){
	// Store each block of the piece into the board
	for(int i1 = pX, i2 = 0; i1 < pX + PIECE_BLOCKS; i1++, i2++){
		for(int j1 = pY, j2 = 0; j1 < pY + PIECE_BLOCKS; j1++, j2++){
			// Store only the blocks of the piece that are not holes
			if(mPieces->getBlockType(pPiece, pRotation, j2, i2) != 0){
				mBoard[i1][j1] = POS_FILLED;
			}
		}
	}
}

//delete all lines that should be removed
void Board::deletePossibleLines(){
	for(int j = 0; j < BOARD_HEIGHT; j++){
		int i;
		for(i = 0; i < BOARD_WIDTH; i++){
			if(mBoard[i][j] != POS_FILLED) break;
		}
		if(i == BOARD_WIDTH) deleteLine(j);
	}
}

//if the first line has blocks then game over
bool Board::isGameOver(){
	for(int i = 0; i < BOARD_WIDTH; i++){
		if(mBoard[i][0] == POS_FILLED) return true;
	}
	return false;
}