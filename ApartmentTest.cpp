#include <cstdlib>
#include "Apartment.h"
#include "MtmTst.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

static void deleteSquares(Apartment::SquareType** squares, int length) {
	for (int i = 0; i < length; ++i) {
		delete[] squares[i];
	}
	delete[] squares;
}

//Create a empty board for testing apartment class.
static Apartment::SquareType** createSquaresEmpty(int length, int width) {
	Apartment::SquareType**layout = new Apartment::SquareType*[length];
	for (int i = 0; i < length; i++) {
		layout[i] = new Apartment::SquareType[width];
		for (int j = 0; j < width; j++) {
			layout[i][j] = Apartment::EMPTY;
		}
	}
	return layout;
}

static Apartment::SquareType** createSquaresTilesPattern(int length, int width,
		int tile_length, int tile_width) {
	Apartment::SquareType** squarePtr = createSquaresEmpty(length, width);
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < width; j++) {
			if (j % tile_width == 0 || i % tile_length == 0) {
				squarePtr[i][j] = Apartment::WALL;
			}
		}
	}
	return squarePtr;
}

static Apartment::SquareType** createSquaresWallsOnly(int length, int width) {
	Apartment::SquareType** squarePtr = createSquaresEmpty(length, width);
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < width; j++) {
			squarePtr[i][j] = Apartment::WALL;
		}
	}
	return squarePtr;
}

bool testConstructor() {
	const int length = 3;
	const int width = 4;
	const int price = 1;
	Apartment::SquareType** board = createSquaresEmpty(length, width);
	ASSERT_THROW(Apartment::IllegalArgException,
			Apartment(nullptr, length, width, price));
	ASSERT_THROW(Apartment::IllegalArgException,
			Apartment(board, length, width, -1));
	ASSERT_THROW(Apartment::IllegalArgException,
			Apartment(board, length, 0, price));
	ASSERT_THROW(Apartment::IllegalArgException,
			Apartment(board, 0, width, price));
	ASSERT_THROW(Apartment::IllegalArgException,
			Apartment(board, length, -1, price));
	ASSERT_THROW(Apartment::IllegalArgException,
			Apartment(board, -1, width, price));
	ASSERT_NO_THROW(Apartment(board, length, width, 0));
	ASSERT_NO_THROW(Apartment(board, length, width, price));
	deleteSquares(board, length);
	return true;
}

bool testCopyCtor() {
	const int length = 13;
	const int width = 7;
	const int price = 1234567;
	Apartment::SquareType** board =
			createSquaresTilesPattern(length, width, 5, 4);
	/* Apartment of blocks 5*4:
	 *  weee...
	 * 	weee...
	 *  weee...
	 *  weee...
	 *  wwww...  */
	const Apartment original(board, length, width, price);
	ASSERT_NO_THROW(Apartment(original));
	const Apartment copy(original);
	ASSERT_EQUALS(original.getTotalArea(), copy.getTotalArea());
	ASSERT_EQUALS(original.getLength(), copy.getLength());
	ASSERT_EQUALS(original.getWidth(), copy.getWidth());
	ASSERT_EQUALS(original.getPrice(), copy.getPrice());
	ASSERT_EQUALS(Apartment::WALL, copy(0,0));
	ASSERT_EQUALS(Apartment::EMPTY, copy(1,1));
	ASSERT_EQUALS(Apartment::EMPTY, copy(12,6));
	deleteSquares(board, length);
	return true;
}

bool testAssignOperator() {
	const int length = 3;
	const int width = 4;
	const int price = 1;
	Apartment::SquareType** board =
			createSquaresTilesPattern(length, width, 5, 4);
	Apartment::SquareType** empty_board =
			createSquaresEmpty(2 * length, 2 * width);
	Apartment::SquareType** walls_board = createSquaresWallsOnly(length, width);
	Apartment tiled(board, length, width, price),
			empty(empty_board, 2 * length, 2 * width, price),
			walls(walls_board, length, width, price);
	ASSERT_EQUALS(0, walls.getTotalArea());
	walls = empty;
	ASSERT_NOT_EQUALS(0, walls.getTotalArea());
	ASSERT_NO_THROW(tiled = tiled);
	ASSERT_NO_THROW(walls = tiled);
	ASSERT_NO_THROW(empty = tiled);
	//now all 3 apartments are the same
	ASSERT_EQUALS(walls.getTotalArea(), empty.getTotalArea());
	ASSERT_EQUALS(walls.getLength(), empty.getLength());
	ASSERT_EQUALS(walls.getWidth(), empty.getWidth());
	ASSERT_EQUALS(walls.getPrice(), empty.getPrice());
	deleteSquares(board, length);
	deleteSquares(empty_board, 2*length);
	deleteSquares(walls_board, length);
	return true;
}

