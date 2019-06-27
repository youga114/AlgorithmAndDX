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

//현재위치에서 일정한 방법으로 미리 이동 해보고 
//이동 가능한지 알려줌
void CanMove(Vector2& Current, queue<Vector2>& EscapeMap)
{
	Vector2 Next;
	//4방향 움직이기
	for (int dir = (int)Direction::Right; dir <= (int)Direction::Up; ++dir)
	{
		Next = Current; // 다음에 갈곳
		Next = Next + Dir[dir]; //방향 이동. Right->Down->Left->Up
		if (Next.x < 0 || Next.y < 0 || Next.x >= MAX || Next.y >= MAX) //이동 할곳이 정확한지
		{
			continue;//현재 방향 다음 방향 이동
		}

		if (maze[Next.y][Next.x] == WAYY) //미리 가보는곳이 갈수 있는지?
		{
			EscapeMap.push(Next);
		}
	}
}

int main()
{
	//방향 정보 매핑 초기화
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
	//알고리즘 시작
	while (!EscapeMap.empty())
	{
		Current = EscapeMap.front();
		EscapeMap.pop();

		maze[Current.y][Current.x] = Current.wayNum++; //현재 위치 지도에 표시

		if (Current.x == MAX - 1 && Current.y == MAX - 1)
		{
			//목적지 도착 하면 끝
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
		cout << "탈출 불가" << endl;
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