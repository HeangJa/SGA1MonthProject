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

	bossField = IMAGEMANAGER->addImage(TEXT("BossField"), TEXT("Image\\bossfield2.bmp"),
		480, 528, false, RGB(255, 255, 255));
	bossField->setX(40);
	bossField->setY(36);

	lifeImage = IMAGEMANAGER->addImage(TEXT("Life"), TEXT("Image\\life.bmp"),
		32, 32, true, RGB(255, 255, 255));
	lifeImage->setX(660);
	lifeImage->setY(123);

	stage1Image = IMAGEMANAGER->addImage(TEXT("Stage1Image"), TEXT("Image\\stage1.bmp"),
		258, 80, true, RGB(255, 255, 255));
	stage1Image->setX(150);
	stage1Image->setY(260);

	pauseBackground = IMAGEMANAGER->addImage(TEXT("PauseBackground"), TEXT("Image\\pausebackground.bmp"),
		800, 600, true, RGB(255, 255, 255));

	ig_returntogame = IMAGEMANAGER->addImage(TEXT("ReturnToGame"), TEXT("Image\\returntogame.bmp"),
		300, 42, true, RGB(255, 255, 255));
	ig_returntogame->setX(250);
	ig_returntogame->setY(200);
	pauseImageAlpha[RETURNTOGAME] = OPAQUE_;

	ig_retry = IMAGEMANAGER->addImage(TEXT("Retry"), TEXT("Image\\retry.bmp"),
		270, 39, true, RGB(255, 255, 255));
	ig_retry->setX(280);
	ig_retry->setY(300);
	pauseImageAlpha[RETRY] = TRANSLUCENT_;

	ig_returntomenu = IMAGEMANAGER->addImage(TEXT("ReturnToMenu"), TEXT("Image\\returntomenu.bmp"),
		336, 39, true, RGB(255, 255, 255));
	ig_returntomenu->setX(250);
	ig_returntomenu->setY(400);
	pauseImageAlpha[RETURNTOMENU] = TRANSLUCENT_;

	state = PLAYING;
	currentSelected = RETURNTOGAME;

	ingameStartTime = TIMEMANAGER->getWorldTime();

	highScore = 0;

	battleFieldAlpha = OPAQUE_;
	bossFieldAlpha = TRANSPARENT_;
	stage1ImageAlpha = 1;
	changingAlphaValue = 3;
	stage1ImageTimer = 0;

	filePath = "Score.txt";
	setHighScore();

	// init()
	PLAYER->init();
	ENEMYOBJECT->init();
	BOSS->init();
	COLLISION->init();

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
		// ESC�� ������ �Ͻ�����
		if (KEYMANAGER->isOnceKeyDown('P'))
		{
			SOUNDMANAGER->Pause(TEXT("Field"));
			SOUNDMANAGER->Play(TEXT("Pause"), 0.2f);
			state = PAUSE;
		}			

		// �÷��̾ ������ ���ӿ��������� �̵�
		if (PLAYER->getPlayerLife() == 0)
		{
			SOUNDMANAGER->Stop(TEXT("Field"));
			PLAYER->release();
			ENEMYOBJECT->release();
			ITEMS->release();
			SCENEMANAGER->ChangeScene(TEXT("GameOverScene"));
		}

		// �ʵ� �̵�
		for (int i = 0; i < 2; i++)
		{
			battleField[i]->setY(battleField[i]->getY() + 1);

			if (battleField[i]->getY() == (36 + 528))
				battleField[i]->setY(36 - 528);
		}
		// �ʵ� ���İ�
		if (TIMEMANAGER->setTime(ingameStartTime) > 80 - 80)
		{
			battleFieldAlpha -= 2;
			if (battleFieldAlpha < TRANSPARENT_)
				battleFieldAlpha = TRANSPARENT_;
		}
		if (battleFieldAlpha == TRANSPARENT_)
		{
			bossFieldAlpha += 2;
			if (bossFieldAlpha > OPAQUE_)
				bossFieldAlpha = OPAQUE_;
		}
			
			

		// ��������
		stageAlphaControl();

		// �÷��̾�
		PLAYER->update();

		// �� ������Ʈ
		ENEMYOBJECT->update(TIMEMANAGER->setTime(ingameStartTime));

		// ������
		ITEMS->moveItem();

		// ����
		BOSS->update(TIMEMANAGER->setTime(ingameStartTime));

		//�浹
		COLLISION->collisionCheck();

	}

	else if (state == PAUSE)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			if (currentSelected != RETURNTOGAME)
			{
				SOUNDMANAGER->Play(TEXT("Select"), 0.2f);
				pauseImageAlpha[currentSelected] = TRANSLUCENT_;
				currentSelected--;
				pauseImageAlpha[currentSelected] = OPAQUE_;
			}
		}

		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			if (currentSelected != RETURNTOMENU)
			{
				SOUNDMANAGER->Play(TEXT("Select"), 0.2f);
				pauseImageAlpha[currentSelected] = TRANSLUCENT_;
				currentSelected++;
				pauseImageAlpha[currentSelected] = OPAQUE_;
			}
		}

		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			SOUNDMANAGER->Play(TEXT("Ok"), 0.2f);
			switch(currentSelected)
			{
			case RETURNTOGAME:
				SOUNDMANAGER->Resume(TEXT("Field"));
				state = PLAYING;
				break;

			case RETRY:
				PLAYER->release();
				ENEMYOBJECT->release();
				ITEMS->release();
				init();
				state = PLAYING;
				break;

			case RETURNTOMENU:
				SOUNDMANAGER->Stop(TEXT("Field"));
				SCENEMANAGER->ChangeScene(TEXT("MenuScene"));
				break;
			}
		}
	}
}

