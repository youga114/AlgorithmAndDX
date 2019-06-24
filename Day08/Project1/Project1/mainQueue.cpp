#include <iostream>
#include <cstdio>
#include "LQueue.h"
using namespace std;

int main()
{
	LQueue<int> q;

	for (int i = 0; i < 10; ++i)
		q.Push(i);
	for (int i = 0; i < 10; ++i)
	{
		cout << q.Front() << endl;
		q.Pop();
	}

	return 0;
}