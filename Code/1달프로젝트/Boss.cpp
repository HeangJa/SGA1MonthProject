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

	bossBullet0 = IMAGEMANAGER->addFrameImage(TEXT("BossBullet0"), TEXT("Image\\e_Bullet2.bmp"),
		256, 16, 16, 1, true, RGB(255, 255, 255));

	bossBullet1 = IMAGEMANAGER->addFrameImage(TEXT("BossBullet1"), TEXT("Image\\e_Bullet.bmp"),
		258, 192, 8, 6, true, RGB(255, 255, 255));

	bossState = NOTCREATE;
	bossPattern = APPEAR;
	bossDiameter = 64;
	bossSpeed = 1.f;
	bossAngle = PI * 3 / 4;
	bossHp = BOSS_MAXHP;

	bossPosX = 280;
	bossPosY = 0;

	bossMotionTimer = 0;
	bossStayTimer = 0;
	bossBulletBreakTimer = 0;
	createBossBulletTimer = 0;
	isBossStop = false;
	isBossBulletBreak = true;
	isCreateBossBullet = true;

	bossHpBarPercent = 100;

	bossBackgroundAlpha = TRANSLUCENT_;
	bossBackgroundAlphaSpeed = 0.5f;

	bulletTermTimer = 0;
	bulletCountNum = 0;
	changingBulletAngle = 0;

	setBullet();
}

void Boss::release()
{
}

void Boss::update(float ingameCurrentTime)
{
	moveBoss(ingameCurrentTime);

	if(bossState == ALIVE)
		createBossBullet(ingameCurrentTime);
	if(b_Bullet.size() > 0)
		moveBossBullet(ingameCurrentTime);
}

void Boss::render(HDC hdc)
{
	TCHAR szTemp[100] = { 0, };
	if (bossState == ALIVE)
	{
		if (!(bossPattern == APPEAR))
		{
			bossbackgroundImage->alphaRender(hdc, bossPosX - 125, bossPosY - 118, bossBackgroundAlpha);
			bossHpBar->render(hdc, bossHpBar->getX(), bossHpBar->getY(), 0, 0, 440 * bossHpBarPercent / 100, 5);
		}

		bossImage->frameRender(hdc, bossPosX - (bossDiameter / 2), bossPosY - (bossDiameter / 2),
			bossImage->getFrameX(), bossImage->getFrameY());

		// 디버그용
		if (KEYMANAGER->isStayKeyDown(VK_LSHIFT))
			EllipseMakeCenter(hdc, bossPosX, bossPosY, bossDiameter, bossDiameter);
	}

	b_Bullet_it = b_Bullet.begin();
	int i = 0;
	for (; b_Bullet_it != b_Bullet.end(); b_Bullet_it++, i++)
	{
		if ((*b_Bullet_it).type == 0 || (*b_Bullet_it).type == 1 || (*b_Bullet_it).type == 2)
		{
			bossBullet0->frameRender(hdc, (*b_Bullet_it).x - 8, (*b_Bullet_it).y - 8, 
				(*b_Bullet_it).imageFrameX, (*b_Bullet_it).imageFrameY);
		}

		if ((*b_Bullet_it).type == 3 || (*b_Bullet_it).type == 4)
		{
			bossBullet1->frameRender(hdc, (*b_Bullet_it).x - 16, (*b_Bullet_it).y - 16,
				(*b_Bullet_it).imageFrameX, (*b_Bullet_it).imageFrameY);
		}

		// 디버그용
		if (KEYMANAGER->isStayKeyDown(VK_LSHIFT))
			EllipseMakeCenter(hdc, (*b_Bullet_it).x, (*b_Bullet_it).y, (*b_Bullet_it).diameter, (*b_Bullet_it).diameter);
	}

	
	_stprintf_s(szTemp, sizeof(szTemp), TEXT("보스위치 : %f, %f"), bossPosX, bossPosY);
	TextOut(hdc, 540, 450, szTemp, _tcslen(szTemp));
	
	_stprintf_s(szTemp, sizeof(szTemp), TEXT("보스 탄 개수 : %d, %d"), b_Bullet.size(), bulletTermTimer);
	TextOut(hdc, 540, 480, szTemp, _tcslen(szTemp));

	_stprintf_s(szTemp, sizeof(szTemp), TEXT("각도변화 : %f"), changingBulletAngle);
	TextOut(hdc, 540, 510, szTemp, _tcslen(szTemp));
}

