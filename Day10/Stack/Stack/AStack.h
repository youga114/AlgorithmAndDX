#pragma once
template <typename T>
class AStack
{
public:
	AStack(int DefaultSize = 100);
	virtual ~AStack();

	void Push(T NewData);
	T Pop();

private:
	T* Data;
	int Cursor;
	int MaxSize;
	int Size;
};

template <typename T>
AStack<T>::AStack(int DefaultSize)
{
	Cursor = 0;
	Size = 0;
	MaxSize = DefaultSize;
	Data = new T[MaxSize];
}


template <typename T>
AStack<T>::~AStack()
{
	delete[] Data;
}

template <typename T>
void AStack<T>::Push(T NewData)
{
	if (Size < MaxSize)
	{
		Data[Cursor] = NewData;
		Size++;
		Cursor++;
	}
}

template <typename T>
T AStack<T>::Pop()
{
	if (Size < 1)
	{
		return 0;
	}

	Size--;
	return Data[--Cursor];
}