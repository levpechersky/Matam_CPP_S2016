#include "Apartment.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

//******************************************************************************
//**********************Static functions of the Class***************************
//******************************************************************************
Apartment::SquareType** Apartment::allocateBoard(int length, int width) {
	SquareType**layout = new SquareType*[length];
	for (int i = 0; i < length; i++) {
		layout[i] = new SquareType[width];
	}
	return layout;
}

Apartment::SquareType** Apartment::copyBoard(Apartment::SquareType**squares,
		int length, int width) {
	SquareType**layout = allocateBoard(length, width);
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < width; j++) {
			layout[i][j] = squares[i][j];
		}
	}
	return layout;
}

void Apartment::destroyBoard(Apartment::SquareType**squares, int length) {
	for (int i = 0; i < length; i++) {
		delete[] squares[i];
	}
	delete[] squares;
}

//******************************************************************************
//*******************************Methods****************************************
//******************************************************************************
int Apartment::getTotalArea() const {
	int area = 0;
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < width; j++) {
			area += (layout[i][j] == EMPTY);
		}
	}
	return area;
}

int Apartment::getPrice() const {
	return price;
}

int Apartment::getLength() const {
	return length;
}

int Apartment::getWidth() const {
	return width;
}

bool Apartment::squareIsInBound(int row, int col) const {
	return row >= 0 && row < length && col >= 0 && col < width;
}

Apartment::SquareType** Apartment::joinLayoutsVertically(
		const Apartment& apartment) const {
	int new_length(length + apartment.length);
	int new_width(width > apartment.width ? width : apartment.width);
	SquareType** new_layout = allocateBoard(new_length, new_width);
	for (int i = 0; i < new_length; i++) {
		for (int j = 0; j < new_width; j++) {
			if (i < length) {
				new_layout[i][j] = j < width ? layout[i][j] : WALL;
			} else {
				new_layout[i][j] =
						j < apartment.width ?
								apartment.layout[i - length][j] : WALL;
			}
		}
	}
	return new_layout;
}

Apartment::SquareType** Apartment::joinLayoutsHorizontally(
		const Apartment& apartment) const {
	int new_width(width + apartment.width);
	SquareType** new_layout = allocateBoard(length, new_width);
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < new_width; j++) {
			new_layout[i][j] =
					j < width ? layout[i][j] : apartment.layout[i][j - width];
		}
	}
	return new_layout;
}

//******************************************************************************
//*******************************Operators**************************************
//******************************************************************************

Apartment& Apartment::operator= (const Apartment& apartment){
	Apartment::SquareType** temp=copyBoard(apartment.layout,apartment.length,apartment.width);
	destroyBoard(layout,length);
	length=apartment.length;
	width=apartment.width;
	price=apartment.price;
	layout=temp;

Apartment& Apartment::operator=(const Apartment& apartment) {
	SquareType** temp = copyBoard(apartment.layout, apartment.length,
			apartment.width);
	destroyBoard(layout, length);
	length = apartment.length;
	width = apartment.width;
	price = apartment.price;
	layout = temp;
	return *this;
}

Apartment& Apartment::operator+=(const Apartment& apartment) {
	SquareType** joined = nullptr;
	int tmp_length = length;
	if (length == apartment.length && width != apartment.length) {
		joined = joinLayoutsVertically(apartment);
		width += apartment.width;
	} else {
		joined = joinLayoutsHorizontally(apartment);
		width = width > apartment.width ? width : apartment.width;
		length += apartment.length;
	}
	destroyBoard(layout, tmp_length);
	layout = joined;
	price += apartment.price;
	return *this;
}

const Apartment::SquareType& Apartment::operator()(int row, int col) const {
	return const_cast<SquareType &>(static_cast<const SquareType &>((*this)(row,
			col)));
}

Apartment::SquareType& Apartment::operator()(int row, int col) {
	if (!squareIsInBound(row, col)) {
		throw OutOfApartmentBoundsException();
	}
	return layout[row][col];
}

bool operator<(const Apartment& apartment_1, const Apartment& apartment_2) {
	int area_1(apartment_1.getTotalArea()), area_2(apartment_2.getTotalArea()),
			price_1(apartment_1.getPrice()), price_2(apartment_2.getPrice());
	if (area_1 != 0 && area_2 != 0) {
		int ratio_1(price_1 * area_2), ratio_2(price_2 * area_1); // if areas aren't 0: p1/a1 < p2/a2 <=> p1*a2 < p2*a1. No FP numbers.
		if (ratio_1 != ratio_2) {
			return (ratio_1 < ratio_2);
		}
	} else if (area_1 == 0) {
		//if area and price is 0: "0/0" is equal to anything - return false
		//if area is 0 and price isn't: "x/0" considered infinity and ratio_1>ratio_2 - return false
		return false;
	} else if (area_2 == 0) {
		//if area and price is 0: "0/0" is equal to anything - return false
		//if area is 0 and price isn't: "x/0" considered infinity and ratio_1<ratio_2 - return true
		return price_2 != 0;
	}
	//if ratios are equal, or both areas are 0 (e.g comapring two "infinities") - compare prices.
	return price_1 < price_2;
}

Apartment operator+(const Apartment& apartment_1,
		const Apartment& apartment_2) {
	return Apartment(apartment_1) += apartment_2;
}

//******************************************************************************
//***************************C'tors, D'tor**************************************
//******************************************************************************
Apartment::Apartment(SquareType** squares, int length, int width, int price) :
		length(length), width(width), price(price), layout(
				copyBoard(squares, length, width)) {
	if (!(squares && length > 0 && width > 0 && price >= 0)) {
		throw IllegalArgException();
	}
}

Apartment::Apartment(const Apartment& apartment) :
		length(apartment.length), width(apartment.width), price(
				apartment.price), layout(
				copyBoard(apartment.layout, length, width)) {
}

Apartment::~Apartment() {
	destroyBoard(layout, length);
}
