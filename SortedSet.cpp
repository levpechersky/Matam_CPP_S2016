#include "SortedSet.h"

template<class T, class Compare>
const typename SortedSet<T, Compare>::Iterator SortedSet<T, Compare>::begin() const {
	return Iterator();//TEMP
}

template<class T, class Compare>
const typename SortedSet<T, Compare>::Iterator SortedSet<T, Compare>::end() const {
	return Iterator();//TEMP
}

template<class T, class Compare>
const typename SortedSet<T, Compare>::Iterator SortedSet<T, Compare>::find(
		const T& element) const {
	return Iterator();//TEMP
}

template<class T, class Compare>
bool SortedSet<T, Compare>::insert(const T& element) {
	return true; //TEMP
}

template<class T, class Compare>
bool SortedSet<T, Compare>::remove(const T& element) {
	return true; //TEMP
}

template<class T, class Compare>
int SortedSet<T, Compare>::size() const {
	return 0; //TEMP
}

template<class T, class Compare>
SortedSet<T, Compare> SortedSet<T, Compare>::operator&(const SortedSet&) const {
	return SortedSet();//TEMP
}

template<class T, class Compare>
SortedSet<T, Compare> SortedSet<T, Compare>::operator|(const SortedSet&) const {
	return SortedSet();//TEMP
}

template<class T, class Compare>
SortedSet<T, Compare> SortedSet<T, Compare>::operator-(const SortedSet&) const {
	return SortedSet();//TEMP
}

template<class T, class Compare>
SortedSet<T, Compare> SortedSet<T, Compare>::operator^(const SortedSet&) const {
	return SortedSet();//TEMP
} //TODO probably should be implemented as (A|B)-(A&B), maybe as non-member
