#include <iostream>
#include "MyVector.h"
#include <stdlib.h>
#include <time.h>

int main()
{
	MyVector<int> v;

	for (int i = 0; i < 20; ++i)
	{
		v.PushBack(i);
	}

	srand((unsigned int)time(0));
	v.erase(4);
	v.insert(5, 200);

	for (int i = 0; i < v.GetSize(); ++i)
	{
		std::cout << v[i] << std::endl;
	}

	return 0;
}