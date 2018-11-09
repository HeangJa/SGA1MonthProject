#include "Game.h"
#include "GameClearScene.h"


GameClearScene::GameClearScene()
{
}

GameClearScene::~GameClearScene()
{
}

HRESULT GameClearScene::init()
{
	_background = IMAGEMANAGER->addImage(TEXT("GameClearScene"), TEXT("Image\\gameclearscene.bmp"),
		800, 600, false, RGB(0, 0, 0));

	player = IMAGEMANAGER->addFrameImage(TEXT("Player"), TEXT("Image\\info.bmp"),
		126, 154, 1, 4, true, RGB(255, 255, 255));
	player->setFrameY(2);

	score = IMAGEMANAGER->addFrameImage(TEXT("Score"), TEXT("Image\\info.bmp"),
		126, 154, 1, 4, true, RGB(255, 255, 255));
	score->setFrameY(1);

	cursor = IMAGEMANAGER->addImage(TEXT("Cursor"), TEXT("Image\\cursor.bmp"),
		30, 10, true, RGB(255, 255, 255));
	cursor->setX(201);
	cursor->setY(215);
	cursorAlpha = OPAQUE_;

	highscore = IMAGEMANAGER->addImage(TEXT("HighScore"), TEXT("Image\\highscore.bmp"),
		378, 106, true, RGB(0, 0, 0));
	highscore->setX(220);
	highscore->setY(50);

	state = SAVESCORE;

	for (int i = 0; i < SAVENAMELENGTH; i++)
		saveName[i] = 65;

	cursorTimer = 0;
	currentCursor = 0;

	filePath = "Score.txt";

	ZeroMemory(showHighScoreName, SAVENAMELENGTH * SHOWHIGHSCORELIMIT);
	showHighScoreLength = 0;

	SOUNDMANAGER->Play(TEXT("GameClear"), 0.2f);

	return S_OK;
}

void GameClearScene::release()
{
}

void GameClearScene::update()
{
	if (state == SAVESCORE)
	{
		cursorTimer++;
		if (cursorTimer == 30)
		{
			cursorTimer = 0;
			if (cursorAlpha == OPAQUE_)
				cursorAlpha = TRANSPARENT_;
			else if (cursorAlpha == TRANSPARENT_)
				cursorAlpha = OPAQUE_;
		}

		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			saveName[currentCursor]++;
			if (saveName[currentCursor] > 90)
				saveName[currentCursor] = 65;
		}

		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			saveName[currentCursor]--;
			if (saveName[currentCursor] < 65)
				saveName[currentCursor] = 90;
		}

		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			cursor->setX(cursor->getX() + 32);

			currentCursor++;
			if (currentCursor == 3)
			{
				currentCursor = 0;
				cursor->setX(201);
				state = SHOWHIGHSCORE;

				ofstream writeFile(filePath.data(), ios_base::app);
				if (writeFile.is_open())
				{
					writeFile << saveName[0] << saveName[1] << saveName[2] << endl;
					writeFile << PLAYER->getPlayerScore() << endl;
					writeFile.close();
				}

				loadScore();
				setScore();
			}
		}
	}

	else if (state == SHOWHIGHSCORE)
	{
		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			SOUNDMANAGER->Stop(TEXT("GameClear"));
			SCENEMANAGER->ChangeScene(TEXT("MenuScene"));
		}
	}
}

void GameClearScene::render()
{
	IMAGEMANAGER->render(TEXT("GameClearScene"), getMemDC(), 0, 0);

	TCHAR szTemp[100] = { 0, };
	HFONT font1, font2, oldFont;
	font1 = CreateFont(
		40,							// 높이		(0 = 종횡비를 일정하게 적용)
		0,							// 넓이		(0 = 종횡비를 일정하게 적용)
		0,							// 기울기	(실제 각도로 기술, 3시방향이 0도)
		0,							// 방향
		40,							// 굵기		(0 ~ 1000) 일반적인 굵기가 40
		false,						// 이탈리체	(bool값)
		0,							// 밑줄		(bool값)
		0,							// 취소선	(bool값)
		HANGUL_CHARSET,				// 문자셋
		0, 0, 0, 0,					// 논리적 폰트 정보에 대한 물리적 폰트 정보의 매칭, 자간
		TEXT("HY견고딕"));			// 폰트

	oldFont = (HFONT)SelectObject(getMemDC(), font1);
	
	if (state == SAVESCORE)
	{
		player->frameRender(getMemDC(), 180, 120);
		score->frameRender(getMemDC(), 430, 120);
		cursor->alphaRender(getMemDC(), cursor->getX(), cursor->getY(), cursorAlpha);

		_stprintf_s(szTemp, sizeof(szTemp), TEXT("%c%c%c"), saveName[0], saveName[1], saveName[2]);
		TextOut(getMemDC(), 200, 180, szTemp, _tcslen(szTemp));

		NUMBERMANAGER->DrawNumber(getMemDC(), PLAYER->getPlayerScore(), 400, 175, 2, 6);
	}

	else if(state == SHOWHIGHSCORE)
	{
		mHighScore_it = mHighScore.begin();

		IMAGEMANAGER->render(TEXT("HighScore"), getMemDC());
		
		if (showHighScoreLength > 5)
			showHighScoreLength = SHOWHIGHSCORELIMIT;

		for (int i = 0; i < showHighScoreLength; i++, mHighScore_it++)
		{
			_stprintf_s(szTemp, sizeof(szTemp), TEXT("%c%c%c"), showHighScoreName[i][0], showHighScoreName[i][1], showHighScoreName[i][2]);
			TextOut(getMemDC(), 200, 185 + 70 * i, szTemp, _tcslen(szTemp));

			NUMBERMANAGER->DrawNumber(getMemDC(), mHighScore_it->first, 400, 180 + 70 * i, 2, 6);
		}
	}

	SelectObject(getMemDC(), oldFont);
	DeleteObject(font1);
}

void GameClearScene::loadScore()
{
	int flag		= 0;
	int tempName	= 0;
	int tempScore	= 0;

	ifstream openFile(filePath.data());
	if (openFile.is_open())
	{
		string line;
		while (getline(openFile, line)) {
			if (flag % 2 == 0)
			{
				tempName = atoi(line.c_str());
			}

			else
			{
				tempScore = atoi(line.c_str());
				mHighScore.insert(pair<int, int>(tempScore, tempName));
			}
			flag++;
		}
		showHighScoreLength = mHighScore.size();
		openFile.close();
	}
}

// 저장 이름 구하기(6자리 숫자를 2자리씩 나눠서 변수에 저장, 상위 5개의 점수만 보여줌)
void GameClearScene::setScore()
{
	int name[SAVENAMELENGTH] = { 0, };
	mHighScore_it = mHighScore.begin();
	for (int i = 0; i < SHOWHIGHSCORELIMIT; i++, mHighScore_it++)
	{
		name[0] = (mHighScore_it->second) / 10000;
		name[2] = (mHighScore_it->second) % 100;

		name[1] = ((mHighScore_it->second) - (name[0] * 10000)) / 100;

		for (int j = 0; j < 3; j++)
		{
			showHighScoreName[i][j] = name[j];
		}
	}
}