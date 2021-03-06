#include "Game.h"
#include "Player.h"
#include "Xml.h"


Player::Player()
{
}

Player::~Player()
{
}

void Player::init()
{
	if (playerType == REIMU)
	{
		playerImage = IMAGEMANAGER->addFrameImage(TEXT("Reimu"), TEXT("Image\\reimuSD.bmp"),
			259, 146, 8, 3, true, RGB(255, 255, 255));
		playerImage->setX(270);
		playerImage->setY(500);

		supporter = IMAGEMANAGER->addFrameImage(TEXT("ReimuSpecialSupporter"), TEXT("Image\\reimuball.bmp"),
			48, 15, 3, 1, true, RGB(255, 255, 255));
		supporter->setFrameY(1);

		bulletImage = IMAGEMANAGER->addFrameImage(TEXT("ReimuBullet"), TEXT("Image\\bullet.bmp"),
			28, 14, 2, 1, true, RGB(255, 255, 255));
		bulletImage->setFrameX(REIMU);

		supportBulletImage = IMAGEMANAGER->addFrameImage(TEXT("ReimuSupportBullet"), TEXT("Image\\supportbullet.bmp"),
			32, 16, 2, 1, true, RGB(255, 255, 255));
		supportBulletImage->setFrameX(REIMU);

		specialBulletImage = IMAGEMANAGER->addImage(TEXT("ReimuSpecialBullet"), TEXT("Image\\specialbullet.bmp"),
			60, 60, true, RGB(255, 255, 255));
	}

	else if (playerType == MARISA)
	{
		playerImage = IMAGEMANAGER->addFrameImage(TEXT("Marisa"), TEXT("Image\\marisaSD.bmp"),
			257, 145, 8, 3, true, RGB(255, 255, 255));
		playerImage->setX(270);
		playerImage->setY(500);

		supporter = IMAGEMANAGER->addFrameImage(TEXT("MarisaSpecialSupporter"), TEXT("Image\\marisaball.bmp"),
			64, 14, 4, 1, true, RGB(255, 255, 255));
		supporter->setFrameX(0);

		bulletImage = IMAGEMANAGER->addFrameImage(TEXT("MarisaBullet"), TEXT("Image\\bullet.bmp"),
			28, 14, 2, 1, true, RGB(255, 255, 255));
		bulletImage->setFrameX(MARISA);

		supportBulletImage = IMAGEMANAGER->addFrameImage(TEXT("MarisaSupportBullet"), TEXT("Image\\supportbullet.bmp"),
			32, 16, 2, 1, true, RGB(255, 255, 255));
		supportBulletImage->setFrameX(MARISA);

		specialBulletImage = IMAGEMANAGER->addImage(TEXT("MarisaSpecialBullet"), TEXT("Image\\specialbullet2.bmp"),
			60, 60, true, RGB(255, 255, 255));
	}

	playerShiftImage = IMAGEMANAGER->addImage(TEXT("ShiftImage"), TEXT("Image\\shift.bmp"),
		64, 64, true, RGB(255, 255, 255));

	playerShiftMaskImage = IMAGEMANAGER->addImage(TEXT("ShiftMaskImage"), TEXT("Image\\maskshift.bmp"),
		64, 64, true, RGB(255, 255, 255));

	// 플레이어 정보
	playerImage->setFrameX(P_ANI_NORMAL);
	playerDiameter = 10;
	playerSpeed = NORMAL_SPEED;
	playerAlpha = OPAQUE_;
	isPlayerDead = false;
	isPlayerInvincible = false;
	playerInvincibleTimer = 0;
	playerScore = 0;
	playerLife = 5;
	playerPower = 20;

	// 플레이어 탄 정보
	loadBulletFile();	// 탄 정보 파일 불러오기
	createBulletTimer = 0;
	createSupportBulletTimer = 0;
	specialBulletAlpha = 0;
	specialBulletDuration = 0;
	specialBulletOn = false;

	// 회전 변환
	ZeroMemory(vertices, 3);
	fAnchorX = 0;
	fAnchorY = 0;
	fAngle = 0;

	mask = createMask(playerShiftImage->getMemDC(), 64, 64);
}

