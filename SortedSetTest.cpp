#include <cstdlib>
#include "SortedSet.h"
#include "MtmTst.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using std::endl;
using std::cout;

struct strCompare{
	bool operator()(const std::string& s1, const std::string& s2){
		return s1.compare(s2) < 0;
	}
};

struct Int {
    int i;

    Int(int i) : i(i) {}

    operator int() const { return i; }
};

class IntCompare {
public:
    bool operator()(const Int& i1, const Int& i2) const {
        return static_cast<int>(i1) < static_cast<int>(i2);
    }
};


//Generates string from integer seed, as it was converted to a 26-cimal number
//This is one-to-one function, for same seed you will get same string
//for different seeds - different strings.
//For example: strGenerator(77381556) returns std::string "string"
// 77381556 = 18 + 19*26 + 17*26^2 + 8*26^3 + 13*26^4 + 6*26^5
//            s     t       r        i         n        g
static std::string string(int seed){
	char out_str[8]; //maximal int value is nearly 26^6.6, and 1 more char for '\0'
	int i = 0;
	while (seed > 0) {
		out_str[i] = char(97 + seed % 26);//97 is ascii code of 'a'
		seed /= 26;//26 is obviously number of letters
		i++;
	}
	out_str[i] = '\0';
	return std::string(out_str);
}


bool testSortedSetCtor() {
	ASSERT_NO_THROW((SortedSet<int>()));
	ASSERT_NO_THROW((SortedSet<Int, IntCompare>()));
	ASSERT_NO_THROW((SortedSet<std::string, strCompare>()));
	return true;
}

bool testSortedSetCopyCtor() {
	const int upper_bound = 1000;
	SortedSet<Int, IntCompare> original;
	SortedSet<std::string, strCompare> str_original;
	for(int i=upper_bound, step=0; i>0; i-=step, step++){
		original.insert(i);
		str_original.insert(string(i));
	}
	SortedSet<Int, IntCompare> copy(original);
	SortedSet<std::string, strCompare> str_copy(str_original);
	ASSERT_EQUALS(original, copy);
	ASSERT_EQUALS(str_original, str_copy);
	//test independency
	ASSERT_EQUALS(true, original.remove(upper_bound));
	ASSERT_EQUALS(true, str_original.remove(string(upper_bound)));
	ASSERT_NOT_EQUALS(original, copy);
	ASSERT_NOT_EQUALS(str_original, str_copy);

	return true;
}

bool testSortedSetAssignOperator() {
	const int upper_bound = 750;
	SortedSet<Int, IntCompare> original;
	SortedSet<std::string, strCompare> str_original;
	for(int i=upper_bound, step=0; i>0; i-=step, step++){
		original.insert(i);
		str_original.insert(string(i));
	}
	SortedSet<Int, IntCompare> copy;
	SortedSet<std::string, strCompare> str_copy;
	copy = original;
	str_copy = str_original;
	ASSERT_EQUALS(original, copy);
	ASSERT_EQUALS(str_original, str_copy);
	//test independency
	ASSERT_EQUALS(true, original.remove(upper_bound));
	ASSERT_EQUALS(true, str_original.remove(string(upper_bound)));
	ASSERT_NOT_EQUALS(original, copy);
	ASSERT_NOT_EQUALS(str_original, str_copy);

	return true;
}

bool testBeginEnd(){
	SortedSet<Int, IntCompare> int_set;
	auto end = int_set.end();
	ASSERT_EQUALS(end, int_set.begin());
	int_set.insert(1);
	ASSERT_EQUALS(1, *(int_set.begin()));
	int_set.insert(1234567);
	auto it = int_set.begin();
	++it;
	it++;
	ASSERT_EQUALS(end, it);
	return true;
}

bool testSize(){
	const int numElements = 3000;
	SortedSet<Int, IntCompare> int_set;
	ASSERT_EQUALS(0, int_set.size());
    for (int i = numElements; i > 0; --i) {
        ASSERT_EQUALS(numElements - i, int_set.size());
        int_set.insert(i);
    }
    for (int i = 2; i <= numElements; i += 2) {
        int_set.remove(i);
        ASSERT_EQUALS(numElements - i/2, int_set.size());
    }
	return true;
}

