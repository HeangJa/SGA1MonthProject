#include "Game.h"
#include "NumberManager.h"


NumberManager::NumberManager()
{
}

NumberManager::~NumberManager()
{
}

HRESULT NumberManager::init()
{
	numberImage[0] = IMAGEMANAGER->addFrameImage(TEXT("Number1"), TEXT("Image\\num(S).bmp"), 190, 22, 10, 1,
		true, RGB(255, 255, 255));
	numberImage[0]->setFrameY(0);
	
	numberImage[1] = IMAGEMANAGER->addFrameImage(TEXT("Number1.5"), TEXT("Image\\num(M).bmp"), 285, 33, 10, 1,
		true, RGB(255, 255, 255));
	numberImage[1]->setFrameY(0);

	numberImage[2] = IMAGEMANAGER->addFrameImage(TEXT("Number2"), TEXT("Image\\num(L).bmp"), 380, 44, 10, 1,
		true, RGB(255, 255, 255));
	numberImage[2]->setFrameY(0);

	return S_OK;
}

void NumberManager::release()
{
	delete numberImage;
}

void NumberManager::DrawNumber(HDC hdc, int number, int x, int y, float size, int length)
{
	assert(length != 0);

	// 표현할 숫자 길이
	if (length == 2)
	{
		for (int i = 0; i < 2; i++)
		{
			num[i] = number / (pow(10, 1 - i));
			number -= num[i] * (pow(10, 1 - i));

			numberImage[0]->setFrameX(num[i]);

			if (size == 1)
			{
				numberImage[0]->setFrameX(num[i]);
				IMAGEMANAGER->frameRender(TEXT("Number1"), hdc, x + (17 * i * size), y);
			}
			else if (size == 1.5)
			{
				numberImage[1]->setFrameX(num[i]);
				IMAGEMANAGER->frameRender(TEXT("Number1.5"), hdc, x + (17 * i * size), y);
			}

			else if (size == 2)
			{
				numberImage[2]->setFrameX(num[i]);
				IMAGEMANAGER->frameRender(TEXT("Number2"), hdc, x + (17 * i * size), y);
			}
		}
	}

	if (length == 6)
	{
		for (int i = 0; i < NUMBERLIMIT; i++)
		{
			num[i] = number / (pow(10, 5 - i));
			number -= num[i] * (pow(10, 5 - i));

			if (size == 1)
			{
				numberImage[0]->setFrameX(num[i]);
				IMAGEMANAGER->frameRender(TEXT("Number1"), hdc, x + (17 * i * size), y);
			}				
			else if (size == 1.5)
			{
				numberImage[1]->setFrameX(num[i]);
				IMAGEMANAGER->frameRender(TEXT("Number1.5"), hdc, x + (17 * i * size), y);
			}
				
			else if (size == 2)
			{
				numberImage[2]->setFrameX(num[i]);
				IMAGEMANAGER->frameRender(TEXT("Number2"), hdc, x + (17 * i * size), y);
			}				
		}
	}
}
