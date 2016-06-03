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

	friend class SortedSet<T>;
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
private:
    Node<T>* first;

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
    	 * the function assumes the set iterator is not NULL.
    	 */

  /* TODO check if is possible-> if the iterator was pointing to the last element (or set was empty) than
   *  the operator return same element. check if null ,
   *  Add appropriate code TODO -END
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

    	/* Iterator's constructor:
      	 * The function creates the iterator.
    	 * @param node: a node pointer which will be the first element.
    	 * if the node pointer is not provided than the set will be empty. //TODO check if is possible
    	 * return:
    	 * a new iterator object.
    	 */
    	Iterator(Node<T>* node = nullptr) : node(node) {}
    };

    SortedSet() : first(nullptr) {};

	/* Sets Iterator to the first element
	 * return:
	 *
	 */
    const Iterator begin() const;//TODO not sure about return value type

	/* Sets Iterator to the end of set.
	 * As a result, iterator doesn't point to valid element,
	 * e.g. you can't dereference iterator after end().
	 * return:
	 *
	 */
    const Iterator end() const;

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

	/*
	 * return:
	 * new SortedSet, containing an union of two sets.
	 */
    SortedSet operator|(const SortedSet&) const;

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
};


#endif //MTM4_SORTEDSET_H
