
template <class T>class ArrayList; // Forward Declaration

template <class T>
class ArrayListIterator;

template <class T>
class ArrayListPosition;

template<class T>
ArrayListIterator<T> operator+ (const ArrayListIterator<T>& left, int v);

template<class T>
ArrayListIterator<T> operator+(int v, const ArrayListIterator<T>& right);

template<class T>
ArrayListIterator<T> operator-(const ArrayListIterator<T>& left, int v);

template<class T>
ArrayListIterator<T> operator-(int v, const ArrayListIterator<T>& right);


template <class T>
class ArrayListIterator : public ListIterator<ArrayListIterator<T>, ArrayList<T> > {
	friend class ArrayList<T>;
	friend class ArrayListPosition<T>;
public:
	typedef ArrayList<T> list;
	typedef ArrayListPosition<T> position;

	inline ArrayListIterator() : intValue(0), owner(nullptr) { }

	// prefix
	ArrayListIterator& operator++()
	{
		intValue++;
        if (intValue > owner->size()) {
            intValue -= owner->size();
        }
		return *this;
	}

	// postfix
	ArrayListIterator operator++(int)
	{
		ArrayListIterator tmp = *this;
		operator++(); // prefix-increment this instance
		return tmp;   // return value before increment
	}


	// prefix
	ArrayListIterator& operator--()
	{
		intValue--;
        if (intValue < 0) {
            intValue += owner->size();
        }
		return *this;
	}


	// postfix
	ArrayListIterator operator--(int)
	{
		ArrayListIterator tmp = *this;
		operator--();
		return tmp;
	}


	T& operator*() {
		if (owner == nullptr) {
			throw "Null pointer";
		}
		if (intValue >= 0 && intValue < owner->length) {
			return owner->elements[intValue];
		}
        throw ListOutOfBoundsException();
	};

	T *operator->() {
		if (owner == nullptr) {
			throw "Null pointer";
		}
		if (intValue >= 0 && intValue < owner->length) {
			return &(owner->elements[intValue]);
		}
        throw ListOutOfBoundsException();
		//return owner->_read(*this);
	}

	bool operator==(const ArrayListIterator& other) const;
	bool operator!=(const ArrayListIterator& other) const;

	ArrayListIterator<T>& operator+=(int);

	friend ArrayListIterator<T> operator+<>(const ArrayListIterator<T>& left, int v);
	friend ArrayListIterator<T> operator+<>(int v, const ArrayListIterator<T>& right);
	friend ArrayListIterator<T> operator-<>(const ArrayListIterator<T>& left, int v);
	friend ArrayListIterator<T> operator-<>(int v, const ArrayListIterator<T>& right);
private:

	bool operator==(const int& other) const;
	bool operator!=(const int& other) const;

	//inline ArrayListIterator(int val) { intValue = val; }
	inline ArrayListIterator(int val, const ArrayList<T>*o) : intValue(val), owner(o) {
		if (intValue < 0) {
            intValue += owner->size();
			//throw "Out of bounds exception";
        } else if (intValue > owner->size() ) {
            intValue -= owner->size();
        }
	}
	int intValue;
	const ArrayList<T>* owner;

};

template <class T>
inline bool ArrayListIterator<T>::operator==(const int& other) const {
	return intValue == other;
}

template <class T>
inline bool ArrayListIterator<T>::operator!=(const int& other) const {
	return intValue != other;
}

template <class T>
inline bool ArrayListIterator<T>::operator==(const ArrayListIterator& other) const {
	return intValue == other.intValue;
}

template <class T>
inline bool ArrayListIterator<T>::operator!=(const ArrayListIterator& other) const {
	return intValue != other.intValue;
}

template<class T>
inline ArrayListIterator<T>& ArrayListIterator<T>::operator+=(int v) {
	this->intValue += v;
	return *this;
}

template< class T>
ArrayListIterator<T> operator+(const ArrayListIterator<T>& left, int v) {
	return ArrayListIterator<T>(left.intValue + v, left.owner);
}

template< class T>
ArrayListIterator<T> operator+(int v, const ArrayListIterator<T>& right) {
	return ArrayListIterator<T>(right.intValue + v, right.owner);
}

template< class T>
ArrayListIterator<T> operator-(const ArrayListIterator<T>& left, int v) {
	return ArrayListIterator<T>(left.intValue - v, left.owner);
}

template< class T>
ArrayListIterator<T> operator-(int v, const ArrayListIterator<T>& right) {
	return ArrayListIterator<T>(right.intValue - v, right.owner);
}