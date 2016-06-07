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

//bool testConstructor() {
//
//	return true;
//}
//
//bool testCopyCtor() {
//
//	return true;
//}
//
//bool testAssignOperator() {
//
//	return true;
//}

bool testSize(){

	return true;
}

bool testInsert() {
	SortedSet<int> int_set;
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
	SortedSet<int> int_set;
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
	SortedSet<int> int_set;
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

bool testUnion(){
	SortedSet<int> set_1, set_2;
	for(int i=-100; i<=10; i++){
		ASSERT_EQUALS(true, set_1.insert(i));
	}
	for(int i=-10; i<=100; i++){
		ASSERT_EQUALS(true, set_2.insert(i));
	}
	// [-100, 10] U [-10, 100] = [-100, 100]
	SortedSet<int> set_union = set_1 | set_2;
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
	SortedSet<std::string, strCompare> str_set_union = str_set_1 | str_set_2;
	for (int i = 0; i <= 500; i++) {
		if (i % 2 == 0 || i % 3 == 0) {
			ASSERT_EQUALS(true, str_set_union.remove(string(i)));
		} else {
			ASSERT_EQUALS(false, str_set_union.remove(string(i)));
		}
	}
	ASSERT_EQUALS(0, str_set_union.size());

	return true;
}

bool testIntersection(){
	SortedSet<int> set_1, set_2;
	for(int i=-100; i<=10; i++){
		ASSERT_EQUALS(true, set_1.insert(i));
	}
	for(int i=-10; i<=100; i++){
		ASSERT_EQUALS(true, set_2.insert(i));
	}
	// [-100, 10] n [-10, 100] = [-10, 10]
	SortedSet<int> set_intersection = set_1 & set_2;
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
	//
	SortedSet<std::string, strCompare> str_set_intersection = str_set_1 & str_set_2;
	for (int i = 1000; i <= 5000; i++) {
		if (i % 5 == 0 && i % 7 == 0) {
			ASSERT_EQUALS(true, str_set_intersection.remove(string(i)));
		} else {
			ASSERT_EQUALS(false, str_set_intersection.remove(string(i)));
		}
	}
	ASSERT_EQUALS(0, str_set_intersection.size());

	return true;
}

bool testRelativeComplement(){
	SortedSet<int> set_1, set_2;
	for(int i=-100; i<=100; i++){
		ASSERT_EQUALS(true, set_1.insert(i));
	}
	for(int i=-99; i<=100; i+=2){
		ASSERT_EQUALS(true, set_2.insert(i));
	}
	// { -100 <= x <= 100 | x is integer }\{ -100 <= x <= 100 | x=2n+1 } =
	// = { -100 <= x <= 100 | x=2n }
	SortedSet<int> result = set_1 - set_2;
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
	SortedSet<std::string, strCompare> str_result = str_set_1 - str_set_2;
	for (int i = 1000; i <= 5000; i++) {
		if (i % 5 == 0 && i % 7 != 0) {
			ASSERT_EQUALS(true, str_result.remove(string(i)));
		} else {
			ASSERT_EQUALS(false, str_result.remove(string(i)));
		}
	}
	ASSERT_EQUALS(0, str_result.size());

	return true;
}

bool testSymmetricDifference(){
	SortedSet<int> set_1, set_2;
	for(int i=-100; i<=50; i++){
		ASSERT_EQUALS(true, set_1.insert(i));
	}
	for(int i=-50; i<=100; i++){
		ASSERT_EQUALS(true, set_2.insert(i));
	}
	SortedSet<int> result = set_1 ^ set_2;
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
	SortedSet<std::string, strCompare> str_result = str_set_1 ^ str_set_2;
	for (int i = 1000; i <= 5000; i++) {
		if ((i % 5 == 0 || i % 7 == 0) && i % 35 != 0) {
			ASSERT_EQUALS(true, str_result.remove(string(i)));
		} else {
			ASSERT_EQUALS(false, str_result.remove(string(i)));
		}
	}
	ASSERT_EQUALS(0, str_result.size());

	return true;
}

bool testComboTest(){

	return true;
}

int main() {
//	RUN_TEST(testConstructor);
//	RUN_TEST(testCopyCtor);
//	RUN_TEST(testAssignOperator);
	RUN_TEST(testSize);
	RUN_TEST(testInsert);
	RUN_TEST(testRemove);
	RUN_TEST(testFind);
	RUN_TEST(testUnion);
	RUN_TEST(testIntersection);
	RUN_TEST(testRelativeComplement);
	RUN_TEST(testSymmetricDifference);
	RUN_TEST(testComboTest);
	return 0;
}