void Player::release()
{
	p_Bullet.clear();

	// 프로그램이 끝날땐 반드시 해제해주셔야 합니다.
	DeleteDC(hdcMask);
	DeleteObject(hBitmapMask);
}

void Player::update()
{
	// 플레이어 이동 및 모션
	playerSpeed = NORMAL_SPEED;

	if (KEYMANAGER->isStayKeyDown(VK_LSHIFT) || KEYMANAGER->isStayKeyDown(VK_RSHIFT))
		playerSpeed = SHIFT_SPEED;

	if (!KEYMANAGER->isStayKeyDown(VK_LEFT) && !KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		playerImage->setFrameY(P_ANI_NORMAL);
		if (playerMotionTimer == MOTION_DELAY)
		{
			playerImage->setFrameX(playerImage->getFrameX() + 1);
			playerMotionTimer = 0;
		}

		if (playerImage->getFrameX() == 7)
			playerImage->setFrameX(0);
	}	

	if(KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		if(playerImage->getX() - playerSpeed > F_LEFT)
			playerImage->setX(playerImage->getX() - playerSpeed);

		playerImage->setFrameY(P_ANI_LEFT);
		if (playerMotionTimer == MOTION_DELAY)
		{
			playerImage->setFrameX(playerImage->getFrameX() + 1);
			playerMotionTimer = 0;
		}

		if (playerImage->getFrameX() == 7)
			playerImage->setFrameX(2);

	}

	if(KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		if (playerImage->getX() + playerSpeed + P_SIZE_X < F_RIGHT)
			playerImage->setX(playerImage->getX() + playerSpeed);

		playerImage->setFrameY(P_ANI_RIGHT);
		if (playerMotionTimer == MOTION_DELAY)
		{
			playerImage->setFrameX(playerImage->getFrameX() + 1);
			playerMotionTimer = 0;
		}

		if (playerImage->getFrameX() == 7)
			playerImage->setFrameX(2);
	}

	if(KEYMANAGER->isStayKeyDown(VK_UP))
	{
		if (playerImage->getY() - playerSpeed > F_UP)
			playerImage->setY(playerImage->getY() - playerSpeed);
	}

	if(KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		if (playerImage->getY() + playerSpeed + P_SIZE_Y < F_DOWN)
			playerImage->setY(playerImage->getY() + playerSpeed);
	}

	// 플레이어 서포터(왼쪽 위)
	if (KEYMANAGER->isStayKeyDown(VK_LSHIFT) || KEYMANAGER->isStayKeyDown(VK_RSHIFT))
	{
		supporterPos[0] = { (LONG)playerImage->getX() - 4, (LONG)playerImage->getY() - 20 };
		supporterPos[1] = { (LONG)playerImage->getX() + 32 - 12, (LONG)playerImage->getY() - 20 };
		supporterPos[2] = { (LONG)playerImage->getX() - 20, (LONG)playerImage->getY() - 5 };
		supporterPos[3] = { (LONG)playerImage->getX() + 32 + 20 - 16, (LONG)playerImage->getY() - 5 };
	}
	else
	{
		supporterPos[0] = { (LONG)playerImage->getX() - 8, (LONG)playerImage->getY() - 20 };
		supporterPos[1] = { (LONG)playerImage->getX() + 32 - 8, (LONG)playerImage->getY() - 20 };
		supporterPos[2] = { (LONG)playerImage->getX() - 20 - 8, (LONG)playerImage->getY() };
		supporterPos[3] = { (LONG)playerImage->getX() + 32 + 20 - 8, (LONG)playerImage->getY() };
	}
	

	// 플레이어 탄
	if (KEYMANAGER->isStayKeyDown('Z'))
	{
		if (createBulletTimer % CREATEBULLETDELAY == 0)
			createBullet();

		createBulletTimer++;
	}
	if (KEYMANAGER->isOnceKeyUp('Z'))
	{
		createBulletTimer = 0;
		createSupportBulletTimer = 0;
	}
	// 스페셜 탄
	if (KEYMANAGER->isStayKeyDown('X') && specialBulletOn == false)
	{
		specialBulletOn = true;
		createSpecialBullet();
		playerPower -= 5;
	}	
		
	// 탄 이동
	moveBullet();

	// 이미지 회전 관련
	playerShiftImage->setX(playerImage->getX() - 13);
	playerShiftImage->setY(playerImage->getY() - 5);

	fAngle += 1;
	if (fAngle >= 360.0f)
		fAngle = 0.0f;

	rotate(fAngle);

	playerShiftMaskImage->setX(playerShiftImage->getX());
	playerShiftMaskImage->setY(playerShiftImage->getY());

	// 죽었을 때
	ifPlayerDead();

	// 모션 타이머 증가
	playerMotionTimer++;

	// 플레이어 좌표
	playerPosX = playerImage->getX() + 16;
	playerPosY = playerImage->getY() + 24;
}

