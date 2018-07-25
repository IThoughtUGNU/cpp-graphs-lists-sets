//
//  set.h
//  StruttureDati-1
//
//  Created by Ruggiero Altini on 14/11/16.
//  Copyright © 2016 Ruggiero Altini. All rights reserved.
//

#ifndef set_h
#define set_h

template <class T, class DerivedSet>
class Set {
public:
    typedef T value_type;
    
    // Distruttore
    virtual ~Set() {}
    
    // Operatori
    virtual void init() = 0;
    virtual bool isEmpty() const = 0;               // Insieme vuoto
    virtual bool contains(const value_type&) const = 0;    // Appartiene
    virtual DerivedSet& add(const value_type&) = 0;        // Inserisci
    virtual DerivedSet& remove(const value_type&) = 0;     // Cancella
    
    virtual DerivedSet unionWith(const DerivedSet&) const = 0;      // Unione
    virtual DerivedSet intersection(const DerivedSet&) const = 0;   // Intersezione
    virtual DerivedSet difference(const DerivedSet&) const = 0;     // Differenza
    
};

#endif /* set_h */
