#pragma once

class Animation;

class Image
{
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE,	// 리소스로부터
		LOAD_FILE,		// 파일로부터
		LOAD_EMPTY,		// 빈 비트맵으로부터
		LOAD_END
	};

	typedef struct tagImageInfo
	{
		DWORD	resID;
		HDC		hMemDC;
		HBITMAP hBit;
		HBITMAP hOldBit;
		float	x;				// 이미지 x 좌표 
		float   y;				// 이미지 y 좌표
		int		width;
		int     height;

		int		currentFrameX;	// 현재 프레임 x
		int		currentFrameY;	// 현재 프레임 y
		int		maxFrameX;		// 최대 프레임 x
		int		maxFrameY;		// 최대 프레임 y
		int		frameWidth;		// 프레임 가로크기
		int		frameHeight;	// 프레임 세로크기
		BYTE	loadType;
		RECT	boundingBox;	// 바운딩박스

		tagImageInfo()
		{
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOldBit = NULL;
			width = 0;
			height = 0;
			x = 0.f;
			y = 0.f;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			boundingBox = RectMake(0, 0, 0, 0);
			loadType = LOAD_RESOURCE;
		}
	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO		_imageInfo;		// 이미지의 정보 구조체
	TCHAR*				_fileName;		// 파일 이름
	BOOL				_trans;			// 트랜스컬러 유무	
	COLORREF			_transColor;	// 트랜스컬러
	BLENDFUNCTION		_blendFunc;		// 알파블랜드 처리에 관한 함수 정보
	LPIMAGE_INFO		_blendImage;	// 알파블랜드를 적용할 이미지 정보

public:
	Image();
	~Image();

	// 빈 비트맵 이미지 초기화
	HRESULT init(int width, int height);

	// 파일로 부터의 이미지 초기화
	HRESULT init(const TCHAR* fileName, int width, int height,
		BOOL trans = FALSE, COLORREF transColor = FALSE);

	//(7월 25일 추가)
	HRESULT init(const TCHAR* fileName, float x, float y,
		int width, int height, BOOL trans = FALSE,
		COLORREF transColor = FALSE);

	HRESULT init(const TCHAR* fileName, float x, float y, 
		int width, int height, int frameX, int frameY,
		BOOL trans = FALSE, COLORREF transColor = FALSE);

	HRESULT init(const TCHAR* fileName, int width, int height, 
		int frameX, int frameY, BOOL trans = FALSE, 
		COLORREF transColor = FALSE);
	//(7월 25일 추가)

	// 이미지 릴리즈
	void release();

	// 트랜스처리를 다른 픽셀값으로 바꿀 경우 사용
	void setTransColor(BOOL trans, COLORREF transColor);

	//(7월 25일 추가)
	void render(HDC hdc);
	//(7월 25일 추가)

	// 랜더링함수,  뿌릴DC  뿌릴곳의 X  뿌릴곳의 Y
	void render(HDC hdc, int destX, int destY);

	// 랜더링함수, 뿌릴DC  뿌릴곳의 X  뿌릴곳의 Y  복사해올 소스의 위치      소스의 넓이, 높이
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	// 루프 랜더 함수
	void loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);

	// 프레임 랜더 함수 (7월 25일 추가)
	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);
	// (7월 25일 추가)

	void aniRender(HDC hdc, int destX, int destY, Animation* ani);


	// 알파랜더 함수
	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);

	
	inline HDC getMemDC() { return _imageInfo->hMemDC; }

	inline HBITMAP getBitmap() { return _imageInfo->hBit; }

	//======================================================================================
	// (7월 26일 추가)

 	inline void		setX(float x) { _imageInfo->x = x; }
	inline float	getX() { return _imageInfo->x; }

	inline void		setY(float y) { _imageInfo->y = y; }
	inline float	getY() { return _imageInfo->y; }

	inline void		setCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}

	inline float	getCenterX()
	{
		return _imageInfo->maxFrameX <= 0 ? _imageInfo->x + (_imageInfo->width / 2) : _imageInfo->x + (_imageInfo->frameWidth / 2);
	}

	inline float	getCenterY()
	{
		return _imageInfo->maxFrameY <= 0 ? _imageInfo->y + (_imageInfo->height / 2) : _imageInfo->y + (_imageInfo->frameHeight / 2);
	}


	inline int getWidth() { return _imageInfo->width; }
	inline int getHeight() { return _imageInfo->height; }

	inline RECT boundingBox()
	{
		RECT rc = RectMake(int(_imageInfo->x),
			int(_imageInfo->y),
			int(_imageInfo->frameWidth),
			int(_imageInfo->frameHeight));

		return rc;
	}

	inline void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX)
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}

	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY)
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}

	inline int getMaxFrameX() { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY() { return _imageInfo->maxFrameY; }

	inline int getFrameX() { return _imageInfo->currentFrameX; }
	inline int getFrameY() { return _imageInfo->currentFrameY; }

	inline int getFrameWidth() { return _imageInfo->frameWidth; }
	inline int getFrameHeight() { return _imageInfo->frameHeight; }
};

