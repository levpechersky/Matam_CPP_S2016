/*
 * Apartment.cpp
 *
 *  Created on: May 29, 2016
 */

#include "Apartment.h"
#include <algorithm>

//====Non-members:==============================================================
Apartment::SquareType** allocateSquares(int width, int length) {
	Apartment::SquareType** new_layout = new Apartment::SquareType*[length];
	for (int i = 0; i < length; i++) {
		new_layout[i] = new Apartment::SquareType[width];
	}
	return new_layout;
}

bool operator<(const Apartment& apartment_1, const Apartment& apartment_2) { //TODO looks a bit ugly
	int area_1(apartment_1.getTotalArea()), area_2(apartment_2.getTotalArea()),
		price_1(apartment_1.getPrice()), price_2(apartment_2.getPrice());
	if (area_1 != 0 && area_2 != 0) {
		int ratio_1(price_1 / area_1), ratio_2(price_2 / area_2);
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

//====Public:===================================================================
Apartment& Apartment::operator+=(const Apartment& apartment) {
	//TODO width and length are calculated in join... functions. May be considered code duplication
	SquareType** joined = NULL;
	if (length == apartment.length && width != apartment.length) {
		joined = joinLayoutsVertically(apartment);
		width += apartment.width;
	} else {
		joined = joinLayoutsHorizontally(apartment);
		width = std::max(width, apartment.width);
		length += apartment.length;
	}
	//TODO destroySquares();
	layout = joined;
	price += apartment.price;
	return *this;
}

const Apartment::SquareType& Apartment::operator()(int row, int col) const {
	if (!squareIsInBound(row, col)) {
		throw OutOfApartmentBoundsException();
	}
	return layout[row][col];
}

Apartment::SquareType& Apartment::operator()(int row, int col) {
	if (!squareIsInBound(row, col)) {
		throw OutOfApartmentBoundsException();
	}
	return layout[row][col];
}

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

//====Private:==================================================================
bool Apartment::squareIsInBound(int row, int col) const {
	return row >= 0 && row < length && col >= 0 && col < width;
}

Apartment::SquareType** Apartment::joinLayoutsVertically(
	const Apartment& apartment) const {
	int new_length(getLength() + apartment.getLength());
	int new_width(std::max(getWidth(), apartment.getWidth())); //TODO check if it's ok to use this max() function
	SquareType** new_layout = allocateSquares(new_width, new_length);
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
	SquareType** new_layout = allocateSquares(new_width, length);
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < new_width; j++) {
			new_layout[i][j] =
				j < width ? layout[i][j] : apartment.layout[i][j - width];
		}
	}
	return new_layout;
}

