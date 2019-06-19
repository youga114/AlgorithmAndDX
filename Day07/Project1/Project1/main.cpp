#include <iostream>
#include <vector>
using namespace std;


int main()
{
	//정수를 입력 받아서 2진수로 표현하세요.
	//4
	//=> 100
	
	int num;
	cin >> num;
	/*vector<bool> v;
	long long divideNum = 1;
	for (int i = 0; i < 32; i++)
		divideNum *= 2;

	while (divideNum!=0)
	{
		int temp = num / divideNum;
		v.push_back(temp);
		if (temp)
			num -= divideNum;
		divideNum /= 2;
	}
	
	for (int i = 0; i < v.size(); ++i)
		cout << v[i];
	cout << endl;*/

	for (int i = 31; i >= 0; --i)
	{
		int bitmask = 1 << i;

		cout << ((num&bitmask) >= 1) ? 1 : 0;
		/*if ((num&bitmask) >= 1)
			cout << 1;
		else
			cout << 0;*/
	}

	return 0;
}