void Boss::setBullet()
{
	// bulletType
	bossBullet[0].type = 0;
	bossBullet[0].state = NOTCREATE;
	bossBullet[0].x = 0.f;
	bossBullet[0].y = 0.f;
	bossBullet[0].diameter = 16;
	bossBullet[0].angle = 0;
	bossBullet[0].speed = 4;
	bossBullet[0].imageFrameX = 1;
	bossBullet[0].imageFrameY = 0;

	bossBullet[1].type = 1;
	bossBullet[1].state = NOTCREATE;
	bossBullet[1].x = 0.f;
	bossBullet[1].y = 0.f;
	bossBullet[1].diameter = 16;
	bossBullet[1].angle = 0;
	bossBullet[1].speed = 4;
	bossBullet[1].imageFrameX = 1;
	bossBullet[1].imageFrameY = 0;

	bossBullet[2].type = 2;
	bossBullet[2].state = NOTCREATE;
	bossBullet[2].x = 0.f;
	bossBullet[2].y = 0.f;
	bossBullet[2].diameter = 16;
	bossBullet[2].angle = 0;
	bossBullet[2].speed = 6;
	bossBullet[2].imageFrameX = 14;
	bossBullet[2].imageFrameY = 0;

	bossBullet[3].type = 3;
	bossBullet[3].state = NOTCREATE;
	bossBullet[3].x = 0.f;
	bossBullet[3].y = 0.f;
	bossBullet[3].diameter = 32;
	bossBullet[3].angle = 0;
	bossBullet[3].speed = 3;
	bossBullet[3].imageFrameX = 1;
	bossBullet[3].imageFrameY = 1;

	bossBullet[4].type = 4;
	bossBullet[4].state = NOTCREATE;
	bossBullet[4].x = 0.f;
	bossBullet[4].y = 0.f;
	bossBullet[4].diameter = 32;
	bossBullet[4].angle = 0;
	bossBullet[4].speed = 3;
	bossBullet[4].imageFrameX = 3;
	bossBullet[4].imageFrameY = 1;
}

