#pragma once

class Image;

static Image* _backBuffer = IMAGEMANAGER->addImage(TEXT("backBuffer"), WINSIZEX, WINSIZEY);

class gameNode
{
private:
	HDC		_hdc;
	bool	_managerInit;

protected:
	Image*	_background;

public:

	Image*	getBackBuffer() { return _backBuffer; }
	HDC		getMemDC() { return _backBuffer->getMemDC(); }
	HDC		getHDC() { return _hdc; }

	virtual HRESULT init();
	virtual HRESULT init(bool bInit);

	virtual void	update();
	virtual void	render();
	virtual void	release();

	LRESULT			MainProc(HWND, UINT, WPARAM, LPARAM);

	gameNode();
	virtual ~gameNode();
};

