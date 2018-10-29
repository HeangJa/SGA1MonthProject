#pragma once

#include "singletonBase.h"
#include <time.h>

class randomFunction : public singletonBase< randomFunction >
{
public:
	randomFunction()
	{
		srand(GetTickCount());
	}

	~randomFunction(){}

	inline int getInt(int _Num) { return rand() % _Num; }
	inline int getFromIntTo(int _fromNum, int _toNum)
	{
		return rand() % (_toNum - _fromNum + 1) + _fromNum;
	}

	//=========================================================

	inline float getFloat(float num)
	{
		return (float)rand() / (float)num;
	}

	inline float getFromFloatTo(float fromNum, float toNum)
	{
		float rnd = (float)rand() / (float)RAND_MAX;
		return (rnd * (toNum - fromNum) + fromNum);
	}
};