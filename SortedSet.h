#ifndef MTM4_SORTEDSET_H
#define MTM4_SORTEDSET_H
#include <assert.h>
#include <cstdlib>
#include <functional>

// ****************************************************************************
// ***************************** node class ***********************************
// ****************************************************************************

template <class T>
class Node {
private:
	T* data;
	Node *next;
	friend class SortedSet<T>;
	//constructor
	Node(const T &element) : data(new T(element)), next(NULL) {}
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
	//copy constructor
	Node(const Node& node) : data(new T(node.data)), next(node.next) {}
};

// ****************************************************************************
// ***************************** SortedSet class ******************************
// ****************************************************************************
template <class T, class Compare = std::less<T> >
class SortedSet {
public:
    class iterator {
    public:
    	/* Iterator copy constructor:
    	 * @param iterator: a const reference for an iterator to copy.
    	 * return:
    	 * a new iterator object.
    	 *
    	 */
    	iterator(const iterator& iterator) : node(iterator.node) {}

    	/* Iterator assignment operator (=):
         * Get const reference of a iterator object, and copy it to this.
    	 * @param iterator: a const reference for an iterator to be assigned.
	     * return:
	     * reference to this.
    	 */
    	iterator& operator=(const iterator& iterator) {
    		node = iterator.node;
    		return *this;
    	}

    	/* Iterator's destructor:
    	 * The function deletes the iterator.
    	 */
    	~iterator() {
    		node=NULL;
    	}

       /**************Operators of iterator******************************

    	/* Iterator promoting
    	 * There are two versions:
    	 * 1. pre version (++iterator)
    	 * 2. post version (iterator++)
    	 *
    	 * Both versions will not receive parameters.
    	 * return:
    	 * udpating the iterator which the function was called on, to the next
    	 * iterator inside set.
    	 * the function assumes the set iterator is not NULL.
    	 */

  /* TODO check if is possible-> if the iterator was pointing to the last element (or set was empty) than
   *  the operator return same element. check if null ,
   *  Add appropriate code TODO -END
   */
    	iterator& operator++(){
    		node = node->next;
    		return *this;
    	}
    	iterator operator++(int){
    		iterator temp= *this;
    		++*this;
    		return temp;
    	}

    	/* Iterator's dereferencing:
    	 * return:
    	 * T element which was pointed by the iterator.
    	 * the function assumes the set iterator is not NULL.
    	 * // what return if null TODO
    	 */
    	T operator* (){
    	    if (node == NULL) {
    		    // what return TODO
    	    }
    	    return *(node->data);
    	}

    	/* Iterator comparison operator (==):
    	 * @param iterator: a const reference iterator to compare to.
    	 * return: boolean value indicates whether the iterator were equal or not.
    	 */
		bool operator==(const iterator& iterator){
			return iterator.node==node;
		}

		/* Iterator non equal operator (!=):
		 * @param iterator: a const reference iterator to compare to.
		 * return: boolean value indicates whether the iterator were not equal.
		 */
		bool operator!=(const iterator& it){
			return !(*this==iterator);
		}

    private:
    	Node<T>* node;
    	/* Iterator's constructor:
      	 * The function creates the iterator.
    	 * @pram node: a node pointer which will be the first element.
    	 * if the node pointer is not provided than the set will be empty. //TODO check if is possible
    	 * return:
    	 * a new iterator object.
    	 */
    	iterator(Node<T>* node = NULL) : node(node) {}
    };

};


#endif //MTM4_SORTEDSET_H
