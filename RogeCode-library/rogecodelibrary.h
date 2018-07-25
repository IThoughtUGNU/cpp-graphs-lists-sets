//
//  rogecodelibrary.h
//  RogeCodeLib
//
//  Created by Ruggiero Altini on 17/12/16
//  Copyright © 2017 Ruggiero Altini. All rights reserved.
//

#ifndef rogecodelibrary_h
#define rogecodelibrary_h

#define guard(CONDITION) \
    if (CONDITION) {}


struct constants {

    static const int SHIFT_UP;
    static const int SHIFT_DOWN;
};

namespace rogecode {

    template <class T>
    void changeDimension(T*& _vector, int oldDimension, int newDimension);
    
    template<class T>
    void shiftArray(T*& _vector, int start, int size, int sign);
}

template <class T>
void rogecode::changeDimension(T*& _vector, int oldDimension, int newDimension) {
    int number;
    T* temp = new T[newDimension];

    if (oldDimension < newDimension) {
        number = oldDimension;
    } else {
        number = newDimension;
    }
    for (int i = 0; i<number; i++) {
        temp[i] = _vector[i];
    }
    delete[] _vector;
    _vector = temp;
}


template<class T>
inline void rogecode::shiftArray(T*& _vector, int start, int size, int sign) {
    if (sign != 1 && sign != -1) {
        throw "Invalid sign";
    }
    if (sign == 1) {
        for (int i = size-1; i > start; --i) {
            _vector[i] = _vector[i - 1];
        }
    } else if (sign == -1) {
        for (int i = start; i < size-1; ++i) {
            _vector[i] = _vector[i + 1];
        }
    }
}

#endif