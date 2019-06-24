#include <iostream>
#include "AStack.h"
using namespace std;

int main()
{
	AStack<char> IntStack;

	char tempC='0';
	while (tempC != '\n')
	{
		scanf("%1c", &tempC);
		IntStack.Push(tempC);
	}
	while (tempC != 0)
	{
		tempC = IntStack.Pop();
		cout << tempC;
	}
	cout << endl;

	/*for (int i = 0; i < 10; ++i)
	{
		IntStack.Push(i);
	}

	for (int i = 0; i < 10; ++i)
	{
		cout << IntStack.Pop() << endl;
	}*/

	return 0;
}