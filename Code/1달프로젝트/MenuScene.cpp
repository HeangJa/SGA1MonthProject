#include "Game.h"
#include "MenuScene.h"


MenuScene::MenuScene()
{
	_background = IMAGEMANAGER->addImage(TEXT("MenuScene"), TEXT("Image\\menuscene.bmp"),
		800, 600, false, RGB(0, 0, 0));

	title = IMAGEMANAGER->addImage(TEXT("Title"), TEXT("Image\\title.bmp"),
		515, 112, true, RGB(255, 255, 255));

	gamestart = IMAGEMANAGER->addFrameImage(TEXT("GameStart"), TEXT("Image\\gamestart.bmp"),
		642, 72, 2, 1, true, RGB(255, 255, 255));

	quit = IMAGEMANAGER->addFrameImage(TEXT("Quit"), TEXT("Image\\quit.bmp"),
		324, 62, 2, 1, true, RGB(255, 255, 255));
}

MenuScene::~MenuScene()
{
}

HRESULT MenuScene::init()
{
	title->setX(150);
	title->setY(100);
	titleAlpha = TRANSPARENT_;

	gamestart->setX(250);
	gamestart->setY(320);
	gamestart->setFrameX(ON);

	quit->setX(330);
	quit->setY(420);
	quit->setFrameX(OFF);

	currentMenu = GAME_START;

	SOUNDMANAGER->Play(TEXT("Menu"), 0.2f);

	return S_OK;
}

void MenuScene::release()
{
}

void MenuScene::update()
{
	if (titleAlpha != OPAQUE_)
	{
		titleAlpha += 3;
	}
	else
	{
		if (KEYMANAGER->isOnceKeyDown(VK_UP) || KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			SOUNDMANAGER->Stop(TEXT("Select"));
			SOUNDMANAGER->Play(TEXT("Select"), 0.2f);

			if (currentMenu == GAME_START)
			{
				currentMenu = QUIT;
				gamestart->setFrameX(OFF);
				quit->setFrameX(ON);
			}
			else if (currentMenu == QUIT)
			{
				currentMenu = GAME_START;
				gamestart->setFrameX(ON);
				quit->setFrameX(OFF);
			}
		}

		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			SOUNDMANAGER->Play(TEXT("Ok"), 0.2f);

			if (currentMenu == GAME_START)
			{
				SCENEMANAGER->ChangeScene(TEXT("SelectScene"));
			}
			else if (currentMenu == QUIT)
			{
				SOUNDMANAGER->Stop(TEXT("Menu"));
				PostQuitMessage(0);
			}

		}
	}
		
}

void MenuScene::render()
{
	IMAGEMANAGER->render(TEXT("MenuScene"), getMemDC(), 0, 0);
	title->alphaRender(getMemDC(), titleAlpha);

	if (titleAlpha == OPAQUE_) {
		gamestart->frameRender(getMemDC(), gamestart->getX(), gamestart->getY());
		quit->frameRender(getMemDC(), quit->getX(), quit->getY());
	} 	
}
