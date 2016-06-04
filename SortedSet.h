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
	//constructor
	Node(const T &element) : data(new T(element)), next(nullptr) {}
	//constructor
	Node() : data(NULL), next(NULL) {}
	//copy constructor
	Node(const Node& node) : data(new T(node.data)), next(node.next) {}
	//destructor
	~Node() {
		delete data;
		//delete this;
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

		/* Iterator constructor:
		 * @param node: a pointer to node, new iterator will point to.
		 * 		if <node> is null, new iterator is considered pointing to end.
		 * return: new Iterator.
		 */
		Iterator(Node<T>* node = nullptr) :	node(node) {}

	private:
		friend class SortedSet<T, Compare> ;
		Node<T>* node;
	};
	
	/* Sets Iterator to the first element
	 * return:
	 * 
	 */
	Iterator begin() {
		iterator.node = first; //empty node first...
		return iterator;
	}
	
	/* Sets Iterator to the end of set.
	 * As a result, iterator doesn't point to valid element,
	 * e.g. you can't dereference iterator after end().
	 * return:
	 *
	 */
	Iterator end() {
		for (begin(); iterator.node->data; iterator++);
		return iterator;
	}
	
	/* Searches the set for an item, that equals <element>.
	 * If found - iterator will point to found item.
	 * Otherwise, iterator will point to end().
	 * return:
	 *
	 */
	Iterator find(const T& element) {
		Iterator end = Iterator();
		begin();
		while (iterator != end && Compare()(*iterator, element)) {
			++iterator;
		}
		//now i is null or larger or equal
		if (iterator == end || Compare()(element, *iterator)) { //if i is null or larger than <element>
			return end;
		}
		return iterator;
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
			first->next = nullptr;
			return true;
		}
		if (Compare()(element, *(first->data))) { //All items in set are greater than <element> - insert first
			Node<T>* tmp = new Node<T>(element);
			tmp->next = first;
			first = tmp;
			return true;
		}
		Iterator previous = begin(), end = Iterator();
		iterator++;
		while (iterator != end && Compare()(*iterator, element)) {
			++previous;
			++iterator;
		}
		if (iterator == end || Compare()(element, *iterator)) { //if next is empty or greater than <element> - insert after previous
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
    bool remove(const T& element){
		Iterator previous = begin(), end = Iterator();
		if(previous == end){
			return false;
		}
		iterator++;
		if( !Compare()(*previous, element) && !Compare()(element, *previous)){//if <element> is the first item
			first = iterator.node;
			previous.node->next = nullptr;
			delete previous.node;
			previous.node = nullptr;
			return true;
		}
		while (iterator != end && Compare()(*iterator, element)) {
			++previous;
			++iterator;
		}
		//iterator is NULL or greater or equal
		//i is lower than <element>
		if(iterator != end && !Compare()(element, *iterator)){//if iterator points to valid item, and that item is equal to <element>
			previous.node->next = iterator.node->next;
			iterator.node->next = nullptr;
			delete iterator.node;
			iterator.node = nullptr;
			return true;
		}
    	return false;
    }

	/*
	 * return:
	 * number of elements in set
	 */
    int size() const{
    	return 0;//TEMP
    }

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

	/* SortedSet constructor.
	 *
	 * return:
	 * new empty SortedSet
	 */
	SortedSet() : first(), iterator(first) {}

	/* SortedSet destructor.
	 */
	~SortedSet() { removeList(first); }

	/* SortedSet copy constructor.
	 *
	 * return:
	 * new SortedSet, containing all members of <set>
	 */
	SortedSet(const SortedSet& set) : first(new Node<T>()), iterator() {
		copyList(first, set.first);
		if (set.iterator.node->data) {
			begin();
			return;
		}
		end();
	}

	/* SortedSet assignment operator ( = ).
	 */
	SortedSet& operator=(const SortedSet& set) {
		Node<T>* helper = new Node<T>();
		copyList(helper, set.first);
		removeList(first);
		first = helper;
		return *this;
	}

private:
	Node<T>* first;
	Iterator iterator;

	/* Destroys Linked list */
	static void removeList(Node<T>* first) {
		if (first->next == nullptr) {
			return;
		}
		Node<T>* helper = first->next;
		while (helper) {
			Node<T>* next = helper->next;
			delete helper;
			helper = next;
		}
		delete first;
	}

	/* Copies Linked List */
	static void copyList(Node<T>* to_copy, Node<T>* copy) {
		Node<T>* helper1 = to_copy->next;
		Node<T>* helper2 = copy->next;
		while (helper1) {
			helper2 = new Node<T>(helper1->data);
			helper2 = helper2->next;
			helper1->next;
		}
	}
};

#endif //MTM4_SORTEDSET_H
