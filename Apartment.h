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
	/* Apartment constractor.
	 *
	 * @param squares - two-dimensional array that holds the apartment building ,
	 * and its dimensions are width and length .
	 * @param length -the length of the apartment.
	 * @param width - the width of the apartment.
	 * @price-the price of the apartment.
	 * IllegalArgException - if width or height are not positive,
	 * price is negative, squares is NULL
	 * return:
	 * 	a new apartment object
	 */
	Apartment(SquareType** squares, int length, int width, int price);
	/* Apartment copy constractor.
	 *
	 * @param apartment - the copied apartment.
	 * return:
	 * a new apartment object.
	 */
	Apartment(const Apartment& apartment);
	/* Apartment destractor.
	 *
	 * Delete the Apartment object (this).
	 */
	~Apartment();

/*****************Operators****************************************************/

	/* Apartment assignment operator.
	 *
	 * Get a apartment object, and copy it to this.
	 * @param apartment - the copied apartment object.
	 * return:
	 * 	reference to this.
	 */
	Apartment& operator= (const Apartment& apartment);
	Apartment& operator+= (const Apartment& apartment);
	const SquareType& operator() (int row, int col) const;
	SquareType& operator() (int row, int col);

/*****************Other methods************************************************/
	/* getTotalArea return the number of empty squares in board apartment.
	 *
	 * return:
	 * 	empty squares in board apartment.
	 */
	int getTotalArea() const;
	/* getPrice return apartment price.
	 *
	 * return:
	 * 	apartment price.
	 */
	int getPrice() const;
	/* getLength return apartment length.
	 *
	 * return:
	 * 	apartment length.
	 */
	int getLength() const;
	/* getWidth return apartment width.
	 *
	 * return:
	 * 	apartment width.
	 */
	int getWidth() const;

private:
	int length, width, price;
	SquareType** layout;
	/* allocateBoard get length and width, allocate new squares (apartment board) for
	 * an apartment.
	 *
	 * @param length - the length of the board that we want to allocate.
	 * @param width - the width of the board that we want to allocate.
	 *
	 * return:
	 * 	new squares (apartment board).
	 */
	static SquareType** allocateBoard(int length, int width);
	/* copyBoard get squares and dimensional board (length and width),
	 * allocate new apartment board and copy the given squares,
	 * according given dimensional.
	 *
	 * @param squares - two-dimensional array that holds the apartment building ,
	 * and its dimensions are width and length .
	 * @param length -the length of the apartment.
	 * @param width - the width of the apartment.
	 *
	 * return:
	 * 	new squares (apartment board).
	 */
	static SquareType** copyBoard(SquareType**squares,int length, int width);
	/* destroyBoard frees all memory allocated for the given squares.
	 *
	 * @param squares - two-dimensional array (apartment board) that we want to delete.
	 * @param length -the length of the squares that we want to delete.
	 *
	 * Delete squares.
	 */
	static void destroyBoard(SquareType**squares,int length);
	bool squareIsInBound(int row, int col) const;
	SquareType** joinLayoutsVertically(const Apartment& apartment) const;
	SquareType** joinLayoutsHorizontally(const Apartment& apartment) const;
};

/***************External operator functions************************************/
Apartment operator+(const Apartment& apartment_1, const Apartment& apartment_2);
bool operator< (const Apartment& apartment_1, const Apartment& apartment_2);

#endif //MTM4_APARTMENT_H
