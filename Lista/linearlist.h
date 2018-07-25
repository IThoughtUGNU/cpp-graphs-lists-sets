//
//  linearlist.h
//  LinearList
//
//  Created by Ruggiero Altini on 14/11/16.
//  Copyright © 2016 Ruggiero Altini. All rights reserved.
//
//  C++11 compliant


#ifndef LINEARLIST_H_
#define LINEARLIST_H_

#include <iostream>

using std::cout;
using std::endl;
using std::ostream;

template<class P, class L>
class ListPosition;

template<class P, class L>
class ListIterator /*: public iterator_base<ListPosition<P> > */ {
public:
	typedef L list;
	typedef P position;

	virtual P& operator++() = 0;
	virtual P& operator--() = 0;
	virtual P operator++(int) = 0;
	virtual P operator--(int) = 0;

	//inline virtual ListIterator<P, L>(const ListPosition<P, L>&) = 0;
	//virtual ~ListPosition() { }

	virtual bool operator==(const P& other) const = 0;
	virtual bool operator!=(const P& other) const = 0;
};


template<class P, class L>
class ListPosition /*: public iterator_base<ListPosition<P> > */ {
public:
	typedef L list;

    virtual P& operator++() = 0;
    virtual P& operator--() = 0;
    virtual P operator++(int) = 0;
    virtual P operator--(int) = 0;

    //virtual ~ListPosition() { }
    
    virtual bool operator==(const P& other) const = 0;
    virtual bool operator!=(const P& other) const = 0;
};

struct ListException : public std::exception
{
    std::string s;
    ListException(std::string ss) : s(ss) {}
    ~ListException() throw () {}
    const char* what() const throw() { return s.c_str(); }
};

struct ListOutOfBoundsException : public ListException
{
    ListOutOfBoundsException(std::string ss = "Error: Out of bounds exception") : ListException(ss) {}
    ~ListOutOfBoundsException() throw () {}
    const char* what() const throw() { return s.c_str(); }
};


struct ListEmptyException : public ListException
{
    ListEmptyException(std::string ss = "Error: Tried to fetch an element from an empty list") : ListException(ss) {}
    ~ListEmptyException() throw () {}
    const char* what() const throw() { return s.c_str(); }
};

template<class T, class I, class P>
class LinearList
{
public:
    typedef T value_type;
	typedef I iterator;
	typedef P position;

    // distruttore
    //LinearList(const LinearList<T,I,P>& l);
    virtual ~LinearList() {}

    // operatori
    virtual void init() = 0; // Crea Lista
    virtual bool isEmpty() const = 0;
    virtual value_type read(const position&) const = 0;
    virtual void write(const value_type&, const position&) = 0;
    virtual position begin() const = 0;
    virtual position last() const;
    virtual bool end(const position&) const = 0;
    virtual position next(const position&) const = 0;
    virtual position previous(const position&) const = 0;
    virtual void insert(const value_type&, const position&) = 0;
    virtual position erase(const position&) = 0;

	virtual iterator begin() = 0;
	virtual iterator erase(iterator& p) = 0;
	virtual iterator last();
	virtual iterator next(const iterator&) = 0;
	virtual iterator previous(const iterator&) = 0;
    
    // Convenience methods - FUNZIONI IMPLEMENTABILI
    virtual int size() const;
    virtual void push_back(const value_type&);
    virtual void push_front(const value_type&);
    virtual value_type pop_back();
    virtual value_type pop_front();
    virtual void clear();

    virtual bool operator==(const LinearList<T,I,P>& other) const = 0;
    virtual bool operator!=(const LinearList<T, I, P>& other) const = 0;
};


/*
template <class T, class I, class P>
LinearList<T,I,P>::LinearList(const LinearList<T,I,P>& l) {
    for (auto pos = l.begin(); !l.end(pos); ++pos) {
        this->push_back(l.read(pos));
    }
}*/


template <class T, class I, class P>
typename LinearList<T,I,P>::iterator LinearList<T, I, P>::last() {
	iterator last = begin();
	for (auto pos = begin(); !end(pos); ++pos) {
		last = pos;
	}
	return last;
}
/*
template <class T, class I, class P>
typename LinearList<T,I,P>::iterator LinearList<T, I, P>::next(const iterator& it) {
	return next(position(it));
}

template <class T, class I, class P>
typename LinearList<T,I,P>::iterator LinearList<T, I, P>::previous(const iterator& it) {
	return previous(it);
}
*/
template <class T, class I, class P>
typename LinearList<T,I,P>::position LinearList<T,I,P>::last() const {
    position last = begin();
    for(auto pos = begin(); !end(pos); ++pos) {
        last = pos;
    }
    return last;
}

template <class T, class I, class P>
int LinearList<T,I,P>::size() const {
    int count = 0;
    for(auto pos = begin(); !end(pos); ++pos) {
        count++;
    }
    return count;
}

template <class T, class I, class P>
void LinearList<T,I,P>::push_back(const value_type& el) {
    insert(el, ++last());
}

template <class T, class I, class P>
void LinearList<T,I,P>::push_front(const value_type& el) {
    insert(el, begin());
}

template <class T, class I, class P>
typename LinearList<T,I,P>::value_type LinearList<T,I,P>::pop_front() {
    if(isEmpty()) {
        throw "Empty list";
    }
    auto pos = begin();
    auto val = read(begin());
    erase(pos);
    return val;
}

template <class T, class I, class P>
typename LinearList<T,I,P>::value_type LinearList<T,I,P>::pop_back() {
    if(isEmpty()) {
        throw "Empty list";
    }
    auto pos = last();
    auto val = read(last());
    erase(pos);
    return val;
}

template <class T, class I, class P>
void LinearList<T,I,P>::clear() {
    if(isEmpty()) {
        return;
    }
    while(!end(begin())) {
        pop_front();
    }
}

/*
 template<class T, class I, class P>
 int LinearList<T,I,P>::size() const {
 int count = 0;
 position p;
 p = this->begin();
 while (!end(p)){
 count++;
 p = next(p);
 }
 
 return count;
 }*/


/* Sovraccarica <<. Attenzione se il tipo restituito da read non è primitivo, allora
 * anche per questo tipo bisogna sovraccaricare l'operatore <<
 */
template< class T, class I, class P>
ostream& operator<<(ostream& os, const LinearList<T,I,P> &l){
    typename LinearList<T,I,P>::position p;
    p = l.begin();
    cout << "[";
    while (!l.end(p)){
        if (p != l.begin())
            cout << ", " << l.read(p);
        else
            cout << l.read(p);
        p = l.next(p);
    }
    cout << "]" << endl;
    return os;
}

#endif
