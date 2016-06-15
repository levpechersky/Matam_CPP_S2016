#ifndef MTM4_SORTEDSET_H
#define MTM4_SORTEDSET_H
#include <assert.h>
#include <functional>

template<class T, class Compare = std::less<T> >
class SortedSet;

// ****************************************************************************
// ***************************** node class ***********************************
// ****************************************************************************

template<class T, class Compare = std::less<T> >
class Node {
public:
	T* data;
	Node* next;

	friend class SortedSet<T, Compare> ;

	//Constructors:
	Node(const T &element) : data(new T(element)), next(nullptr) {}
	Node() : data(nullptr), next(nullptr) {}

	//Copy constructor:
	Node(const Node& node) : data(new T(node.data)), next(nullptr) {}

	//Destructor:
	~Node() { delete data; }

	//Assignment operator (=):
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

template<class T, class Compare>
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
    	Iterator(const Iterator& iterator) : node(iterator.node) {}

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
		~Iterator() {}

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
		Iterator& operator++() {
			node = node->next;
			return *this;
		}
		Iterator operator++(int) {
			Iterator temp = *this;
			++*this;
			return temp;
		}

    	/* Iterator's dereferencing:
    	 * return:
    	 * T element which was pointed by the iterator.
    	 * IMPORTANT: the function assumes the set iterator is not NULL.
    	 * 		hence, iterator must be checked before dereferencing.
    	 */
		const T operator*() const {
			return *(node->data);
		}

    	/* Iterator comparison operator (==):
    	 * @param iterator: a const reference iterator to compare to.
    	 * return: boolean value indicates whether the iterator were equal or not.
    	 */
		bool operator==(const Iterator& iterator) const {
			return iterator.node == node;
		}

		/* Iterator non equal operator (!=):
		 * @param iterator: a const reference iterator to compare to.
		 * return: boolean value indicates whether the iterator were not equal.
		 */
		bool operator!=(const Iterator& iterator) const {
			return !(*this == iterator);
		}

    private:
		/* Iterator constructor:
		 * Since user knows nothing about Node class, user isn't allowed
		 * to use this constructor. Instead of it, begin() and end() methods
		 * of SortedSet are provided.
		 * @param node: a pointer to node, new iterator will point to.
		 * 		if <node> is null, new iterator is considered pointing to end.
		 * return: new Iterator.
		 */
		Iterator(Node<T>* node = nullptr) :	node(node) {}

		friend class SortedSet<T, Compare> ;
		Node<T>* node;

	};//********* End of Iterator class ****************************************
	
	/* Sets Iterator to the first element
	 * return:
	 *  Iterator pointing to the first element, or if set is empty -
	 *  	to the end of set
	 */
	Iterator begin() const {
		return Iterator(first);
	}
	
	/* Sets Iterator to the end of set.
	 * As a result, iterator doesn't point to valid element,
	 * e.g. you can't dereference iterator after end().
	 * return:
	 *  Iterator pointing to the end of set.
	 */
	Iterator end() const {
		return Iterator();
	}
	
	/* Searches the set for an item, that equals <element>.
	 * If found - iterator will point to found item.
	 * Otherwise, iterator will point to end().
	 * return:
	 *  Iterator pointing to the <element>, if <element> found
	 *  Iterator pointing to the end of set if <element> not found
	 */
	Iterator find(const T& element) const {
		Iterator this_end = end(), current=begin();
		for(; current != this_end && Compare()(*current, element); ++current);
		if (current == this_end || Compare()(element, *current)) {
			return this_end;
		}
		return current;
	}
	
	/* Adds an element to set, if it wasn't contained in the set before.
	 * Items are added in a way, that set stays ordered (as defined by
	 * Compare template parameter)
	 *
	 * return:
	 * true - if set did not contain <element> before (and it was added)
	 * false - if set did contain <element> before. Set stays unchanged
	 * 	in that case.
	 */
	bool insert(const T& element) {
		if (!first) { //Set empty - insert anyway
			first = new Node<T>(element);
			return true;
		}
		if (Compare()(element, *(first->data))) { //All items in set are greater than <element> - insert first
			Node<T>* tmp = first;
			first = new Node<T>(element);
			first->next = tmp;
			return true;
		}
		if (!Compare()(*(first->data), element)) {
			return false;
		}
		Iterator this_end = end(), previous = begin(), iterator = begin();
		++iterator;
		while (iterator != this_end && Compare()(*iterator, element)) {
			++previous;
			++iterator;
		}
		if ((iterator == this_end || Compare()(element, *iterator))) {
			Node<T>* tmp = new Node<T>(element);
			tmp->next = previous.node->next;
			previous.node->next = tmp;
			return true;
		}
		return false;
	}

	/* Removes an element from the set.
	 *
	 * return:
	 * true - if <element> found and has been removed
	 * false - if <element> has not been found
	 */
	bool remove(const T& element) {
		Iterator this_end = end(), previous = begin(), iterator = begin();
		if (previous == this_end) {
			return false;
		}
		++iterator;
		if (!Compare()(*previous, element) && !Compare()(element, *previous)) {
			first = iterator.node;
			delete previous.node;
			return true;
		}
		while (iterator != this_end && Compare()(*iterator, element)) {
			++previous;
			++iterator;
		}
		if (iterator != this_end && !Compare()(element, *iterator)) {
			previous.node->next = iterator.node->next;
			delete iterator.node;
			return true;
		}
		return false;
	}

	/*
	 * return:
	 * number of elements in set
	 */
	int size() const {
		int count = 0;
		for (Iterator this_end = end(), current = begin(); current != this_end;
				++current) {
			count++;
		}
		return count;
	}

	/* SortedSet constructor.
	 *
	 * return:
	 * new empty SortedSet
	 */
	SortedSet() : first(nullptr){}

	/* SortedSet destructor.
	 */
	~SortedSet() { removeList(first); }

	/* SortedSet copy constructor.
	 *
	 * return:
	 * new SortedSet, containing all members of <set>
	 */
	SortedSet(const SortedSet& set) : first(copyList(set.first)){}

	/* SortedSet assignment operator ( = ).
	 */
	SortedSet& operator=(const SortedSet& set) {
		Node<T>* helper = copyList(set.first);
		removeList(first);
		first = helper;
		return *this;
	}


