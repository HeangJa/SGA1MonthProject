#pragma once
#include "singletonBase.h"

class Image;

class ImageManager : public singletonBase<ImageManager>
{
private:
	typedef map<string, Image*>				mapImageList;
	typedef map<string, Image*>::iterator	mapImageIter;

private:
	mapImageList			_mImageList;

public:
	ImageManager();
	~ImageManager();


	HRESULT	init();
	void release();

	Image* addImage(string strKey, int width, int height);
	Image* addImage(string strKey, const TCHAR* fileName, int width, int height, bool trans, COLORREF transColor);
	Image* addImage(string strKey, const TCHAR* fileName, float x, float y, int width, int height, 
		bool trans, COLORREF transColor);

	Image* addFrameImage(string strKey, const TCHAR* fileName, float x, float y, int width, int height,
		int frameX, int frameY, bool trans, COLORREF transColor);
	Image* addFrameImage(string strKey, const TCHAR* fileName, int width, int height,
		int frameX, int frameY, bool trans, COLORREF transColor);

	Image* findImage(string strKey);

	bool   deleteImage(string strKey);

	bool   deleteAll();

	void   render(string strKey, HDC hdc);
	void   render(string strKey, HDC hdc, int destX, int destY);
	void   render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	void   frameRender(string strKey, HDC hdc, int destX, int destY);
	void   frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	void   loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);

};

