#include <iostream>
#include "AQueue.h"
using namespace std;

int main()
{
	AQueue<int> q;
	for (unsigned int i = 0; i < 10; ++i)
		q.Push(i);

	for (unsigned int i = 0; i < 10; ++i)
	{
		cout << q.Front() << endl;
		q.Pop();
	}

	return 0;
}