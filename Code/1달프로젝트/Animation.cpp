#include "Game.h"
#include "Animation.h"


Animation::Animation() 
	: _frameNum(0),
	_frameWidth(0),
	_frameHeight(0),
	_loop(false),
	_frameUpdateSec(0),
	_elapsedSec(0),
	_nowPlayIndex(0),
	_play(false),
	_value(0),
	_callFunc(0),
	_callFuncParam(0)
{
}

Animation::~Animation()
{
}

bool Animation::init(int totalW, int totalH, int frameW, int frameH)
{
	_frameWidth = frameW;
	int _frameNumWidth = totalW / _frameWidth;

	_frameHeight = frameH;
	int _frameNumHeight = totalH / _frameHeight;

	_frameNum = _frameNumWidth * _frameNumHeight;

	for (int i = 0; i < _frameNumHeight; ++i)
	{
		for (int j = 0; j < _frameNumWidth; ++j)
		{
			POINT framePos;
			framePos.x = j * _frameWidth;
			framePos.y = i * _frameHeight;

			_frameList.push_back(framePos);
		}
	}

	setDefPlayFrame();

	return true;
}

bool Animation::init(Image * image)
{
	init(image->getWidth(), image->getHeight(), 
		image->getFrameWidth(), image->getFrameHeight());
	return true;
}

void Animation::release()
{
}

void Animation::setDefPlayFrame(bool reverse, bool loop)
{
	_loop = loop;
	_playList.clear();

	if (reverse)
	{
		for (int i = 0; i < _frameNum; ++i)
		{
			_playList.push_back(i);
		}
		for (int i = _frameNum - 1; i >= 0; --i)
		{
			_playList.push_back(i);
		}
	}
	else
	{
		for (int i = 0; i < _frameNum; ++i)
		{
			_playList.push_back(i);
		}
	}
}

// AniManager 작업을 위해 추가된 부분
void Animation::setDefPlayFrame(CALL_FUNC func, bool reverse, bool loop)
{
	_callFunc = func;
	setDefPlayFrame(reverse, loop);
}

void Animation::setDefPlayFrame(CALL_FUNC_PARAM func, void * val, bool reverse, bool loop)
{
	_value = val;
	_callFuncParam = func;
	setDefPlayFrame(reverse, loop);
}

void Animation::setPlayFrame(int * playArr, int arrLen, bool loop)
{
	_loop = loop;
	_playList.clear();

	for (int i = 0; i < arrLen; ++i)
	{
		_playList.push_back(playArr[i]);
	}
}

void Animation::setPlayFrame(CALL_FUNC func, int * playArr, int arrLen, bool loop)
{
	_callFunc = func;
	setPlayFrame(playArr, arrLen, loop);
}

void Animation::setPlayFrame(CALL_FUNC_PARAM func, void * val, int * playArr, int arrLen, bool loop)
{
	_value = val;
	_callFuncParam = func;
	setPlayFrame(playArr, arrLen, loop);
}

void Animation::setPlayFrame(int start, int end, bool reverse, bool loop)
{
	_loop = loop;
	_playList.clear();

	if (start == end)
	{
		_playList.clear();
		stop();
		return;
	}
	
	if(start > end)
	{
		if (reverse)
		{
			for (int i = start; i >= end; --i)
			{
				_playList.push_back(i);
			}
			for (int i = end + 1; i < start; ++i)
			{
				_playList.push_back(i);
			}
		}
		else
		{
			for (int i = start; i >= end; --i)
			{
				_playList.push_back(i);
			}
		}
	}
	else
	{
		if (reverse)
		{
			for (int i = start; i < end; ++i)
			{
				_playList.push_back(i);
			}
			for (int i = end-1; i > start; --i)
			{
				_playList.push_back(i);
			}
		}
		else
		{
			for (int i = start; i < end; ++i)
			{
				_playList.push_back(i);
			}
		}
	}
}

void Animation::setPlayFrame(CALL_FUNC func, int start, int end, bool reverse, bool loop)
{
	_callFunc = func;
	setPlayFrame(start, end, reverse, loop);
}

void Animation::setPlayFrame(CALL_FUNC_PARAM func, void * val, int start, int end, bool reverse, bool loop)
{
	_value = val;
	_callFuncParam = func;
	setPlayFrame(start, end, reverse, loop);
}

void Animation::setFPS(int framePerSec)
{
	_frameUpdateSec = 1.0f / (float)framePerSec;
}

void Animation::frameUpdate(float elapsedTime)
{
	if (_play)
	{
		_elapsedSec += elapsedTime;

		if (_elapsedSec >= _frameUpdateSec)
		{
			_elapsedSec -= _frameUpdateSec;
			_nowPlayIndex++;

			if (_nowPlayIndex == _playList.size())
			{
				if (_loop)
					_nowPlayIndex = 0;
				else
				{
					_nowPlayIndex--;
					_play = false;

					//AniManager 작업으로 추가된 부분
					if (_callFunc)
					{
						_callFunc();
					}
					else if (_callFuncParam)
					{
						_callFuncParam(_value);
					}
				}
			}
		}
	}
}

void Animation::start()
{
	_play = true;
	_nowPlayIndex = 0;
}

void Animation::stop()
{
	_play = false;
	_nowPlayIndex = 0;
}

void Animation::pause()
{
	_play = false;
}

void Animation::resume()
{
	_play = true;
}
