#pragma once
template<typename T>
class AQueue
{
public:
	AQueue(int DefaultSize = 10)
	{
		Data = new T[DefaultSize];
		MaxSize = DefaultSize;
		Size = 0;
		Head = 0;
		Tail = -1;
	}
	virtual ~AQueue()
	{
		delete[] Data;
	}
	void Push(T NewValue)
	{
		if (Size >= MaxSize)
		{
			return;
		}
		Tail++;
		Tail = Tail % MaxSize;
		Data[Tail] = NewValue;
		Size++;
	}
	void Pop()
	{
		if (Size < 1)
		{
			return;
		}

		Head++;
		Head %= MaxSize;
		Size--;
	}

	T Front()
	{
		if (Size < 1)
		{
			return 0;
		}
		return Data[Head];
	}

	T Back()
	{
		if (Size < 1)
		{
			return 0;
		}
		return Data[Tail];
	}

	inline unsigned int GetSize()
	{
		return Size;
	}

private:
	T* Data;
	unsigned int Size;
	unsigned int MaxSize;

	unsigned int Head;
	unsigned int Tail;
};

