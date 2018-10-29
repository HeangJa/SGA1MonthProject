#include "Game.h"
#include "Timer.h"
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

Timer::Timer()
{
}

Timer::~Timer()
{
}

HRESULT Timer::init()
{
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&_periodFrequency))
	{
		_isHardware = true;

		QueryPerformanceCounter((LARGE_INTEGER*)&_lastTime);

		_timeScale = 1.0f / _periodFrequency;
	}
	else
	{
		_isHardware = false;

		_lastTime = timeGetTime();
		_timeScale = 0.001f;
	}

	_frameRate = 0;
	_FPSframeCount = 0;
	_FPSTimeElapsed = 0;
	_worldTime = 0;

	return S_OK;
}

void Timer::tick(float lockFPS)
{
	if (_isHardware)
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
	}
	else
	{
		_curTime = timeGetTime();
	}

	_timeElapsed = (_curTime - _lastTime) * _timeScale;

	if (lockFPS > 0.0f)
	{
		while (_timeElapsed < 1.0f / lockFPS)
		{
			if (_isHardware)
				QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
			else
				_curTime = timeGetTime();

			_timeElapsed = (_curTime - _lastTime) * _timeScale;
		}
	}

	_lastTime = _curTime;
	_FPSframeCount++;
	_FPSTimeElapsed += _timeElapsed;
	_worldTime += _timeElapsed;
	
	if (_FPSTimeElapsed > 1.0f)
	{
		_frameRate = _FPSframeCount;
		_FPSframeCount = 0;
		_FPSTimeElapsed = 0.0f;
	}
}

unsigned long Timer::getFrameRate(TCHAR * str)
{
	if (str != NULL)
	{
		_stprintf(str, TEXT("FPS : %d"), _frameRate);
	}

	return _frameRate;
}
