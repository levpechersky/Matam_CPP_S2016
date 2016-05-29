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
	// following 2 throw OutOfApartmentBoundsException
	const SquareType& operator() (int row, int col) const; //TODO not 100% sure about those const's
	SquareType& operator() (int row, int col);
	bool operator< (const Apartment& apartment) const; //TODO maybe should be friend

	/* Other methods */
	int getTotalArea() const;
	int getPrice() const;
	int getLength() const;
	int getWidth() const;

private:
	SquareType** layout;
	int length, width, price;
};

/*****************************
 * External operator function
 ****************************/

//TODO this one should be implemented using += operator
Apartment operator+(const Apartment& apartment_1, const Apartment& apartment_2);

#endif //MTM4_APARTMENT_H
