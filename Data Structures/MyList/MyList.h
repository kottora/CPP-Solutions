#pragma once

#include <cassert>
#include <iomanip>
#include <iostream>

using namespace std;

template<typename T>
class MyList
{
	struct Node
	{
		T Data;
		Node* Next, *Prev;
	
		Node(T Data, Node* Prev = nullptr, Node* Next = nullptr)
		{
			this->Data = Data;
			this->Prev = Prev;
			this->Next = Next;
		}
	};

	Node* Top, *Tail;
	int SIZE;

	bool search_for_erase(T item, Node*& it)
	{
		Node* it1 = Top;
		for (size_t i(0); i < SIZE; ++i)
		{
			if (it1->Data == item)
			{
				it = it1;
				return true;
			}
			it1 = it1->Next;
		}
		return false;
	}

public:

	MyList();
	MyList(const MyList&);
	~MyList();
	MyList& operator=(const MyList&);
	void insert(T, int);
	void push(T);
	void erase(T);
	bool search(T);
	void display(ostream&) const;
	T& operator[](int);
};

template<typename T>
MyList<T>::MyList()
{
	Top = Tail = nullptr;
	SIZE = 0;
}

template<typename T>
MyList<T>::MyList(const MyList<T>& other)
{
	if (other.SIZE == 0)
	{
		Top = Tail = nullptr;
		SIZE = 0;
	}
	else
	{
		Top = Tail = new Node(other.Top->Data);
		SIZE = 1;

		Node *Oit = other.Top->Next;
		Node *Tit = Top;
		for (size_t i(0); i < other.SIZE - 1; ++i)
		{
			Tail = Tit->Next = new Node(Oit->Data, Tit);
			++SIZE;
			Oit = Oit->Next;
			Tit = Tit->Next;
		}

		Tail->Next = Top;
		Top->Prev = Tail;
	}
}

template<typename T>
MyList<T>::~MyList()
{
	Node* it = Top, *tmp = Top;

	for (size_t i(0); i < SIZE; ++i)
	{
		it = it->Next;
		delete tmp;
		tmp = it;
	}

	Top = Tail = nullptr;
	SIZE = 0;
}

template<typename T>
MyList<T>& MyList<T>::operator=(const MyList<T>& other)
{
	if (this != &other)
	{
		this->~MyList();
		
		if (other.SIZE == 0)
		{
			Top = Tail = nullptr;
			SIZE = 0;
		}
		else
		{
			Top = Tail = new Node(other.Top->Data);
			SIZE = 1;

			Node* Oit = other.Top->Next;
			Node* Tit = Top;
			for (size_t i(0); i < other.SIZE - 1; ++i)
			{
				Tail = Tit->Next = new Node(Oit->Data, Tit);
				++SIZE;
				Oit = Oit->Next;
				Tit = Tit->Next;
			}

			Tail->Next = Top;
			Top->Prev = Tail;
		}
	}
	return *this;
}

template<typename T>
void MyList<T>::insert(T item, int index)
{
	assert(index >= 0 && index <= SIZE);
	
	if (SIZE == 0)
	{
		Top = Tail = new Node(item);
		Tail->Next = Top;
		Top->Prev = Tail;
	}
	else if(index == 0)
	{
		Node* tmp = new Node(item, Tail, Top);
		Tail->Next = Top->Prev = tmp;
		Top = tmp;
		tmp = nullptr;
	}
	else if (index == SIZE)
	{
		Node* tmp = new Node(item, Tail, Top);
		Tail->Next = Top->Prev = tmp;
		Tail = tmp;
		tmp = nullptr;
	}
	else
	{
		if (index < SIZE / 2)
		{
			Node* it = Top;
			for (size_t i(0); i < index - 1; ++i)
			{
				it = it->Next;
			}
			Node* tmp = new Node(item, it, it->Next);
			(it->Next)->Prev = tmp;
			it->Next = tmp;
			tmp = nullptr;
		}
		else
		{
			Node* it = Tail;
			for (size_t i(0); i < SIZE - (index + 1); ++i)
			{
				it = it->Prev;
			}
			Node* tmp = new Node(item, it->Prev, it);
			(it->Prev)->Next = tmp;
			it->Prev = tmp;
			tmp = nullptr;
		}
	}

	++SIZE;
}

template<typename T>
void MyList<T>::push(T item)
{
	if (SIZE == 0)
	{
		Top = Tail = new Node(item);
		Tail->Next = Top;
		Top->Prev = Tail;
	}
	else
	{
		Node* tmp = new Node(item, Tail, Top);
		Tail->Next = Top->Prev = tmp;
		Tail = tmp;
		tmp = nullptr;
	}

	++SIZE;
}

template<typename T>
bool MyList<T>::search(T data)
{
	Node* it1 = Top, * it2 = Tail;
	for (size_t i(0); i < SIZE; ++i)
	{
		if (it1->Data == data || it2->Data == data)
		{
			return true;
		}
		it1 = it1->Next;
		it2 = it2->Prev;
	}
	return false;
}

template<typename T>
void MyList<T>::erase(T item)
{
	Node* it = nullptr;
	if (search_for_erase(item, it))
	{
		if (SIZE == 1)
		{
			delete Top;
			Top = Tail = nullptr;
			SIZE = 0;
		}
		else if (it == Top)
		{
			Top = Top->Next;
			Top->Prev = Tail;
			Tail->Next = Top;
			delete it;
			it = nullptr;
		}
		else if(it == Tail)
		{
			Tail = Tail->Prev;
			Tail->Next = Top;
			Top->Prev = Tail;
			delete it;
			it = nullptr;
		}
		else
		{
			(it->Prev)->Next = it->Next;
			(it->Next)->Prev = it->Prev;
			delete it;
			it = nullptr;
		}

		--SIZE;
	}
	else
	{
		cout << "Can't Delete, " << item << " is not in List" << endl;
	}
}

template<typename T>
T& MyList<T>::operator[](int index)
{
	assert(index >= 0 && index < SIZE);

	if (index < SIZE / 2)
	{
		Node* it = Top;
		for (size_t i(0); i < index; ++i)
		{
			it = it->Next;
		}
		return it->Data;
	}
	else
	{
		Node* it = Tail;
		for (size_t i(0); i < SIZE - (index + 1); ++i)
		{
			it = it->Prev;
		}
		return it->Data;
	}
}

template<typename T>
void MyList<T>::display(ostream& out)const
{
	Node* it = Top;
	for (size_t i(0); i < SIZE; ++i)
	{
		out << setw(5) << it->Data << "  ";
		it = it->Next;
		if ((i + 1) % 10 == 0)
		{
			out << endl;
		}	
	}
	out << endl;
}

template<typename T>
ostream& operator<<(ostream& out, const MyList<T>& list)
{
	list.display(out);
	return out;
}