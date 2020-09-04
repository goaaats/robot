#ifndef GOAT_CMATH
#define GOAT_CMATH

#include <NEMain.h>
#include <nds/ndstypes.h>

typedef struct
{
	double x;
	double y;
	double z;
} Point;

Point GetPointInCircle(int x, int y, int z, double radius, int rad);

#endif