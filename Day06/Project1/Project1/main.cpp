#include <iostream>
#include "MyVector.h"

int main()
{
	MyVector v;

	for (int i = 0; i < 10; ++i)
	{
		v.PushBack(i);
	}

	for (int i = 0; i < v.GetSize(); ++i)
	{
		std::cout << v[i] << std::endl;
	}

	return 0;
}