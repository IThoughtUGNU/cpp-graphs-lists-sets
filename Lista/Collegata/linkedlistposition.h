//
//  linkedlistposition.h
//  LinkedList
//
//  Created by Ruggiero Altini on 11/01/17.
//  Copyright © 2016 Ruggiero Altini. All rights reserved.
//
//  C++11 compliant

#include "linkedlistiterator.h"

template<class T>
class LinkedList;

template <class T>
class LinkedListIterator;

template<class T>
LinkedListPosition<T> operator+ (const LinkedListPosition<T>& left, int v);

template<class T>
LinkedListPosition<T> operator+(int v, const LinkedListPosition<T>& right);

template<class T>
LinkedListPosition<T> operator-(const LinkedListPosition<T>& left, int v);

template<class T>
LinkedListPosition<T> operator-(int v, const LinkedListPosition<T>& right);


template <class T>
class LinkedListPosition : public ListPosition<LinkedListPosition<T>, LinkedList<T> > {
    friend class LinkedList<T>;
    friend class LinkedListIterator<T>;
public:
    typedef LinkedList<T> list;

    inline LinkedListPosition(ListNode<T> *node) :node(node) { /*this->node = node;*/ }
    inline LinkedListPosition() : node(nullptr) {}

    inline LinkedListPosition(const LinkedListIterator<T>& it) {
        this->node = it.node;
    }

    // prefix
    LinkedListPosition& operator++()
    {
        node = node->next;
        return *this;
    }

    // postfix
    LinkedListPosition operator++(int)
    {
        LinkedListPosition tmp = *this;
        operator++(); // prefix-increment this instance
        return tmp;   // return value before increment
    }


    // prefix
    LinkedListPosition& operator--()
    {
        // implement increment logic on this instance, return reference to it.
        node = node->prev;
        return *this;
    }


    // postfix
    LinkedListPosition operator--(int)
    {
        LinkedListPosition tmp = *this;
        operator--();
        return tmp;
    }

    /*T& operator*() {
    if (node == nullptr) {
    throw "Empty position";
    }
    return node->value;
    };*/

    const T& operator*() const {
        if (node == nullptr) {
            throw "Empty position";
        }
        return node->value;
    };

    /*T *operator->() {
    if (node == nullptr) {
    throw "Empty position";
    }
    return &(node->value);
    }*/

    T *operator->() const {
        if (node == nullptr) {
            throw "Empty position";
        }
        return &(node->value);
    }

    bool operator==(const LinkedListPosition& other) const;
    bool operator!=(const LinkedListPosition& other) const;


    inline LinkedListPosition<T>& operator+=(int v);

    friend LinkedListPosition<T> operator+<>(const LinkedListPosition<T>& left, int v);
    friend LinkedListPosition<T> operator+<>(int v, const LinkedListPosition<T>& right);
    friend LinkedListPosition<T> operator-<>(const LinkedListPosition<T>& left, int v);
    friend LinkedListPosition<T> operator-<>(int v, const LinkedListPosition<T>& right);

    /*~LinkedListPosition() {

    }*/
private:
    ListNode<T> *node;

};

template <class T>
inline bool LinkedListPosition<T>::operator==(const LinkedListPosition& other) const {
    return node == other.node;
}

template <class T>
inline bool LinkedListPosition<T>::operator!=(const LinkedListPosition& other) const {
    return node != other.node;
}

template<class T>
inline LinkedListPosition<T>& LinkedListPosition<T>::operator+=(int v) {
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
LinkedListPosition<T> operator+(const LinkedListPosition<T>& left, int v) {
    LinkedListPosition<T> newPos = LinkedListPosition<T>(left);

    for (int i = 0; i < v; ++i) {
        if (newPos.node == nullptr) {
            throw "Out of bounds";
        }
        newPos.node = newPos.node->next;
    }
    return newPos;
}

template< class T>
LinkedListPosition<T> operator+(int v, const LinkedListPosition<T>& right) {
    LinkedListPosition<T> newPos = LinkedListPosition<T>(right);

    for (int i = 0; i < v; ++i) {
        if (newPos.node == nullptr) {
            throw "Out of bounds";
        }
        newPos.node = newPos.node->next;
    }
    return newPos;
}

template< class T>
LinkedListPosition<T> operator-(const LinkedListPosition<T>& left, int v) {
    LinkedListPosition<T> newPos = LinkedListPosition<T>(left);

    for (int i = 0; i < v; ++i) {
        if (newPos.node == nullptr) {
            throw "Out of bounds";
        }
        newPos.node = newPos.node->prev;
    }
    return newPos;
}

template< class T>
LinkedListPosition<T> operator-(int v, const LinkedListPosition<T>& right) {
    LinkedListPosition<T> newPos = LinkedListPosition<T>(right);

    for (int i = 0; i < v; ++i) {
        if (newPos.node == nullptr) {
            throw "Out of bounds";
        }
        newPos.node = newPos.node->prev;
    }
    return newPos;
}