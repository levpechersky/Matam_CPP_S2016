#include <cstdlib>
#include "Apartment.h"
#include "MtmTst.h"

bool apartmentTestExample() {
 /*   const int length = 3;
    const int width = 4;
    const int price = 1;
    Apartment::SquareType** squares = new Apartment::SquareType*[length];
    for (int i = 0; i < length; ++i) {
        squares[i] = new Apartment::SquareType[width];
        for (int j = 0; j < width; ++j) {
                squares[i][j] = Apartment::EMPTY;
        }
    }
    ASSERT_NO_THROW(Apartment(squares, length, width, price));
    const Apartment apt(squares, length, width, price);
    ASSERT_EQUALS(length, apt.getLength());
    Apartment apt2(apt);
    ASSERT_NO_THROW(apt2 += apt);
    ASSERT_EQUALS(true, apt < apt2);
    deleteSquares(squares, length); TODO: uncomment when ready*/
    return true;
}

bool apartmentTest() {
    RUN_TEST(apartmentTestExample);
    return true;
}
