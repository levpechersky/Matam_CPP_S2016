#ifndef MTM4_SORTEDSET_H
#define MTM4_SORTEDSET_H
#include <assert.h>
#include <functional>

// ****************************************************************************
// ***************************** node class ***********************************
// ****************************************************************************

template <class T>
class Node {
private:
	T* data;
	Node* next;

	template <class T, class Compare = std::less<T> >
	friend class SortedSet<T,Compare>;
	//constructor
	Node(const T &element) : data(new T(element)), next(nullptr) {}
	//copy constructor
	Node(const Node& node) : data(new T(node.data)), next(node.next) {}
	//destructor
	~Node() {
		delete data;
	}
	//assignment operator (=):
	Node& operator=(const Node& node) {
		T* temp = new T(node.data);
		delete data;
		data = temp;
		next = node.next;
		return *this;
	}
};

// ****************************************************************************
// ***************************** SortedSet class ******************************
// ****************************************************************************
template <class T, class Compare = std::less<T> >
class SortedSet {
public:
    class Iterator {
    public:
    	/* Iterator copy constructor:
    	 * @param iterator: a const reference for an iterator to copy.
    	 * return:
    	 * a new iterator object.
    	 *
    	 */
    	Iterator(const Iterator& iterator) : node(iterator.node) {}//TODO pointer to the same arg

    	/* Iterator assignment operator (=):
         * Get const reference of a iterator object, and copy it to this.
    	 * @param iterator: a const reference for an iterator to be assigned.
	     * return:
	     * reference to this.
    	 */
    	Iterator& operator=(const Iterator& iterator) {
    		node = iterator.node;
    		return *this;
    	}

    	/* Iterator's destructor:
    	 * The function deletes the iterator.
    	 */
    	~Iterator() {
    		node=nullptr;
    	}

       /**************Operators of iterator******************************/

    	/* Iterator promoting
    	 * There are two versions:
    	 * 1. pre version (++iterator)
    	 * 2. post version (iterator++)
    	 *
    	 * Both versions will not receive parameters.
    	 * return:
    	 * updating the iterator which the function was called on, to the next
    	 * iterator inside set.
    	 * IMPORTANT: the function assumes the set iterator is not NULL.
    	 */
    	Iterator& operator++(){
    		node = node->next;
    		return *this;
    	}
    	Iterator operator++(int){
    		Iterator temp= *this;
    		++*this;
    		return temp;
    	}

    	/* Iterator's dereferencing:
    	 * return:
    	 * T element which was pointed by the iterator.
    	 * IMPORTANT: the function assumes the set iterator is not NULL.
    	 * 		hence, iterator must be checked before dereferencing.
    	 */
    	const T operator* (){
    	    return *(node->data);
    	}

    	/* Iterator comparison operator (==):
    	 * @param iterator: a const reference iterator to compare to.
    	 * return: boolean value indicates whether the iterator were equal or not.
    	 */
		bool operator==(const Iterator& iterator){
			return iterator.node==node;
		}

		/* Iterator non equal operator (!=):
		 * @param iterator: a const reference iterator to compare to.
		 * return: boolean value indicates whether the iterator were not equal.
		 */
		bool operator!=(const Iterator& iterator){
			return !(*this==iterator);
		}
    private:
    	Node<T>* node;
    	friend class SortedSet<T>;

    	/* Iterator's constructor:
      	 * The function creates the iterator.
    	 * @param node: a node pointer which will be the first element.
    	 * if the node pointer is not provided than the set will be empty.
    	 * return:
    	 * a new iterator object.
    	 */
    	Iterator(Node<T>* node = nullptr) : node(node) {}
    };
	/* Sets Iterator to the first element
	 * return:
	 *
	 */
     Iterator begin() const;

	/* Sets Iterator to the end of set.
	 * As a result, iterator doesn't point to valid element,
	 * e.g. you can't dereference iterator after end().
	 * return:
	 *
	 */
    Iterator end() const;

	/* Searches the set for an item, that equals <element>.
	 * If found - iterator will point to found item.
	 * Otherwise, iterator will point to end().
	 * return:
	 *
	 */
    const Iterator find(const T& element) const;

	/* Adds an element to set, if it wasn't contained in the set before.
	 *
	 * return:
	 * true - if set did not contain <element> before (and it was added)
	 * false - if set did contain <element> before. Set stays unchanged
	 * 	in that case.
	 */
    bool insert(const T& element);

	/* Removes an element from the set.
	 *
	 * return:
	 * true - if <element> found and has been removed
	 * false - if <element> has not been found
	 */
    bool remove(const T& element);

	/*
	 * return:
	 * number of elements in set
	 */
    int size() const;

