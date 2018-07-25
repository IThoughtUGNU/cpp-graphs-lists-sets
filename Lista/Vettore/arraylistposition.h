template <class T>class ArrayList; // Forward Declaration

template <class T>
class ArrayListPosition;

template <class T>
class ArrayListIterator;

template<class T>
ArrayListPosition<T> operator+ (const ArrayListPosition<T>& left, int v);

template<class T>
ArrayListPosition<T> operator+(int v, const ArrayListPosition<T>& right);

template<class T>
ArrayListPosition<T> operator-(const ArrayListPosition<T>& left, int v);

template<class T>
ArrayListPosition<T> operator-(int v, const ArrayListPosition<T>& right);


template <class T>
class ArrayListPosition : public ListPosition<ArrayListPosition<T>, ArrayList<T> > {
    friend class ArrayList<T>;
    friend class ArrayListIterator<T>;
public:
    typedef ArrayList<T> list;

    inline ArrayListPosition() : intValue(0), owner(nullptr) { }
    inline ArrayListPosition(const ArrayListIterator<T>& it) : intValue(it.intValue), owner(it.owner) { }

    // prefix
    ArrayListPosition& operator++()
    {
        intValue++;
        return *this;
    }

    // postfix
    ArrayListPosition operator++(int)
    {
        ArrayListPosition tmp = *this;
        operator++(); // prefix-increment this instance
        return tmp;   // return value before increment
    }


    // prefix
    ArrayListPosition& operator--()
    {
        intValue--;
        return *this;
    }


    // postfix
    ArrayListPosition operator--(int)
    {
        ArrayListPosition tmp = *this;
        operator--();
        return tmp;
    }

    /*
    T& operator*() {
    if (owner == nullptr) {
    throw "Null pointer";
    }
    if (intValue >= 0 && intValue < owner->length) {
    return owner->elements[intValue];
    }
    throw "Out of bounds";
    };*/

    const T& operator*() const {
        if (owner == nullptr) {
            throw "Null pointer";
        }
        return owner->_read(*this);
    };

    /*
    T *operator->() {
    if (owner == nullptr) {
    throw "Null pointer";
    }
    if (intValue >= 0 && intValue < owner->length) {
    return &(owner->elements[intValue]);
    }
    throw "Out of bounds";
    //return owner->_read(*this);
    }*/

    T *operator->() const {
        if (owner == nullptr) {
            throw "Null pointer";
        }
        return &(owner->read(*this));
    }

    bool operator==(const ArrayListPosition& other) const;
    bool operator!=(const ArrayListPosition& other) const;

    ArrayListPosition<T>& operator+=(int);

    friend ArrayListPosition<T> operator+<>(const ArrayListPosition<T>& left, int v);
    friend ArrayListPosition<T> operator+<>(int v, const ArrayListPosition<T>& right);
    friend ArrayListPosition<T> operator-<>(const ArrayListPosition<T>& left, int v);
    friend ArrayListPosition<T> operator-<>(int v, const ArrayListPosition<T>& right);
private:

    bool operator==(const int& other) const;
    bool operator!=(const int& other) const;

    //inline ArrayListPosition(int val) { intValue = val; }
    inline ArrayListPosition(int val, const ArrayList<T>*o) : intValue(val), owner(o) {
        if (intValue < 0) {
            throw "Out of bounds exception";
        }
    }
    int intValue;
    const ArrayList<T>* owner;

};

template <class T>
inline bool ArrayListPosition<T>::operator==(const int& other) const {
    return intValue == other;
}

template <class T>
inline bool ArrayListPosition<T>::operator!=(const int& other) const {
    return intValue != other;
}

template <class T>
inline bool ArrayListPosition<T>::operator==(const ArrayListPosition& other) const {
    return intValue == other.intValue;
}

template <class T>
inline bool ArrayListPosition<T>::operator!=(const ArrayListPosition& other) const {
    return intValue != other.intValue;
}

template<class T>
inline ArrayListPosition<T>& ArrayListPosition<T>::operator+=(int v) {
    this->intValue += v;
    return *this;
}

template< class T>
ArrayListPosition<T> operator+(const ArrayListPosition<T>& left, int v) {
    return ArrayListPosition<T>(left.intValue + v, left.owner);
}

template< class T>
ArrayListPosition<T> operator+(int v, const ArrayListPosition<T>& right) {
    return ArrayListPosition<T>(right.intValue + v, right.owner);
}

template< class T>
ArrayListPosition<T> operator-(const ArrayListPosition<T>& left, int v) {
    return ArrayListPosition<T>(left.intValue - v, left.owner);
}

template< class T>
ArrayListPosition<T> operator-(int v, const ArrayListPosition<T>& right) {
    return ArrayListPosition<T>(right.intValue - v, right.owner);
}