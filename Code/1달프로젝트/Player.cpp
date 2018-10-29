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
	}

	playerShiftImage = IMAGEMANAGER->addImage(TEXT("ShiftImage"), TEXT("Image\\shift.bmp"),
		60, 60, true, RGB(255, 255, 255));

	playerShiftMaskImage = IMAGEMANAGER->addImage(TEXT("ShiftMaskImage"), TEXT("Image\\maskshift.bmp"),
		60, 60, true, RGB(255, 255, 255));

	// 플레이어 정보
	playerImage->setFrameX(P_ANI_NORMAL);
	playerPos = { (LONG)playerImage->getX() + 26, (LONG)playerImage->getY() + 24 };
	playerDiameter = 10;
	playerSpeed = NORMAL_SPEED;
	playerAlpha = OPAQUE_;
	isPlayerDead = true;
	isPlayerInvincible = false;
	playerInvincibleTimer = 0;
	playerLife = 3;
	playerPower = 39;

	// 플레이어 탄 정보
	loadBulletFile();	// 탄 정보 파일 불러오기
	createBulletTimer = 0;
	createSupportBulletTimer = 0;

	// 회전 변환
	ZeroMemory(vertices, 3);
	fAnchorX = 0;
	fAnchorY = 0;
	fAngle = 0;
}

void Player::release()
{
	if (playerType == REIMU)
		IMAGEMANAGER->deleteImage(TEXT("Reimu"));

	if (playerType == MARISA)
		IMAGEMANAGER->deleteImage(TEXT("Marisa"));
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
	supporterPos[0] = { (LONG)playerImage->getX() - 8, (LONG)playerImage->getY() - 20 };
	supporterPos[1] = { (LONG)playerImage->getX() + 32 - 8, (LONG)playerImage->getY() - 20 };
	supporterPos[2] = { (LONG)playerImage->getX() - 20 - 8, (LONG)playerImage->getY() };
	supporterPos[3] = { (LONG)playerImage->getX() + 32 + 20 - 8, (LONG)playerImage->getY() };

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
}

void Player::render(HDC hdc)
{
	// 회전변환
	PlgBlt(hdc, vertices, playerShiftImage->getMemDC(), 0, 0, 		
		playerShiftImage->getWidth(), playerShiftImage->getHeight(), NULL, vertices[0].x, vertices[0].y);
	
	// 플레이어
	playerImage->alphaRender(hdc, playerImage->getX(), playerImage->getY(), 
		playerImage->getFrameX(), playerImage->getFrameY(), playerAlpha);

	// SHIFT누를 때
	if(KEYMANAGER->isStayKeyDown(VK_LSHIFT) || KEYMANAGER->isStayKeyDown(VK_RSHIFT))
		EllipseMakeCenter(hdc, playerPos.x, playerPos.y, playerDiameter, playerDiameter);

	// 서포터
	for (int i = 0; i < (int)(playerPower / 10); i++)
		supporter->frameRender(hdc, supporterPos[i].x, supporterPos[i].y);

	// 탄
	renderBullet(hdc);

	//playerShiftImage->alphaRender(hdc, 120);
}

