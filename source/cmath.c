#include "cmath.h"

Point GetPointInCircle(int x, int y, int z, double radius, int rad)
{
    Point retPoint;

	retPoint.x = f32tofloat(x + radius * cosLerp(degreesToAngle(rad)));
	retPoint.y = f32tofloat(y + radius * sinLerp(degreesToAngle(rad)));
	retPoint.z = f32tofloat(z + radius * sinLerp(degreesToAngle(rad)));

	return retPoint;
}