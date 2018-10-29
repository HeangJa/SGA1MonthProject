#pragma once

class Timer
{
private:
	bool			_isHardware;			// QPF로의 리턴 여부에 따른 flag
	float			_timeScale;				// 측정된 시간차(간격) = delta Time 
	float			_timeElapsed;			// 시간흐름-> tickCount 

	//__int64 : 64비트 정수 = long long

	__int64			_curTime;				// 현재 신호를 보내는 빈도
	__int64			_lastTime;				// cpu에 신호를 보내고 받을때까지의 간격
	__int64			_periodFrequency;		// cpu 클럭? 

	unsigned long	_frameRate;				// 프레임 속도
	unsigned long	_FPSframeCount;			// 프레임 카운터

	float			_FPSTimeElapsed;		// 프레임의 시간 흐름
	float			_worldTime;				// 컴파일된 후 경과 시간

public:
	Timer();
	~Timer();

	HRESULT			init();
	void			tick(float lockFPS = 0.0f);
	unsigned long	getFrameRate(TCHAR* str = NULL);

	inline float	getElapsedTime() const { return _timeElapsed; }
	inline float    getWorldTime() const { return _worldTime; }
};

