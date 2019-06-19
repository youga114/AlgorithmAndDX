#pragma once
template<typename T>
class MyVector
{
public:
	MyVector();
	virtual ~MyVector();

	void PushBack(T NewValue);
	
	T operator[](size_t Pos);
	int GetSize();
	bool Erase(size_t Index);
	void insert(int idx, T data);
	void clear();
private:
	T* Data;
	size_t StorageSize;
	size_t InsertPosition;
	size_t Size;
};

template<typename T>
MyVector<T>::MyVector()
{
	StorageSize = 5;
	InsertPosition = 0;
	Size = 0;
	Data = new T[StorageSize];
}

template<typename T>
MyVector<T>::~MyVector()
{
	delete[] Data;
}

template<typename T>
void MyVector<T>::PushBack(T NewValue)
{
	if (Size >= StorageSize)
	{
		//저장소 새로 생성, 추가
		StorageSize = StorageSize * 2;

		T* temp = new T[StorageSize];
		memcpy(temp, Data, InsertPosition * sizeof(T));

		//예전에 작은 저장소 삭제
		delete[] Data;
		Data = temp;
	}

	Data[InsertPosition++] = NewValue;
	Size++;
}

template<typename T>
T MyVector<T>::operator[](size_t GetPos)
{
	return Data[GetPos];
}

template<typename T>
int MyVector<T>::GetSize()
{
	return InsertPosition;
}

template<typename T>
bool MyVector<T>::Erase(size_t Index)
{
	if (Index > Size || Index < 0)
	{
		return false;
	}

	memcpy(Data + Index, Data + Index + 1, sizeof(T)*(Size - Index));

	InsertPosition--;
	Size--;

	return true;
}

template<typename T>
void MyVector<T>::insert(int idx, T data)
{
	if (Index > Size || Index < 0)
	{
		return false;
	}

	if (Size >= StorageSize)
	{
		//저장소 새로 생성, 추가
		StorageSize = StorageSize * 2;

		T* temp = new T[StorageSize];
		memcpy(temp, Data, InsertPosition * sizeof(T));

		//예전에 작은 저장소 삭제
		delete[] Data;
		Data = temp;
	}

	memcpy(Data + Index + 1, Data + Index, sizeof(T)*(Size - Index));

	Data[Index] = Value;

	Size++;
	InsertPosition++;

	/////////////////내 코드

	//if (InsertPosition == StorageSize)
	//{
	//	//저장소 새로 생성, 추가
	//	T* temp = new T[StorageSize * 2];
	//	memcpy(temp, Data, (idx - 1) * sizeof(T));
	//	temp[idx - 1] = data;
	//	for (size_t i = idx - 1; i < InsertPosition; ++i)
	//	{
	//		temp[i + 1] = Data[i];
	//	}
	//	//예전에 작은 저장소 삭제
	//	delete[] Data;
	//	Data = temp;
	//	StorageSize = StorageSize * 2;
	//	InsertPosition++;
	//}
	//else
	//{
	//	std::cout << "hi2" << std::endl;
	//	//저장소 충분
	//	for (size_t i = InsertPosition; i >= idx - 1; --i)
	//	{
	//		Data[i + 1] = Data[i];
	//	}
	//	Data[idx - 1] = data;
	//	InsertPosition++;
	//}
}

template<typename T>
void MyVector<T>::clear()
{
	InsertPosition = 0;
}