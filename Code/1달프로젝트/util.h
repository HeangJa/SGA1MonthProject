#pragma once

#define PI		3.141592654f
#define PI2		PI * 2

namespace UTIL
{
	float getDistance(float startX, float startY, float endX, float endY);
	float getAngle(float x1, float y1, float x2, float y2);
}