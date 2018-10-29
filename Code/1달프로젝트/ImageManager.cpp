#include "Game.h"
#include "ImageManager.h"
#include "Image.h"

ImageManager::ImageManager()
{
}

ImageManager::~ImageManager()
{
}

HRESULT ImageManager::init()
{
	return S_OK;
}

void ImageManager::release()
{
	deleteAll();
}

Image * ImageManager::addImage(string strKey, int width, int height)
{
	Image* img = findImage(strKey);
	if (img)
		return img;

	img = new Image;

	if (FAILED(img->init(width, height)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	_mImageList.insert(std::make_pair(strKey, img));

	return img;
}

Image * ImageManager::addImage(string strKey, const TCHAR * fileName, int width, int height, bool trans, COLORREF transColor)
{
	Image* img = findImage(strKey);
	if (img)
		return img;

	img = new Image;

	if (FAILED(img->init(fileName, width, height, trans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	_mImageList.insert(std::make_pair(strKey, img));

	return img;
}

Image * ImageManager::addImage(string strKey, const TCHAR * fileName, float x, float y, int width, int height, bool trans, COLORREF transColor)
{
	Image* img = findImage(strKey);
	if (img)
		return img;

	img = new Image;

	if (FAILED(img->init(fileName, x, y, width, height, trans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	_mImageList.insert(std::make_pair(strKey, img));

	return img;
}

Image * ImageManager::addFrameImage(string strKey, const TCHAR * fileName, float x, float y, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor)
{
	Image* img = findImage(strKey);
	if (img)
		return img;

	img = new Image;

	if (FAILED(img->init(fileName, x, y, width, height, frameX, frameY, trans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	_mImageList.insert(std::make_pair(strKey, img));

	return img;
}

Image * ImageManager::addFrameImage(string strKey, const TCHAR * fileName, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor)
{
	Image* img = findImage(strKey);
	if (img)
		return img;

	img = new Image;

	if (FAILED(img->init(fileName, width, height, frameX, frameY, trans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	_mImageList.insert(std::make_pair(strKey, img));

	return img;
}

Image * ImageManager::findImage(string strKey)
{
	mapImageIter key = _mImageList.find(strKey);

	if (key != _mImageList.end())
	{
		return key->second;
	}

	return NULL;
}

bool ImageManager::deleteImage(string strKey)
{
	mapImageIter key = _mImageList.find(strKey);

	if (key != _mImageList.end())
	{
		key->second->release();
		SAFE_DELETE(key->second);
		_mImageList.erase(key);
		return true;
	}
	return false;
}

bool ImageManager::deleteAll()
{
	mapImageIter it = _mImageList.begin();

	for (; it != _mImageList.end();)
	{
		if (it->second != NULL)
		{
			it->second->release();
			SAFE_DELETE(it->second);
			it = _mImageList.erase(it);
		}
		else
			++it;
	}
	_mImageList.clear();

	return true;
}

void ImageManager::render(string strKey, HDC hdc)
{
	Image* img = findImage(strKey);
	if (img)
		img->render(hdc);
}

void ImageManager::render(string strKey, HDC hdc, int destX, int destY)
{
	Image* img = findImage(strKey);
	if (img)
		img->render(hdc, destX, destY);
}

void ImageManager::render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	Image* img = findImage(strKey);
	if (img)
		img->render(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight);
}

void ImageManager::frameRender(string strKey, HDC hdc, int destX, int destY)
{
	Image* img = findImage(strKey);
	if (img)
		img->frameRender(hdc, destX, destY);
}

void ImageManager::frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	Image* img = findImage(strKey);
	if (img)
		img->frameRender(hdc, destX, destY, currentFrameX, currentFrameY);
}

void ImageManager::loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	Image* img = findImage(strKey);
	if (img)
		img->loopRender(hdc, drawArea, offsetX, offsetY);
}
