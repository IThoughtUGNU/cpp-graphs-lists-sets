//
//  listnode.h
//  LinkedList
//
//  Created by Ruggiero Altini on 01/12/16.
//  Copyright © 2016 Ruggiero Altini. All rights reserved.
//

#ifndef listnode_h
#define listnode_h

//#include "linkedlist.h"

template <class T>
class LinkedList; // Forward Declaration

template<class T>
class LinkedListPosition;

template<class T>
class LinkedListIterator;

template<class T>
LinkedListPosition<T> operator+ (const LinkedListPosition<T>& left, int v);

template<class T>
LinkedListPosition<T> operator+(int v, const LinkedListPosition<T>& right);

template<class T>
LinkedListPosition<T> operator-(const LinkedListPosition<T>& left, int v);

template<class T>
LinkedListPosition<T> operator-(int v, const LinkedListPosition<T>& right);

template<class T>
LinkedListIterator<T> operator+ (const LinkedListIterator<T>& left, int v);

template<class T>
LinkedListIterator<T> operator+(int v, const LinkedListIterator<T>& right);

template<class T>
LinkedListIterator<T> operator-(const LinkedListIterator<T>& left, int v);

template<class T>
LinkedListIterator<T> operator-(int v, const LinkedListIterator<T>& right);


template <class T>
class ListNode {
    
public:
    typedef T value_type;
    
    friend class LinkedList<T>;
    friend class LinkedListPosition<T>;
	friend class LinkedListIterator<T>;
    
    
    static ListNode<value_type>* init();
    static ListNode<value_type>* init(ListNode<value_type>* next, ListNode<value_type>* prev);
    static ListNode<value_type>* init(value_type value, ListNode<value_type>* next = nullptr, ListNode<value_type>* prev = nullptr);
    
    inline value_type getValue() { return value; }

    friend LinkedListPosition<T> operator+<>(const LinkedListPosition<T>& left, int v);
    friend LinkedListPosition<T> operator+<>(int v, const LinkedListPosition<T>& right);
    friend LinkedListPosition<T> operator-<>(const LinkedListPosition<T>& left, int v);
    friend LinkedListPosition<T> operator-<>(int v, const LinkedListPosition<T>& right);

    friend LinkedListIterator<T> operator+<>(const LinkedListIterator<T>& left, int v);
    friend LinkedListIterator<T> operator+<>(int v, const LinkedListIterator<T>& right);
    friend LinkedListIterator<T> operator-<>(const LinkedListIterator<T>& left, int v);
    friend LinkedListIterator<T> operator-<>(int v, const LinkedListIterator<T>& right);
private:
    T value;
    ListNode<T> *next;
    ListNode<T> *prev;
    
    ListNode(); // Costruttore reso intenzionalmente privato
    
};

template <class T>
ListNode<T>::ListNode():next(nullptr), prev(nullptr) {
    
}

template <class T>
ListNode<T>* ListNode<T>::init(){
    auto newNode = new ListNode<T>;
    newNode->next = newNode;
    newNode->prev = newNode;
    
    return newNode;
}

template <class T>
ListNode<T>* ListNode<T>::init(ListNode<value_type>* next, ListNode<value_type>* prev) {
    
    auto newNode = new ListNode<T>;
    newNode->next = next;
    newNode->prev = prev;
    
    return newNode;
}

template <class T>
ListNode<T>* ListNode<T>::init(value_type value, ListNode<value_type>* next, ListNode<value_type>* prev) {
    
    auto newNode = new ListNode<T>();
    newNode.value = value;
    newNode.next = next;
    newNode.prev = prev;
    
    return newNode;
}

/* Sovraccarica <<. Attenzione se il tipo restituito da read non è primitivo, allora
 * anche per questo tipo bisogna sovraccaricare l'operatore <<
 */
template< class T>
std::ostream& operator<<(std::ostream& os, const ListNode<T> & node){
    std::cout << node.getValue();
    return os;
}


#endif /* listnode_h */
