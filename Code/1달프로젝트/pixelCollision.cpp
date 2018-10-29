#include "Game.h"
#include "pixelCollision.h"

pixelCollision::pixelCollision()
{
}

pixelCollision::~pixelCollision()
{
}

HRESULT pixelCollision::init()
{
	IMAGEMANAGER->addImage(TEXT("BackGround"), TEXT("mountain.bmp"),
		WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	_ball = IMAGEMANAGER->addImage(TEXT("Ball"), TEXT("ball.bmp"),
		60, 60, true, RGB(255, 0, 255));

	_x = WINSIZEX / 2 - 150;
	_y = WINSIZEY / 2 + 400;

	_rc = RectMakeCenter(_x, _y, _ball->getWidth(), _ball->getHeight());

	_probeY = _y + _ball->getHeight() / 2;

	return S_OK;
}

void pixelCollision::release()
{
}

void pixelCollision::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		_x -= 3;
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		_x += 3;

	_rc = RectMakeCenter(_x, _y, _ball->getWidth(), _ball->getHeight());

	_probeY = _y + _ball->getHeight() / 2;

	for (int i = _probeY - 100; i < _probeY + 100; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage(TEXT("BackGround"))->getMemDC(), _x, i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (!(r == 255 && g == 0 && b == 255))
		{
			_y = i - _ball->getHeight() / 2;
			break;
		}
	}
}

void pixelCollision::render()
{
	IMAGEMANAGER->render(TEXT("BackGround"), getMemDC());
	_ball->render(getMemDC(), _rc.left, _rc.top);
}

bool pixelCollision::GetLandY(Image * pImage, RECT & _rc, 
	int _depth, COLORREF _color)
{
	int rTemp = GetRValue(_color);
	int gTemp = GetGValue(_color);
	int bTemp = GetBValue(_color);

	_rc = RectMakeCenter(_x, _y, _ball->getWidth(), _ball->getHeight());

	_probeY = _y + _ball->getHeight() / 2;

	for (int i = _probeY - _depth; i < _probeY + _depth; ++i)
	{
		COLORREF color = GetPixel(pImage->getMemDC(), _x, i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (!(r == rTemp && g == gTemp && b == bTemp))
		{
			_y = i - _ball->getHeight() / 2;
			break;
		}
	}

	return false;
}
