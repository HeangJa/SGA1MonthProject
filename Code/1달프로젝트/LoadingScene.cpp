#include "Game.h"
#include "LoadingScene.h"


LoadingScene::LoadingScene()
{
}

LoadingScene::~LoadingScene()
{
}

HRESULT LoadingScene::init()
{
	_background = IMAGEMANAGER->addImage(TEXT("LoadingScene"), TEXT("Image\\loadingscene.bmp"),
		800, 600, false, RGB(0, 0, 0));
	loading		= IMAGEMANAGER->addImage(TEXT("Loading"), TEXT("Image\\loading.bmp"),
		123, 54, true, RGB(255, 255, 255));
	loading->setX(650);
	loading->setY(520);

	loadingAlpha = 0;
	alphaSpeed = 3;
	loadingTime = 0;

	return S_OK;
}

void LoadingScene::release()
{
}

void LoadingScene::update()
{
	// 로딩 이미지 알파값 변경
	loadingAlpha += alphaSpeed;

	if (loadingAlpha > 253 || loadingAlpha < 3)
		alphaSpeed = -alphaSpeed;

	// 로딩 씬 지속시간 설정
	loadingTime++;
	if (loadingTime == 300)
	{
		loadingTime = 0;
		SCENEMANAGER->ChangeScene(TEXT("MenuScene"));
	}
}

void LoadingScene::render()
{
	IMAGEMANAGER->render(TEXT("LoadingScene"), getMemDC(), 0, 0);
	loading->alphaRender(getMemDC(), loadingAlpha);
}
