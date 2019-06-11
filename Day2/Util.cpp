#include "Util.h"



Util::Util()
{
}


Util::~Util()
{
}

int Util::Clamp(int Current, int Min, int Max)
{
	if (Current < Min)
	{
		return Min;
	}

	if (Current > Max)
	{
		return Max;
	}

	return Current;
}
