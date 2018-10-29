#include "Game.h"
#include "backBuffer.h"

backBuffer::backBuffer() : _backBufferInfo(NULL)
{
}

backBuffer::~backBuffer()
{
}

HRESULT backBuffer::init(int _width, int _height)
{
	HDC hdc = GetDC(g_hWnd);

	_backBufferInfo = new backBuffer_INFO;
	_backBufferInfo->hMemDC = CreateCompatibleDC(hdc);
	_backBufferInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _width, _height);
	_backBufferInfo->hOldBit = (HBITMAP)SelectObject(_backBufferInfo->hMemDC, _backBufferInfo->hBit);
	_backBufferInfo->width = _width;
	_backBufferInfo->height = _height;

	if (_backBufferInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}

	ReleaseDC(g_hWnd, hdc);

	return S_OK;
}

void backBuffer::release()
{
	if (_backBufferInfo)
	{
		SelectObject(_backBufferInfo->hMemDC, _backBufferInfo->hOldBit);
		DeleteObject(_backBufferInfo->hBit);
		DeleteDC(_backBufferInfo->hMemDC);

		SAFE_DELETE(_backBufferInfo);
	}
}

void backBuffer::render(HDC hdc, int _destX, int _destY)
{
	BitBlt(hdc,												// 복사할 DC
		_destX, _destY,										// 복사를 할 좌표
		_backBufferInfo->width, _backBufferInfo->height,	// 복사될 DC
		_backBufferInfo->hMemDC, 0, 0, SRCCOPY);			// 복사되는 영역
}