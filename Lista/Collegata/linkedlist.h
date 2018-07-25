//
//  linkedlist.h
//  LinkedList
//
//  Created by Ruggiero Altini on 01/12/16.
//  Copyright © 2016 Ruggiero Altini. All rights reserved.
//
//  C++11 compliant

#ifndef linkedlist_h
#define linkedlist_h

#include "../linearlist.h"
#include <iostream>
#include "listnode.h"
#include <initializer_list>
#include "linkedlistposition.h"
#include "linkedlistiterator.h"

//using namespace std;
using std::cout;
using std::ostream;
using std::initializer_list;

//template <class T>class LinkedList; // Forward Declaration

//template <class T>
//class LinkedListPosition;

//template <class T>
//class LinkedListIterator;

template <class T>
class LinkedList : public LinearList<T, LinkedListIterator<T>, LinkedListPosition<T> > {
    
    
public:
	typedef typename LinearList<T, LinkedListIterator<T>, LinkedListPosition<T> >::iterator iterator;
    typedef typename LinearList<T, LinkedListIterator<T>, LinkedListPosition<T> >::position position;
	typedef typename LinearList<T, LinkedListIterator<T>, LinkedListPosition<T> >::value_type value_type;

    // Costruttori
    LinkedList();
    // Costruttore di copia
    LinkedList(const LinkedList<T>& );

    template <class other_iterator, class other_position>
    LinkedList(const LinearList<value_type, other_iterator, other_position>& list);

    // Costruttore aggregato
    LinkedList(initializer_list<T> initializerList);
    
    // distruttore
    ~LinkedList();
    
    // Operatori
    void init(); // Crea Lista
    bool isEmpty() const ;
    value_type read(const position&) const;
    void write(const value_type&, const position&);
    position begin() const;
    position last() const;
    bool end(const position&) const;
    position next(const position&) const;
    position previous(const position&) const ;
    void insert(const value_type&, const position&);
    position erase(const position&);

	// OVERLOAD ITERATORS
    bool end(const iterator&) const;
    iterator erase(iterator& p);
	iterator begin();
	iterator last();
	iterator next(const iterator&);
	iterator previous(const iterator&);
    
    // Convenience methods - FUNZIONI IMPLEMENTABILI
    int size() const;
    void push_back(const value_type&);
    void push_front(const value_type&);
    value_type pop_back();
    value_type pop_front();
    void clear();
    
    // Overload operatori
    LinkedList<T>& operator=(const LinkedList<T> &L) ;
    bool operator==(const LinearList<value_type, iterator, position> &l) const;
    bool operator!=(const LinearList<value_type, iterator, position> &l) const;
    LinkedList<T>& operator+=(const LinkedList<T> &right);

private:
    int length;
    ListNode<T> *head;
    bool rawHead;
};

template<class T>
LinkedList<T>::LinkedList(initializer_list<T> initializerList): length(0), head(nullptr) {
    init();
    for(T elem : initializerList )
    {
        this->push_back(elem);
    }
}

template <class T>
void LinkedList<T>::init() {
    if (head != nullptr) {
        delete head;
    }
    head = ListNode<T>::init();
}

template <class T>
LinkedList<T>::LinkedList():length(0), head(nullptr) {
    init();
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T>& other) : length(0), head(nullptr) {
    init();
    if(!other.isEmpty()) {
        for(auto i = other.begin(); !other.end(i); i++) {
            this->push_back(read(i));
        }
    }
}

template<class T>
template <class other_iterator, class other_position>
LinkedList<T>::LinkedList(const LinearList<value_type, other_iterator, other_position>& list): length(0), head(nullptr) {
    init();
    for (auto it = list.begin(); !list.end(it); ++it) {
        push_back(*it);
    }
}

template<class T>
LinkedList<T>::~LinkedList() {
    this->clear();
}

template<class T>
inline bool LinkedList<T>::end(const position& p) const {
    return p.node == head;
}

template<class T>
inline bool LinkedList<T>::end(const iterator& p) const {
	return p.node == head;
}

template<class T>
inline bool LinkedList<T>::isEmpty() const {
    return (head == head->next);
}

template<class T>
inline auto LinkedList<T>::next(const position& p) const -> position {
    return position(p.node->next);
}

template<class T>
inline auto LinkedList<T>::previous(const position& p) const -> position {
    return p.node->prev;
}

template<class T>
inline auto LinkedList<T>::read(const position& p) const -> value_type {
    if(!end(p)) {
        return p.node->value;
    } else {
        throw ListOutOfBoundsException();
    }
}

template<class T>
inline void LinkedList<T>::write(const value_type& el, const position& p) {
    if(!end(p)) {
        p.node->value = el;
    } else {
        throw ListOutOfBoundsException();
    }
}