void InGameScene::render()
{
	// �ʵ� �̹���
	for (int i = 0; i < 2; i++)
	{
		battleField[i]->alphaRender(getMemDC(), battleFieldAlpha);
	}
	bossField->alphaRender(getMemDC(), bossFieldAlpha);

	// ���
	IMAGEMANAGER->render(TEXT("BattleScene"), getMemDC(), 0, 0);
	
	// ������ info��
	info->render(getMemDC());

	NUMBERMANAGER->DrawNumber(getMemDC(), highScore, 646, 43, 1.5f, 6);
	NUMBERMANAGER->DrawNumber(getMemDC(), PLAYER->getPlayerScore(), 646, 83, 1.5f, 6);

	for (int i = 0; i < PLAYER->getPlayerLife(); i++)
	{
		lifeImage->render(getMemDC(), lifeImage->getX() + 40*i, lifeImage->getY());
	}

	NUMBERMANAGER->DrawNumber(getMemDC(), PLAYER->getPlayerPower(), 690, 163, 1.5f, 2);

	// ��������
	if (stage1ImageAlpha > 0)
		stage1Image->alphaRender(getMemDC(), stage1ImageAlpha);

	// �÷��̾�
	PLAYER->render(getMemDC());

	// �� ������Ʈ
	ENEMYOBJECT->render(getMemDC());

	// ������
	ITEMS->render(getMemDC());

	// ����
	BOSS->render(getMemDC());

	//�浹
	COLLISION->effectRender(getMemDC());

	// �Ͻ������� ��
	if(state == PAUSE)
	{
		pauseBackground->alphaRender(getMemDC(), TRANSLUCENT_);
		ig_returntogame->alphaRender(getMemDC(), pauseImageAlpha[RETURNTOGAME]);
		ig_retry->alphaRender(getMemDC(), pauseImageAlpha[RETRY]);
		ig_returntomenu->alphaRender(getMemDC(), pauseImageAlpha[RETURNTOMENU]);
	}

	// ����ð�
	TCHAR szTemp[100] = { 0, };
	_stprintf(szTemp, TEXT("����ð� : %f, %f"), TIMEMANAGER->setTime(ingameStartTime), ingameStartTime);
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
