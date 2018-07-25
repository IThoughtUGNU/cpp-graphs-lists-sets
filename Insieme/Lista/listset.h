//
//  listset.h
//  StruttureDati-1
//
//  Created by Ruggiero Altini on 14/11/16.
//  Copyright © 2016 Ruggiero Altini. All rights reserved.
//

//#pragma once
#ifndef listset_h
#define listset_h

#include "../set.h"
#include "../../Lista/Vettore/arraylist.h"
//#include <initializer_list>

//using std::initializer_list;

template<class T>
class ListSet: public Set<T, ListSet<T> > {
public:
    typedef typename Set<T, ListSet<T> >::value_type value_type;
    
    // Costruttore
    ListSet();
    ListSet(const initializer_list<T>& initializerList); // Costruttore "letterale" (non è un vero literal)
    ListSet(const ListSet<T>& set); // Costruttore di copia
    
    // Distruttore
    ~ListSet();
    
    // Operatori
    void init();
    bool isEmpty() const; // Insieme Vuoto
    bool contains(const value_type&) const; // Appartiene
    ListSet<T>& add(const value_type&); // Inserisci
    ListSet<T>& remove(const value_type&); // Cancella
    void print() const;
    
    ListSet<T> unionWith(const ListSet<T>&) const;
    ListSet<T> intersection(const ListSet<T>&) const;
    ListSet<T> difference(const ListSet<T>&) const;
    
    ListSet<T>& operator=(const ListSet<T>&); // Assignment Operator
    bool operator==(const ListSet<T> &) const; // Equality Operator
    bool operator!=(const ListSet<T> &set) const;
    ListSet<T>& operator+=(ListSet<T> const&); // Unione
    ListSet<T>& operator^=(ListSet<T> const&); // Intersezione
    ListSet<T>& operator-=(ListSet<T> const&); // Differenza
    
private:
    ArrayList<T> listSet;
};

template<class T>
ListSet<T>::ListSet() {
    init();
}

template<class T>
ListSet<T>::~ListSet() {
    //~listSet;
    
}

template<class T>
ListSet<T>::ListSet(const initializer_list<T>& initializerList) {
    init();
    for(T elem : initializerList )
    {
        this->listSet.push_back(elem);
    }
}

template<class T>
ListSet<T>::ListSet(const ListSet<T>& set) {
    for (auto it = set.listSet.begin(); !set.listSet.end(it); ++it) {
        listSet.push_back(set.listSet.read(it));
    }
    //this->unionWith(set);
}

template<class T>
void ListSet<T>::init() {
    listSet.init();
}

template<class T>
bool ListSet<T>::isEmpty() const {
    return listSet.size() == 0;
}

template<class T>
bool ListSet<T>::contains(const value_type& elem) const {
    auto pos = listSet.begin();
    while(!listSet.end(pos)) {
        if(listSet.read(pos) == elem) {
            return true;
        }
        pos = listSet.next(pos);
    }
    return false;
}

template<class T>
ListSet<T>& ListSet<T>::add(const value_type& elem) {
    if(!contains(elem)) {
        listSet.push_back(elem);
    }
    return *this;
}

template<class T>
ListSet<T>& ListSet<T>::remove(const value_type& elem) {
    auto pos = listSet.begin();
    while(!listSet.end(pos)) {
        if(listSet.read(pos) == elem) {
            listSet.erase(pos);
            break;
        }
        pos = listSet.next(pos);
    }
    return *this;
}


template<class T>
ListSet<T> ListSet<T>::unionWith(const ListSet<T>& otherSet) const {
    ListSet<T> union_;
    
    for(auto i = listSet.begin(); !listSet.end(i); i = listSet.next(i)) {
        union_.add(listSet.read(i)); // L'add controlla già la condizione d'appartenenza
    }
    for(auto i = otherSet.listSet.begin(); !otherSet.listSet.end(i); i = otherSet.listSet.next(i)) {
        union_.add(otherSet.listSet.read(i)); // """"
    }
    return union_;
}

template<class T>
ListSet<T> ListSet<T>::intersection(const ListSet<T>& otherSet) const {
    ListSet<T> inters;
    
    for(auto i = otherSet.listSet.begin(); !otherSet.listSet.end(i); i = listSet.next(i)) {
        value_type elem = otherSet.listSet.read(i);
        if(contains(elem)) {
            inters.add(elem);
        }
    }
    return inters;
}

template<class T>
ListSet<T> ListSet<T>::difference(const ListSet<T>& otherSet) const {
    ListSet<T> diff;
    
    for(auto i = listSet.begin(); !listSet.end(i); i = listSet.next(i)) {
        value_type elem = listSet.read(i);
        if(!otherSet.contains(elem)) {
            diff.add(elem);
        }
    }
    return diff;
}

template<class T>
void ListSet<T>::print() const {
    std::cout << listSet;
}

/* Sovraccarica <<. Attenzione se il tipo restituito da read non è primitivo, allora
 * anche per questo tipo bisogna sovraccaricare l'operatore <<
 */
template< class T>
ostream& operator<<(ostream& os, const ListSet<T> &l){
    l.print();
    return os;
}

// NOTA:
// I seguenti operatori sono usati come abbreviazioni/alias per le operazioni sugli insiemi
// +    ->  unione
// ^    ->  intersezione
// -    ->  differenza

template< class T>
ListSet<T> operator+(const ListSet<T>& left, const ListSet<T>& right) {
    return left.unionWith(right);
}

template< class T>
ListSet<T> operator^(const ListSet<T>& left, const ListSet<T>& right) {
    return left.intersection(right);
}

template< class T>
ListSet<T> operator-(const ListSet<T>& left, const ListSet<T>& right) {
    return left.difference(right);
}

/* operatore di assegnamento */
template<class T>
ListSet<T>& ListSet<T>::operator=(const ListSet<T>& set){
    if (this != &set){   // attenzione agli autoassegnamenti: l = l
        this->listSet = set.listSet;
    }
    return *this;
}

/* operatore di test di uguaglianza */
template<class T>
bool ListSet<T>::operator==(const ListSet<T> &set) const{
    if (this == &set) {
        return true;
    }
    ListSet<T> t = *this - set;
    if (!t.isEmpty()) {
        return false;
    }
    t = set - *this;
    if (!t.isEmpty()) {
        return false;
    }
    return true;
}

template<class T>
bool ListSet<T>::operator!=(const ListSet<T> &set) const {
    return !(*this == set);
}

template<class T>
ListSet<T>& ListSet<T>::operator+=(ListSet<T> const& right) {
    *this = (*this + right);
    return *this;
}

template<class T>
ListSet<T>& ListSet<T>::operator^=(ListSet<T> const& right) {
    *this = (*this ^ right);
    return *this;
}


template<class T>
ListSet<T>& ListSet<T>::operator-=(ListSet<T> const& right) {
    *this = (*this - right);
    return *this;
}

#endif /* listset_h */