void Player::render(HDC hdc)
{
	// 회전변환
	if (KEYMANAGER->isStayKeyDown(VK_LSHIFT) || KEYMANAGER->isStayKeyDown(VK_RSHIFT))
	{
		PlgBlt(hdc, vertices, playerShiftImage->getMemDC(), 0, 0,
			playerShiftImage->getWidth(), playerShiftImage->getHeight(),
			mask, 0, 0);
	}	
	
	// 플레이어
	playerImage->alphaRender(hdc, playerImage->getX(), playerImage->getY(),
		playerImage->getFrameX(), playerImage->getFrameY(), playerAlpha);

	// SHIFT누를 때
	if(KEYMANAGER->isStayKeyDown(VK_LSHIFT) || KEYMANAGER->isStayKeyDown(VK_RSHIFT))
		EllipseMakeCenter(hdc, playerPosX, playerPosY, playerDiameter, playerDiameter);

	// 서포터
	for (int i = 0; i < (int)(playerPower / 10); i++)
		supporter->frameRender(hdc, supporterPos[i].x, supporterPos[i].y);

	// 스페셜 탄
	if (specialBulletOn == true)
	{
		for (int i = 0; i < PLAYER_SPECIALBULLET_NUMLIMIT; i++)
		{
			if(specialBullet[i].y > F_UP && specialBullet[i].x > F_LEFT && specialBullet[i].x < F_RIGHT)
				specialBulletImage->alphaRender(hdc, specialBullet[i].x - 32, specialBullet[i].y - 32, specialBulletAlpha);
		}
	}

	// 탄
	renderBullet(hdc);
}

void Player::ifPlayerDead()
{
	// 죽었을 때 init같은
	if (isPlayerDead == true)
	{
		SOUNDMANAGER->Stop(TEXT("PlayerDead"));
		
		SOUNDMANAGER->Play(TEXT("PlayerDead"), 0.2f);
		playerLife -= 1;
		isPlayerDead = false;
		isPlayerInvincible = true;
		playerAlpha = TRANSLUCENT_;

		// 탄 전부 제거
		ENEMYOBJECT->e_BulletClear();
		BOSS->b_BulletClear();

		for (int i = 0; i < playerPower / 4; i++)
		{
			ITEMS->createItem(BLUE_ITEM, RND->getFromIntTo(playerImage->getX() - 50, playerImage->getX() + 50),
				RND->getFromIntTo(playerImage->getY() - 50, playerImage->getY() + 50));
			ITEMS->createItem(RED_ITEM, RND->getFromIntTo(playerImage->getX() - 50, playerImage->getX() + 50),
				RND->getFromIntTo(playerImage->getY() - 50, playerImage->getY() + 50));
		}
		playerPower = 0;

		playerImage->setX(270);
		playerImage->setY(10000);
	}

	// 무적 시간동안
	if (isPlayerInvincible == true)
	{
		playerInvincibleTimer++;

		if (playerInvincibleTimer == 60)
		{
			playerImage->setX(270);
			playerImage->setY(520);
		}
		
		if(playerInvincibleTimer < 120 && playerImage->getY() > 460)
			playerImage->setY(playerImage->getY() - 1);

		if (playerInvincibleTimer == PLAYER_INVINCIBLE_DELAY)
		{
			playerAlpha = OPAQUE_;
			isPlayerInvincible = false;
			playerInvincibleTimer = 0;
		}
			
	}
}

