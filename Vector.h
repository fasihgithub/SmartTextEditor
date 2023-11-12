#pragma once

struct out_of_range
{
};


template<class T> class Vector
{
public:
	/* --- Constructor --- */
	//Default Construtor
	Vector();
	explicit Vector(int s);
	explicit Vector(int s, T);

	//copy constructor
	Vector(const Vector& arg);
	//copy assignment
	Vector<T>& operator=(const Vector<T>& arg);
	//Destructor
	~Vector();
	// -------------------------------------- -
		// -------------------- - iterator
	class iterator;
	iterator begin();
	const iterator begin() const;
	iterator end();
	const iterator end()const;
	const iterator cbegin() const;
	const iterator cend() const;
	//0-0-00----------------
	//Capacity
	bool empty() const;//const signifies it is a constant function
	//returns size of allocated storage capacity
	size_t capacity() const;

	//requests a change in capacity
	//reserve() will never deccrase the capacity.
	void reserve(int newmalloc);

	//change the Vector's size
	//if the newsize is smaller, the last elements will be lost.
	//has a default value param for custom values when resizing.
	void resize(int newsize, T val = T());
	//returns the size of the Vector (number of elements).
	size_t size() const;
	//returns the maximum number of elements the Vector can hold
	size_t max_size() const;
	//reduces capacity to fit the size
	void shrink_to_fit();
	//---------------------------------
	//Modifiers
	//removes all elements from the Vector
	//capacity is not changed
	void clear();

	//Inserts element at the back
	void push_back(const T& d);
	//removes the last element from the Vector
	void pop_back();
	//-------------
	//---------------------------
	//element access
	//access elements with bounds checking
	T& at(int n);
	//access elements with bounds checking for constant Vectors.
	const T& at(int n) const;
	//acccess elements, no bounds checking
	T& operator[](int i);
	//access elements, no bounds checking
	const T& operator[](int i) const;
	//returns a reference to the first element
	T& front();
	//returns a reference to the first element
	const T& front() const;
	//returns reference to the first element
	T& back();
	//returns a reference to the last element
	const T& back() const;
	//returns a pointer to the array used by Vector
	T* data();
	//returns a pointer to the array used by Vector
	const T* data() const;
	//----------------------------
private:
	size_t _size; //total elements in the Vector
	T* _elements;//pointer to first element of Vector
	size_t _space; //total amount of space utilized by the Vector array
};


template<class T>
class Vector<T>::iterator
{
public:
	iterator(T* p) :_curr(p)
	{}
	//operator overloading
	iterator& operator++()
	{
		_curr++;
		return *this;
	}

	iterator& operator--()
	{
		_curr--;
		return *this;
	}
	T& operator*()
	{
		return *_curr;
	}

	bool operator==(const iterator& b) const
	{
		return *_curr == *b._curr;
	}

	bool operator!=(const iterator& b) const
	{
		return *_curr != *b._curr;
	}
private:
	T* _curr;
};

//Constructor/Destructor
template<class T>
Vector<T>::Vector() : _size(0), _elements(0), _space(0)
{}

template<class T>
inline Vector<T>::Vector(int s)
	: _size(s), _elements(new T[s]), _space(s)
{
	for (int i = 0; i < _size; i++)
	{
		_elements[i] = T();
	}
}

//initialize a vector with size and assigned all it elements with a number
template<class T>
inline Vector<T>::Vector(int s, T n)
	: _size(s), _elements(new T[s]), _space(s)
{
	for (int i = 0; i < _size; i++)
	{
		_elements[i] = (n);
	}
}

//parameterized constructor to initizalie it from another vector
template<class T>
inline Vector<T>::Vector(const Vector& arg)
	:_size(arg._size), _elements(new T[arg._size])
{
	for (int i = 0; i < arg._size; i++)
	{
		_elements[i] = arg._elements[i];
	}
}
//initialize a vector from vector. It removes the prevoius values of the array an the new vector will have the assigned vector values
template<class T>
inline Vector<T>& Vector<T>::operator=(const Vector<T>& a)
{
	if (this == &a) return *this;// self-assignment not work needed
	//current Vector has enough space, os there is no need for new allocation
	if (a._size() <= _space)
	{
		for (int index = 0; index < a._size; ++index)
		{
			_elements[index] = a._elements[index];
			_size = a._size;
			return *this;
		}
	}
	T* p = new T[a._size];
	for (int index = 0; index < a._size; ++index)
	{
		p[index] = a._elements[index];
	}
	delete[] _elements;
	_size = a._size;
	_space = a._size;
	_elements = p;
	return *this;
}

