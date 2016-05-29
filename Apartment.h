#ifndef MTM4_APARTMENT_H
#define MTM4_APARTMENT_H

#include <exception>

class Apartment {
public:
	class ApartmentException: public std::exception {};
	class IllegalArgException: public ApartmentException {};
	class OutOfApartmentBoundsException: public ApartmentException {};

	enum SquareType {EMPTY, WALL, NUM_SQUARE_TYPES};

	/* C'tors, D'tor */
	Apartment(SquareType** squares, int length, int width, int price);
	Apartment(const Apartment& apartment);
	~Apartment();

	/* Operators */
	Apartment& operator= (const Apartment& apartment); //TODO should handle self-assignments
	Apartment& operator+= (const Apartment& apartment);
	const SquareType& operator() (int row, int col) const;
	SquareType& operator() (int row, int col);

	/* Other methods */
	int getTotalArea() const;
	int getPrice() const;
	int getLength() const;
	int getWidth() const;

private:
	SquareType** layout;
	int length, width, price;

	bool squareIsInBound(int row, int col) const;
	SquareType** joinLayoutsVertically(const Apartment& apartment) const;
	SquareType** joinLayoutsHorizontally(const Apartment& apartment) const;
};

/*****************************
 * External operator function
 ****************************/

Apartment operator+(const Apartment& apartment_1, const Apartment& apartment_2);
bool operator< (const Apartment& apartment_1, const Apartment& apartment_2);

#endif //MTM4_APARTMENT_H
