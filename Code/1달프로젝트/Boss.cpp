#include "Game.h"
#include "Boss.h"


Boss::Boss()
{
}

Boss::~Boss()
{
}

void Boss::init()
{
	bossImage = IMAGEMANAGER->addFrameImage(TEXT("Boss"), TEXT("Image\\boss.bmp"),
		257, 198, 4, 3, true, RGB(255, 255, 255));

	bossbackgroundImage = IMAGEMANAGER->addImage(TEXT("BossBackground"), TEXT("Image\\bossbackground.bmp"),
		249, 235, true, RGB(255, 255, 255));

	bossHpBar = IMAGEMANAGER->addImage(TEXT("BossHpBar"), TEXT("Image\\bosshpbar.bmp"),
		440, 5, false, RGB(255, 255, 255));
	bossHpBar->setX(60);
	bossHpBar->setY(60);

	bossBullet0 = IMAGEMANAGER->addFrameImage(TEXT("BossBullet0"), TEXT("Image\\e_bullet2.bmp"),
		256, 16, 16, 1, true, RGB(255, 255, 255));

	bossBullet1 = IMAGEMANAGER->addFrameImage(TEXT("BossBullet1"), TEXT("Image\\e_bullet.bmp"),
		258, 192, 8, 6, true, RGB(255, 255, 255));

	bossState = NOTCREATE;
	bossPattern = APPEAR;
	bossDiameter = 64;
	bossSpeed = 1.f;
	bossAngle = PI * 3 / 4;
	bossHp = 1200;

	bossPosX = 280;
	bossPosY = 0;

	bossMotionTimer = 0;
	bossStayTimer = 0;
	isBossStop = false;

	bossHpBarPercent = 100;

	bossBackgroundAlpha = TRANSLUCENT_;
	bossBackgroundAlphaSpeed = 0.5f;
}

void Boss::release()
{
}

void Boss::update(float ingameCurrentTime)
{
	if (ingameCurrentTime > 90 - 90 && bossState == NOTCREATE)
		bossState = CREATE;

	if (bossPosX > F_LEFT && bossPosX < F_RIGHT &&
		bossPosY + (bossDiameter / 2) > F_UP && bossPosY < F_DOWN && bossState == CREATE)
	{
		bossState = ALIVE;
	}

	if (bossPattern == APPEAR)
	{
		if (bossPosY > 150)
		{
			isBossStop = true;
			bossAngle = PI * 5 / 4;
			bossSpeed = 0;
			bossPattern = PATTERN0;
		}			
		else
			bossAngle = PI * 3 / 2;
	}
	else if (bossPattern == PATTERN0)
	{
		if (bossPosX < 200)
		{
			bossSpeed = 0.f;
			bossAngle = PI * 2;
			isBossStop = true;
		}

		else if (bossPosX > 400)
		{
			bossSpeed = 0.f;
			bossAngle = PI * 3 / 4;
			isBossStop = true;
		}

		else if (bossPosY < 150)
		{
			bossSpeed = 0.f;
			bossAngle = PI * 5 / 4;
			isBossStop = true;
		}

		if (isBossStop == true)
		{
			bossStayTimer++;

			if (bossStayTimer == 60) 
			{
				bossSpeed = 1.f;
				isBossStop = false;
				bossStayTimer = 0;
			}
		}
	}
	else if (bossPattern == PATTERN1)
	{

	}
	else if (bossPattern == PATTERN2)
	{

	}
	else if (bossPattern == PATTERN3)
	{

	}

	// 이동
	bossPosX += (cosf(bossAngle) * bossSpeed);
	bossPosY += (-sinf(bossAngle) * bossSpeed);

	// 각도에 따른 애니메이션
	// 왼쪽
	if (bossAngle > (PI / 2) && bossAngle < (3 * PI / 2)
		&& bossSpeed > 0)
	{
		if (!(bossImage->getFrameX() >= 0 && bossImage->getFrameX() <= 2))
			bossImage->setFrameX(0);

		if (!(bossImage->getFrameY() == 2))
			bossImage->setFrameY(2);

		if (bossMotionTimer == MOTION_DELAY * 3)
		{
			bossMotionTimer = 0;
			bossImage->setFrameX(bossImage->getFrameX() + 1);

			if (bossImage->getFrameX() == 3)
				bossImage->setFrameX(0);
		}

		bossMotionTimer++;
	}

	// 오른쪽
	else if (!(bossAngle > (PI / 2) && bossAngle < (3 * PI / 2))
		&& bossSpeed > 0)
	{
		if (!(bossImage->getFrameX() >= 0 && bossImage->getFrameX() <= 2))
			bossImage->setFrameX(0);

		if (!(bossImage->getFrameY() == 1))
			bossImage->setFrameY(1);

		if (bossMotionTimer == MOTION_DELAY * 3)
		{
			bossMotionTimer = 0;
			bossImage->setFrameX(bossImage->getFrameX() + 1);

			if (bossImage->getFrameX() == 3)
				bossImage->setFrameX(0);
		}

		bossMotionTimer++;
	}

	// 좌우 이동 아닐 때
	else
	{
		if (!(bossImage->getFrameX() >= 0 && bossImage->getFrameX() <= 3))
			bossImage->setFrameX(0);

		if (!(bossImage->getFrameY() == 0))
			bossImage->setFrameY(0);

		if (bossMotionTimer == (MOTION_DELAY * 3))
		{
			bossMotionTimer = 0;
			bossImage->setFrameX(bossImage->getFrameX() + 1);

			if (bossImage->getFrameX() == 4)
				bossImage->setFrameX(0);
		}

		bossMotionTimer++;
	}

	// 보스 배경 알파값 변경
	if (bossState == ALIVE)
	{
		if (bossBackgroundAlpha < 80 || bossBackgroundAlpha > 130)
			bossBackgroundAlphaSpeed *= -1;

		bossBackgroundAlpha -= bossBackgroundAlphaSpeed;
	}
}

void Boss::render(HDC hdc)
{
	if (bossState == ALIVE)
	{
		if (!(bossPattern == APPEAR))
		{
			bossbackgroundImage->alphaRender(hdc, bossPosX - 125, bossPosY - 118, bossBackgroundAlpha);
			bossHpBar->render(hdc, bossHpBar->getX(), bossHpBar->getY(), 0, 0, 440 * bossHpBarPercent / 100, 5);
		}

		bossImage->frameRender(hdc, bossPosX - (bossDiameter / 2), bossPosY - (bossDiameter / 2),
			bossImage->getFrameX(), bossImage->getFrameY());
	}
	
	TCHAR szTemp[100] = { 0, };
	_stprintf_s(szTemp, sizeof(szTemp), TEXT("위치 : %f, %f, %d"), bossPosX, bossPosY, bossStayTimer);
	TextOut(hdc, 540, 500, szTemp, _tcslen(szTemp));

	_stprintf_s(szTemp, sizeof(szTemp), TEXT("프레임 : %d, %d, %d"), bossImage->getFrameX(), bossImage->getFrameY(), bossMotionTimer);
	TextOut(hdc, 540, 550, szTemp, _tcslen(szTemp));
}

void Boss::createBoss(float ingameCurrentTime)
{
}

void Boss::moveBoss(float ingameCurrentTime)
{
}

void Boss::createBossBullet(float ingameCurrentTime)
{
}

void Boss::moveBossBullet(float ingameCurrentTime)
{
}
