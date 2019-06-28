#include <iostream>
#include <queue>
#include <stack>
using namespace std;

#define MAX 5

int Maze[MAX][MAX] = {
	{0, 1, 1, 1, 0},
	{0, 0, 0, 0, 0},
	{1, 0, 1, 1, 1},
	{1, 0, 1, 1, 1},
	{1, 0, 0, 0, 0},
};

int main()
{
	queue<int> qX;
	queue<int> qY;
	queue<int> qNum;
	qX.push(0);
	qY.push(0);
	qNum.push(100);
	int x, y, num;

	while (1)
	{
		x = qX.front();
		qX.pop();
		y = qY.front();
		qY.pop();
		num = qNum.front();
		qNum.pop();
		if (x<0 || y<0 || x>MAX - 1 || y>MAX - 1)
		{
			continue;
		}
		if (Maze[y][x] != 0)
		{
			continue;
		}

		Maze[y][x] = num;
		if (x == MAX - 1 && y == MAX - 1)
		{
			break;
		}

		qX.push(x + 1);
		qY.push(y);
		qNum.push(++num);

		qX.push(x);
		qY.push(y + 1);
		qNum.push(num);

		qX.push(x - 1);
		qY.push(y);
		qNum.push(num);

		qX.push(x);
		qY.push(y - 1);
		qNum.push(num);
	}

	stack<int> sX;
	stack<int> sY;
	while (x != 0 || y != 0)
	{
		sX.push(x);
		sY.push(y);
		num--;
		if (x < MAX - 1)
		{
			if (Maze[y][x + 1] == num)
			{
				x++;
				continue;
			}
		}
		if (y < MAX - 1)
		{
			if (Maze[y + 1][x] == num)
			{
				y++;
				continue;
			}
		}
		if (x > 0)
		{
			if (Maze[y][x - 1] == num)
			{
				x--;
				continue;
			}
		}
		if (y > 0)
		{
			if (Maze[y - 1][x] == num)
			{
				y--;
				continue;
			}
		}
	}
	sX.push(x);
	sY.push(y);

	int size = sX.size();
	for (int i = 0; i < size; i++)
	{
		cout << "[" << sY.top() << ", " << sX.top() << "]" << endl;
		sX.pop();
		sY.pop();
	}

	return 0;
}