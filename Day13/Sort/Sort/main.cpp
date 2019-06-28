#include <iostream>
using namespace std;

void Swap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}

void SelectionSort(int* Data, int size)
{
	for (int i = 0; i < size; ++i)
	{
		for (int j = i; j < size; ++j)
		{
			if (Data[i] > Data[j])
			{
				Swap(Data[i], Data[j]);
			}
		}
	}
}

void BubbleSort(int* Data, int size, bool(*fp)(int, int))
{
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size - 1; ++j)
		{
			if (fp(Data[j], Data[j + 1]))
			{
				Swap(Data[j], Data[j + 1]);
			}
		}
	}
}

bool cmp(int a, int b)
{
	return a > b;
}

bool cmp2(int a, int b)
{
	return a < b;
}

int partition(int* Data, int begin, int end, bool(*fp)(int, int))
{
	int pivot = Data[end];
	int left = begin;
	int right = end - 1;
	
	while (1)
	{
		while (fp(Data[left], pivot))
		{
			left++;
		}
		while (fp(pivot, Data[right]))
		{
			right--;
		}

		if (left > right)
		{
			Swap(Data[left], Data[end]);
			break;
		}

		Swap(Data[left], Data[right]);
	}

	return left;
}

void QuickSort(int* Data, int begin, int end, bool(*fp)(int, int))
{
	if (begin < end)
	{
		int pivot = partition(Data, begin, end, fp);
		QuickSort(Data, begin, pivot - 1, fp);
		QuickSort(Data, pivot + 1, end, fp);
	}
}

int main()
{
	int Data[10] = { 10,2,12,15,16,20,49,60,3,6 };

	QuickSort(Data, 0, 9, cmp2);

	for (int i = 0; i < 10; ++i)
	{
		cout << Data[i] << ", ";
	}
	cout << endl;

	return 0;
}