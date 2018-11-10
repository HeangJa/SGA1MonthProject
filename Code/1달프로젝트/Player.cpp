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

	// �÷��̾� ����
	playerImage->setFrameX(P_ANI_NORMAL);
	playerDiameter = 10;
	playerSpeed = NORMAL_SPEED;
	playerAlpha = OPAQUE_;
	isPlayerDead = false;
	isPlayerInvincible = false;
	playerInvincibleTimer = 0;
	playerScore = 0;
	playerLife = 10;
	playerPower = 39;

	// �÷��̾� ź ����
	loadBulletFile();	// ź ���� ���� �ҷ�����
	createBulletTimer = 0;
	createSupportBulletTimer = 0;

	// ȸ�� ��ȯ
	ZeroMemory(vertices, 3);
	fAnchorX = 0;
	fAnchorY = 0;
	fAngle = 0;
}

void Player::release()
{
	p_Bullet.clear();
}

void Player::update()
{
	// �÷��̾� �̵� �� ���
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

	// �÷��̾� ������(���� ��)
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
	

	// �÷��̾� ź
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
		
	// ź �̵�
	moveBullet();

	// �̹��� ȸ�� ����
	playerShiftImage->setX(playerImage->getX() - 13);
	playerShiftImage->setY(playerImage->getY() - 5);

	fAngle += 1;
	if (fAngle >= 360.0f)
		fAngle = 0.0f;

	rotate(fAngle);

	playerShiftMaskImage->setX(playerShiftImage->getX());
	playerShiftMaskImage->setY(playerShiftImage->getY());

	// �׾��� ��
	ifPlayerDead();

	// ��� Ÿ�̸� ����
	playerMotionTimer++;

	// �÷��̾� ��ǥ
	playerPosX = playerImage->getX() + 16;
	playerPosY = playerImage->getY() + 24;
}

void Player::render(HDC hdc)
{
	// ȸ����ȯ
	//PlgBlt(hdc, vertices, playerShiftImage->getMemDC(), 0, 0, 		
	//	playerShiftImage->getWidth(), playerShiftImage->getHeight(), NULL, vertices[0].x, vertices[0].y);
	
	// �÷��̾�
	playerImage->alphaRender(hdc, playerImage->getX(), playerImage->getY(),
		playerImage->getFrameX(), playerImage->getFrameY(), playerAlpha);

	// SHIFT���� ��
	if(KEYMANAGER->isStayKeyDown(VK_LSHIFT) || KEYMANAGER->isStayKeyDown(VK_RSHIFT))
		EllipseMakeCenter(hdc, playerPosX, playerPosY, playerDiameter, playerDiameter);

	// ������
	for (int i = 0; i < (int)(playerPower / 10); i++)
		supporter->frameRender(hdc, supporterPos[i].x, supporterPos[i].y);

	// ź
	renderBullet(hdc);
}

void Player::ifPlayerDead()
{
	// �׾��� �� init����
	if (isPlayerDead == true)
	{
		SOUNDMANAGER->Stop(TEXT("PlayerDead"));
		SOUNDMANAGER->Play(TEXT("PlayerDead"), 0.2f);
		playerLife -= 1;
		isPlayerDead = false;
		isPlayerInvincible = true;
		playerAlpha = TRANSLUCENT_;

		// ź ���� ����
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

	// ���� �ð�����
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

	// sin, cos�� ���ϱ�
	float s = sinf(theta);
	float c = cosf(theta);

	// ȸ�� �߽� ��ǥ(�̹��� �߾�)
	float centerX = playerShiftImage->getX() + (playerShiftImage->getWidth() / 2);
	float centerY = playerShiftImage->getY() + (playerShiftImage->getHeight() / 2);

	// ȸ�� ��ȯ
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
	SOUNDMANAGER->Play(TEXT("PlayerAttack"), 0.1f);

	// �⺻ ź1(�߽���)
	bullet.state = ALIVE;
	bullet.x = playerImage->getX();
	bullet.y = playerImage->getY();
	bullet.diameter = load_bullet[NORMAL].diameter;
	bullet.angle = PI / 2;
	bullet.speed = load_bullet[NORMAL].speed;;
	bullet.damage = load_bullet[NORMAL].damage;
	bullet.type = NORMAL;
	p_Bullet.push_back(bullet);

	// �⺻ ź2
	bullet.x = playerImage->getX() + 32;
	p_Bullet.push_back(bullet);

	if (createSupportBulletTimer % CREATESUPPORTBULLETDELAY == 0)
	{
		// ����Ʈ ź
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

void Player::moveBullet()
{
	p_Bullet_it = p_Bullet.begin();
	for (; p_Bullet_it != p_Bullet.end();)
	{
		// ����Ʈ ź�� ��
		
		// ȣ�ֱ��
		if (playerType == REIMU && (*p_Bullet_it).type == SUPPORT && BOSS->getBossState() == ALIVE)
		{
			(*p_Bullet_it).angle = UTIL::getAngle((*p_Bullet_it).x, (*p_Bullet_it).y,
				BOSS->getBossPosX(), BOSS->getBossPosY());
		}

		else if ((*p_Bullet_it).type == SUPPORT && ENEMYOBJECT->getE_ObjectSize() > 0)
		{
			e_Object_distance.clear();
			// �� ������Ʈ ���� ����
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

		// �� ��� ������ �����ų� �浹�� ��� ����
		if ((*p_Bullet_it).x < F_LEFT || (*p_Bullet_it).x > F_RIGHT ||
			(*p_Bullet_it).y < F_UP || (*p_Bullet_it).y > F_DOWN ||
			(*p_Bullet_it).state == DEAD)
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
	_stprintf_s(szTemp, sizeof(szTemp), TEXT("�÷��̾� �Ѿ� ���� : %d"), p_Bullet.size());
	TextOut(hdc, 540, 330, szTemp, _tcslen(szTemp));
#endif	// DEBUG_MODE
}