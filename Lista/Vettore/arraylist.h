//
//  arraylist.h
//  ArrayList
//
//  Created by Ruggiero Altini on 14/11/16.
//  Copyright © 2016 Ruggiero Altini. All rights reserved.
//
//  C++11 compliant

#ifndef ARRAYLIST_H_
#define ARRAYLIST_H_

#include "../linearlist.h"

#include <initializer_list>
#include <iostream>
#include "arraylistposition.h"
#include "arraylistiterator.h"

//using namespace std;
using std::cout;
using std::ostream;
using std::initializer_list;

template< class T>
class ArrayList : public LinearList<T, ArrayListIterator<T>, ArrayListPosition<T> >
{
	friend class ArrayListPosition<T>;
    friend class ArrayListIterator<T>;
public:
    
    typedef typename LinearList<T, ArrayListIterator<T>, ArrayListPosition<T> >::value_type value_type;
    typedef typename LinearList<T, ArrayListIterator<T>, ArrayListPosition<T> >::position position;
    typedef typename LinearList<T, ArrayListIterator<T>, ArrayListPosition<T> >::iterator iterator;
    
    ArrayList(int dim = 10); // costruttore
    ArrayList(initializer_list<T>);
    
    // costruttore di copia
    ArrayList(const ArrayList<T>& Lista);

    // costruttore di copia-cast
    template <class other_iterator, class other_position>
    ArrayList(const LinearList<value_type, other_iterator, other_position>&);

    //distruttore
    ~ArrayList();
    
    // operatori
    void init(); // Crea Lista
    bool isEmpty() const; // Lista Vuota
    value_type read(const position&) const; // Leggi lista
    void write(const value_type&, const position&); // Scrivi lista
    position begin() const; // Primo Lista
    position last() const; // Ultimo della lista -> Posizione (diverso da Fine Lista!!!)
    bool end(const position&) const; // Fine Lista
    position next(const position&) const; // Succ Lista
    position previous(const position&) const; // Prec Lista
    void insert(const value_type&, const position&); // Ins Lista
    position erase(const position&); // Canc Lista
    value_type readByIndex(int) const;

	// OVERLOAD ITERATORS
	bool end(const iterator&) const;
	iterator erase(iterator& p);
	iterator begin();
	iterator last();
	iterator next(const iterator&);
	iterator previous(const iterator&);
    
    // Convenience methods - FUNZIONI DI SERVIZIO IMPLEMENTABILI
    int size() const;
    void push_back(const value_type&);
    void push_front(const value_type&);
    value_type pop_back();
    value_type pop_front();
    void clear();
    
    // Operator Overloading
    ArrayList<T>& operator=(const ArrayList<T>&); // Assignment Operator
    bool operator==(const LinearList<value_type, iterator, position> &) const; // Equality Operator
    bool operator!=(const LinearList<value_type, iterator, position> &l) const;
    ArrayList<T>& operator+=(ArrayList<T> const&); // Accodamento
    
    
protected:
    value_type* elements; // vettore
    int length; // length della lista
    int dimension; // dimension del vetore
    
private:
    void changeDimension(T*&, int, int);
	value_type& _read(const position&) const;
    
};

template<class T>
ArrayList<T>::ArrayList(int dim) {
    dimension = dim;
    elements = new T[dimension];
    init();
    
}

template<class T>
ArrayList<T>::ArrayList(initializer_list<T> initializerList) {
    dimension = 10;
    elements = new T[dimension];
    init();
    
    for(T elem : initializerList )
    {
        this->push_back(elem);
        //std::cout << elem << std::endl ;
    }
}

/* il costruttore di copia effettua una copia o clone di un ogreadto. Questo costruttore viene invocato,
 * per esempio, quando un ogreadto viene passato per valore ad una funzione o quando una funzione
 * restituisce un ogreadto. */
template<class T>
ArrayList<T>::ArrayList(const ArrayList<T>& list) {
    dimension = list.dimension;
    length = list.length;
    elements = new T[dimension];
    for (int i=0; i<list.dimension; i++) {
        elements[i] = list.elements[i];
    }
}

