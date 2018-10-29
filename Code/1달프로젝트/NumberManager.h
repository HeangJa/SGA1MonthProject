#pragma once
#include "singletonBase.h"
#include "MacroDefine.h"

class NumberManager : public singletonBase<NumberManager>
{
private:
	Image*  numberImage[3];

	int num[NUMBERLIMIT];

public:
	NumberManager();
	~NumberManager();

	HRESULT	init();
	void release();

	void DrawNumber(HDC hdc, int num, int x, int y, float size, int length = 0);
};

