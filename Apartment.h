#ifndef MTM4_APARTMENT_H
#define MTM4_APARTMENT_H

#include <exception>

class Apartment {
public:
	class ApartmentException: public std::exception {};
	class IllegalArgException: public ApartmentException {};
	class OutOfApartmentBoundsException: public ApartmentException {};
	enum SquareType {EMPTY, WALL, NUM_SQUARE_TYPES};
	//************************* C'tors, D'tor************************
	Apartment(SquareType** squares, int length, int width, int price);
	Apartment(const Apartment& apartment);
	~Apartment();
	//*************************Operators******************************
	Apartment& operator= (const Apartment& apartment); //TODO should handle self-assignments
	//*************************C'tors, D'tor***************************
	int getPrice() const;
	int getLength() const;
	int getWidth() const;
	int getTotalArea() const;
private:
	int length, width, price;
	SquareType** layout;
	static SquareType** allocateBoard(int length, int width);
	static SquareType** copyBoard(SquareType**squares,int length, int width);
	static void destroyBoard(SquareType**squares,int length);
};

#endif //MTM4_APARTMENT_H