template<class T>
template <class other_iterator, class other_position>
ArrayList<T>::ArrayList(const LinearList<value_type, other_iterator, other_position>& list): elements(nullptr) {
    dimension = list.size()+10;
    init();
    for (auto it = list.begin(); !list.end(it); ++it) {
        push_back(*it);
    }
}


template<class T>
ArrayList<T>::~ArrayList() {
    delete [] elements;
}

template<class T>
inline void ArrayList<T>::init(){
    if (elements != nullptr) {
        delete[] elements;
    }
    elements = new T[dimension];
    length = 0;
}


template<class T>
bool ArrayList<T>::isEmpty() const {
    return(length == 0);
}

template<class T>
typename ArrayList<T>::value_type ArrayList<T>::read(const position& p) const {
    if(p.intValue >= 0 && p.intValue < length) {
        return elements[p.intValue];
    }
    throw ListOutOfBoundsException();
}

template<class T>
auto ArrayList<T>::_read(const position& p) const -> value_type& {
	if (p.intValue >= 0 && p.intValue < length) {
		return elements[p.intValue];
	}
    throw ListOutOfBoundsException();
}

template<class T>
void ArrayList<T>::write(const value_type& el, const position& pos) {
    if(pos.intValue >= 0 && pos.intValue < length) {
        elements[pos.intValue] = el;
    } else {
        throw ListOutOfBoundsException();
    }
}

template<class T>
auto ArrayList<T>::begin() const -> position {
    ArrayListPosition<T> it(0, this);
    //it.owner = this;
    return it;
}

template<class T>
bool ArrayList<T>::end(const position& pos) const {
    return (pos.intValue == length);
}

template<class T>
typename ArrayList<T>::position ArrayList<T>::last() const {
    ArrayListPosition<T> it(length - 1, this);
    return it;
    //return length-1;
}

template<class T>
typename ArrayList<T>::position ArrayList<T>::next(const position& pos) const {
    if(pos.intValue < length) {
        return ArrayList<T>::position(pos.intValue+1, this);
    } else {
        return ArrayList<T>::position(0, this); //TODO: Sistemare
    }
}

template<class T>
typename ArrayList<T>::position ArrayList<T>::previous(const position& pos) const {
    return ArrayList<T>::position(length % pos.intValue-1, this);
}

template<class T>
void ArrayList<T>::insert(const value_type& el, const position& pos) {
    if (length == dimension){
        changeDimension(elements, dimension, dimension * 2);
        dimension = dimension * 2;
    }
    if ( pos.intValue >= 0 && (pos.intValue <= length)) { // precondizione
        for(int i = length; i >= pos.intValue && length > 0; i--) {
            elements[i] = elements[i-1];
        }
        elements[pos.intValue]= el;
        length++;
    }
}

// MARK: - Overload

/*
template<class T>
bool ArrayList<T>::end(iterator) const;

template<class T>
typename ArrayList<T>::iterator ArrayList<T>::erase(iterator p) {

}

template<class T>
typename ArrayList<T>::iterator ArrayList<T>::begin() {

}

template<class T>
typename ArrayList<T>::iterator ArrayList<T>::last() {

}

template<class T>
typename ArrayList<T>::iterator ArrayList<T>::next(const iterator& it) {

}

template<class T>
typename ArrayList<T>::iterator ArrayList<T>::previous(const iterator& it) {
	
}*/

// MARK: - Convenience methods

template <class T>
int ArrayList<T>::size() const {
    return length;
}

template<class T>
void ArrayList<T>::push_back(const value_type& el) {
    insert(el, ArrayList<T>::position(length, this));
}

template<class T>
void ArrayList<T>::push_front(const value_type& el) {
    insert(el, ArrayList<T>::position(0, this));
}


template<class T>
typename ArrayList<T>::value_type ArrayList<T>::pop_back() {
    if (length == 0) {
        throw ListEmptyException();
    }
    value_type val = elements[length-1];
    length--;
    return val;
}

template<class T>
typename ArrayList<T>::value_type ArrayList<T>::pop_front() {
    if (length == 0) {
        throw ListEmptyException();
    }
    value_type val = elements[0];
    erase(ArrayListPosition<T>(0,this));
    return val;
}


template<class T>
void ArrayList<T>::clear() {
    while(!end(begin())) {
        pop_back();
    }
}

