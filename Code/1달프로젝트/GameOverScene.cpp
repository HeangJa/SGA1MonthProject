#include "Game.h"
#include "GameOverScene.h"


GameOverScene::GameOverScene()
{
	_background = IMAGEMANAGER->addImage(TEXT("GameOverScene"), TEXT("Image\\gameoverscene.bmp"),
		800, 600, false, RGB(0, 0, 0));

	gameover = IMAGEMANAGER->addImage(TEXT("GameOver"), TEXT("Image\\gameover.bmp"),
		542, 90, true, RGB(0, 0, 0));
	gameover->setX(125);
	gameover->setY(100);

	go_retry = IMAGEMANAGER->addImage(TEXT("Retry"), TEXT("Image\\retry.bmp"),
		270, 39, true, RGB(255, 255, 255));
	go_retry->setX(280);
	go_retry->setY(300);

	go_returntomenu = IMAGEMANAGER->addImage(TEXT("ReturnToMenu"), TEXT("Image\\returntomenu.bmp"),
		336, 39, true, RGB(255, 255, 255));
	go_returntomenu->setX(250);
	go_returntomenu->setY(400);
}

GameOverScene::~GameOverScene()
{
}

HRESULT GameOverScene::init()
{
	retryAlpha = OPAQUE_;

	returntomenuAlpha = TRANSLUCENT_;

	currentMenu = RETRY;

	SOUNDMANAGER->Play(TEXT("End"), 0.2f);

	return S_OK;
}

void GameOverScene::release()
{
}

void GameOverScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_UP) || KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		SOUNDMANAGER->Play(TEXT("Select"), 0.2f);

		if (currentMenu == RETRY)
		{
			currentMenu = RETURNTOMENU;
			retryAlpha = TRANSLUCENT_;
			returntomenuAlpha = OPAQUE_;
		}
		else if (currentMenu == RETURNTOMENU)
		{
			currentMenu = RETRY;
			retryAlpha = OPAQUE_;
			returntomenuAlpha = TRANSLUCENT_;
		}
	}

	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		SOUNDMANAGER->Play(TEXT("Ok"), 0.2f);

		if (currentMenu == RETRY)
		{
			SOUNDMANAGER->Stop(TEXT("End"));

			SCENEMANAGER->ChangeScene(TEXT("InGameScene"));
		}
		else if (currentMenu == RETURNTOMENU)
		{
			SOUNDMANAGER->Stop(TEXT("End"));

			SCENEMANAGER->ChangeScene(TEXT("MenuScene"));
		}

	}
}

void GameOverScene::render()
{
	IMAGEMANAGER->render(TEXT("GameOverScene"), getMemDC(), 0, 0);
	gameover->render(getMemDC());
	go_retry->alphaRender(getMemDC(), retryAlpha);
	go_returntomenu->alphaRender(getMemDC(), returntomenuAlpha);
}
