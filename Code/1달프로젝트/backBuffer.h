#pragma once
class backBuffer
{

	typedef struct tagbackBufferInfo
	{
		HDC			hMemDC;
		HBITMAP		hBit;
		HBITMAP		hOldBit;
		float		x;
		float		y;
		int			width;
		int			height;

		tagbackBufferInfo()
		{
			hMemDC = NULL;
			hBit = NULL;
			hOldBit = NULL;
			x = 0;
			y = 0;
			width = 0;
			height = 0;
		}
	}backBuffer_INFO, *LPbackBuffer_INFO;

private:
	LPbackBuffer_INFO	_backBufferInfo;
public:
	backBuffer();
	~backBuffer();

	HRESULT init(int _width, int _height);

	void release();
	void render(HDC _hdc, int _destX, int _dextY);

	inline HDC getMemDC() { return _backBufferInfo->hMemDC; }

};

