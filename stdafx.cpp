#include "DXUT.h"

VOID ResizeArray(int ** array, int size)
{
	if (*array)
	{
		delete[](*array);
		(*array) = nullptr;
	}

	(*array) = new int[size];
}
