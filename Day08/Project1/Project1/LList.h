#pragma once
//------------
//|  |  1  | |
//------------
//------------
//|  |  2  | |
//------------
//------------
//|  |  3  | |
//------------
template<typename T>
class Node
{
public:
	T Value;

	Node<T>* Prev;
	Node<T>* Next;
};

template<typename T>
class LList
{
public:
	LList();
	virtual ~LList();

	class Iterator
	{
	private:
		Node<T>* Current;
	public:
		Iterator(Node<T>* init = nullptr) : Current(init) {}
		Iterator& operator++()
		{
			Current = Current->Next;
			return *this;
		}

		Iterator operator++(int)
		{
			Node<T> Temp = *Current;
			Current = Current->Next;
			return Iterator(&Temp);
		}

		Node<T>* operator* ()
		{
			return Current;
		}

		bool operator!=(const Iterator& rhs)
		{
			return (Current != rhs.Current);
		}

		bool operator==(const Iterator& rhs)
		{
			return (Current == rhs.Current);
		}
	};

	class ReverseIterator
	{
	private:
		Node<T>* Current;
	public:
		ReverseIterator(Node<T>* init = nullptr) : Current(init) {}
		ReverseIterator& operator++()
		{
			Current = Current->Prev;
			return *this;
		}

		ReverseIterator operator++(int)
		{
			Node<T> Temp = *Current;
			Current = Current->Prev;
			return ReverseIterator(&Temp);
		}

		Node<T>* operator* ()
		{
			return Current;
		}

		bool operator!=(const ReverseIterator& rhs)
		{
			return (Current != rhs.Current);
		}

		bool operator==(const ReverseIterator& rhs)
		{
			return (Current == rhs.Current);
		}
	};

	void PushBack(T NewValue);
	void PushFront(T NewValue);

	void InsertAfter(LList::Iterator Where, T SearchValue);
	void InsertBefore(LList::Iterator Where, T SearchValue);
	Iterator Find(T SearchValue);

	Iterator Begin() { return Iterator(Head->Next); }
	Iterator End() { return Iterator(Tail); }

	ReverseIterator RBegin() { return ReverseIterator(Tail->Prev); }
	ReverseIterator REnd() { return ReverseIterator(Head); }

	Iterator Erase(Iterator Where)
	{
		(*Where)->Prev->Next = (*Where)->Next;
		(*Where)->Next->Prev = (*Where)->Prev;
		Iterator Return = Iterator((*Where)->Next);
		delete (*Where);

		Size--;
		return Return;
	}

	Iterator Erase(ReverseIterator Where)
	{
		(*Where)->Prev->Next = (*Where)->Next;
		(*Where)->Next->Prev = (*Where)->Prev;
		Iterator Return = Iterator((*Where)->Next);
		delete (*Where);

		Size--;
		return Return;
	}

	unsigned int GetSize()
	{
		return Size;
	}

protected:
	Node<T>* Tail;
	Node<T>* Head;

	Node<T>* MakeNode(T NewValue);

	unsigned int Size;
};

template<typename T>
LList<T>::LList()
{
	Head = new Node<T>();
	Tail = new Node<T>();
	Head->Next = Tail;
	Tail->Prev = Head;
	Size = 0;
}


template<typename T>
LList<T>::~LList()
{
}

template<typename T>
void LList<T>::PushBack(T NewValue)
{
	Node<T>* NewNode = MakeNode(NewValue);

	if (NewNode)
	{
		NewNode->Prev = Tail->Prev;
		Tail->Prev = NewNode;
		NewNode->Next = Tail;
		NewNode->Prev->Next = NewNode;

		Size++;
	}
}

template<typename T>
void LList<T>::PushFront(T NewValue)
{
	Node<T>* NewNode = MakeNode(NewValue);

	if (NewNode)
	{
		NewNode->Prev = Head;
		NewNode->Next = Head->Next;
		NewNode->Next->Prev = NewNode;
		Head->Next = NewNode;

		Size++;
	}
}

template<typename T>
void LList<T>::InsertAfter(LList<T>::Iterator Where, T NewValue)
{
	if (Where != nullptr)
	{
		Node<T>* NewNode = MakeNode(NewValue);


		NewNode->Next = (*Where)->Next;
		NewNode->Prev = (*Where);
		(*Where)->Next = NewNode;
		NewNode->Next->Prev = NewNode;

		Size++;
	}
}

template<typename T>
void LList<T>::InsertBefore(LList<T>::Iterator Where, T NewValue)
{
	if (Where != nullptr)
	{
		Node<T>* NewNode = MakeNode(NewValue);


		NewNode->Next = (*Where);
		NewNode->Prev = (*Where)->Prev;
		(*Where)->Prev = NewNode;
		NewNode->Prev->Next = NewNode;

		Size++;
	}
}

template<typename T>
typename LList<T>::Iterator LList<T>::Find(T SearchValue)
{
	for (LList<T>::Iterator Current = Begin(); Current != End(); ++Current)
	{
		if ((*Current)->Value == SearchValue)
		{
			return Current;
		}
	}

	return nullptr;
}

template<typename T>
Node<T> * LList<T>::MakeNode(T NewValue)
{
	Node<T>* NewNode = new Node<T>();
	NewNode->Value = NewValue;

	return NewNode;
}