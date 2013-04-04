
#ifndef GAME_H_
#define GAME_H_

#include "board.h"
#include "pieces.h"
#include "io.h"
#include <time.h>

#define WAIT_TIME 700		//No. of milliseconds that the piece remains before going 1 block down

class Game{
  private :

  	int mScreenHeight;					//Screen height in pixel
  	int mNextPosX, mNextPosY;			//Position of next piece
  	int mNextPiece, mNextRotation;		//Kind and rotation of next piece

  	Board *mBoard;
  	Pieces *mPieces;
  	IO *mIO;

  	int getRand			(int pA, int pB);
  	void initGame		();
  	void drawPiece		(int pX, int pY, int pPiece, int pRotation);
  	void drawBoard		();

  public :

  	int mPosX, mPosY;		//Position of falling piece
  	int mPiece, mRotation;	//Kind and rotation of falling piece

  	Game 				(Board *pBoard, Pieces *pPieces, IO *pIO, int pScreenHeight);

  	void drawScene		();
  	void createNewPiece	();

};

#endif