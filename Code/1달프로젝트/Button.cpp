#include "Game.h"
#include "Button.h"

Button::Button()
{
}

Button::~Button()
{
}

bool Button::Init(const string imageName, int x, int y,
	POINT btnDownFramePoint, POINT btnUpFramePoint, FUNC pFunc)
{
	_callBackFunc	= pFunc;
	_direction = BUTTONDIR_NULL;

	_x = x;
	_y = y;

	_btnDownFramePoint = btnDownFramePoint;
	_btnUpFramePoint = btnUpFramePoint;

	_imageName = imageName;
	_image = IMAGEMANAGER->findImage(imageName);
	_rc = RectMakeCenter(x, y, _image->getFrameWidth(), _image->getFrameHeight());

	return true;
}

void Button::Release()
{
}

void Button::Update()
{
	if (PtInRect(&_rc, g_ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_direction = BUTTONDIR_DOWN;
		}
		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON) && _direction == BUTTONDIR_DOWN)
		{
			_direction = BUTTONDIR_UP;
			(*_callBackFunc)();
		}
	}
	else
		_direction = BUTTONDIR_NULL;
}

void Button::Render(HDC hdc)
{
	switch (_direction)
	{
	case BUTTONDIR_NULL:
	case BUTTONDIR_UP:
		_image->frameRender(hdc, _rc.left, _rc.top, 
			_btnUpFramePoint.x, _btnUpFramePoint.y);
		break;
	case BUTTONDIR_DOWN:
		_image->frameRender(hdc, _rc.left, _rc.top, 
			_btnDownFramePoint.x, _btnDownFramePoint.y);
		break;
	}
}
