#include "Game.h"
#include "InGameScene.h"

InGameScene::InGameScene()
{
}

InGameScene::~InGameScene()
{
}

HRESULT InGameScene::init()
{
	_background = IMAGEMANAGER->addImage(TEXT("BattleScene"), TEXT("Image\\battlescene.bmp"),
		800, 600, true, RGB(255, 255, 255));

	info = IMAGEMANAGER->addImage(TEXT("Info"), TEXT("Image\\info.bmp"),
		126, 154, true, RGB(255, 255, 255));
	info->setX(522);
	info->setY(40);

	battleField[0] = IMAGEMANAGER->addImage(TEXT("BattleField"), TEXT("Image\\battlefield2.bmp"),
		480, 528, false, RGB(255, 255, 255));
	battleField[0]->setX(40);
	battleField[0]->setY(36);

	battleField[1] = IMAGEMANAGER->addImage(TEXT("BattleField2"), TEXT("Image\\battlefield2.bmp"),
		480, 528, false, RGB(255, 255, 255));
	battleField[1]->setX(40);
	battleField[1]->setY(36 - 528);

	lifeImage = IMAGEMANAGER->addImage(TEXT("Life"), TEXT("Image\\life.bmp"),
		32, 32, true, RGB(255, 255, 255));
	lifeImage->setX(660);
	lifeImage->setY(123);

	stage1Image = IMAGEMANAGER->addImage(TEXT("Stage1Image"), TEXT("Image\\stage1.bmp"),
		258, 80, true, RGB(255, 255, 255));
	stage1Image->setX(150);
	stage1Image->setY(260);

	state = PLAYING;

	ingameStartTime = TIMEMANAGER->getWorldTime();

	highScore = 0;

	stage1ImageAlpha = 1;
	changingAlphaValue = 3;
	stage1ImageTimer = 0;

	filePath = "Score.txt";
	setHighScore();

	// 오브젝트들 초기화
	PLAYER->init();
	ENEMYOBJECT->init();
	ITEMS->init();

	SOUNDMANAGER->Play(TEXT("Field"), 0.2f);

	return S_OK;
}

void InGameScene::release()
{
}

void InGameScene::update()
{
	if (state == PLAYING)
	{
		// 플레이어가 죽으면 게임오버씬으로 이동
		if (PLAYER->getPlayerLife() == 0)
		{
			SOUNDMANAGER->Stop(TEXT("Field"));
			SCENEMANAGER->ChangeScene(TEXT("GameOverScene"));
		}

		// 필드 이동
		for (int i = 0; i < 2; i++)
		{
			battleField[i]->setY(battleField[i]->getY() + 1);

			if (battleField[i]->getY() == (36 + 528))
				battleField[i]->setY(36 - 528);
		}

		// 스테이지
		stageAlphaControl();

		// 플레이어
		PLAYER->update();

		// 적 오브젝트
		ENEMYOBJECT->createEnemy(TIMEMANAGER->getIngameSceneTime(ingameStartTime));
		ENEMYOBJECT->moveEnemy();

		// 아이템
		ITEMS->moveItem();

	}

	else if (state == PAUSE)
	{

	}
}

void InGameScene::render()
{
	// 필드 이미지
	for (int i = 0; i < 2; i++)
	{
		battleField[i]->render(getMemDC());
	}

	// 배경
	IMAGEMANAGER->render(TEXT("BattleScene"), getMemDC(), 0, 0);
	
	// 오른쪽 info들
	info->render(getMemDC());

	NUMBERMANAGER->DrawNumber(getMemDC(), highScore, 646, 43, 1.5f, 6);
	NUMBERMANAGER->DrawNumber(getMemDC(), PLAYER->getPlayerScore(), 646, 83, 1.5f, 6);

	for (int i = 0; i < PLAYER->getPlayerLife(); i++)
	{
		lifeImage->render(getMemDC(), lifeImage->getX() + 40*i, lifeImage->getY());
	}

	NUMBERMANAGER->DrawNumber(getMemDC(), PLAYER->getPlayerPower(), 690, 163, 1.5f, 2);

	// 스테이지
	if (stage1ImageAlpha > 0)
		stage1Image->alphaRender(getMemDC(), stage1ImageAlpha);

	// 플레이어
	PLAYER->render(getMemDC());

	// 적 오프젝트
	ENEMYOBJECT->render(getMemDC());

	// 아이템
	ITEMS->render(getMemDC());

	// 경과시간
	TCHAR szTemp[100] = { 0, };
	_stprintf(szTemp, TEXT("경과시간 : %f"), TIMEMANAGER->getIngameSceneTime(ingameStartTime));
	TextOut(getMemDC(), 540, 300, szTemp, _tcslen(szTemp));
}

void InGameScene::setHighScore()
{
	int flag = 0;

	ifstream openFile(filePath.data());
	if (openFile.is_open())
	{
		string line;
		while (getline(openFile, line)) {
			if (flag % 2)
			{
				scoreStorage.push_back(atoi(line.c_str()));
			}
			flag++;
		}
		openFile.close();
	}

	sort(scoreStorage.begin(), scoreStorage.end(), greater<int>());
	scoreStorage_it = scoreStorage.begin();

	highScore = *scoreStorage_it;
}

void InGameScene::stageAlphaControl()
{
	if (stage1ImageAlpha > 0)
	{
		stage1ImageAlpha += changingAlphaValue;

		if (stage1ImageAlpha > 254)
		{
			stage1ImageAlpha = OPAQUE_;
			changingAlphaValue = 0;
			stage1ImageTimer++;
			
			if (stage1ImageTimer == 120)
			{
				stage1ImageTimer = 0;
				changingAlphaValue = -3;
			}
		}

		if (stage1ImageAlpha < 0)
			stage1ImageAlpha = 0;
	}
}
