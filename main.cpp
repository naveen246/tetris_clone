
#include "game.h"

int main(){
	IO mIO;
	int mScreenHeight = mIO.getScreenHeight();

	Pieces mPieces;

	Board mBoard(&mPieces, mScreenHeight);

	Game mGame(&mBoard, &mPieces, &mIO, mScreenHeight);

	//get actual clock milliseconds (SDL)
	unsigned long mTime1 = SDL_GetTicks();

	while(!mIO.isKeyDown(SDLK_ESCAPE)){
		mIO.clearScreen();
		mGame.drawScene();		//draw piece and board
		mIO.updateScreen();		//put graphics content on screen

		int mKey = mIO.pollKey();

		switch(mKey){
			case SDLK_RIGHT :
			{
				if(mBoard.isPossibleMovement(mGame.mPosX + 1, mGame.mPosY, mGame.mPiece, mGame.mRotation))
					mGame.mPosX++;
				break;
			}
			case SDLK_LEFT :
			{
				if(mBoard.isPossibleMovement(mGame.mPosX - 1, mGame.mPosY, mGame.mPiece, mGame.mRotation))
					mGame.mPosX--;
				break;
			}
			case SDLK_DOWN :
			{
				if(mBoard.isPossibleMovement(mGame.mPosX, mGame.mPosY + 1, mGame.mPiece, mGame.mRotation))
					mGame.mPosY++;
				break;
			}
			case SDLK_x :
			{
				while(mBoard.isPossibleMovement(mGame.mPosX, mGame.mPosY, mGame.mPiece, mGame.mRotation)) { mGame.mPosY++; }

				mBoard.storePiece(mGame.mPosX, mGame.mPosY - 1, mGame.mPiece, mGame.mRotation);

				mBoard.deletePossibleLines();

				if(mBoard.isGameOver()){
					mIO.getKey();
					exit(0);
				}

				mGame.createNewPiece();
				break;
			}
			case SDLK_z :
			{
				if(mBoard.isPossibleMovement(mGame.mPosX, mGame.mPosY, mGame.mPiece, (mGame.mRotation + 1) % 4))
					mGame.mRotation = (mGame.mRotation + 1) % 4;
				break;
			}
		}

		//vertical movement

		unsigned long mTime2 = SDL_GetTicks();

		if(mTime2 - mTime1 > WAIT_TIME){
			if(mBoard.isPossibleMovement(mGame.mPosX, mGame.mPosY + 1, mGame.mPiece, mGame.mRotation)) {
				mGame.mPosY++;
			} else{
				mBoard.storePiece(mGame.mPosX, mGame.mPosY, mGame.mPiece, mGame.mRotation);
				mBoard.deletePossibleLines();
				if(mBoard.isGameOver()){
					mIO.getKey();
					exit(0);
				}
				mGame.createNewPiece();
			}

			mTime1 = SDL_GetTicks();
		}
	}

	return 0;
}