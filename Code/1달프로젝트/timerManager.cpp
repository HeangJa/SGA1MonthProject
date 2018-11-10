#include "Game.h"
#include "timerManager.h"
#include "Timer.h" 

timerManager::timerManager() : _timer(NULL)
{
}

timerManager::~timerManager() 
{
}

HRESULT timerManager::init()
{
	_timer = new Timer;
	_timer->init();

	return S_OK;
}

void timerManager::release()
{
	SAFE_DELETE(_timer);
}

void timerManager::update(float lock)
{
	if (_timer != NULL)
	{
		_timer->tick(lock);
	}
}

void timerManager::render(HDC hdc)
{
	TCHAR szTemp[256] = { 0, };
	SetBkMode(hdc, TRANSPARENT);

#if defined(DEBUG_MODE)
	{
		_stprintf(szTemp, TEXT("FPS : %d"), _timer->getFrameRate());
		TextOut(hdc, 0, 0, szTemp, _tcslen(szTemp));

		_stprintf(szTemp, TEXT("World time : %f"), _timer->getWorldTime());
		TextOut(hdc, 0, 20, szTemp, _tcslen(szTemp));

		_stprintf(szTemp, TEXT("Elapsed Time : %f"), _timer->getElapsedTime());
		TextOut(hdc, 0, 40, szTemp, _tcslen(szTemp));
	}
#else
	_stprintf(szTemp, TEXT("FPS : %d"), _timer->getFrameRate());
	TextOut(hdc, 0, 0, szTemp, _tcslen(szTemp));
#endif	// DEBUG_MODE
}

float timerManager::getElapsedTime() const
{
	return _timer->getElapsedTime();
}

float timerManager::getWorldTime() const
{
	return _timer->getWorldTime();
}

float timerManager::setTime(float time) const
{
	return _timer->getWorldTime() - time;
}