void Player::rotate(float angle)
{
	float theta = angle * PI / 180.0f;

	// sin, cos값 구하기
	float s = sinf(theta);
	float c = cosf(theta);

	// 회전 중심 좌표(이미지 중앙)
	float centerX = playerShiftImage->getX() + (playerShiftImage->getWidth() / 2);
	float centerY = playerShiftImage->getY() + (playerShiftImage->getHeight() / 2);

	// 회전 변환
	// Upper-Left
	vertices[0].x = (LONG)(((playerShiftImage->getX() - centerX) * c - (playerShiftImage->getY() - centerY) * s) + playerShiftImage->getX() + (playerShiftImage->getWidth() / 2) - 2.5);
	vertices[0].y = (LONG)(((playerShiftImage->getX() - centerX) * s + (playerShiftImage->getY() - centerY) * c) + playerShiftImage->getY() + (playerShiftImage->getWidth() / 2) - 2);
	// Upper-Right
	vertices[1].x = (LONG)(((playerShiftImage->getX() + playerShiftImage->getWidth() - centerX) * c - (playerShiftImage->getY() - centerY) * s) + playerShiftImage->getX() + (playerShiftImage->getWidth() / 2) - 2.5);
	vertices[1].y = (LONG)(((playerShiftImage->getX() + playerShiftImage->getWidth() - centerX) * s + (playerShiftImage->getY() - centerY) * c) + playerShiftImage->getY() + (playerShiftImage->getWidth() / 2) - 2);
	// Lower-Left
	vertices[2].x = (LONG)(((playerShiftImage->getX() - centerX) * c - (playerShiftImage->getY() + playerShiftImage->getHeight() - centerY) * s) + playerShiftImage->getX() + (playerShiftImage->getWidth() / 2) - 2.5);
	vertices[2].y = (LONG)(((playerShiftImage->getX() - centerX) * s + (playerShiftImage->getY() + playerShiftImage->getHeight() - centerY) * c) + playerShiftImage->getY() + (playerShiftImage->getWidth() / 2) - 2);
}

void Player::loadBulletFile()
{
	// 일반 탄
	int i = 0;

	XmlDocument* doc = new XmlDocument;
	XmlError err = doc->LoadFile(TEXT("DataBase\\PlayerBullet.xml"));
	assert(err == Xml::XML_SUCCESS);
	
	XmlElement* playerbullet = doc->FirstChildElement(TEXT("PlayerBullet"));
	XmlElement* Type = playerbullet->FirstChildElement();

	XmlAttribute* value;

	for (; Type != NULL; Type = Type->NextSiblingElement(), i++)
	{
		XmlElement* radius = Type->FirstChildElement();
		value = (XmlAttribute*)radius->FirstAttribute();
		load_bullet[i].diameter = strtod(value->Value(), 0);

		XmlElement* angle1 = radius->NextSiblingElement();
		value = (XmlAttribute*)angle1->FirstAttribute();
		load_bullet[i].angle1 = strtod(value->Value(), 0);

		XmlElement* angle2 = angle1->NextSiblingElement();
		value = (XmlAttribute*)angle2->FirstAttribute();
		load_bullet[i].angle2 = strtod(value->Value(), 0);

		XmlElement* speed = angle2->NextSiblingElement();
		value = (XmlAttribute*)speed->FirstAttribute();
		load_bullet[i].speed = strtod(value->Value(), 0);

		XmlElement* damage = speed->NextSiblingElement();
		value = (XmlAttribute*)damage->FirstAttribute();
		load_bullet[i].damage = atoi(value->Value());
	}

	// 스페셜 탄
	for (i = 0; i < PLAYER_SPECIALBULLET_NUMLIMIT; i++)
	{
		specialBullet[i].diameter = 64;
		specialBullet[i].speed = 0.5f;
	}
}

