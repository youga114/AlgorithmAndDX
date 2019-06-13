#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
	int inputNum;
	cin >> inputNum;
	vector<string> file;
	for (int i = 0; i < inputNum; i++)
	{
		string temp;
		cin >> temp;
		file.push_back(temp);
	}

	for (int i = 0; i < file[0].size(); i++)
	{
		bool flag = false;
		for (int j = 1; j < inputNum; j++) {
			if (file[0][i] != file[j][i]) {
				flag = true;
				break;
			}
		}
		if (flag == false)
			cout << file[0][i];
		else
			cout << "?";
	}

	return 0;
}