template<class T>
typename ArrayList<T>::value_type ArrayList<T>::readByIndex(int index) const {
    return read(index);
}


template<class T>
auto ArrayList<T>::erase(const position& pos) -> position {
    if ( pos.intValue >= 0 && ( pos.intValue < length )) {// precondizione
        if (!isEmpty()) {
            for (int i = pos.intValue; i < length; i++) {
                elements[i]=elements[i+1];
            }
            length--;
        }

        return pos;
    } else {
        throw ListOutOfBoundsException();
    }
}


template<class T>
bool ArrayList<T>::end(const iterator& i) const {
    return end(position(i));
}

template<class T>
auto ArrayList<T>::erase(iterator& pos) -> iterator {
    if (pos.intValue >= 0 && (pos.intValue < length)) {// precondizione
        if (!isEmpty()) {
            for (int i = pos.intValue; i < length; i++) {
                elements[i] = elements[i + 1];
            }
            length--;
        } else {
            throw ListEmptyException();
        }

        return pos;
    } else {
        throw ListOutOfBoundsException();
    }
}


template<class T>
auto ArrayList<T>::begin()->iterator {
    typename ArrayList<T>::iterator it(0, this);
    return it;
}

template<class T>
auto ArrayList<T>::last()->iterator {
    if (length == 0) {
        throw ListEmptyException("Error: List is empty. There is no last");
    }

    typename ArrayList<T>::iterator it(length - 1, this);
    return it;
}

template<class T>
auto ArrayList<T>::next(const iterator& pos)->iterator {
    if (pos.intValue < length) {
        return ArrayList<T>::iterator(pos.intValue + 1, this);
    } else {
        return ArrayList<T>::iterator(0, this); //TODO: Sistemare
    }
}

template<class T>
auto ArrayList<T>::previous(const iterator& pos)->iterator {
    return typename ArrayList<T>::iterator(pos.intValue - 1, this);
}

template<class T>
void ArrayList<T>::changeDimension(T*& a, int oldDimension, int newDimension){
    
    T* temp = new T[newDimension];
    int number;
    if (oldDimension < newDimension) {
        number = oldDimension;
    } else {
        number = newDimension;
    }
    for (int i=0; i<number; i++) {
        temp[i]=a[i];
    }
    delete [] a;
    a = temp;
}

/* operatore di assegnamento */
template<class T>
ArrayList<T>& ArrayList<T>::operator=(const ArrayList<T>& l){
    if (this != &l){   // attenzione agli autoassegnamenti: l = l
        this->dimension = l.dimension;
        this->length = l.length;
        delete this->elements;
        this->elements = new T[dimension];
        for (int i=0; i<l.dimension; i++)
            this->elements[i] = l.elements[i];
    }
    return *this;
}

/* operatore di test di uguaglianza */
template<class T>
bool ArrayList<T>::operator==(const LinearList<value_type, iterator, position> &l) const{
    if (l.size() != this->length)
        return false;
    /*for (int i=0; i<this->dimension; i++)
        if (this->elements[i] != l.elements[i])
            return false;*/
    auto jt = l.begin();
    for (auto it = begin(); !end(it); ++it, ++jt) {
        if (*it != *jt) {
            return false;
        }
    }
    return true;
}
template<class T>
bool ArrayList<T>::operator!=(const LinearList<value_type, iterator, position> &l) const {
    return !(*this == l);
}

template< class T>
ArrayList<T> operator+(const ArrayList<T>& left, const ArrayList<T>& right) {
    ArrayList<T> newList(left.size()+right.size()+10);
    auto pos = newList.begin();
    for(auto p = left.begin(); !left.end(p); p++) {
        newList.insert(left.read(p), pos++);
    }
    for(auto p = right.begin(); !right.end(p); p++) {
        newList.insert(right.read(p), pos++);
    }
    return newList;
}

template<class T>
ArrayList<T>& ArrayList<T>::operator+=(const ArrayList<T> &right)  {
    changeDimension(elements, dimension, dimension+right.size());
    for(auto p = right.begin(); !right.end(p); p++) {
        this->push_back(right.read(p));
    }
    
    //*this = *this + right;
    return *this;
}


#endif /* ARRAYLIST_H_ */