void Player::createBullet()
{
	SOUNDMANAGER->Stop(TEXT("PlayerAttack"));
	SOUNDMANAGER->Play(TEXT("PlayerAttack"), 0.1f);

	// 기본 탄1(중심점)
	bullet.state = ALIVE;
	bullet.x = playerImage->getX();
	bullet.y = playerImage->getY();
	bullet.diameter = load_bullet[NORMAL].diameter;
	bullet.angle = PI / 2;
	bullet.speed = load_bullet[NORMAL].speed;;
	bullet.damage = load_bullet[NORMAL].damage;
	bullet.type = NORMAL;
	p_Bullet.push_back(bullet);

	// 기본 탄2
	bullet.x = playerImage->getX() + 32;
	p_Bullet.push_back(bullet);

	if (createSupportBulletTimer % CREATESUPPORTBULLETDELAY == 0)
	{
		// 서포트 탄
		for (int i = 0; i < (int)(playerPower / 10); i++)
		{
			bullet.x = supporterPos[i].x + 8;
			bullet.y = supporterPos[i].y + 8;
			bullet.diameter = load_bullet[SUPPORT].diameter;

			if (KEYMANAGER->isStayKeyDown(VK_LSHIFT))
				bullet.angle = PI / 2;
			else
			{
				if (i % 2 == 0)
					bullet.angle = PI * 3 / 4;
				else
					bullet.angle = PI / 4;
			}
			bullet.speed = load_bullet[SUPPORT].speed;
			bullet.damage = load_bullet[SUPPORT].damage;
			if(playerType == MARISA)
				bullet.damage = load_bullet[SUPPORT].damage * 2;
			bullet.type = SUPPORT;
			p_Bullet.push_back(bullet);
		}

		createSupportBulletTimer = 0;
	}
	
	createSupportBulletTimer++;
}

void Player::createSpecialBullet()
{
	specialBullet[0].x = playerPosX - 64;
	specialBullet[0].y = playerPosY - 88;

	specialBullet[1].x = playerPosX;
	specialBullet[1].y = playerPosY - 88;

	specialBullet[2].x = playerPosX + 64;
	specialBullet[2].y = playerPosY - 88;
}

void Player::moveBullet()
{
	p_Bullet_it = p_Bullet.begin();
	for (; p_Bullet_it != p_Bullet.end();)
	{
		// 서포트 탄일 때
		
		// 호밍기능
		if (playerType == REIMU && (*p_Bullet_it).type == SUPPORT && BOSS->getBossState() == ALIVE)
		{
			(*p_Bullet_it).angle = UTIL::getAngle((*p_Bullet_it).x, (*p_Bullet_it).y,
				BOSS->getBossPosX(), BOSS->getBossPosY());
		}

		else if ((*p_Bullet_it).type == SUPPORT && ENEMYOBJECT->getE_ObjectSize() > 0)
		{
			e_Object_distance.clear();
			// 적 오브젝트 정보 수집
			e_Object_it = ENEMYOBJECT->getE_Object_Begin();
			for (; e_Object_it != ENEMYOBJECT->getE_Object_End(); e_Object_it++)
			{
				e_Object_distance.insert(pair<float, POINT>(
					UTIL::getDistance((*p_Bullet_it).x, (*p_Bullet_it).y, (*e_Object_it).x, (*e_Object_it).y),
					{ (LONG)(*e_Object_it).x, (LONG)(*e_Object_it).y }
				));
			}

			(*p_Bullet_it).angle = UTIL::getAngle((*p_Bullet_it).x, (*p_Bullet_it).y,
				(*e_Object_distance.begin()).second.x, (*e_Object_distance.begin()).second.y);
		}

		(*p_Bullet_it).x += cosf((*p_Bullet_it).angle) * (*p_Bullet_it).speed;
		(*p_Bullet_it).y -= sinf((*p_Bullet_it).angle) * (*p_Bullet_it).speed;

		// 맵 경계 밖으로 나갔거나 충돌한 경우 제거
		if ((*p_Bullet_it).x < F_LEFT || (*p_Bullet_it).x > F_RIGHT ||
			(*p_Bullet_it).y < F_UP || (*p_Bullet_it).y > F_DOWN ||
			(*p_Bullet_it).state == DEAD)
			p_Bullet_it = p_Bullet.erase(p_Bullet_it);
		else
			p_Bullet_it++;
	}

	if (specialBulletOn == true)
	{
		for (int i = 0; i < PLAYER_SPECIALBULLET_NUMLIMIT; i++)
		{
			if (specialBulletAlpha != 255)
				specialBulletAlpha += 3;

			specialBullet[i].y -= specialBullet[i].speed;
		}

		specialBulletDuration++;

		if (specialBulletDuration == PLAYER_SPECIALBULLET_DURATION)
		{
			specialBulletDuration = 0;
			specialBulletAlpha = 0;
			specialBulletOn = false;
		}
	}
}