void Player::ifPlayerDead()
{
	// 죽었을 때 init같은
	if (isPlayerDead == true)
	{
		SOUNDMANAGER->Play(TEXT("PlayerDead"), 0.2f);
		isPlayerDead = false;
		isPlayerInvincible = true;
		playerAlpha = TRANSLUCENT_;
		playerImage->setX(270);
		playerImage->setY(500);
	}

	// 무적 시간동안
	if (isPlayerInvincible == true)
	{
		playerInvincibleTimer++;
		
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
	playerPos = { (LONG)centerX, (LONG)centerY };

	// 회전 변환
	// Upper-Left
	vertices[0].x = (LONG)(((playerShiftImage->getX() - centerX) * c - (playerShiftImage->getY() - centerY) * s) + playerShiftImage->getX() + (playerShiftImage->getWidth() / 2));
	vertices[0].y = (LONG)(((playerShiftImage->getX() - centerX) * s + (playerShiftImage->getY() - centerY) * c) + playerShiftImage->getY() + (playerShiftImage->getWidth() / 2));
	// Upper-Right
	vertices[1].x = (LONG)(((playerShiftImage->getX() + playerShiftImage->getWidth() - centerX) * c - (playerShiftImage->getY() - centerY) * s) + playerShiftImage->getX() + (playerShiftImage->getWidth() / 2));
	vertices[1].y = (LONG)(((playerShiftImage->getX() + playerShiftImage->getWidth() - centerX) * s + (playerShiftImage->getY() - centerY) * c) + playerShiftImage->getY() + (playerShiftImage->getWidth() / 2));
	// Lower-Left
	vertices[2].x = (LONG)(((playerShiftImage->getX() - centerX) * c - (playerShiftImage->getY() + playerShiftImage->getHeight() - centerY) * s) + playerShiftImage->getX() + (playerShiftImage->getWidth() / 2));
	vertices[2].y = (LONG)(((playerShiftImage->getX() - centerX) * s + (playerShiftImage->getY() + playerShiftImage->getHeight() - centerY) * c) + playerShiftImage->getY() + (playerShiftImage->getWidth() / 2));
}

void Player::loadBulletFile()
{
	int i = 0;

	XmlDocument* doc = new XmlDocument;
	XmlError err = doc->LoadFile(TEXT("PlayerBullet.xml"));
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
}

void Player::createBullet()
{
	SOUNDMANAGER->Stop(TEXT("PlayerAttack"));
	SOUNDMANAGER->Play(TEXT("PlayerAttack"), 0.2f);

	// 기본 탄1(중심점)
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
			if (i % 2 == 0)
				bullet.angle = PI * 3 / 4;
			else
				bullet.angle = PI / 4;
			bullet.speed = load_bullet[SUPPORT].speed;
			bullet.damage = load_bullet[SUPPORT].damage;
			bullet.type = SUPPORT;
			p_Bullet.push_back(bullet);
		}

		createSupportBulletTimer = 0;
	}
	
	createSupportBulletTimer++;
}

void Player::moveBullet()
{
	p_Bullet_it = p_Bullet.begin();
	for (; p_Bullet_it != p_Bullet.end();)
	{
		(*p_Bullet_it).x += cosf((*p_Bullet_it).angle) * (*p_Bullet_it).speed;
		(*p_Bullet_it).y -= sinf((*p_Bullet_it).angle) * (*p_Bullet_it).speed;

		// 맵 경계 밖으로 나갔는지 확인
		if ((*p_Bullet_it).x < F_LEFT || (*p_Bullet_it).x > F_RIGHT ||
			(*p_Bullet_it).y < F_UP || (*p_Bullet_it).y > F_DOWN)
			p_Bullet_it = p_Bullet.erase(p_Bullet_it);
		else
			p_Bullet_it++;
	}
}

void Player::renderBullet(HDC hdc)
{
	p_Bullet_it = p_Bullet.begin();
	for (; p_Bullet_it != p_Bullet.end(); p_Bullet_it++)
	{
		if ((*p_Bullet_it).type == NORMAL)
			bulletImage->frameRender(hdc, (*p_Bullet_it).x -7, (*p_Bullet_it).y - 7);

		// 디버그용
		if (KEYMANAGER->isStayKeyDown(VK_LSHIFT))
			EllipseMakeCenter(hdc, (*p_Bullet_it).x, (*p_Bullet_it).y, (*p_Bullet_it).diameter, (*p_Bullet_it).diameter);

		if ((*p_Bullet_it).type == SUPPORT)
		{
			supportBulletImage->frameRender(hdc, (*p_Bullet_it).x - 8, (*p_Bullet_it).y - 8);

			// 디버그용
			if (KEYMANAGER->isStayKeyDown(VK_LSHIFT))
				EllipseMakeCenter(hdc, (*p_Bullet_it).x, (*p_Bullet_it).y, (*p_Bullet_it).diameter, (*p_Bullet_it).diameter);
		}
	}

	// 디버그용
	TCHAR szTemp[100] = { 0, };
	Rectangle(hdc, 530, 280, 750, 400);
	_stprintf_s(szTemp, sizeof(szTemp), TEXT("플레이어 총알 개수 : %d"), p_Bullet.size());
	TextOut(hdc, 540, 330, szTemp, _tcslen(szTemp));
}