bool testInsert() {
	SortedSet<Int, IntCompare> int_set;
	ASSERT_EQUALS(true, int_set.insert(10));
	ASSERT_EQUALS(true, int_set.insert(3));
	ASSERT_EQUALS(false, int_set.insert(3));
	ASSERT_EQUALS(true, int_set.insert(42));
	ASSERT_EQUALS(false, int_set.insert(42));
	ASSERT_EQUALS(false, int_set.insert(10));
	ASSERT_EQUALS(true, int_set.insert(45));
	ASSERT_EQUALS(true, int_set.insert(25));
	ASSERT_EQUALS(true, int_set.insert(2));
	auto current = int_set.begin();
	ASSERT_EQUALS(*current++, 2);
	ASSERT_EQUALS(*current++, 3);
	ASSERT_EQUALS(*current++, 10);
	ASSERT_EQUALS(*current++, 25);
	ASSERT_EQUALS(*current++, 42);
	ASSERT_EQUALS(*current, 45);

	SortedSet<std::string, strCompare> str_set;
	ASSERT_EQUALS(true, str_set.insert("King's Landing"));
	ASSERT_EQUALS(false, str_set.insert("King's Landing"));
	ASSERT_EQUALS(true, str_set.insert("Winterfell"));
	ASSERT_EQUALS(false, str_set.insert("Winterfell"));
	ASSERT_EQUALS(true, str_set.insert("Harrenhall"));
	ASSERT_EQUALS(false, str_set.insert("Harrenhall"));
	ASSERT_EQUALS(true, str_set.insert("Meereen"));
	ASSERT_EQUALS(true, str_set.insert("Castle Black"));
	auto str_current = str_set.begin();
	ASSERT_EQUALS(*str_current++, "Castle Black");
	ASSERT_EQUALS(*str_current++, "Harrenhall");
	ASSERT_EQUALS(*str_current++, "King's Landing");
	ASSERT_EQUALS(*str_current++, "Meereen");
	ASSERT_EQUALS(*str_current, "Winterfell");

	return true;
}

bool testRemove(){
	SortedSet<Int, IntCompare> int_set;
	ASSERT_EQUALS(false, int_set.remove(45));
	int_set.insert(-1);
	int_set.insert(-20);
	int_set.insert(30);
	int_set.insert(40);
	ASSERT_EQUALS(false, int_set.remove(50));
	ASSERT_EQUALS(false, int_set.remove(-50));
	ASSERT_EQUALS(true, int_set.remove(40));
	ASSERT_EQUALS(false, int_set.remove(40));
	ASSERT_EQUALS(true, int_set.remove(-20));
	ASSERT_EQUALS(false, int_set.remove(-20));
	ASSERT_EQUALS(false, int_set.remove(10));
	auto current = int_set.begin();
	ASSERT_EQUALS(*current++, -1);
	ASSERT_EQUALS(*current++, 30);
	ASSERT_EQUALS(current, int_set.end());

	SortedSet<std::string, strCompare> str_set;
	ASSERT_EQUALS(false, str_set.remove("Winterfell"));
	str_set.insert("King's Landing");
	str_set.insert("Harrenhall");
	str_set.insert("Meeryn");
	str_set.insert("Castle Black");
	ASSERT_EQUALS(false, str_set.remove("Winterfell"));
	ASSERT_EQUALS(false, str_set.remove("Astapor"));
	ASSERT_EQUALS(true, str_set.remove("Harrenhall"));
	ASSERT_EQUALS(false, str_set.remove("Harrenhall"));
	ASSERT_EQUALS(true, str_set.remove("Castle Black"));
	ASSERT_EQUALS(false, str_set.remove("Castle Black"));
	ASSERT_EQUALS(true, str_set.remove("Meeryn"));
	ASSERT_EQUALS(false, str_set.remove("Meeryn"));
	auto str_current = str_set.begin();
	ASSERT_EQUALS(*str_current++, "King's Landing");
	ASSERT_EQUALS(str_current, str_set.end());

	return true;
}

bool testFind(){
	SortedSet<Int, IntCompare> int_set;
	ASSERT_EQUALS(int_set.end(), int_set.find(5));
	int_set.insert(5);
	ASSERT_EQUALS(int_set.begin(), int_set.find(5));
	int_set.insert(10);
	int_set.insert(15);
	int_set.insert(20);
	int_set.insert(-5);
	int_set.insert(-10);
	int_set.insert(-20);
	ASSERT_EQUALS(int_set.end(), int_set.find(-200));
	ASSERT_EQUALS(int_set.end(), int_set.find(200));
	ASSERT_EQUALS(int_set.end(), int_set.find(0));
	ASSERT_EQUALS(-20, *(int_set.find(-20)));
	ASSERT_EQUALS(20, *(int_set.find(20)));
	ASSERT_EQUALS(10, *(int_set.find(10)));

	SortedSet<std::string, strCompare> str_set;
	ASSERT_EQUALS(str_set.end(), str_set.find("John's Snow Mother"));
	str_set.insert("King's Landing");
	ASSERT_EQUALS(str_set.begin(), str_set.find("King's Landing"));
	str_set.insert("Harrenhall");
	str_set.insert("Meeryn");
	str_set.insert("Castle Black");
	ASSERT_EQUALS(str_set.end(), str_set.find("Winterfell"));
	ASSERT_EQUALS(str_set.end(), str_set.find("Astapor"));
	ASSERT_NOT_EQUALS(str_set.end(), str_set.find("Harrenhall"));

	return true;
}