void Player::renderBullet(HDC hdc)
{
	p_Bullet_it = p_Bullet.begin();
	for (; p_Bullet_it != p_Bullet.end(); p_Bullet_it++)
	{
		if ((*p_Bullet_it).type == NORMAL)
			bulletImage->frameRender(hdc, (*p_Bullet_it).x -7, (*p_Bullet_it).y - 7);

		if ((*p_Bullet_it).type == SUPPORT)
		{
			supportBulletImage->frameRender(hdc, (*p_Bullet_it).x - 8, (*p_Bullet_it).y - 8);
		}

#if defined(DEBUG_MODE)
		if (KEYMANAGER->isStayKeyDown(VK_LSHIFT))
			EllipseMakeCenter(hdc, (*p_Bullet_it).x, (*p_Bullet_it).y, (*p_Bullet_it).diameter, (*p_Bullet_it).diameter);
#endif	// DEBUG_MODE
	}

#if defined(DEBUG_MODE)
	TCHAR szTemp[100] = { 0, };
	Rectangle(hdc, 530, 280, 750, 580);
	_stprintf_s(szTemp, sizeof(szTemp), TEXT("플레이어 총알 개수 : %d"), p_Bullet.size());
	TextOut(hdc, 540, 330, szTemp, _tcslen(szTemp));
#endif	// DEBUG_MODE
}

HBITMAP Player::createMask(HDC hdcBitmap, int width, int height)
{
	// hdcBitmap(출력할 스프라이트)으로 지정한 데이터의 마스크를 만들어서 리턴합니다.

	// 투명색 지정 현재 투명색은 분홍색으로 지정되어 있습니다만,

	// 흰색이나 검정색으로 하시려면 RGB(255, 255, 255) 또는 RGB(0, 0, 0) 으로 수정하시면 됩니다.
	COLORREF oldBackColor = SetBkColor(hdcBitmap, RGB(255, 255, 255));


	// 마스크 비트맵을 만듭니다. (물론 DC도 같이 만듭니다.)

	// 보통 마스크 비트맵은 1BPP 짜리 흑백 비트맵으로 만듭니다.
	hdcMask = CreateCompatibleDC(NULL);
	hBitmapMask = CreateBitmap(width, height, 1, 1, NULL); // 마스크 비트맵 생성

	SelectObject(hdcMask, hBitmapMask);


	// hdcMask와 hBitmapMask에 hdcBitmap(출력할 스프라이트)의 마스크를 만듭니다.
	BitBlt(
		hdcMask,
		0, 0,
		width, height,
		hdcBitmap,
		0, 0,
		NOTSRCCOPY);

	// 배경색을 원래 색으로 돌려놓습니다.    
	SetBkColor(hdcBitmap, oldBackColor);

	// 생성된 마스크비트맵을 리턴
	return hBitmapMask;
}
