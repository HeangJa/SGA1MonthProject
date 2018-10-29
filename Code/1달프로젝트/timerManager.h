#pragma once
#include "singletonBase.h"

class Timer;

class timerManager : public singletonBase<timerManager>
{
private:
	Timer *					_timer;

public:
	timerManager();
	~timerManager();

	HRESULT					init();
	void					release();
	void					update(float lock = 0.0f);
	void					render(HDC hdc);

	float					getElapsedTime() const;
	float					getWorldTime() const;
	float					getIngameSceneTime(float ingameStartTime) const;
};