	/*
	 * return:
	 * new SortedSet, containing an intersection of two sets.
	 */
    SortedSet operator&(const SortedSet&) const;


	/* Creates new set, containing an elements, which are contained in first
	 * set (left operand) but aren't contained in the second one (right operand)
	 * e.g. A-B returns (in terms of math) A\B
	 *
	 * return:
	 * new SortedSet, as described above
	 */
    SortedSet operator-(const SortedSet&) const;

	/* Creates new set, containing an elements, which are contained in one of
	 * sets only.
	 * e.g A^B returns (in terms of math) (A U B)\(A n B), where 'n' stands
	 *  for intersection of A and B
	 *
	 * return:
	 * new SortedSet, as described above
	 */
    SortedSet operator^(const SortedSet&) const;//TODO probably should be implemented as (A|B)-(A&B)

    ~SortedSet();
    SortedSet(const SortedSet& set);
    SortedSet& operator=(const SortedSet& set);


private:
    Node<T>* first;
    Iterator iterator;
    SortedSet();
};

template<class T, class Compare>
SortedSet<T, Compare>::Iterator SortedSet<T, Compare>::begin() const {
	return Iterator(first);
}

template<class T, class Compare>
SortedSet<T, Compare>::Iterator SortedSet<T, Compare>::end() const {
	return Iterator();
}

template<class T, class Compare>
const SortedSet<T, Compare>::Iterator SortedSet<T, Compare>::find(
		const T& element) const {
	auto i = begin(), last = end();
	while (i != last && Compare()(*i, element)) {
		++i;
	}
	//now i is null or larger or equal
	if (i == last || Compare()(element, *i)) {//if i is null or larger than <element>
		return last;
	}
	return i;
}

template<class T, class Compare>
bool SortedSet<T, Compare>::insert(const T& element) {
	if (!first) {
		first = new Node<T>(element);
		first->next = nullptr;
		return true;
	}
	auto i = begin(), end = this->end(), next=++i;
	while (next != end && Compare()(*(next), element)) {
		++i;
		++next;
	}
	//i points to last valid item, that is lower or equal to <element>
	if (Compare()(*i, element)) {//if i lower than <element>, insert after i
		Node<T>* tmp = new Node<T>(element);
		tmp->next = i.node->next;
		i.node->next = tmp;
		return true;
	}
	return false;
}

template<class T, class Compare>
bool SortedSet<T, Compare>::remove(const T& element) {
	return true; //TEMP
}

template<class T, class Compare>
int SortedSet<T, Compare>::size() const {
     int count=0;
	 for(begin();iterator.node->next;iterator++){
	 count++;
  }
  return count;
}

template<class T, class Compare>
SortedSet<T, Compare> SortedSet<T, Compare>::operator&(const SortedSet&) const {
	return SortedSet();//TEMP
}

/*
 * return:
 * new SortedSet, containing an union of two sets.
 */
template<class T, class Compare>
SortedSet<T, Compare> operator|(const SortedSet<T, Compare>& set1, const SortedSet<T, Compare>& set2 ){
	int size1=set1.size();
	int size2=set2.size();
	SortedSet<T, Compare>& temp_set;
	//for(int i=0; i<size1 && i<size2; i++)TODO
}

template<class T, class Compare>
SortedSet<T, Compare> SortedSet<T, Compare>::operator-(const SortedSet&) const {
	return SortedSet();//TEMP
}

template<class T, class Compare>
SortedSet<T, Compare> SortedSet<T, Compare>::operator^(const SortedSet&) const {
	return SortedSet();//TEMP
} //TODO probably should be implemented as (A|B)-(A&B), maybe as non-member



template<class T, class Compare>
SortedSet<T, Compare> ::~SortedSet() {
	Node<T>* current = first;
	if (first == NULL) {
		return;
	}
	while (! current->next) {
		Node<T>* next = current->next;
		delete current;
		current = next;
	}
	delete current;
	first=NULL;
	return;
}


template<class T, class Compare>
SortedSet<T, Compare> ::SortedSet():
    first(nullptr), iterator(){
}

template<class T, class Compare>
SortedSet<T, Compare> ::SortedSet(const SortedSet<T, Compare>& set){
	if (set.first == nullptr) {
		first = NULL;
		return;
	}
	first = new Node<T> (*((set.first)->data));
	Iterator<T> set_end = set.end();
	if (iterator == set_end ) {
		return;
	}
	while( iterator != set_end ) {
		iterator++;
		insert(*iterator);
	}
	return;
}
template<class T, class Compare>
SortedSet<T, Compare>& SortedSet<T, Compare> ::operator=(const SortedSet& set){

}

#endif //MTM4_SORTEDSET_H
