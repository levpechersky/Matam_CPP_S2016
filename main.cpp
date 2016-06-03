#include <iostream>
#include "SortedSet.h"
using namespace std;

int main(){
	cout << "Hello world!" << endl;
	SortedSet<int, std::less<int>> set;
	set.find(5);
	set.insert(5);
	set.insert(3);
	set.insert(8);
	cout << *(set.find(5)) << endl;

	return 0;
}