bool testUnion(){//Also tests Union Assignment
	SortedSet<Int, IntCompare> set_1, set_2;
	for(int i=-100; i<=10; i++){
		ASSERT_EQUALS(true, set_1.insert(i));
	}
	for(int i=-10; i<=100; i++){
		ASSERT_EQUALS(true, set_2.insert(i));
	}
	// [-100, 10] U [-10, 100] = [-100, 100]
	SortedSet<Int, IntCompare> set_union = set_1 | set_2;
	ASSERT_EQUALS(201, set_union.size());
	int j=-100;
	for(auto it = set_union.begin(); it != set_union.end(); ++it){
		ASSERT_EQUALS(j, *it);
		j++;
	}

	SortedSet<std::string, strCompare> str_set_1, str_set_2;
	for (int i = 0; i <= 500; i += 2) {
		ASSERT_EQUALS(true, str_set_1.insert(string(i)));
	}
	for (int i = 0; i <= 500; i += 3) {
		ASSERT_EQUALS(true, str_set_2.insert(string(i)));
	}
	// {x<=500 | x=2n} U {x<=500 | x=3n} = {x<=500 | x=2n or x=3n}
	str_set_1 |= str_set_2;
	for (int i = 0; i <= 500; i++) {
		if (i % 2 == 0 || i % 3 == 0) {
			ASSERT_EQUALS(true, str_set_1.remove(string(i)));
		} else {
			ASSERT_EQUALS(false, str_set_1.remove(string(i)));
		}
	}
	ASSERT_EQUALS(0, str_set_1.size());

	return true;
}

bool testIntersection(){//Also tests Intersection Assignment
	SortedSet<Int, IntCompare> set_1, set_2;
	for(int i=-100; i<=10; i++){
		ASSERT_EQUALS(true, set_1.insert(i));
	}
	for(int i=-10; i<=100; i++){
		ASSERT_EQUALS(true, set_2.insert(i));
	}
	// [-100, 10] n [-10, 100] = [-10, 10]
	SortedSet<Int, IntCompare> set_intersection = set_1 & set_2;
	ASSERT_EQUALS(21, set_intersection.size());
	int j=-10;
	for(auto it = set_intersection.begin(); it != set_intersection.end(); ++it){
		ASSERT_EQUALS(j, *it);
		j++;
	}

	SortedSet<std::string, strCompare> str_set_1, str_set_2;
	for (int i = 1000; i <= 5000; i += 5) {
		ASSERT_EQUALS(true, str_set_1.insert(string(i)));
	}
	for (int i = 1001 /* 143*7 */; i <= 5000; i += 7) {
		ASSERT_EQUALS(true, str_set_2.insert(string(i)));
	}
	str_set_1 &= str_set_2;
	for (int i = 1000; i <= 5000; i++) {
		if (i % 5 == 0 && i % 7 == 0) {
			ASSERT_EQUALS(true, str_set_1.remove(string(i)));
		} else {
			ASSERT_EQUALS(false, str_set_1.remove(string(i)));
		}
	}
	ASSERT_EQUALS(0, str_set_1.size());

	return true;
}

