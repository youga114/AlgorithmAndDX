#include <stdio.h>

template<typename T>
T add(T a, T b)
{
	return a + b;
}

template<typename T, typename Y>
class Cal
{
public:
	T add(T a, T b)
	{
		return a + b;
	}
};

int main()
{
	int a = 2;
	int b = 3;
	float c = 2.3f;
	float d = 1.3f;

	Cal<int,int> calInt;
	Cal<float,float> calFloat;

	printf("a + b = %d\n", calInt.add(a, b));
	printf("c + d = %f\n", calFloat.add(c, d));

	return 0;
}