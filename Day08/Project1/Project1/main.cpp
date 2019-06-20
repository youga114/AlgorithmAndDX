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

	for (Node* CurrentPosition = l.Head->Next; CurrentPosition != l.Tail; CurrentPosition = CurrentPosition->Next)
	{
		cout << CurrentPosition->Value << endl;
	}

	return 0;
}