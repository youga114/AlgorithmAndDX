#include <iostream>
using namespace std;

#define MAX 10

int Image[MAX][MAX]=
{
	{0,0,1,1,1,0,1,1,0,0},
	{0,0,0,0,0,0,0,1,0,0},
	{1,1,1,0,0,0,0,1,0,0},
	{0,0,0,0,0,0,0,1,0,0},
	{0,0,0,0,0,0,0,1,0,0},
	{0,0,0,0,0,0,0,1,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,1,1,0,0,0,0,0,0,0},
	{0,1,1,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0}
};

int CountImage(int x, int y)
{
	if (x < 0 || y < 0 || x >= MAX || y >= MAX)
	{
		return 0;
	}
	else if (Image[y][x] != 1)
	{
		return 0;
	}
	else
	{
		Image[y][x] = -1;
		return 1 + CountImage(x + 1, y) + CountImage(x, y + 1) + CountImage(x - 1, y) + CountImage(x, y - 1)
			+ CountImage(x - 1, y - 1) + CountImage(x - 1, y + 1) + CountImage(x + 1, y - 1) + CountImage(x + 1, y + 1);
	}
}

int main()
{
	cout << CountImage(1, 8) << endl;
	return 0;
}