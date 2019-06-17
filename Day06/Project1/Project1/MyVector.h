#pragma once
class MyVector
{
public:
	MyVector();
	virtual ~MyVector();

	void PushBack(int NewValue);
	
	int operator[](size_t Pos);
	int GetSize();
private:
	int* Data;
	size_t StorageSize;
	size_t Pos;
};