bool testRelativeComplement(){//Also tests Relative Complement Assignment
	SortedSet<Int, IntCompare> set_1, set_2;
	for(int i=-100; i<=100; i++){
		ASSERT_EQUALS(true, set_1.insert(i));
	}
	for(int i=-99; i<=100; i+=2){
		ASSERT_EQUALS(true, set_2.insert(i));
	}
	// { -100 <= x <= 100 | x is integer }\{ -100 <= x <= 100 | x=2n+1 } =
	// = { -100 <= x <= 100 | x=2n }
	SortedSet<Int, IntCompare> result = set_1 - set_2;
	ASSERT_EQUALS(101, result.size());
	int j=-100;
	for(auto it = result.begin(); it != result.end(); ++it){
		ASSERT_EQUALS(j, *it);
		j+=2;
	}

	SortedSet<std::string, strCompare> str_set_1, str_set_2;
	for (int i = 1000; i <= 5000; i += 5) {
		ASSERT_EQUALS(true, str_set_1.insert(string(i)));
	}
	for (int i = 1001 /* 143*7 */; i <= 5000; i += 7) {
		ASSERT_EQUALS(true, str_set_2.insert(string(i)));
	}
	str_set_1 -= str_set_2;
	for (int i = 1000; i <= 5000; i++) {
		if (i % 5 == 0 && i % 7 != 0) {
			ASSERT_EQUALS(true, str_set_1.remove(string(i)));
		} else {
			ASSERT_EQUALS(false, str_set_1.remove(string(i)));
		}
	}
	ASSERT_EQUALS(0, str_set_1.size());

	return true;
}

bool testSymmetricDifference(){//Also tests Symmetric Difference Assignment
	SortedSet<Int, IntCompare> set_1, set_2;
	for(int i=-100; i<=50; i++){
		ASSERT_EQUALS(true, set_1.insert(i));
	}
	for(int i=-50; i<=100; i++){
		ASSERT_EQUALS(true, set_2.insert(i));
	}
	SortedSet<Int, IntCompare> result = set_1 ^ set_2;
	ASSERT_EQUALS(100, result.size());
	int j=-100;
	for(auto it = result.begin(); it != result.end(); ++it){
		ASSERT_EQUALS(j, *it);
		if(++j == -50){
			j=51;
		}
	}

	SortedSet<std::string, strCompare> str_set_1, str_set_2;
	for (int i = 1000; i <= 5000; i += 5) {
		ASSERT_EQUALS(true, str_set_1.insert(string(i)));
	}
	for (int i = 1001 /* 143*7 */; i <= 5000; i += 7) {
		ASSERT_EQUALS(true, str_set_2.insert(string(i)));
	}
	str_set_1 ^= str_set_2;
	for (int i = 1000; i <= 5000; i++) {
		if ((i % 5 == 0 || i % 7 == 0) && i % 35 != 0) {
			ASSERT_EQUALS(true, str_set_1.remove(string(i)));
		} else {
			ASSERT_EQUALS(false, str_set_1.remove(string(i)));
		}
	}
	ASSERT_EQUALS(0, str_set_1.size());

	return true;
}


bool testComboTest(){
	const int upper_bound = 500;
	//checking some theorems of set theory
	SortedSet<Int, IntCompare> A, B, C;
	for (int i = 0; i < upper_bound; i++) {
		if (i % 3 == 0) {
			A.insert(i);
		}
		if (i % 5 == 0) {
			B.insert(i);
		}
		if (i % 7 == 0) {
			C.insert(i);
		}
	}
	SortedSet<Int, IntCompare> S1, S2;
	// 1. |A U B| = |A| + |B| - |A n B|
	S1 = A | B;
	S2 = A & B;
	ASSERT_EQUALS(S1.size(), A.size() + B.size() - S2.size());
	// 2. (B \ A) n C = (B n C) \ A
	S1 = (B - A) & C;
	S2 = (B & C) - A;
	ASSERT_EQUALS(S1, S2);
	// 3. B ^ A = (B U A) - (B n A)
	S1 = B ^ A;
	S2 = (B | A) - (B & A);
	ASSERT_EQUALS(S1, S2);
	// 4. B ^ A = A ^ B
	S1 = B ^ A;
	S2 = A ^ B;
	ASSERT_EQUALS(S1, S2);
	// 5. A n (B ^ C) = (A n B)^(A n C)
	S1 = A & (B ^ C);
	S2 = (A & B) ^ (A & C);
	ASSERT_EQUALS(S1, S2);

	return true;
}

//int main() {
//	RUN_TEST(testSortedSetCtor);
//	RUN_TEST(testSortedSetCopyCtor);
//	RUN_TEST(testSortedSetAssignOperator);
//	RUN_TEST(testBeginEnd);
//	RUN_TEST(testSize);
//	RUN_TEST(testInsert);
//	RUN_TEST(testRemove);
//	RUN_TEST(testFind);
//	RUN_TEST(testUnion);
//	RUN_TEST(testIntersection);
//	RUN_TEST(testRelativeComplement);
//	RUN_TEST(testSymmetricDifference);
//	RUN_TEST(testComboTest);
//	return 0;
//}
