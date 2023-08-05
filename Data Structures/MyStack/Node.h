#pragma once

template<class T>
class Node
{
	template<class U>
	friend class MyStack;

	T Data;
	Node* Next;

public:

	Node(T, Node<T>* = nullptr);
};

template<typename T>
Node<T>::Node(T Data, Node<T>* Next)
{
	this->Data = Data;
	this->Next = Next;
}