bool testGetPrice() {
	const int length = 3;
	const int width = 4;
	const int price = 8765164;
	Apartment::SquareType** board = createSquaresEmpty(length, width);
	const Apartment apartment(board, length, width, price);
	ASSERT_EQUALS(price, apartment.getPrice());
	deleteSquares(board, length);
	return true;
}

bool testGetLength() {
	const int length = 93;
	const int width = 4;
	const int price = 1;
	Apartment::SquareType** board = createSquaresEmpty(length, width);
	const Apartment apartment(board, length, width, price);
	ASSERT_EQUALS(length, apartment.getLength());
	deleteSquares(board, length);
	return true;
}

bool testGetWidth() {
	const int length = 3;
	const int width = 111;
	const int price = 1;
	Apartment::SquareType** board = createSquaresEmpty(length, width);
	const Apartment apartment(board, length, width, price);
	ASSERT_EQUALS(width, apartment.getWidth());
	deleteSquares(board, length);
	return true;
}

bool testGetTotalArea() {
	const int length = 3;
	const int width = 4;
	const int price = 1;
	Apartment::SquareType** board = createSquaresEmpty(length, width);
	Apartment apartment(board, length, width, price);
	ASSERT_EQUALS(width * length, apartment.getTotalArea());
	for (int i = 0; i < width; i++) {
		board[0][i] = Apartment::WALL;
	}
	const Apartment apartment2(board, length, width, price);
	ASSERT_EQUALS(width * (length - 1), apartment2.getTotalArea());
	apartment(0, 0) = Apartment::WALL;
	ASSERT_EQUALS(width * length - 1, apartment.getTotalArea());
	deleteSquares(board, length);
	return true;
}

bool testOperatorAddAssign() {
	const int price = 1000;
	Apartment::SquareType** board3x3 = createSquaresEmpty(3, 3);
	const Apartment apartment3x3(board3x3, 3, 3, price);
	Apartment tmp(apartment3x3);
	ASSERT_NO_THROW(tmp+=tmp);
	//same object, same length and width. result - apartment 6x3
	ASSERT_EQUALS(6, tmp.getLength());
	ASSERT_EQUALS(3, tmp.getWidth());
	ASSERT_NO_THROW(tmp+=apartment3x3);
	//same width, different length. result - apartment 9x3
	ASSERT_EQUALS(3*apartment3x3.getTotalArea(), tmp.getTotalArea());
	ASSERT_EQUALS(3*apartment3x3.getPrice(), tmp.getPrice());//prices added
	Apartment::SquareType** board9x5 = createSquaresEmpty(9, 5);
	const Apartment apartment9x5(board9x5, 9, 5, price);
	ASSERT_NO_THROW(tmp+=apartment9x5);
	//same length, different width. result - apartment 9x8
	ASSERT_EQUALS(9, tmp.getLength());
	ASSERT_EQUALS(8, tmp.getWidth());
	ASSERT_EQUALS(9*8, tmp.getTotalArea());//apartment was all empty
	ASSERT_NO_THROW(tmp+=apartment3x3);
	//9x8 + 3x3 = 12x8, all dimensions are different
	ASSERT_EQUALS(12, tmp.getLength());
	ASSERT_EQUALS(8, tmp.getWidth());
	ASSERT_EQUALS(9*8+3*3, tmp.getTotalArea());
	ASSERT_EQUALS(Apartment::EMPTY, tmp(9,2));
	ASSERT_EQUALS(Apartment::EMPTY, tmp(8,3));
	ASSERT_EQUALS(Apartment::WALL, tmp(9,3));
	deleteSquares(board3x3, 3);
	deleteSquares(board9x5, 9);
	return true;
}

