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
	/* Apartment constructor.
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

	/* Apartment copy constructor.
	 *
	 * @param apartment - the copied apartment.
	 * return:
	 * a new apartment object.
	 */
	Apartment(const Apartment& apartment);

	/* Apartment destructor.
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

	/* Apartment append operator.
	 *
	 * Two apartments are joined into the left one. It's area will be sum of
	 * areas, price - sum of prices.
	 * If apartments have same width - their layouts are joined vertically
	 * If apartments have same length - their layouts are joined horizontally
	 * Otherwise, apartments are joined vertically.
	 * For further explanation - look joinLayoutsVertically(Horizontally)
	 * description.
	 * @param apartment - an appartment to append.
	 * return:
	 * 	reference to this.
	 */
	Apartment& operator+= (const Apartment& apartment);

	/* This operator provides access to layout tiles (both versions).
	 *
	 * This functions throw OutOfApartmentBoundsException in case given
	 * coordinates are out of layout's bounds.
	 * @param row - row index in layout.
	 * @param col - column index in layout.
	 * return:
	 * 	reference to tile in row <row> and column <col>.
	 */
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
	int getPrice() const { return price; };

	/* getLength return apartment length.
	 *
	 * return:
	 * 	apartment length.
	 */
	int getLength() const  { return length; };

	/* getWidth return apartment width.
	 *
	 * return:
	 * 	apartment width.
	 */
	int getWidth() const  { return width; };

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

	/* Checks whether given coordinates are legal, e.g are in bounds of layout.
	 *
	 * @param row - row index in layout.
	 * @param col - column index in layout.
	 *
	 * return:
	 * 	true if coordinates are legal
	 * 	else otherwise
	 */
	bool squareIsInBound(int row, int col) const;

	/* Creates new allocated layout, which consists of two apartments' layouts.
	 * apartment will be appended to the bottom of this' layout.
	 * In case widths aren't equal, resulting width will be the maximum of
	 * widths, and an empty space will be filled with WALL tiles, so total area
	 * will be exactly the sum of areas. Original apartments stay unchanged.
	 * Resulting length will be sum of lengths.
	 *
	 * @param apartment - an apartment to append.
	 *
	 * return:
	 * 	new joined squares (apartment layout).
	 */
	SquareType** joinLayoutsVertically(const Apartment& apartment) const;

	/* Creates new allocated layout, which consists of two apartments' layouts.
	 * apartment will be appended to the right of this' layout.
	 * Length of both apartments should be equal.
	 * Original apartments stay unchanged.
	 * Resulting width will be sum of widths.
	 *
	 * @param apartment - an apartment to append.
	 *
	 * return:
	 * 	new joined squares (apartment layout).
	 */
	SquareType** joinLayoutsHorizontally(const Apartment& apartment) const;
};

/***************External operator functions************************************/

/* Joins two apartments into temporary apartment and returns it.
 * For further explanation look operator+= description.
 *
 * @param apartment_1 - an apartment to append to (though stays unchanged).
 * @param apartment_2 - an apartment to append.
 * return:
 * 	new joined squares (apartment layout).
 */
Apartment operator+(const Apartment& apartment_1, const Apartment& apartment_2);

/* Compares two apartments by price/area ratio. For area definition look
 * getTotalArea description.
 * In case area is 0, ratio considered infinity, unless the price is also zero.
 * In that case ratio "0/0" is considered equal to any other value.
 * In case two apartments same ratio - an apartment with
 * lower price is considered smaller.
 *
 * return:
 * 	true if apartment_1 considered smaller than apartment_2
 * 	false otherwise
 */
bool operator< (const Apartment& apartment_1, const Apartment& apartment_2);

#endif //MTM4_APARTMENT_H