private:
	Node<T>* first;
	/* Destroys Linked list */
	static void removeList(Node<T>* first) {
		Node<T>* helper = first;
		while (helper) {
			Node<T>* next = helper->next;
			delete helper;
			helper = next;
		}
		first = nullptr;
	}

	/* Copies Linked List */
	static Node<T>* copyList(Node<T>* original) {
		if(!original){
			return nullptr;
		}
		Node<T>* copy = new Node<T>(*(original->data));
		Node<T>* helper_2 = copy;
		Node<T>* helper_1 = original->next;
		while (helper_1) {
			helper_2->next = new Node<T>(*(helper_1->data));
			helper_2 = helper_2->next;
			helper_1 = helper_1->next;
		}
		return copy;
	}

};//****************** End of SortedSet class **********************************

/*
 * Union of sets A and B is defined as a set of objects that belong to A or B
 *
 * return:
 * new SortedSet, containing union of two sets.
 */
template<class T, class Compare>
SortedSet<T, Compare> operator|(const SortedSet<T, Compare>& set_1,
		const SortedSet<T, Compare>& set_2) {
	SortedSet<T, Compare> result(set_1);
	auto this_end = set_2.end(), iterator = set_2.begin();
	for (; iterator != this_end; iterator++) {
		result.insert(*iterator);
	}
	return result;
}
/* Same as described above, with assignment to the left operand
 * Returns reference to the left operand                                      */
template<class T, class Compare>
SortedSet<T, Compare>& operator|=(SortedSet<T, Compare>& set_1,
		const SortedSet<T, Compare>& set_2) {
	return set_1 = set_1 | set_2;
}

/*
 * Intersection of sets A and B is defined as a set of objects that belong
 * to set A and set B
 *
 * return:
 * new SortedSet, containing an intersection of two sets.
 */
template<class T, class Compare>
SortedSet<T, Compare> operator&(const SortedSet<T, Compare>& set_1,
		const SortedSet<T, Compare>& set_2) {
	SortedSet<T, Compare> copy(set_1), result;
	auto this_end = set_2.end(), iterator = set_2.begin();
	for (; iterator != this_end; iterator++) {
		if (!copy.insert(*iterator)) {
			result.insert(*iterator);
		}
	}
	return result;
}
/* Same as described above, with assignment to the left operand
 * Returns reference to the left operand                                      */
template<class T, class Compare>
SortedSet<T, Compare>& operator&=(SortedSet<T, Compare>& set_1,
		const SortedSet<T, Compare>& set_2) {
	return set_1 = set_1 & set_2;
}

/* Creates new set, containing an elements, which are contained in first
 * set (left operand) but aren't contained in the second one (right operand)
 * e.g. A-B returns (in terms of math) A\B
 *
 * return:
 * new SortedSet, as described above
 */
template<class T, class Compare>
SortedSet<T, Compare> operator-(const SortedSet<T, Compare>& set_1,
		const SortedSet<T, Compare>& set_2) {
	SortedSet<T, Compare> copy(set_2), result;
	auto this_end = set_1.end(), iterator = set_1.begin();
	for (; iterator != this_end; iterator++) {
		if (copy.insert(*iterator)) {
			result.insert(*iterator);
		}
	}
	return result;
}
/* Same as described above, with assignment to the left operand
 * Returns reference to the left operand                                      */
template<class T, class Compare>
SortedSet<T, Compare>& operator-=(SortedSet<T, Compare>& set_1,
		const SortedSet<T, Compare>& set_2) {
	return set_1 = set_1 - set_2;
}

/* Creates new set, containing an elements, which are contained in one of
 * sets only.
 * e.g A^B returns (in terms of math) (A U B)\(A n B), where 'n' stands
 *  for intersection of A and B
 *
 * return:
 * new SortedSet, as described above
 */
template<class T, class Compare>
SortedSet<T, Compare> operator^(const SortedSet<T, Compare>& set_1,
		const SortedSet<T, Compare>& set_2) {
	return (set_1 - set_2) | (set_2 - set_1);
}
/* Same as described above, with assignment to the left operand
 * Returns reference to the left operand                                      */
template<class T, class Compare>
SortedSet<T, Compare>& operator^=(SortedSet<T, Compare>& set_1,
		const SortedSet<T, Compare>& set_2) {
	return set_1 = set_1 ^ set_2;
}

/* Two sets are equal if and only if they have the same elements.
 *
 * return:
 * true - if sets are equal
 * false - otherwise
 */
template<class T, class Compare>
bool operator==(const SortedSet<T, Compare>& set_1,
		const SortedSet<T, Compare>& set_2) {
	auto iterator_1 = set_1.begin(), iterator_2 = set_2.begin(),
			end = set_1.end();
	while (iterator_1 != end && iterator_2 != end) {
		if (Compare()(*iterator_1, *iterator_2) ||
				Compare()(*iterator_2++, *iterator_1++)) {
			return false;
		}
	}
	if (iterator_1 != end || iterator_2 != end) {
		return false;
	}
	return true;
}

#endif //MTM4_SORTEDSET_H
