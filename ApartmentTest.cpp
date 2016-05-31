#include <cstdlib>
#include "Apartment.h"
#include "MtmTst.h"
//using Apartment::IllegalArgException;

//Create a empty board for testing apartment calss.
static Apartment:: SquareType** createBoardEmpty(int length, int width){
	Apartment::SquareType**layout=new Apartment::SquareType*[length];
	for (int i = 0; i < length; i++){
		layout[i] = new Apartment::SquareType[width];
		for(int j=0; j<width; j++){
			layout[i][j]=Apartment::EMPTY;
		}
	}
	return layout;
}

static void deleteSquares(Apartment:: SquareType**squares,int length){
	for (int i = 0; i < length; i++){
	   delete[] squares[i];
	}
	delete[] squares;
}

bool testConstructor() {
	const int length = 3;
	const int width = 4;
	Apartment:: SquareType** board= createBoardEmpty(length,width);
	//const int price = 1;
	deleteSquares(board,length);

    return true;
}

bool testCopyCtor() {
	const int length = 3;
	const int width = 4;
	Apartment:: SquareType** board= createBoardEmpty(length,width);
	//const int price = 1;
	deleteSquares(board,length);

    return true;
}

bool testDtor() {
	const int length = 3;
	const int width = 4;
	Apartment:: SquareType** board= createBoardEmpty(length,width);
	//const int price = 1;
	deleteSquares(board,length);

    return true;
}

bool testAssignOperator() {
	const int length = 3;
	const int width = 4;
	Apartment:: SquareType** board= createBoardEmpty(length,width);
	//const int price = 1;
	deleteSquares(board,length);

    return true;
}

bool testGetPrice() {
	const int length = 3;
	const int width = 4;
	Apartment:: SquareType** board= createBoardEmpty(length,width);
	//const int price = 1;
	deleteSquares(board,length);

    return true;
}
bool testGetLength() {
	const int length = 3;
	const int width = 4;
	Apartment:: SquareType** board= createBoardEmpty(length,width);
	//const int price = 1;
	deleteSquares(board,length);

    return true;
}
bool testGetWidth() {
	const int length = 3;
	const int width = 4;
	Apartment:: SquareType** board= createBoardEmpty(length,width);
	//const int price = 1;
	deleteSquares(board,length);

    return true;
}
bool testGetTotalArea() {
	const int length = 3;
	const int width = 4;
	Apartment:: SquareType** board= createBoardEmpty(length,width);
	//const int price = 1;
	deleteSquares(board,length);
    return true;
}
int main(){
	RUN_TEST(testConstructor);
	RUN_TEST(testCopyCtor);
	RUN_TEST(testDtor);
	RUN_TEST(testAssignOperator);
	RUN_TEST(testGetPrice);
	RUN_TEST(testGetLength);
	RUN_TEST(testGetWidth);
	RUN_TEST(testGetTotalArea);
	return 0;
}
