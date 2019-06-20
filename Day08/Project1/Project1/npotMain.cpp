//#include <iostream>
//#include <vector>
////#include <fstream>
//using namespace std;
//
//int main()
//{
//	int num;
//	vector<unsigned long long> v;
//	cin >> num;
//
//	/*ifstream inFile;
//	inFile.open("input.txt");*/
//
//
//	for (int i = 0; i < num; ++i)
//	{
//		unsigned long long tempNum, npot = 1;
//		cin >> tempNum;
//		//inFile >> tempNum;
//
//		while (npot < tempNum)
//		{
//			npot <<= 1;
//		}
//		v.push_back(npot);
//	}
//
//	unsigned long long xorNum = v[0];
//
//	for (int i = 1; i < v.size(); ++i)
//	{
//		xorNum ^= v[i];
//	}
//
//	cout << xorNum << endl;
//
//	return 0;
//}