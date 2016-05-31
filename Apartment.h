#ifndef MTM4_APARTMENT_H
#define MTM4_APARTMENT_H

#include <exception>

class Apartment {
public:
	class ApartmentException: public std::exception {};
	class IllegalArgException: public ApartmentException {};
	class OutOfApartmentBoundsException: public ApartmentException {};

	enum SquareType {EMPTY, WALL, NUM_SQUARE_TYPES};

/*****************C'tors, D'tor************************************************/
	Apartment(SquareType** squares, int length, int width, int price);
	Apartment(const Apartment& apartment);
	~Apartment();

/*****************Operators****************************************************/
	Apartment& operator= (const Apartment& apartment);
	Apartment& operator+= (const Apartment& apartment);
	const SquareType& operator() (int row, int col) const;
	SquareType& operator() (int row, int col);

/*****************Other methods************************************************/
	int getTotalArea() const;
	int getPrice() const;
	int getLength() const;
	int getWidth() const;

private:
	int length, width, price;
	SquareType** layout;

	static SquareType** allocateBoard(int length, int width);
	static SquareType** copyBoard(SquareType**squares,int length, int width);
	static void destroyBoard(SquareType**squares,int length);
	bool squareIsInBound(int row, int col) const;
	SquareType** joinLayoutsVertically(const Apartment& apartment) const;
	SquareType** joinLayoutsHorizontally(const Apartment& apartment) const;
};

/***************External operator functions************************************/
Apartment operator+(const Apartment& apartment_1, const Apartment& apartment_2);
bool operator< (const Apartment& apartment_1, const Apartment& apartment_2);

#endif //MTM4_APARTMENT_H