template<class T>
void LinkedList<T>::insert(const value_type& el, const position& p) {
    position newPos;
    newPos.node = ListNode<T>::init();
    newPos.node->prev = p.node->prev;
    newPos.node->next = p.node;
    p.node->prev = newPos.node;

    newPos.node->prev->next = newPos.node;
    newPos.node->value = el;
    /*
    newPos.node->prev = p.node;
    newPos.node->next = p.node->next;
    newPos.node->prev->next = newPos.node;
    newPos.node->next->prev = newPos.node;*/
    /*
    position newPos;
    newPos.node = ListNode<T>::init(p.node, p.node->prev);
    newPos.node->value = el;

    position p2 = p;

    p2.node->prev->next = newPos.node;
    p2.node->prev = newPos.node;
    */

    length++;
}

template<class T>
typename LinkedList<T>::position LinkedList<T>::erase(const position& p) {
    position toReturn(p.node->next);
    if(!isEmpty() && !end(p)) {
        p.node->prev->next = p.node->next;
        p.node->next->prev = p.node->prev;
        delete p.node;
        length--;

        return toReturn;
    } else {
        throw ListException("Error: Invalid position");
    }
}
template<class T>
inline auto LinkedList<T>::erase(iterator& p) -> iterator {
	iterator toReturn(p.node->next);
	if (!isEmpty() && !end(p)) {
		p.node->prev->next = p.node->next;
		p.node->next->prev = p.node->prev;
		delete p.node;
		length--;

		return toReturn;
	} else {
		throw ListException("Error: Invalid position");
	}
}

template<class T>
inline auto LinkedList<T>::begin() const -> position {
    /*if (length == 0) {
        iterator _head;
        _head.node->next = head->next;
        _head.node->prev = nullptr;
        return _head;
    }*/
    return LinkedListPosition<T>(head->next);
}

template<class T>
inline auto LinkedList<T>::last() const -> position {
    if (isEmpty()) {
        throw ListException("Error: List is empty. There is no last.");
    }
    return LinkedListPosition<T>(head->prev);
}

// OVERLOAD
template<class T>
inline auto LinkedList<T>::begin() -> iterator {
    /*if (length == 0) {
        iterator _head;
        _head.node = ListNode<T>::init();
        _head.node->next = head->next;
        _head.node->prev = nullptr;
        return _head;
    }*/
	return LinkedListIterator<T>(head->next);
}
template<class T>
inline auto LinkedList<T>::last() -> iterator {
	return LinkedListIterator<T>(head->prev);
}

template<class T>
inline auto LinkedList<T>::next(const iterator& it) -> iterator {
	return iterator(it.node->next);
}
template<class T>
inline auto LinkedList<T>::previous(const iterator& it) -> iterator {
	return iterator(it.node->prev);
}

template<class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T> &other) {
    if (this != &other) {
        init();
        
        if(!other.isEmpty()) {
            for(auto i = other.begin(); !other.end(i); i++) {
                this->push_back(read(i));
            }
        }
    }
    return *this;
}

template <class T>
bool LinkedList<T>::operator==(const LinearList<value_type, iterator, position> &right) const {
    if(right.size() != length) {
        return false;
    }
    auto p = begin();
    auto _p = right.begin();
    while(!end(p)) {
        if(read(p++) != right.read(_p++)) {
            return false;
        }
    }
    return true;
}

template <class T>
bool LinkedList<T>::operator!=(const LinearList<value_type, iterator, position> &right) const {
    return !(*this == right);
}

template< class T>
LinkedList<T> operator+(const LinkedList<T>& left, const LinkedList<T>& right) {
    LinkedList<T> newList;
    for(auto p = left.begin(); !left.end(p); ++p) {
        newList.push_back(left.read(p));
    }
    for(auto p = right.begin(); !right.end(p); ++p) {
        newList.push_back(right.read(p));
    }
    return newList;
}

template<class T>
LinkedList<T>& LinkedList<T>::operator+=(const LinkedList<T> &right)  {
    for(auto p = right.begin(); !right.end(p); p++) {
        this->push_back(right.read(p));
    }
    
    return *this;
}

// MARK: - Convenience methods
template <class T>
void LinkedList<T>::push_back(const value_type &el) {
    //insert(el, head);
    position newPos;
    newPos.node = ListNode<T>::init();
    newPos.node->next = head;
    newPos.node->prev = head->prev;
    head->prev = newPos.node;
    newPos.node->prev->next = newPos.node;
    newPos.node->value = el;

    ++length;
}

template <class T>
void LinkedList<T>::push_front(const value_type &el) {
    //insert(el, head->next);
    insert(el, head->next);
}

template <class T>
typename LinkedList<T>::value_type LinkedList<T>::pop_front() {
    value_type val = read(begin());
    if(isEmpty()) {
        throw ListEmptyException();
    }
    erase(begin());
    return val;
}
template <class T>
typename LinkedList<T>::value_type LinkedList<T>::pop_back() {
    value_type val = read(last());
    if(isEmpty()) {
        throw ListEmptyException();
    }
    erase(last());
    return val;
}
template<class T>
int LinkedList<T>::size() const {
    return length;
}


template <class T>
void LinkedList<T>::clear() {
    while(!isEmpty()) {
        this->pop_back();
    }
}


#endif /* linkedlist_h */
