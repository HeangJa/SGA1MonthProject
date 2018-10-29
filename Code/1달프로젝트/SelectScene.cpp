#include "Game.h"
#include "SelectScene.h"


SelectScene::SelectScene()
{
}

SelectScene::~SelectScene()
{
}

HRESULT SelectScene::init()
{
	_background = IMAGEMANAGER->addImage(TEXT("SelectScene"), TEXT("Image\\selectscene.bmp"),
		800, 600, false, RGB(0, 0, 0));

	reimu = IMAGEMANAGER->addImage(TEXT("Select_Reimu"), TEXT("Image\\reimu.bmp"),
		481, 254, true, RGB(255, 255, 255));
	reimu->setX(30);
	reimu->setY(30);

	marisa = IMAGEMANAGER->addImage(TEXT("Select_Marisa"), TEXT("Image\\marisa.bmp"),
		459, 219, true, RGB(255, 255, 255));
	marisa->setX(300);
	marisa->setY(320);

	reimuAlpha = OPAQUE_;
	marisaAlpha = TRANSLUCENT_;

	currentCharacter = REIMU;

	return S_OK;
}

void SelectScene::release()
{
}

void SelectScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_UP) || KEYMANAGER->isOnceKeyDown(VK_DOWN)) 
	{
		SOUNDMANAGER->Play(TEXT("Select"), 0.2f);

		if (currentCharacter == REIMU)
		{
			currentCharacter = MARISA;
			reimuAlpha = TRANSLUCENT_;
			marisaAlpha = OPAQUE_;
		}

		else if (currentCharacter == MARISA)
		{
			currentCharacter = REIMU;
			reimuAlpha = OPAQUE_;
			marisaAlpha = TRANSLUCENT_;
		}
	}

	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		SOUNDMANAGER->Play(TEXT("Ok"), 0.2f);
		SOUNDMANAGER->Stop(TEXT("Menu"));

		PLAYER->setPlayerType(currentCharacter);

		SCENEMANAGER->ChangeScene(TEXT("InGameScene"));
	}
}

void SelectScene::render()
{
	IMAGEMANAGER->render(TEXT("SelectScene"), getMemDC(), 0, 0);
	reimu->alphaRender(getMemDC(), reimuAlpha);
	marisa->alphaRender(getMemDC(), marisaAlpha);
}