template<class T>
Vector<T>::~Vector()
{
	delete[] _elements;
}

//iterators
//it returns the first element address in the array 

template<class T>
inline typename Vector<T>::iterator Vector<T>::begin()
{
	return Vector<T>::iterator(&_elements[0]);
}


//it returns the first element address in the array but the return type has an additional keyword constant
template<class T>
inline typename const Vector<T>::iterator Vector<T>::begin() const
{
	return Vector<T>::iterator(&_elements[_size]);
}
//it returns the last element address in the array 
template<class T>
inline typename Vector<T>::iterator Vector<T>::end()
{
	return Vector<T>::iterator(&_elements[_size]);
}

//it returns the last element address in the array  but the return type is constant
template<class T>
inline typename const Vector<T>::iterator Vector<T>::end() const
{
	return Vector<T>::iterator(&_elements[_size]);
}

//it returns the first element address in the array  but the return is constant
template<class T>
inline typename const Vector<T>::iterator Vector<T>::cbegin() const
{
	return Vector<T>::iterator(&_elements[0]);
}

//it returns the last element address in the array but the return type is constant
template<class T>
inline typename const Vector<T>::iterator Vector<T>::cend() const
{
	return Vector<T>::iterator(&_elements[_size]);
}

//capacity
//returns true if no elemnet is inserted till now
template<class T>
inline bool Vector<T>::empty() const
{
	return(_size == 0);
}

//returns the capacity which is the value in _space
template<class T>
inline size_t Vector<T>::capacity() const
{
	return _space;
}

template<class T>
inline void Vector<T>::reserve(int newalloc)
{
	//if the new size is already equal or less then the prevois size then no need to resize
	if (newalloc <= _space) return;
	//other wise create new pointer array of data type T
	T* p = new T[newalloc];

	//size the prevoius array elements in it
	for (int i = 0; i < _size; i++)
	{
		p[i] = _elements[i];
	}
	//delete the previous array
	delete[] _elements;
	//finally make teh _elements array the array with big(new size) size
	_elements = p;
	_space = newalloc;//save the new size in _space varaible
}

//function to resize the vector with new size the
template<class T>
inline void Vector<T>::resize(int newsize, T val)
{
	reserve(newsize);
	for (int index = _size; index < newsize; index++)
	{
		_elements[index] = T();
	}
	_size = newsize;
}

//get the current size of the inserted elements in the vector or count of elements in the vector
template<class T>
inline size_t Vector<T>::size() const
{
	return _size;
}

//modifiers
//insert value at the last of the vector
template<class T>
inline void Vector<T>::push_back(const T& d)
{
	if (_space == 0)
		reserve(8);
	else if (_size == _space)
		reserve(2 * _space);
	_elements[_size] = d;
	++_size;
}

//accessors
template<class T>
inline T& Vector<T>::at(int n)
{
	if (n < 0 || _size <= n) throw out_of_range();
	return _elements[n];
}

template<class T>
inline const T& Vector<T>::at(int n)const
{
	if (n < 0 || _size <= n) throw out_of_range();
	return _elements[n];
}


//Operator overloading

template<class T>
inline T& Vector<T>::operator[](int i)
{
	return _elements[i];
}

template<class T>
inline const T& Vector<T>::operator[](int i) const
{
	return _elements[i];
}

template<class T>
inline T& Vector<T>::front()
{
	return _elements[0];
}
template<class T>
inline const T& Vector<T>::front() const
{
	return _elements[0];
}


template<class T>
inline T& Vector<T>::back()
{
	return _elements[_size - 1];
}


template<class T>
inline const T& Vector<T>::back() const
{
	return _elements[_size - 1];
}

template<class T>
inline T* Vector<T>::data()
{
	return _elements;
}

template<class T>
inline const T* Vector<T>::data() const
{
	return _elements;
}