bool testOperatorFunctor() {
	const int length = 4;
	const int width = 4;
	const int price = 1;
	Apartment::SquareType** board =
			createSquaresTilesPattern(length, width, 2, 2);
	/* wwww
	 * wewe
	 * wwww
	 * wewe */
	Apartment apartment(board, length, width, price);
	ASSERT_THROW(Apartment::OutOfApartmentBoundsException, apartment(-1, 0));
	ASSERT_THROW(Apartment::OutOfApartmentBoundsException, apartment(0, -1));
	ASSERT_THROW(Apartment::OutOfApartmentBoundsException, apartment(length,0));
	ASSERT_THROW(Apartment::OutOfApartmentBoundsException, apartment(0, width));
	ASSERT_EQUALS(Apartment::EMPTY, apartment(1, 1));
	ASSERT_NO_THROW(apartment(0, 0) = Apartment::EMPTY);
	ASSERT_NO_THROW(apartment(length - 1, width - 1) = Apartment::WALL);
	ASSERT_EQUALS(Apartment::EMPTY, apartment(0, 0));
	ASSERT_EQUALS(Apartment::WALL, apartment(length - 1, width - 1));
	deleteSquares(board, length);
	return true;
}

bool testOperatorAdd() {
	//there's not much to check, since it's implemented using op+=
	const int length = 3;
	const int width = 4;
	const int price = 1;
	Apartment::SquareType** board = createSquaresEmpty(length, width);
	Apartment::SquareType** board_2 = createSquaresEmpty(width, length);
	const Apartment apartment(board, length, width, price);//3x4
	const Apartment apartment_2(board_2, width, length, price);//4x3
	const Apartment joined(apartment + apartment_2);
	ASSERT_EQUALS(7, joined.getLength());
	ASSERT_EQUALS(4, joined.getWidth());
	ASSERT_EQUALS(Apartment::EMPTY, joined(3,2));
	ASSERT_EQUALS(Apartment::EMPTY, joined(2,3));
	ASSERT_EQUALS(Apartment::WALL, joined(3,3));
	deleteSquares(board, length);
	deleteSquares(board_2, width);
	return true;
}

bool testOperatorLess() {
	const int length = 3;
	const int width = 3;
	Apartment::SquareType** board = createSquaresEmpty(length, width);//area 9
	Apartment::SquareType** walls_board = createSquaresWallsOnly(length, width);
	Apartment::SquareType** tiles_board =
			createSquaresTilesPattern(length,width,length,width);//area 4
	const Apartment apartment_00(walls_board, length, width, 0),// "0/0" ratio
	 apartment_inf_1(walls_board, length, width, 5),//"infinite" ratio
	 apartment_inf_2(walls_board, length, width, 100),// larger "infinite" ratio
	 apartment_9x100(board, length, width, 900),// ratio: 100 per meter
	 apartment_4x100(tiles_board, length, width, 400),// ratio: 100 per meter
	 apartment_4x200(tiles_board, length, width, 800);// ratio: 200 per meter
	ASSERT_EQUALS(false, apartment_00 < apartment_00);
	ASSERT_EQUALS(true,  apartment_00 < apartment_inf_1);
	ASSERT_EQUALS(true, apartment_00 < apartment_9x100);
	ASSERT_EQUALS(false, apartment_inf_2 < apartment_00);
	ASSERT_EQUALS(true, apartment_inf_1 < apartment_inf_2);
	ASSERT_EQUALS(false, apartment_inf_2 < apartment_inf_1);
	ASSERT_EQUALS(false, apartment_inf_2 < apartment_4x100);
	ASSERT_EQUALS(false, apartment_9x100 < apartment_00);
	ASSERT_EQUALS(true,  apartment_9x100 < apartment_inf_1);
	ASSERT_EQUALS(true, apartment_9x100 < apartment_4x200);//regular case
	ASSERT_EQUALS(true, apartment_4x100 < apartment_9x100);//same ratio
	deleteSquares(board, length);
	deleteSquares(walls_board, length);
	deleteSquares(tiles_board, length);
	return true;
}

bool apartmentTest() {
	RUN_TEST(testConstructor);
	RUN_TEST(testCopyCtor);
	RUN_TEST(testAssignOperator);
	RUN_TEST(testGetPrice);
	RUN_TEST(testGetLength);
	RUN_TEST(testGetWidth);
	RUN_TEST(testGetTotalArea);
	RUN_TEST(testOperatorAddAssign);
	RUN_TEST(testOperatorFunctor);
	RUN_TEST(testOperatorAdd);
	RUN_TEST(testOperatorLess);
	return true;
}
