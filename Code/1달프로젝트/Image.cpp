#include "Game.h"
#include "Image.h"
#include "Animation.h"

#pragma comment(lib, "msimg32.lib")

Image::Image() : _imageInfo(NULL),
				_fileName(NULL),
				_trans(false),
				_transColor(RGB(0,0,0))
{
}

Image::~Image()
{
}

HRESULT Image::init(int width, int height)
{
	if (_imageInfo != NULL)
		release();

	// 화면 DC를 받아와서
	HDC hdc = GetDC(g_hWnd);

	_imageInfo				= new IMAGE_INFO;
	_imageInfo->loadType	= LOAD_EMPTY;
	_imageInfo->resID		= 0;
	_imageInfo->hMemDC		= CreateCompatibleDC(hdc);
	_imageInfo->hBit		= (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOldBit		= (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width		= width;
	_imageInfo->height		= height;

	_fileName	= NULL;
	_trans		= FALSE;
	_transColor = RGB(0, 0, 0);

	// 알파블랜드 설정
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOldBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	// 비트맵 생성에 실패하는 경우가 발생하면
	if (_imageInfo->hBit == NULL)
	{
		release();
		return E_FAIL;    // 실패했다고 리턴
	}

	// 얻어온 화면 DC를 해제
	ReleaseDC(g_hWnd, hdc);

	return S_OK;
}

HRESULT Image::init(const TCHAR* fileName, int width, int height, BOOL trans, COLORREF transColor)
{
	if (_imageInfo != NULL)
		release();

	HDC hdc = GetDC(g_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOldBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	size_t len = _tcslen(fileName);

	_fileName = new TCHAR[len + 1];
	_tcscpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	// 알파블랜드 설정
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOldBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	if (_imageInfo->hBit == NULL)
	{
		release();
		return E_FAIL;
	}

	ReleaseDC(g_hWnd, hdc);
	return S_OK;
}

HRESULT Image::init(const TCHAR * fileName, float x, float y, int width, int height, BOOL trans, COLORREF transColor)
{
	if (_imageInfo != NULL)
		release();

	HDC hdc = GetDC(g_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOldBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;

	size_t len = _tcslen(fileName);

	_fileName = new TCHAR[len + 1];
	_tcscpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	// 알파블랜드 설정
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOldBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	if (_imageInfo->hBit == NULL)
	{
		release();
		return E_FAIL;
	}

	ReleaseDC(g_hWnd, hdc);

	return S_OK;
}

HRESULT Image::init(const TCHAR * fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	if (_imageInfo != NULL)
		release();

	HDC hdc = GetDC(g_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOldBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;

	size_t len = _tcslen(fileName);

	_fileName = new TCHAR[len + 1];
	_tcscpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	// 알파블랜드 설정
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOldBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	if (_imageInfo->hBit == NULL)
	{
		release();
		return E_FAIL;
	}

	ReleaseDC(g_hWnd, hdc);

	return S_OK;
}

HRESULT Image::init(const TCHAR * fileName, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	if (_imageInfo != NULL)
		release();

	HDC hdc = GetDC(g_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOldBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;

	size_t len = _tcslen(fileName);

	_fileName = new TCHAR[len + 1];
	_tcscpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	// 알파블랜드 설정
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOldBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	if (_imageInfo->hBit == NULL)
	{
		release();
		return E_FAIL;
	}

	ReleaseDC(g_hWnd, hdc);

	return S_OK;
}

void Image::release()
{
	if (_imageInfo)
	{
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOldBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		SAFE_DELETE(_imageInfo);
		SAFE_DELETE(_fileName);

		_trans = false;
		_transColor = RGB(0, 0, 0);
	}
}

void Image::setTransColor(BOOL trans, COLORREF transColor)
{
	_trans = trans;
	_transColor = transColor;
}

void Image::render(HDC hdc)
{
	if (_trans)
	{
		GdiTransparentBlt
		(
			hdc,
			_imageInfo->x,
			_imageInfo->y,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_transColor);
	}
	else
	{
		BitBlt(hdc, 
			_imageInfo->x,
			_imageInfo->y,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0, 0, SRCCOPY);
	}
}

void Image::render(HDC hdc, int destX, int destY)
{
	if (_trans)
	{
		GdiTransparentBlt
		(
			hdc,
			destX,
			destY,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_transColor);
	}
	else
	{
		BitBlt(hdc, destX, destY,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0, 0, SRCCOPY);
	}
}

//								그려질 목적지 좌표		복사될 위치			복사될 이미지 크기
void Image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,
			destX,					// 복사될 좌표 X
			destY,					// 복사될 좌표 Y
			sourWidth,				// 복사될 가로 크기
			sourHeight,				// 복사될 세로 크기
			_imageInfo->hMemDC,
			sourX, sourY,			// 복사해올 좌표
			sourWidth,				// 복사해올 가로 크기
			sourHeight,				// 복사해올 세로 크기
			_transColor);
	}
	else
	{
		BitBlt(
			hdc, destX, destY,
			sourWidth, sourHeight,
			_imageInfo->hMemDC,
			sourX, sourY,
			SRCCOPY);
	}
}

void Image::loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	static int nLoopCount = 0;
	static int nRenderCount = 1;

	// 화면 밖으로 나간 부분에 대한 보정
	if (offsetX < 0)
	{
		offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
	}

	if (offsetY < 0)
	{
		offsetY = _imageInfo->height + (offsetY % _imageInfo->height);
	}

	// offset 영역을 받아올 변수
	int sourWidth;
	int sourHeight;

	// 그려주는 영역
	RECT rcDest;
	RECT rcSour;

	// 그려주는 영역을 잡아준다.
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawAreaX;
	int drawAreaH = drawArea->bottom - drawAreaY;

	// 루프는 y축부터
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		rcSour.top = (y + offsetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;

		sourHeight = rcSour.bottom - rcSour.top;

		// 그려주는 영역의 높이보다 y축이 크면
		if (y + sourHeight > drawAreaH)
		{
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		// 화면 밖으로 나간 영역만큼 뿌려줄 위치에 반영
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		// x축 루프...
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			rcSour.left = (x + offsetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;

			sourWidth = rcSour.right - rcSour.left;

			if (x + sourWidth > drawAreaW)
			{
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			render(hdc,
				rcDest.left, rcDest.top,		// 뿌려줄 위치 좌표
				rcSour.left, rcSour.top,		// 가져올 이미지 위치 좌표
				rcSour.right - rcSour.left,		// 이미지의 가로
				rcSour.bottom - rcSour.top);	// 이미지의 세로

			nRenderCount++;
		}
	}

	nLoopCount++;
}

void Image::frameRender(HDC hdc, int destX, int destY)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,
			destX,					// 복사될 좌표 X
			destY,					// 복사될 좌표 Y
			_imageInfo->frameWidth,	// 복사될 가로 크기
			_imageInfo->frameHeight,// 복사될 세로 크기
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth, // 복사해올 좌표
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,	// 복사해올 가로 크기
			_imageInfo->frameHeight,// 복사해올 세로 크기
			_transColor);
	}
	else
	{
		BitBlt(
			hdc, destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth, // 복사해올 좌표
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			SRCCOPY);
	}
}

void Image::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (_trans)
	{
		GdiTransparentBlt(
			hdc,
			destX,					// 복사될 좌표 X
			destY,					// 복사될 좌표 Y
			_imageInfo->frameWidth,	// 복사될 가로 크기
			_imageInfo->frameHeight,// 복사될 세로 크기
			_imageInfo->hMemDC,
			currentFrameX * _imageInfo->frameWidth, // 복사해올 좌표
			currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,	// 복사해올 가로 크기
			_imageInfo->frameHeight,// 복사해올 세로 크기
			_transColor);
	}
	else
	{
		BitBlt(
			hdc, destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			currentFrameX * _imageInfo->frameWidth, // 복사해올 좌표
			currentFrameY * _imageInfo->frameHeight,
			SRCCOPY);
	}
}