void Boss::moveBoss(float ingameCurrentTime)
{
	if (ingameCurrentTime > 90 - 90 && bossState == NOTCREATE)
		bossState = CREATE;

	if (bossPosX > F_LEFT && bossPosX < F_RIGHT &&
		bossPosY + (bossDiameter / 2) > F_UP && bossPosY < F_DOWN && bossState == CREATE)
	{
		bossState = ALIVE;
	}

	// 보스 체력에 따른 패턴 변화
	if (bossHp < 0 && bossPattern == PATTERN3)
	{
		SOUNDMANAGER->Play(TEXT("BossDead"), 0.2f);
		bossPattern = BOSS_DEAD;
		bossStayTimer = 0;
		PLAYER->setPlayerScore(PLAYER->getPlayerScore() + PATTERN3_SCORE);
	}		
	else if (bossHp < BOSS_PATTERN_HP && bossPattern == PATTERN2)
	{
		SOUNDMANAGER->Play(TEXT("EnemyDead"), 0.2f);
		bossPattern = PATTERN3;
		for (int i = 0; i < PATTERN3 * 5; i++)
		{
			ITEMS->createItem(BLUE_ITEM, RND->getFromIntTo(bossPosX - 50, bossPosX + 50),
				RND->getFromIntTo(bossPosY - 50, bossPosY + 50));
			ITEMS->createItem(RED_ITEM, RND->getFromIntTo(bossPosX - 50, bossPosX + 50),
				RND->getFromIntTo(bossPosY - 50, bossPosY + 50));
		}
		bossStayTimer = -1;
		isBossBulletBreak = true;
		PLAYER->setPlayerScore(PLAYER->getPlayerScore() + PATTERN2_SCORE);
	}
	else if (bossHp < BOSS_PATTERN_HP * 2 && bossPattern == PATTERN1)
	{
		SOUNDMANAGER->Play(TEXT("EnemyDead"), 0.2f);
		bossPattern = PATTERN2;
		for (int i = 0; i < PATTERN2 * 5; i++)
		{
			ITEMS->createItem(BLUE_ITEM, RND->getFromIntTo(bossPosX - 50, bossPosX + 50),
				RND->getFromIntTo(bossPosY - 50, bossPosY + 50));
			ITEMS->createItem(RED_ITEM, RND->getFromIntTo(bossPosX - 50, bossPosX + 50),
				RND->getFromIntTo(bossPosY - 50, bossPosY + 50));
		}
		bossStayTimer = -1;
		isBossBulletBreak = true;
		PLAYER->setPlayerScore(PLAYER->getPlayerScore() + PATTERN1_SCORE);
	}
	else if (bossHp < BOSS_PATTERN_HP * 3 && bossPattern == PATTERN0)
	{
		SOUNDMANAGER->Play(TEXT("EnemyDead"), 0.2f);
		bossPattern = PATTERN1;
		for (int i = 0; i < PATTERN1 * 5; i++)
		{
			ITEMS->createItem(BLUE_ITEM, RND->getFromIntTo(bossPosX - 50, bossPosX + 50),
				RND->getFromIntTo(bossPosY - 50, bossPosY + 50));
			ITEMS->createItem(RED_ITEM, RND->getFromIntTo(bossPosX - 50, bossPosX + 50),
				RND->getFromIntTo(bossPosY - 50, bossPosY + 50));
		}
		bossStayTimer = -1;
		isBossBulletBreak = true;
		PLAYER->setPlayerScore(PLAYER->getPlayerScore() + PATTERN0_SCORE);
	}

	// 보스 패턴에 따른 움직임
	if (bossPattern == APPEAR)
	{
		if (bossPosY > 150)
		{
			isBossStop = true;
			bossAngle = PI * 5 / 4;
			bossSpeed = 0;
			bossPattern = PATTERN0;
			SOUNDMANAGER->Stop(TEXT("Field"));
			SOUNDMANAGER->Play(TEXT("Boss"), 0.2f);
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
		if (bossStayTimer == -1)
		{
			bossSpeed = 1.f;
			isBossStop = false;
			bossAngle = UTIL::getAngle(bossPosX, bossPosY, 280, 200);
			if (UTIL::getDistance(bossPosX, bossPosY, 280, 200) < 10)
			{
				bossAngle = PI;
				bossStayTimer = 0;
			}
		}		

		if (bossStayTimer != -1)
		{
			if (bossPosX < 200)
			{
				bossSpeed = 0.f;
				bossAngle = PI * 2;
				isBossStop = true;
			}

			if (bossPosX > 350)
			{
				bossSpeed = 0.f;
				bossAngle = PI;
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
		
	}
	else if (bossPattern == PATTERN2)
	{
		bossSpeed = 1.f;
		bossAngle = UTIL::getAngle(bossPosX, bossPosY, 280, 200);
		if (UTIL::getDistance(bossPosX, bossPosY, 280, 200) < 10)
		{
			bossSpeed = 0.f;
		}
	}
	else if (bossPattern == PATTERN3)
	{
		// 없음
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

	// HP바
	if (bossPattern != BOSS_DEAD)
	{
		if(bossHp != BOSS_MAXHP)
			bossHpBarPercent = (bossHp % BOSS_PATTERN_HP) / (BOSS_PATTERN_HP / 100);
	}

	if (bossPattern == BOSS_DEAD)
	{
		bossSpeed = 0.f;
		bossStayTimer++;
		if (bossStayTimer == 120)
		{
			bossState = DEAD;
		}

		if (bossStayTimer == 300)
		{
			SOUNDMANAGER->Stop(TEXT("Boss"));
			SCENEMANAGER->ChangeScene(TEXT("GameClearScene"));
		}
	}
}

void Boss::createBossBullet(float ingameCurrentTime)
{
	if (bossPattern == PATTERN0)
	{
		if (bulletTermTimer == 20)
		{
			SOUNDMANAGER->Stop(TEXT("EnemyAttack2"));
			SOUNDMANAGER->Play(TEXT("EnemyAttack2"), 0.07f);
			createNWayBullet(3, 0, PI* 2, 30, bossPosX, bossPosY);
			bulletTermTimer = 0;
		}
			
		bulletTermTimer++;
	}

	else if (bossPattern == PATTERN1)
	{
		if (isBossBulletBreak == true)
		{
			bossBulletBreakTimer++;
			if (bossBulletBreakTimer == 120)
			{
				bossBulletBreakTimer = 0;
				isBossBulletBreak = false;
				bulletTermTimer = 0;
			}
		}
		else
		{
			if (bulletTermTimer % 5 == 0 && isCreateBossBullet == true)
			{
				SOUNDMANAGER->Stop(TEXT("EnemyAttack2"));
				SOUNDMANAGER->Play(TEXT("EnemyAttack2"), 0.07f);
				createNWayBullet(2, PI * 1 / 8, PI * 3 / 8, 8, bossPosX, bossPosY);
				createNWayBullet(2, PI * 5 / 8, PI * 7 / 8, 8, bossPosX, bossPosY);
				bulletCountNum++;
			}

			if (bulletTermTimer == 10)
			{
				SOUNDMANAGER->Stop(TEXT("EnemyAttack2"));
				SOUNDMANAGER->Play(TEXT("EnemyAttack2"), 0.07f);
				createNWayBullet(0, PI * 9 / 8, PI * 11 / 8, 3, bossPosX, bossPosY);
				createNWayBullet(0, PI * 13 / 8, PI * 15 / 8, 3, bossPosX, bossPosY);
				bulletTermTimer = 0;
			}

			bulletTermTimer++;

			if (bulletCountNum == 10)
			{
				bulletCountNum = 0;
				isCreateBossBullet = false;
			}

			if (isCreateBossBullet == false)
			{
				createBossBulletTimer++;
				if (createBossBulletTimer == 120)
				{
					createBossBulletTimer = 0;
					isCreateBossBullet = true;
				}
			}
		}
		
	}

	else if (bossPattern == PATTERN2)
	{
		if (isBossBulletBreak == true)
		{
			bossBulletBreakTimer++;
			if (bossBulletBreakTimer == 120)
			{
				bossBulletBreakTimer = 0;
				isBossBulletBreak = false;
				bulletTermTimer = 0;
			}
		}
		else
		{
			if (bulletTermTimer == 20)
			{
				SOUNDMANAGER->Stop(TEXT("EnemyAttack2"));
				SOUNDMANAGER->Play(TEXT("EnemyAttack2"), 0.07f);
				createNWayBullet(3, 0, PI * 2, RND->getFromIntTo(30, 40), bossPosX - 50, bossPosY - 50, 10);
			}

			if (bulletTermTimer == 40)
			{
				SOUNDMANAGER->Stop(TEXT("EnemyAttack2"));
				SOUNDMANAGER->Play(TEXT("EnemyAttack2"), 0.07f);
				createNWayBullet(4, 0, PI * 2, RND->getFromIntTo(30, 40), bossPosX + 50, bossPosY - 50, 10);
				bulletTermTimer = 0;
			}

			bulletTermTimer++;
		}
	}

	else if (bossPattern == PATTERN3)
	{
		if (isBossBulletBreak == true)
		{
			bossBulletBreakTimer++;
			if (bossBulletBreakTimer == 120)
			{
				bossBulletBreakTimer = 0;
				isBossBulletBreak = false;
				bulletTermTimer = 0;
			}
		}
		else
		{
			if (bulletTermTimer % 10 == 0)
			{
				float change = 0;

				if (bulletTermTimer >= 300)
				{
					change = PI / 8;
					if (bulletTermTimer == 600)
						bulletTermTimer = 0;
				}

				SOUNDMANAGER->Stop(TEXT("EnemyAttack2"));
				SOUNDMANAGER->Play(TEXT("EnemyAttack2"), 0.07f);
				createNWayBullet(0, 0 + change, PI * 2 + change, 8, bossPosX, bossPosY);
				createNWayBullet(1, PI / 4 + change, PI * 9 / 4 + change, 8, bossPosX, bossPosY);
			}

			if (bulletTermTimer % 20 == 0)
			{
				SOUNDMANAGER->Stop(TEXT("EnemyAttack2"));
				SOUNDMANAGER->Play(TEXT("EnemyAttack2"), 0.07f);
				createNWayBullet(2, 0 + changingBulletAngle, (PI * 2) + changingBulletAngle, 20, bossPosX, bossPosY);

				changingBulletAngle += PI / 100;

				if ((PI * 2) - changingBulletAngle < 0.1)
					changingBulletAngle = 0;
			}

			bulletTermTimer++;
		}
	}
}

void Boss::moveBossBullet(float ingameCurrentTime)
{
	b_Bullet_it = b_Bullet.begin();
	for (; b_Bullet_it != b_Bullet.end();)
	{
		if (bossPattern == PATTERN1 && (*b_Bullet_it).type == 2 && (*b_Bullet_it).angle < PI)
		{
			int magicNum = (PLAYER->getPlayerPosY() - 200) / 2;
			if (UTIL::getDistance((*b_Bullet_it).x, (*b_Bullet_it).y, bossPosX, bossPosY) > 100)
				(*b_Bullet_it).angle = UTIL::getAngle((*b_Bullet_it).x, (*b_Bullet_it).y, 
					PLAYER->getPlayerPosX(), PLAYER->getPlayerPosY() - magicNum);
		}

		if (bossPattern == PATTERN3 && (*b_Bullet_it).type == 0)
		{
			(*b_Bullet_it).angle += 0.015;
		}

		if (bossPattern == PATTERN3 && (*b_Bullet_it).type == 1)
		{
			(*b_Bullet_it).angle -= 0.015;
		}

		(*b_Bullet_it).x += (cosf((*b_Bullet_it).angle) * (*b_Bullet_it).speed);
		(*b_Bullet_it).y += (-sinf((*b_Bullet_it).angle) * (*b_Bullet_it).speed);

		// 맵 경계 밖으로 나갔거나 충돌한 경우 제거
		if ((*b_Bullet_it).x < F_LEFT || (*b_Bullet_it).x > F_RIGHT ||
			(*b_Bullet_it).y < F_UP || (*b_Bullet_it).y > F_DOWN ||
			(*b_Bullet_it).state == DEAD)
			b_Bullet_it = b_Bullet.erase(b_Bullet_it);
		else
			b_Bullet_it++;
	}
}

void Boss::createNWayBullet(int bulletType, float startAngle, float endAngle, int num, 
	float createPosX, float createPosY, int distance)
{
	float totalAngle = endAngle - startAngle;

	// 원일 때 (소수점 계산시 오류발생으로 오차를 둠)
	if (totalAngle - (PI * 2) < 0.1)
	{
		for (int i = 0; i < num; i++)
		{
			bossBullet[bulletType].angle = startAngle + ((totalAngle / num) * i);
			bossBullet[bulletType].x = createPosX + (cosf(bossBullet[bulletType].angle) * distance);
			bossBullet[bulletType].y = createPosY + (-sinf(bossBullet[bulletType].angle) * distance);
			b_Bullet.push_back(bossBullet[bulletType]);
		}
	}

	// 원이 아닐 때
	else
	{
		for (int i = 0; i < num; i++)
		{
			bossBullet[bulletType].angle = startAngle + ((totalAngle / (num - 1)) * i);
			bossBullet[bulletType].x = createPosX + (cosf(bossBullet[bulletType].angle) * distance);
			bossBullet[bulletType].y = createPosY + (-sinf(bossBullet[bulletType].angle) * distance);
			b_Bullet.push_back(bossBullet[bulletType]);
		}
	}
}
