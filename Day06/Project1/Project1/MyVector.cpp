//#include "MyVector.h"
//#include <memory.h>
//
//
//MyVector::MyVector()
//{
//	StorageSize = 5;
//	Pos = 0;
//	Data = new int[StorageSize];
//}
//
//
//MyVector::~MyVector()
//{
//	delete[] Data;
//}
//
//void MyVector::PushBack(int NewValue)
//{
//	if (Pos == StorageSize)
//	{
//		//저장소 새로 생성, 추가
//		int* T = new int[StorageSize * 2];
//		memcpy(T, Data, Pos * sizeof(int));
//		/*for (int i = 0; i < Size; ++i)
//		{
//			T[i] = Data[i];
//		}*/
//		//예전에 작은 저장소 삭제
//		delete[] Data;
//		Data = T;
//		StorageSize = StorageSize * 2;
//		Data[Pos++] = NewValue;
//	}
//	else
//	{
//		//저장소 충분
//		Data[Pos++] = NewValue;
//	}
//}
//
//int MyVector::operator[](size_t GetPos)
//{
//	return Data[GetPos];
//}
//
//int MyVector::GetSize()
//{
//	return Pos;
//}
