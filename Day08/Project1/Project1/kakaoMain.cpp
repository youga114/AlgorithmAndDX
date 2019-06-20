//#include <iostream>
//using namespace std;
//
//int main()
//{
//	for (int testCase = 1; testCase <= 2; ++testCase)
//	{
//		int n;
//		cin >> n;
//
//		int *arr1 = new int[n];
//		int *arr2 = new int[n];
//
//		for (int i = 0; i < n; ++i)
//			cin >> arr1[i];
//		for (int i = 0; i < n; ++i)
//			cin >> arr2[i];
//
//		int *outArr = new int[n];
//
//		for (int i = 0; i < n; ++i)
//		{
//			outArr[i] = arr1[i] | arr2[i];
//		}
//
//		for (int j = 0; j < n; ++j)
//		{
//			for (int i = n - 1; i >= 0; --i)
//			{
//				cout << (((outArr[j] & (1 << i)) >= 1) ? '#' : ' ');
//			}
//			cout << endl;
//		}
//		cout << endl;
//
//		delete[] arr1;
//		delete[] arr2;
//		delete[] outArr;
//	}
//
//	return 0;
//}