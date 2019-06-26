//#include <iostream>
//#include <string>
//#include <algorithm>
//using namespace std;
//
////n 1~n 합 구하기, 피보나치 수열
//int Sum(int n)	
//{
//	return n == 0 ? 0 : Sum(n - 1) + n;
//}
//
//int Fibo(int n)
//{
//	if (n < 3)
//	{
//		return 1;
//	}
//	else
//	{
//		return Fibo(n - 1) + Fibo(n - 2);
//	}
//}
//
////문자열 거꾸로 찍기(string, char*)
////void stringRecursive(string str, int num)
////{
////	if (num + 1 < str.size())
////		stringRecursive(str, num + 1);
////	cout << str[num];
////
////	return;
////}
//
//void ReversePrint(char* s)
//{
//	if (s[0] == '\0')
//	{
//		return;
//	}
//	else
//	{
//		ReversePrint(s + 1);
//		cout << s[0];
//	}
//}
//
////10진수 2진수로 출력
////void decToBinary(int decNum, int pos)
////{
////	if ((1 << pos) < decNum)
////		decToBinary(decNum, pos + 1);
////
////	if (decNum&(1 << pos))
////		cout << 1;
////	else
////		cout << 0;
////
////	return;
////}
//
//void Binary(int n)
//{
//	if (n < 2)
//	{
//		cout << n;
//	}
//	else
//	{
//		Binary(n / 2);
//		cout << (n % 2);
//	}
//}
//
////찾으면 찾은 인덱스
////없으면 -1
////for
//int Search(int* Data, int Begin, int End, int Target)
//{
//	for (int i = Begin; i <= End; ++i)
//	{
//		if (Data[i] == Target)
//		{
//			return i;
//		}
//	}
//
//	return -1;
//}
//
////Recursive
////int Search(int* Data, int Begin, int End, int Target)
////{
////	if (Begin > End)
////	{
////		return -1;
////	}
////	else
////	{
////		if (Target == Data[Begin])
////		{
////			return Begin;
////		}
////		return Search(Data, Begin + 1, End, Target);
////	}
////}
//
////int Search(int* Data, int Begin, int End, int Target)
////{
////	if (Begin > End)
////	{
////		return -1;
////	}
////	else
////	{
////		if (Target == Data[End])
////		{
////			return End;
////		}
////		return Search(Data, Begin, End - 1, Target);
////	}
////}
//
//int BinarySearch(int* Data, int Begin, int End, int Target)
//{
//	if (Begin > End)
//	{
//		return -1;
//	}
//	else
//	{
//		int Middle = (Begin + End) / 2;
//		if (Target == Data[Middle])
//		{
//			return Middle;
//		}
//		else if (Target < Data[Middle])
//		{
//			return BinarySearch(Data, Begin, Middle - 1, Target);
//		}
//		else
//		{
//			return BinarySearch(Data, Middle + 1, End, Target);
//		}
//	}
//}
//
//int main()
//{
//	//cout << Sum(450) << endl;
//	//cout << Fibo(10) << endl;
//
//	//char str[100];
//	//cin >> str;
//	//ReversePrint(str);
//	//cout << endl;
//	//
//	//int decNum;
//	//cin >> decNum;
//	//Binary(decNum);
//
//	int arr[10] = { 1,2,3,4,5,6,7,8,9,10 };
//	cout << BinarySearch(arr, 0, 9, 8) << endl;
//
//	return 0;
//}

#include <iostream>
using namespace std;

#define MAX 10
#define WAY 0
#define WALL 1
#define BLOCK 2
#define PATH 3

int maze[MAX][MAX]=
{
	{0,0,0,0,1,1,1,1,1,1},
	{1,1,1,0,1,1,1,1,1,1},
	{1,1,1,0,1,1,1,1,1,1},
	{1,1,1,0,1,1,1,1,1,1},
	{1,1,1,0,1,1,1,1,1,1},
	{1,1,1,0,1,1,1,1,1,1},
	{1,1,1,0,0,0,0,0,1,1},
	{1,1,1,1,1,1,1,0,1,1},
	{1,1,1,1,1,1,1,0,1,1},
	{1,1,1,1,1,1,1,0,0,0}
};

bool FindMaze(int x, int y)
{
	if (x<0 || y<0 || x > MAX - 1 || y>MAX - 1)
	{
		return false;
	}
	else if (maze[y][x] != WAY)
	{
		return false;
	}
	else if (x == MAX - 1 && y == MAX - 1)
	{
		maze[y][x] = PATH;
		return true;
	}
	else
	{
		maze[y][x] = PATH;
		if (FindMaze(x + 1, y))
		{
			return true;
		}
		else if (FindMaze(x, y + 1))
		{
			return true;
		}
		else if (FindMaze(x - 1, y))
		{
			return true;
		}
		else if (FindMaze(x, y - 1))
		{
			return true;
		}
		else
		{
			maze[y][x] = BLOCK;
			return false;
		}
	}

	return true;
}

void PrintMap()
{
	for (int y = 0; y < MAX; ++y)
	{
		for (int x = 0; x < MAX; ++x)
		{
			cout << maze[y][x];
		}
		cout << endl;
	}
}

int main()
{
	cout << FindMaze(0, 0) << endl;
	PrintMap();

	return 0;
}