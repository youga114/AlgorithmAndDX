#include <iostream>
#include <queue>

using namespace std;

#define MAX 10
#define WAYY 500
#define WALL 999
#define BLOCK 2
#define PATH 3

class Vector2
{
public:
	Vector2(int wayNum=100) : x(0), y(0), wayNum(wayNum) {}
	int x;
	int y;
	int wayNum;

	Vector2 operator+(const Vector2& RightHandSide)
	{
		Vector2 Result(wayNum);
		Result.x = this->x + RightHandSide.x;
		Result.y = this->y + RightHandSide.y;

		return Result;
	}
};

enum class Direction
{
	Right = 0,
	Down = 1,
	Left = 2,
	Up = 3
};

Vector2 Dir[4];


int maze[MAX][MAX] =
{
	{WAYY, WAYY, WAYY, WAYY, WAYY, WALL, WAYY, WAYY, WAYY, WALL},
	{WALL, WALL, WAYY, WALL, WAYY, WALL, WAYY, WALL, WAYY, WALL},
	{WALL, WALL, WAYY, WALL, WAYY, WALL, WAYY, WALL, WAYY, WALL},
	{WALL, WALL, WAYY, WALL, WAYY, WALL, WAYY, WALL, WAYY, WALL},
	{WALL, WALL, WAYY, WALL, WAYY, WAYY, WAYY, WALL, WAYY, WAYY},
	{WALL, WALL, WAYY, WALL, WALL, WALL, WALL, WALL, WALL, WAYY},
	{WALL, WALL, WAYY, WAYY, WAYY, WAYY, WAYY, WAYY, WALL, WAYY},
	{WALL, WALL, WALL, WALL, WALL, WALL, WALL, WAYY, WALL, WAYY},
	{WALL, WALL, WALL, WALL, WALL, WALL, WALL, WAYY, WALL, WALL},
	{WALL, WALL, WALL, WALL, WALL, WALL, WALL, WAYY, WAYY, WAYY},
};

//������ġ���� ������ ������� �̸� �̵� �غ��� 
//�̵� �������� �˷���
void CanMove(Vector2& Current, queue<Vector2>& EscapeMap)
{
	Vector2 Next;
	//4���� �����̱�
	for (int dir = (int)Direction::Right; dir <= (int)Direction::Up; ++dir)
	{
		Next = Current; // ������ ����
		Next = Next + Dir[dir]; //���� �̵�. Right->Down->Left->Up
		if (Next.x < 0 || Next.y < 0 || Next.x >= MAX || Next.y >= MAX) //�̵� �Ұ��� ��Ȯ����
		{
			continue;//���� ���� ���� ���� �̵�
		}

		if (maze[Next.y][Next.x] == WAYY) //�̸� �����°��� ���� �ִ���?
		{
			EscapeMap.push(Next);
		}
	}
}

int main()
{
	//���� ���� ���� �ʱ�ȭ
	Dir[static_cast<int>(Direction::Right)].x = 1;
	Dir[(int)Direction::Right].y = 0;

	Dir[(int)Direction::Down].x = 0;
	Dir[(int)Direction::Down].y = 1;

	Dir[(int)Direction::Left].x = -1;
	Dir[(int)Direction::Left].y = 0;

	Dir[(int)Direction::Up].x = 0;
	Dir[(int)Direction::Up].y = -1;

	Vector2 Current;

	queue<Vector2> EscapeMap;
	EscapeMap.push(Current);
	//�˰��� ����
	while (!EscapeMap.empty())
	{
		Current = EscapeMap.front();
		EscapeMap.pop();

		maze[Current.y][Current.x] = Current.wayNum++; //���� ��ġ ������ ǥ��

		if (Current.x == MAX - 1 && Current.y == MAX - 1)
		{
			//������ ���� �ϸ� ��
			cout << Current.wayNum - 1 << endl;
			break;
		}
		else
		{
			CanMove(Current, EscapeMap);
		}
	}

	if (Current.x != MAX - 1 && Current.y != MAX - 1)
	{
		cout << "Ż�� �Ұ�" << endl;
	}

	for (int y = 0; y < MAX; ++y)
	{
		for (int x = 0; x < MAX; ++x)
		{
			cout << maze[y][x] << " ";
		}
		cout << endl;
	}



	return 0;
}