void Image::aniRender(HDC hdc, int destX, int destY, Animation * ani)
{
	render(hdc, destX, destY, ani->getFramePos().x, ani->getFramePos().y,
		ani->getFrameWidth(), ani->getFrameHeight());
}

void Image::alphaRender(HDC hdc, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		// 알파블랜드를 적용할 이미지 정보를 복사
		BitBlt(_blendImage->hMemDC, 0, 0,
			_imageInfo->width, _imageInfo->height,
			hdc, _imageInfo->x, _imageInfo->y,
			SRCCOPY);

		// 복사해온 이미지 정보에서 트랜스컬러 제거
		GdiTransparentBlt(_blendImage->hMemDC, 0, 0,
			_imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0,
			_imageInfo->width, _imageInfo->height,
			_transColor);

		// 트랜스컬러 제거까지 적용된 이미지에 블래딩 함수를 사용해서 
		// 알파블랜드를 적용
		AlphaBlend(hdc, _imageInfo->x, _imageInfo->y,
			_imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0,
			_imageInfo->width, _imageInfo->height,
			_blendFunc);
	}
	else
	{
		AlphaBlend(hdc, _imageInfo->x, _imageInfo->y,
			_imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0,
			_imageInfo->width, _imageInfo->height,
			_blendFunc);
	}
}

void Image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		// 알파블랜드를 적용할 이미지 정보를 복사
		BitBlt(_blendImage->hMemDC, 0, 0,
			_imageInfo->width, _imageInfo->height,
			hdc, destX, destY, SRCCOPY);

		// 복사해온 이미지 정보에서 트랜스컬러 제거
		GdiTransparentBlt(_blendImage->hMemDC, 0, 0,
			_imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0,
			_imageInfo->width, _imageInfo->height,
			_transColor);

		// 트랜스컬러 제거까지 적용된 이미지에 블래딩 함수를 사용해서 
		// 알파블랜드를 적용
		AlphaBlend(hdc, destX, destY,
			_imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0,
			_imageInfo->width, _imageInfo->height,
			_blendFunc);
	}
	else
	{
		AlphaBlend(hdc, destX, destY,
			_imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0,
			_imageInfo->width, _imageInfo->height,
			_blendFunc);
	}
}

void Image::alphaRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		// 알파블랜드를 적용할 이미지 정보를 복사
		BitBlt(_blendImage->hMemDC, 0, 0,
			_imageInfo->width, _imageInfo->height,
			hdc, destX, destY, SRCCOPY);

		// 복사해온 이미지 정보에서 트랜스컬러 제거
		GdiTransparentBlt(_blendImage->hMemDC, 0, 0,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC, 
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_transColor);

		// 트랜스컬러 제거까지 적용된 이미지에 블래딩 함수를 사용해서 
		// 알파블랜드를 적용
		GdiAlphaBlend(hdc, destX, destY,
			_imageInfo->frameWidth, 
			_imageInfo->frameHeight,
			_blendImage->hMemDC, 
			0, 0,
			_imageInfo->frameWidth, 
			_imageInfo->frameHeight,
			_blendFunc);
	}
	else
	{
		GdiAlphaBlend(hdc, destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC, 
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth, 
			_imageInfo->frameHeight,
			_blendFunc);
	}
}



