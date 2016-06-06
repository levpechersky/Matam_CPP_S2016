#include <iostream>
#include "SortedSet.h"
using namespace std;
/*
int main(){
	SortedSet<int> set;
	if( set.insert(5) ) cout << "Not Existed" << endl;
	if( set.insert(3) ) cout << "Not Existed" << endl;
	if( set.insert(4) ) cout << "Not Existed" << endl;

	if( ! set.insert(5) ) cout << "Existed" << endl;
	if( !set.insert(3) ) cout << "Existed" << endl;
	if( !set.insert(4) ) cout << "Existed" << endl;


	SortedSet<int>::Iterator i, last;
	i = set.find(8);
	last=set.end();
	if(i==last) cout << "Does not exist" << endl;

	i=set.find(4);
	int num=i.operator *();
	if(num==4) cout << "exist" << endl;


	int size=set.size();
	cout << size << endl;
	if(!set.remove(8)) cout << "Does not exist" << endl;
	size=set.size();
	cout << size << endl;

	if(set.remove(3)) cout << "exist" << endl;
	size=set.size();
	cout << size << endl;

	SortedSet<int> set2;
	set2.insert(5);
	set2.insert(200);
	set2.insert(3);
	set2.insert(2);

	SortedSet<int> set3= operator|(set, set2);
	size=set3.size();
	cout << size << endl;

	SortedSet<int> set4= operator&(set, set2);
	size=set4.size();
	cout << size << endl;
	if( ! set4.insert(5) ) cout << "Existed" << endl;

	SortedSet<int> set5= operator-(set2, set);//SET2: 5, 200 , 3 , 2
	                                          //SET:4, 5
	                                          // SET2-SET= { 200,3,4 }
	size=set5.size();
	cout << size << endl;
	if( !set5.insert(3) && !set5.insert(2) && !set5.insert(200) ) {
		cout << "All 3 num Existed" << endl;
	}

	set.insert(300);
	set.insert(3);
	//SET2: 5, 200 , 3 , 2
    //SET:4, 5, 300, 3
    // SET2^SET= { 200,300,4,2 } -> size=4
	SortedSet<int> set6= operator^(set2, set);
	size=set6.size();
	cout << size << endl;
	if( !set6.insert(300) && !set6.insert(2) && !set6.insert(200) && !set6.insert(4) ) {
		cout << "All 4 num Existed" << endl;
	}



	return 0;
}
*/
