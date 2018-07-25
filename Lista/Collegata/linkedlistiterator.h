//
//  linkedlistposition.h
//  LinkedList
//
//  Created by Ruggiero Altini on 11/01/17.
//  Copyright © 2016 Ruggiero Altini. All rights reserved.
//
//  C++11 compliant

#ifndef linkedlistiterator_h
#define linkedlistiterator_h

//#include "listnode.h"

template<class T> class ListNode;

template <class T>class LinkedList; // Forward Declaration

template <class T>
class LinkedListIterator;

template <class T>
class LinkedListPosition;

template<class T>
LinkedListIterator<T> operator+ (const LinkedListIterator<T>& left, int v);

template<class T>
LinkedListIterator<T> operator+(int v, const LinkedListIterator<T>& right);

template<class T>
LinkedListIterator<T> operator-(const LinkedListIterator<T>& left, int v);

template<class T>
LinkedListIterator<T> operator-(int v, const LinkedListIterator<T>& right);


template <class T>
class LinkedListIterator : public ListIterator<LinkedListIterator<T>, LinkedList<T> > {
	friend class LinkedList<T>;
	friend class LinkedListPosition<T>;

public:
	typedef LinkedList<T> list;
	typedef LinkedListPosition<T> position;

	inline LinkedListIterator(ListNode<T> *node) :node(node) { /*this->node = node;*/ }
	inline LinkedListIterator() : node(nullptr) {}

	// prefix
	LinkedListIterator& operator++()
	{
        if (node != nullptr) {
            node = node->next;
        }
		return *this;
	}

	// postfix
	LinkedListIterator operator++(int)
	{
		LinkedListIterator tmp = *this;
		operator++(); // prefix-increment this instance
		return tmp;   // return value before increment
	}


	// prefix
	LinkedListIterator& operator--()
	{
		// implement increment logic on this instance, return reference to it.
		node = node->prev;
		return *this;
	}


	// postfix
	LinkedListIterator operator--(int)
	{
		LinkedListIterator tmp = *this;
		operator--();
		return tmp;
	}

	T& operator*() {
		if (node == nullptr) {
			throw "Empty position";
		}
		return node->value;
	};

	T *operator->() {
		if (node == nullptr) {
			throw "Empty position";
		}
		return &(node->value);
	}

	bool operator==(const LinkedListIterator& other) const;
	bool operator!=(const LinkedListIterator& other) const;


	inline LinkedListIterator<T>& operator+=(int v);

	friend LinkedListIterator<T> operator+<>(const LinkedListIterator<T>& left, int v);
	friend LinkedListIterator<T> operator+<>(int v, const LinkedListIterator<T>& right);
	friend LinkedListIterator<T> operator-<>(const LinkedListIterator<T>& left, int v);
	friend LinkedListIterator<T> operator-<>(int v, const LinkedListIterator<T>& right);

	/*~LinkedListIterator() {

	}*/
private:
	ListNode<T> *node;

};

template <class T>
inline bool LinkedListIterator<T>::operator==(const LinkedListIterator& other) const {
	return node == other.node;
}

template <class T>
inline bool LinkedListIterator<T>::operator!=(const LinkedListIterator& other) const {
	return node != other.node;
}

template<class T>
inline LinkedListIterator<T>& LinkedListIterator<T>::operator+=(int v) {
	//this->intValue += v;
	for (int i = 0; i < v; ++i) {
		if (node == nullptr) {
			throw "Out of bounds";
		}
		node = node->next;
	}
	return *this;
}

template< class T>
LinkedListIterator<T> operator+(const LinkedListIterator<T>& left, int v) {
	LinkedListIterator<T> newPos = LinkedListIterator<T>(left);

	for (int i = 0; i < v; ++i) {
		if (newPos.node == nullptr) {
			throw "Out of bounds";
		}
		newPos.node = newPos.node->next;
	}
	return newPos;
}

template< class T>
LinkedListIterator<T> operator+(int v, const LinkedListIterator<T>& right) {
	LinkedListIterator<T> newPos = LinkedListIterator<T>(right);

	for (int i = 0; i < v; ++i) {
		if (newPos.node == nullptr) {
			throw "Out of bounds";
		}
		newPos.node = newPos.node->next;
	}
	return newPos;
}

template< class T>
LinkedListIterator<T> operator-(const LinkedListIterator<T>& left, int v) {
	LinkedListIterator<T> newPos = LinkedListIterator<T>(left);

	for (int i = 0; i < v; ++i) {
		if (newPos.node == nullptr) {
			throw "Out of bounds";
		}
		newPos.node = newPos.node->prev;
	}
	return newPos;
}

template< class T>
LinkedListIterator<T> operator-(int v, const LinkedListIterator<T>& right) {
	LinkedListIterator<T> newPos = LinkedListIterator<T>(right);

	for (int i = 0; i < v; ++i) {
		if (newPos.node == nullptr) {
			throw "Out of bounds";
		}
		newPos.node = newPos.node->prev;
	}
	return newPos;
}

#endif
