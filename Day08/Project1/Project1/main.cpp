#include <iostream>
#include <list>
#include "LList.h"
using namespace std;

int main()
{
	LList l;
	for (int i = 0; i < 10; ++i)
	{
		l.Insert(i);
	}

	l.Insert(20, 3);
	l.Insert(30, 20);
	l.Insert(40, 9);

	for (LList::Iterator CurrentPosition = l.Begin(); CurrentPosition != l.End(); ++CurrentPosition)
	{
		cout << (*CurrentPosition)->Value << endl;
	}

	return 0;
}