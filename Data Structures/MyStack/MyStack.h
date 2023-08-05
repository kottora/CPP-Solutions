#pragma once

#include "Node.h"

#include <iostream>
#include <iomanip>
#include <cassert>

template<class T>
class MyStack
{
	Node<T>* Top;
	int Size;

	// interesting
	bool search_for_erase(T item, Node<T>** it)
	{
		*it = Top;
		while ((*it)->Next != nullptr)
		{
			if (item == (*it)->Next->Data)
			{
				return true;
			}
			*it = (*it)->Next;
		}
		*it = nullptr;
		return false;
	}

public:

	MyStack();

	MyStack(const MyStack<T>&);
	~MyStack();
	MyStack<T>& operator=(const MyStack<T>&);

	// interesting
	void erase(T item)
	{
		if (Size > 0)
		{
			if(Top->Data == item)
			{
				Node<T>* tmp = Top;
				Top = Top->Next;
				delete tmp;
				tmp = nullptr;
				--Size;
			}
			else
			{
				Node<T>* it = nullptr;
				if (search_for_erase(item, &it))
				{
					Node<T>* tmp = it->Next;
					it->Next = tmp->Next;
					delete tmp;
					tmp = nullptr;
					--Size;
				}
				else
				{
					std::cout << "Can't delete, " << item << " is not in the Stack" << std::endl;
				}
			}
		}
		else
		{
			std::cout << "Can't delete, Stack is empty" << std::endl;
		}
	}

	void push(T);
	void pop();
	void display(std::ostream&) const;
	T& operator[](int);
	bool search(T);
};

template<typename T>
MyStack<T>::MyStack()
{
	Top = nullptr;
	Size = 0;
}

template<typename T>
MyStack<T>::MyStack(const MyStack<T>& other)
{
	if (other.Size == 0)
	{
		Top = nullptr;
		Size = 0;
	}
	else
	{
		Top = new Node<T>(other.Top->Data);
		Size = 1;

		Node<T>* Oit = other.Top->Next, * Tit = Top;

		while (Oit != nullptr)
		{
			Tit->Next = new Node<T>(Oit->Data);
			++Size;
			Oit = Oit->Next;
			Tit = Tit->Next;
		}
	}
}

template<typename T>
MyStack<T>::~MyStack()
{
	Node<T>* it = Top, * tmp = nullptr;
	while (it != nullptr)
	{
		tmp = it;
		it = it->Next;
		delete tmp;
	}
	tmp = Top = nullptr;
	Size = 0;
}

template<typename T>
MyStack<T>& MyStack<T>::operator=(const MyStack<T>& other)
{
	if (this != &other)
	{
		this->~MyStack();

		if (other.Size != 0)
		{
			Top = new Node<T>(other.Top->Data);
			Size = 1;

			Node<T>* Oit = other.Top->Next, * Tit = Top;

			while (Oit != nullptr)
			{
				Tit->Next = new Node<T>(Oit->Data);
				++Size;
				Oit = Oit->Next;
				Tit = Tit->Next;
			}
		}
	}
	return *this;
}

template<typename T>
void MyStack<T>::push(T item)
{
	if (Top)
	{
		Top = new Node<T>(item, Top);
		++Size;
	}
	else
	{
		Top = new Node<T>(item);
		Size = 1;
	}
}

template<typename T>
void MyStack<T>::pop()
{
	if (Top)
	{
		Node<T>* tmp = Top;
		Top = Top->Next;
		delete tmp;
		tmp = nullptr;
		--Size;
	}
	else
	{
		std::cout << "Can't delete, Stack is empty" << std::endl;
	}
}

template<typename T>
void MyStack<T>::display(std::ostream& out) const
{
	if (Top)
	{
		Node<T>* it = Top;
		int i(1);
		while (it != nullptr)
		{
			out << std::setw(5) << it->Data << " ";
			if (i % 10 == 0)
				out << std::endl;
			++i;
			it = it->Next;
		}
	}
	else
	{
		out << "Stack is empty" << std::endl;
	}
}

template<typename T>
T& MyStack<T>::operator[](int index)
{
	assert(index >= 0 && index < Size);
	Node<T>* it = Top;
	for (size_t i(0); i < index; ++i)
	{
		it = it->Next;
	}
	return it->Data;
}

template<typename T>
bool MyStack<T>::search(T item)
{
	Node<T>* it = Top;
	while (it != nullptr)
	{
		if (it->Data == item)
		{
			return true;
		}
		it = it->Next;
	}
	return false;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const MyStack<T>& other)
{
	other.display(out);
	return out;
}