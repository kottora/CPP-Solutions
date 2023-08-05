#pragma once

#include <iostream>
#include <cassert>
#include <string>

using namespace std;

template<class T>
class MyVector
{
	int capacity, size;
	T* Array;


	bool search_for_erase(T item, int* index)
	{
		for (size_t i(0); i < size; ++i)
		{
			if (item == Array[i])
			{
				*index = i;
				return true;
			}
		}
		return false;
	}

public:

	MyVector();
	MyVector(int);
	MyVector(const MyVector<T>&);
	~MyVector();
	MyVector<T>& operator=(const MyVector<T>&);
	void Push_back(const T&);
	void insert(T, int);
	void erase(T);
	T& operator[](int);
	int Size()const;
	void Shrink_to_size();
};


template<class T>
MyVector<T>::MyVector()
{
	capacity = 2;
	size = 0;
	Array = new T[capacity];
}

template<class T>
MyVector<T>::MyVector(const MyVector<T>& other)
{
	this->capacity = other.capacity;
	this->size = other.size;
	this->Array = new T[capacity];
	for (size_t i(0); i < size; ++i)
	{
		this->Array[i] = other.Array[i];
	}
}

template<class T>
MyVector<T>::~MyVector()
{
	delete[] Array;
}

template<class T>
MyVector<T>& MyVector<T>::operator=(const MyVector<T>& other)
{
	if (this != &other)
	{
		this->~MyVector();
		this->capacity = other.capacity;
		this->size = other.size;
		this->Array = new T[capacity];
		for (size_t i(0); i < size; ++i)
		{
			this->Array[i] = other.Array[i];
		}
	}
	return *this;
}

template<class T>
void MyVector<T>::Push_back(const T& item)
{
	if (size < capacity)
	{
		Array[size] = item;
		++size;
	}
	else
	{
		capacity *= 2;
		T* tmp = new T[capacity];
		for (size_t i(0); i < size; ++i)
		{
			tmp[i] = Array[i];
		}
		delete[] Array;
		Array = tmp;
		tmp = nullptr;

		Array[size] = item;
		++size;
	}
}

template<class T>
void MyVector<T>::insert(T item, int index)
{
	assert(index >= 0 && index <= size);

	if (size < capacity)
	{
		for (size_t i(size); i > index; --i)
		{
			Array[i] = Array[i - 1];
		}
		Array[index] = item;
	}
	else
	{
		capacity *= 2;
		T* tmp = new T[capacity];
		for (size_t i(0); i < size; ++i)
		{
			tmp[i] = Array[i];
		}
		delete[] Array;
		Array = tmp;
		tmp = nullptr;

		for (size_t i(size); i > index; --i)
		{
			Array[i] = Array[i - 1];
		}
		Array[index] = item;
	}

	++size;
}

template<class T>
void MyVector<T>::erase(T item)
{
	int index = -1;
	if (search_for_erase(item, &index))
	{
		for (size_t i(index); i < size - 1; ++i)
		{
			Array[i] = Array[i + 1];
		}
		--size;
	}
	else
	{
		cout << "Can't delete, " << item << " is not in the vector" << endl;
	}
}

template<class T>
T& MyVector<T>::operator[](int index)
{
	assert(index >= 0 && index < size);
	return Array[index];
}

template<class T>
int MyVector<T>::Size()const
{
	return size;
}

template<class T>
void MyVector<T>::Shrink_to_size()
{
	T* tmp = new T[size];
	for (size_t i(0); i < size; ++i)
	{
		tmp[i] = Array[i];
	}
	delete[] Array;
	Array = tmp;
	tmp = nullptr;
	capacity = size;
}


// Global Function

template<class U>
ostream& operator<<(ostream& out, MyVector<U>& other)
{
	for (size_t i(0); i < other.Size(); ++i)
	{
		out << other[i] << "  ";
		if ((i + 1) % 10 == 0)
			out << endl;
	}
	out << endl;
	return out;
}