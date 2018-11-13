#include "Game.h"
#include "EnemyObject.h"
#include "Xml.h"


EnemyObject::EnemyObject()
{
}

EnemyObject::~EnemyObject()
{
	
}

void EnemyObject::init()
{
	// 적 오브젝트
	blueFairy = IMAGEMANAGER->addFrameImage(TEXT("BlueFairy"), TEXT("Image\\fairy.bmp"),
		608, 128, 19, 4, true, RGB(255, 255, 255));
	blueFairy->setFrameY(0);

	redFairy = IMAGEMANAGER->addFrameImage(TEXT("RedFairy"), TEXT("Image\\fairy.bmp"),
		608, 128, 19, 4, true, RGB(255, 255, 255));
	redFairy->setFrameY(1);

	greenFairy = IMAGEMANAGER->addFrameImage(TEXT("GreenFairy"), TEXT("Image\\fairy.bmp"),
		608, 128, 19, 4, true, RGB(255, 255, 255));
	greenFairy->setFrameY(2);

	bigFairy = IMAGEMANAGER->addFrameImage(TEXT("BigFairy"), TEXT("Image\\bigfairy.bmp"),
		698, 59, 11, 1, true, RGB(255, 255, 255));

	currentObjectNum = 0;
	enemyStayTimer = 0;
	createTime = 0.f;

	loadEnemyFile();

	// 적 불릿
	e_BulletImage = IMAGEMANAGER->addFrameImage(TEXT("E_Bullet"), TEXT("Image\\e_bullet.bmp"),
		258, 192, 8, 6, true, RGB(255, 255, 255));

	e_BulletImage2 = IMAGEMANAGER->addFrameImage(TEXT("E_Bullet2"), TEXT("Image\\e_bullet2.bmp"),
		256, 16, 16, 1, true, RGB(255, 255, 255));

	loadEnemyBulletFile();

}

void EnemyObject::release()
{
	e_Object.clear();
	e_Bullet.clear();
}

void EnemyObject::update(float ingameCurrentTime)
{
	createEnemy(ingameCurrentTime);
	moveEnemy(ingameCurrentTime);

	if (e_Object.size() > 0)
		createEnemyBullet(ingameCurrentTime);
	if(e_Bullet.size() > 0)
		moveEnemyBullet();
}

void EnemyObject::loadEnemyFile()
{
	int i = 0;

	XmlDocument* doc = new XmlDocument;
	XmlError err = doc->LoadFile(TEXT("DataBase\\EnemyObject.xml"));
	assert(err == Xml::XML_SUCCESS);

	XmlElement* EnemyObject = doc->FirstChildElement(TEXT("EnemyObject"));
	XmlElement* wave = EnemyObject->FirstChildElement();

	XmlAttribute* value;
	for (; wave != NULL; wave = wave->NextSiblingElement())
	{
		XmlElement* fairy = wave->FirstChildElement(TEXT("Fairy0"));
		for (; fairy != NULL; fairy = fairy->NextSiblingElement(), i++)
		{
			if (i == 6)
				i = 6;
			XmlElement* type = fairy->FirstChildElement();
			value = (XmlAttribute*)type->FirstAttribute();
			enemyObject[i].type = atoi(value->Value());

			XmlElement* state = type->NextSiblingElement();
			value = (XmlAttribute*)state->FirstAttribute();
			enemyObject[i].state = atoi(value->Value());

			XmlElement* createTime = state->NextSiblingElement();
			value = (XmlAttribute*)createTime->FirstAttribute();
			enemyObject[i].createTime = strtod(value->Value(), 0);

			XmlElement* x = createTime->NextSiblingElement();
			value = (XmlAttribute*)x->FirstAttribute();
			enemyObject[i].x = atoi(value->Value());

			XmlElement* y = x->NextSiblingElement();
			value = (XmlAttribute*)y->FirstAttribute();
			enemyObject[i].y = atoi(value->Value());

			XmlElement* diameter = y->NextSiblingElement();
			value = (XmlAttribute*)diameter->FirstAttribute();
			enemyObject[i].diameter = atoi(value->Value());

			XmlElement* angle = diameter->NextSiblingElement();
			value = (XmlAttribute*)angle->FirstAttribute();
			enemyObject[i].angle = strtod(value->Value(), 0);

			XmlElement* speed = angle->NextSiblingElement();
			value = (XmlAttribute*)speed->FirstAttribute();
			enemyObject[i].speed = strtod(value->Value(), 0);

			XmlElement* hp = speed->NextSiblingElement();
			value = (XmlAttribute*)hp->FirstAttribute();
			enemyObject[i].hp = atoi(value->Value());

			XmlElement* imageFrameX = hp->NextSiblingElement();
			value = (XmlAttribute*)imageFrameX->FirstAttribute();
			enemyObject[i].imageFrameX = atoi(value->Value());

			XmlElement* existingTime = imageFrameX->NextSiblingElement();
			value = (XmlAttribute*)existingTime->FirstAttribute();
			enemyObject[i].existingTime = strtod(value->Value(), 0);

			XmlElement* moveType = existingTime->NextSiblingElement();
			value = (XmlAttribute*)moveType->FirstAttribute();
			enemyObject[i].moveType = atoi(value->Value());

			XmlElement* moveTimer = moveType->NextSiblingElement();
			value = (XmlAttribute*)moveTimer->FirstAttribute();
			enemyObject[i].moveTimer = atoi(value->Value());

			XmlElement* bulletType = moveTimer->NextSiblingElement();
			value = (XmlAttribute*)bulletType->FirstAttribute();
			enemyObject[i].bulletType = atoi(value->Value());

			XmlElement* isFire = bulletType->NextSiblingElement();
			value = (XmlAttribute*)isFire->FirstAttribute();
			enemyObject[i].isFire = atoi(value->Value());

			XmlElement* bulletCount = isFire->NextSiblingElement();
			value = (XmlAttribute*)bulletCount->FirstAttribute();
			enemyObject[i].bulletCount = atoi(value->Value());

			XmlElement* bulletCountLimit = bulletCount->NextSiblingElement();
			value = (XmlAttribute*)bulletCountLimit->FirstAttribute();
			enemyObject[i].bulletCountLimit = atoi(value->Value());

			XmlElement* lastBulletFireTime = bulletCountLimit->NextSiblingElement();
			value = (XmlAttribute*)lastBulletFireTime->FirstAttribute();
			enemyObject[i].lastBulletFireTime = strtod(value->Value(), 0);

			XmlElement* nextBulletTermTime = lastBulletFireTime->NextSiblingElement();
			value = (XmlAttribute*)nextBulletTermTime->FirstAttribute();
			enemyObject[i].nextBulletTermTime = strtod(value->Value(), 0);

			XmlElement* reloadTime = nextBulletTermTime->NextSiblingElement();
			value = (XmlAttribute*)reloadTime->FirstAttribute();
			enemyObject[i].reloadTime = strtod(value->Value(), 0);

			if (enemyObject[i].type == BIGFAIRY)
			{
				XmlElement* firstAngle = reloadTime->NextSiblingElement();
				value = (XmlAttribute*)firstAngle->FirstAttribute();
				enemyObject[i].firstAngle = strtod(value->Value(), 0);
			}
		}
	}
}

void EnemyObject::createEnemy(float ingameCurrentTime)
{
	for (int i = 0; i < 100; i++)
	{
		if (enemyObject[i].createTime < ingameCurrentTime && enemyObject[i].state == NOTCREATE)
		{
			enemyObject[i].createTime = ingameCurrentTime;
			enemyObject[i].state = CREATE;
			e_Object.push_back(enemyObject[i]);
		}		
	}
}

void EnemyObject::moveEnemy(float ingameCurrentTime)
{
	if (e_Object.size() == 0)
		enemyStayTimer = 0;

	e_Object_it = e_Object.begin();
	for (; e_Object_it != e_Object.end();)
	{
		// 존재하는 시간 세팅
		(*e_Object_it).existingTime = ingameCurrentTime - (*e_Object_it).createTime;

		// 필드 내 존재 시 상태변경
		if ((*e_Object_it).x > F_LEFT && (*e_Object_it).x < F_RIGHT &&
			(*e_Object_it).y > F_UP && (*e_Object_it).y < F_DOWN && (*e_Object_it).state == CREATE)
		{
			(*e_Object_it).state = ALIVE;
		}

		// 움직임 타입에 따른 이동
		// 타입0 (Wave0)
		if ((*e_Object_it).moveType == 0)
		{
			if ((*e_Object_it).y > 150)
			{
				(*e_Object_it).speed = 0;
			}

			if ((*e_Object_it).existingTime > 8)
			{
				if((*e_Object_it).x < 280)
					(*e_Object_it).angle = PI * 3 / 4;
				else
					(*e_Object_it).angle = PI / 4;
				(*e_Object_it).speed = 2;
			}
			else
				(*e_Object_it).angle = PI * 3 / 2;
		}

		// 타입1 (Wave1 - 1, Wave3)
		if ((*e_Object_it).moveType == 1)
		{
			(*e_Object_it).angle = PI;
		}

		// 타입2 (Wave1 - 2, Wave3)
		if ((*e_Object_it).moveType == 2)
		{
			(*e_Object_it).angle = 0;
		}

		// 타입3 (Wave2 - 1)
		if ((*e_Object_it).moveType == 3)
		{
			if ((*e_Object_it).y > 150)
				(*e_Object_it).angle += 0.02f;
			else
				(*e_Object_it).angle = PI * 3 / 2;

			if ((*e_Object_it).angle > 2 * PI)
				(*e_Object_it).angle = 2 * PI;
		}

		// 타입4 (Wave2 - 2)
		if ((*e_Object_it).moveType == 4)
		{
			if ((*e_Object_it).y > 150)
				(*e_Object_it).angle -= 0.02f;
			else
				(*e_Object_it).angle = PI * 3 / 2;

			if ((*e_Object_it).angle < PI)
				(*e_Object_it).angle = PI;
		}

		// 타입5 (Wave2 - 3, Wave3)
		if ((*e_Object_it).moveType == 5)
		{
			if ((*e_Object_it).y >= 200)
			{
				(*e_Object_it).y = 200;
			}	
			else
				(*e_Object_it).angle = PI * 3 / 2;

			if((*e_Object_it).existingTime > 8)
				(*e_Object_it).angle = PI / 2;
		}

		// 타입6 (Wave3)
		if ((*e_Object_it).moveType == 6)
		{
			if ((*e_Object_it).y >= 150)
			{
				(*e_Object_it).y = 150;
			}
			else
				(*e_Object_it).angle = PI * 3 / 2;

			if ((*e_Object_it).existingTime > 8)
				(*e_Object_it).angle = PI / 2;
		}

		// 이동
		(*e_Object_it).x += (cosf((*e_Object_it).angle) * (*e_Object_it).speed);
		(*e_Object_it).y += (-sinf((*e_Object_it).angle) * (*e_Object_it).speed);

		// 각도에 따른 애니메이션
		// 왼쪽
		if ((*e_Object_it).angle > (PI / 2) && (*e_Object_it).angle < (3 * PI / 2)
			&& (*e_Object_it).speed > 0)
		{
			if ((*e_Object_it).type < 3)
			{
				if (!((*e_Object_it).imageFrameX >= 12 && (*e_Object_it).imageFrameX <= 16))
					(*e_Object_it).imageFrameX = 12;

				if ((*e_Object_it).moveTimer == MOTION_DELAY)
				{
					(*e_Object_it).moveTimer = 0;
					(*e_Object_it).imageFrameX++;

					if ((*e_Object_it).imageFrameX == 17)
						(*e_Object_it).imageFrameX = 12;
				}

				(*e_Object_it).moveTimer++;
			}

			else if ((*e_Object_it).type == 3)
			{
				if (!((*e_Object_it).imageFrameX >= 8 && (*e_Object_it).imageFrameX <= 10))
					(*e_Object_it).imageFrameX = 8;

				if ((*e_Object_it).moveTimer == MOTION_DELAY * 2)
				{
					(*e_Object_it).moveTimer = 0;
					(*e_Object_it).imageFrameX++;

					if ((*e_Object_it).imageFrameX == 11)
						(*e_Object_it).imageFrameX = 8;
				}

				(*e_Object_it).moveTimer++;
			}
		}

		// 오른쪽
		else if (!((*e_Object_it).angle > (PI / 2) && (*e_Object_it).angle < (3 * PI / 2))
			&& (*e_Object_it).speed > 0)
		{
			if ((*e_Object_it).type < 3)
			{
				if (!((*e_Object_it).imageFrameX >= 7 && (*e_Object_it).imageFrameX <= 11))
					(*e_Object_it).imageFrameX = 7;

				if ((*e_Object_it).moveTimer == MOTION_DELAY)
				{
					(*e_Object_it).moveTimer = 0;
					(*e_Object_it).imageFrameX++;

					if ((*e_Object_it).imageFrameX == 12)
						(*e_Object_it).imageFrameX = 7;
				}

				(*e_Object_it).moveTimer++;
			}

			else if ((*e_Object_it).type == 3)
			{
				if (!((*e_Object_it).imageFrameX >= 5 && (*e_Object_it).imageFrameX <= 7))
					(*e_Object_it).imageFrameX = 5;

				if ((*e_Object_it).moveTimer == MOTION_DELAY * 2)
				{
					(*e_Object_it).moveTimer = 0;
					(*e_Object_it).imageFrameX++;

					if ((*e_Object_it).imageFrameX == 8)
						(*e_Object_it).imageFrameX = 5;
				}

				(*e_Object_it).moveTimer++;
			}
		}

		// 좌우 이동 아닐 때
		else
		{
			if ((*e_Object_it).type < 3)
			{
				if (!((*e_Object_it).imageFrameX >= 0 && (*e_Object_it).imageFrameX <= 4))
					(*e_Object_it).imageFrameX = 0;

				if ((*e_Object_it).moveTimer == MOTION_DELAY)
				{
					(*e_Object_it).moveTimer = 0;
					(*e_Object_it).imageFrameX++;

					if ((*e_Object_it).imageFrameX == 5)
						(*e_Object_it).imageFrameX = 0;
				}

				(*e_Object_it).moveTimer++;
			}

			else if ((*e_Object_it).type == 3)
			{
				if (!((*e_Object_it).imageFrameX >= 0 && (*e_Object_it).imageFrameX <= 4))
					(*e_Object_it).imageFrameX = 0;

				if ((*e_Object_it).moveTimer == MOTION_DELAY * 2)
				{
					(*e_Object_it).moveTimer = 0;
					(*e_Object_it).imageFrameX++;

					if ((*e_Object_it).imageFrameX == 5)
						(*e_Object_it).imageFrameX = 0;
				}

				(*e_Object_it).moveTimer++;
			}
		}

		// 필드 밖으로 이동 시 or 죽었을 시 제거
		if ((!((*e_Object_it).x > F_LEFT && (*e_Object_it).x < F_RIGHT &&
			(*e_Object_it).y > F_UP && (*e_Object_it).y < F_DOWN) && (*e_Object_it).state == ALIVE) ||
			(*e_Object_it).state == DEAD)
		{
			// 아이템 생성
			if ((*e_Object_it).state == DEAD)
			{
				SOUNDMANAGER->Play(TEXT("EnemyDead"), 0.1f);

				if((*e_Object_it).type == BLUEFAIRY || (*e_Object_it).type == REDFAIRY)
					ITEMS->createItem((*e_Object_it).type, (*e_Object_it).x, (*e_Object_it).y);
			}				

			// 제거
			e_Object_it = e_Object.erase(e_Object_it);
		}
		else
			++e_Object_it;
	}
}

void EnemyObject::loadEnemyBulletFile()
{
	int i = 0;

	XmlDocument* doc = new XmlDocument;
	XmlError err = doc->LoadFile(TEXT("DataBase\\EnemyBullet.xml"));
	assert(err == Xml::XML_SUCCESS);

	XmlElement* EnemyObject = doc->FirstChildElement(TEXT("EnemyBullet"));
	XmlElement* Type = EnemyObject->FirstChildElement(TEXT("Type0"));

	XmlAttribute* value;

	for (; Type != NULL; Type = Type->NextSiblingElement(), i++)
	{
		XmlElement* type = Type->FirstChildElement();
		value = (XmlAttribute*)type->FirstAttribute();
		enemyBullet[i].type = atoi(value->Value());

		XmlElement* state = type->NextSiblingElement();
		value = (XmlAttribute*)state->FirstAttribute();
		enemyBullet[i].state = atoi(value->Value());

		XmlElement* x = state->NextSiblingElement();
		value = (XmlAttribute*)x->FirstAttribute();
		enemyBullet[i].x = atoi(value->Value());

		XmlElement* y = x->NextSiblingElement();
		value = (XmlAttribute*)y->FirstAttribute();
		enemyBullet[i].y = atoi(value->Value());

		XmlElement* diameter = y->NextSiblingElement();
		value = (XmlAttribute*)diameter->FirstAttribute();
		enemyBullet[i].diameter = atoi(value->Value());

		XmlElement* angle = diameter->NextSiblingElement();
		value = (XmlAttribute*)angle->FirstAttribute();
		enemyBullet[i].angle = strtod(value->Value(), 0);

		XmlElement* speed = angle->NextSiblingElement();
		value = (XmlAttribute*)speed->FirstAttribute();
		enemyBullet[i].speed = strtod(value->Value(), 0);

		XmlElement* imageFrameX = speed->NextSiblingElement();
		value = (XmlAttribute*)imageFrameX->FirstAttribute();
		enemyBullet[i].imageFrameX = atoi(value->Value());

		XmlElement* imageFrameY = imageFrameX->NextSiblingElement();
		value = (XmlAttribute*)imageFrameY->FirstAttribute();
		enemyBullet[i].imageFrameY = atoi(value->Value());
	}
}

void EnemyObject::createEnemyBullet(float ingameCurrentTime)
{
	e_Object_it = e_Object.begin();
	if ((*e_Object_it).state == ALIVE)
	{
		for (; e_Object_it != e_Object.end(); e_Object_it++)
		{
			if ((*e_Object_it).existingTime > FIRST_BULLET_TIME_AFTER_CREATE
				&& (*e_Object_it).isFire == FALSE)
			{
				(*e_Object_it).isFire = TRUE;
				
				// 큰 요정일 때
				if ((*e_Object_it).type == BIGFAIRY)
				{	
					if ((*e_Object_it).bulletCount == 0)
					{
						(*e_Object_it).firstAngle = UTIL::getAngle((*e_Object_it).x, (*e_Object_it).y,
							PLAYER->getPlayerPosX(), PLAYER->getPlayerPosY());
						enemyBullet[(*e_Object_it).bulletType].x = (*e_Object_it).x + cosf((*e_Object_it).firstAngle) * CREATE_ENEMY_BULLET_DISTANCE;
						enemyBullet[(*e_Object_it).bulletType].y = (*e_Object_it).y + (-sinf((*e_Object_it).firstAngle)) * CREATE_ENEMY_BULLET_DISTANCE;

						enemyBullet[(*e_Object_it).bulletType].angle = UTIL::getAngle(enemyBullet[(*e_Object_it).bulletType].x, enemyBullet[(*e_Object_it).bulletType].y,
							PLAYER->getPlayerPosX(), PLAYER->getPlayerPosY());
						e_Bullet.push_back(enemyBullet[(*e_Object_it).bulletType]);
						SOUNDMANAGER->Stop(TEXT("EnemyAttack"));
						SOUNDMANAGER->Play(TEXT("EnemyAttack"), 0.1f);
					}
					else if ((*e_Object_it).bulletCount == 1)
					{
						enemyBullet[(*e_Object_it).bulletType].x = (*e_Object_it).x + (cosf((*e_Object_it).firstAngle - PI / 40) * CREATE_ENEMY_BULLET_DISTANCE);
						enemyBullet[(*e_Object_it).bulletType].y = (*e_Object_it).y + ((-sinf((*e_Object_it).firstAngle - PI / 40))  * CREATE_ENEMY_BULLET_DISTANCE);
						enemyBullet[(*e_Object_it).bulletType].angle = (*e_Object_it).firstAngle - (PI / 40);
						e_Bullet.push_back(enemyBullet[(*e_Object_it).bulletType]);
						SOUNDMANAGER->Stop(TEXT("EnemyAttack"));
						SOUNDMANAGER->Play(TEXT("EnemyAttack"), 0.1f);

						enemyBullet[(*e_Object_it).bulletType].x = (*e_Object_it).x + (cosf((*e_Object_it).firstAngle + PI / 40) * CREATE_ENEMY_BULLET_DISTANCE);
						enemyBullet[(*e_Object_it).bulletType].y = (*e_Object_it).y + ((-sinf((*e_Object_it).firstAngle + PI / 40)) * CREATE_ENEMY_BULLET_DISTANCE);
						enemyBullet[(*e_Object_it).bulletType].angle = (*e_Object_it).firstAngle + (PI / 40);
						e_Bullet.push_back(enemyBullet[(*e_Object_it).bulletType]);
						SOUNDMANAGER->Stop(TEXT("EnemyAttack"));
						SOUNDMANAGER->Play(TEXT("EnemyAttack"), 0.1f);
					}
					else if ((*e_Object_it).bulletCount == 2)
					{
						enemyBullet[(*e_Object_it).bulletType].x = (*e_Object_it).x + cosf((*e_Object_it).firstAngle) * CREATE_ENEMY_BULLET_DISTANCE;
						enemyBullet[(*e_Object_it).bulletType].y = (*e_Object_it).y + (-sinf((*e_Object_it).firstAngle)) * CREATE_ENEMY_BULLET_DISTANCE;
						enemyBullet[(*e_Object_it).bulletType].angle = (*e_Object_it).firstAngle;
						e_Bullet.push_back(enemyBullet[(*e_Object_it).bulletType]);
						SOUNDMANAGER->Stop(TEXT("EnemyAttack"));
						SOUNDMANAGER->Play(TEXT("EnemyAttack"), 0.1f);

						enemyBullet[(*e_Object_it).bulletType].x = (*e_Object_it).x + (cosf((*e_Object_it).firstAngle - PI / 20) * CREATE_ENEMY_BULLET_DISTANCE);
						enemyBullet[(*e_Object_it).bulletType].y = (*e_Object_it).y + ((-sinf((*e_Object_it).firstAngle - PI / 20))  * CREATE_ENEMY_BULLET_DISTANCE);
						enemyBullet[(*e_Object_it).bulletType].angle = (*e_Object_it).firstAngle - (PI / 20);
						e_Bullet.push_back(enemyBullet[(*e_Object_it).bulletType]);
						SOUNDMANAGER->Stop(TEXT("EnemyAttack"));
						SOUNDMANAGER->Play(TEXT("EnemyAttack"), 0.1f);

						enemyBullet[(*e_Object_it).bulletType].x = (*e_Object_it).x + (cosf((*e_Object_it).firstAngle + PI / 20) * CREATE_ENEMY_BULLET_DISTANCE);
						enemyBullet[(*e_Object_it).bulletType].y = (*e_Object_it).y + ((-sinf((*e_Object_it).firstAngle + PI / 20)) * CREATE_ENEMY_BULLET_DISTANCE);
						enemyBullet[(*e_Object_it).bulletType].angle = (*e_Object_it).firstAngle + (PI / 20);
						e_Bullet.push_back(enemyBullet[(*e_Object_it).bulletType]);
						SOUNDMANAGER->Stop(TEXT("EnemyAttack"));
						SOUNDMANAGER->Play(TEXT("EnemyAttack"), 0.1f);
					}
				}
				else // 작은 요정일 때
				{
					enemyBullet[(*e_Object_it).bulletType].x = (*e_Object_it).x;
					enemyBullet[(*e_Object_it).bulletType].y = (*e_Object_it).y + CREATE_ENEMY_BULLET_DISTANCE;
					enemyBullet[(*e_Object_it).bulletType].angle = UTIL::getAngle(enemyBullet[(*e_Object_it).bulletType].x, enemyBullet[(*e_Object_it).bulletType].y,
						PLAYER->getPlayerPosX(), PLAYER->getPlayerPosY());
					e_Bullet.push_back(enemyBullet[(*e_Object_it).bulletType]);
					SOUNDMANAGER->Stop(TEXT("EnemyAttack"));
					SOUNDMANAGER->Play(TEXT("EnemyAttack"), 0.1f);
				}				
		
				(*e_Object_it).lastBulletFireTime = ingameCurrentTime;
				(*e_Object_it).bulletCount++;
			}

			if ((*e_Object_it).isFire == TRUE)
			{
				if ((*e_Object_it).bulletCount == (*e_Object_it).bulletCountLimit)
				{
					(*e_Object_it).bulletCount = 0;
				}

				if (!((*e_Object_it).nextBulletTermTime == 0) &&
					((ingameCurrentTime - (*e_Object_it).lastBulletFireTime) > (*e_Object_it).nextBulletTermTime) &&
					(*e_Object_it).bulletCount != 0)
				{
					(*e_Object_it).isFire = FALSE;
				}
				
				if ((*e_Object_it).reloadTime != 0 &&
					((ingameCurrentTime - (*e_Object_it).lastBulletFireTime) > (*e_Object_it).reloadTime))
					(*e_Object_it).isFire = FALSE;
			}
		}
	}	
}

void EnemyObject::moveEnemyBullet()
{
	e_Bullet_it = e_Bullet.begin();
	for (; e_Bullet_it != e_Bullet.end();)
	{
		if ((*e_Bullet_it).type == ONCE_SHOT || (*e_Bullet_it).type == INTERVAL_SHOT ||
			(*e_Bullet_it).type == RAPID_SHOT)
		{
			(*e_Bullet_it).x += (cosf((*e_Bullet_it).angle) * (*e_Bullet_it).speed);
			(*e_Bullet_it).y += (-sinf((*e_Bullet_it).angle) * (*e_Bullet_it).speed);
		}

		// 맵 경계 밖으로 나갔거나 충돌한 경우 제거
		if ((*e_Bullet_it).x < F_LEFT || (*e_Bullet_it).x > F_RIGHT ||
			(*e_Bullet_it).y < F_UP || (*e_Bullet_it).y > F_DOWN ||
			(*e_Bullet_it).state == DEAD)
			e_Bullet_it = e_Bullet.erase(e_Bullet_it);
		else
			e_Bullet_it++;
	}
}

void EnemyObject::render(HDC hdc)
{
	// 적 오브젝트
	TCHAR szTemp[100] = { 0, };
	int i = 0;
	e_Object_it = e_Object.begin();
	for (; e_Object_it != e_Object.end(); e_Object_it++, i++)
	{
		if ((*e_Object_it).state == ALIVE)
		{
			if ((*e_Object_it).type == BLUEFAIRY)
			{
				blueFairy->frameRender(hdc, (*e_Object_it).x - 16, (*e_Object_it).y - 16, (*e_Object_it).imageFrameX, blueFairy->getFrameY());
			}

			if ((*e_Object_it).type == REDFAIRY)
			{
				redFairy->frameRender(hdc, (*e_Object_it).x - 16, (*e_Object_it).y - 16, (*e_Object_it).imageFrameX, redFairy->getFrameY());
			}

			if ((*e_Object_it).type == GREENFAIRY)
			{
				greenFairy->frameRender(hdc, (*e_Object_it).x - 16, (*e_Object_it).y - 16, (*e_Object_it).imageFrameX, greenFairy->getFrameY());
			}

			if ((*e_Object_it).type == BIGFAIRY)
			{
				bigFairy->frameRender(hdc, (*e_Object_it).x - 32, (*e_Object_it).y - 30, (*e_Object_it).imageFrameX, bigFairy->getFrameY());				
			}

#if defined(DEBUG_MODE)
			if (KEYMANAGER->isStayKeyDown(VK_LSHIFT))
				EllipseMakeCenter(hdc, (*e_Object_it).x, (*e_Object_it).y, (*e_Object_it).diameter, (*e_Object_it).diameter);
#endif	// DEBUG_MODE
		}
	}

	// 적 불릿
	e_Bullet_it = e_Bullet.begin();
	for (; e_Bullet_it != e_Bullet.end(); e_Bullet_it++, i++)
	{
		if ((*e_Bullet_it).type == ONCE_SHOT || (*e_Bullet_it).type == INTERVAL_SHOT ||
			(*e_Bullet_it).type == RAPID_SHOT)
		{
			e_BulletImage2->frameRender(hdc, (*e_Bullet_it).x - 8, (*e_Bullet_it).y - 8, (*e_Bullet_it).imageFrameX, (*e_Bullet_it).imageFrameY);

#if defined(DEBUG_MODE)
			if (KEYMANAGER->isStayKeyDown(VK_LSHIFT))
				EllipseMakeCenter(hdc, (*e_Bullet_it).x, (*e_Bullet_it).y, (*e_Bullet_it).diameter, (*e_Bullet_it).diameter);
#endif	// DEBUG_MODE
		}
	}

#if defined(DEBUG_MODE)
	_stprintf_s(szTemp, sizeof(szTemp), TEXT("적 오브젝트 개수 : %d"), e_Object.size());
	TextOut(hdc, 540, 360, szTemp, _tcslen(szTemp));
	_stprintf_s(szTemp, sizeof(szTemp), TEXT("적 불릿 개수: %d"), e_Bullet.size());
	TextOut(hdc, 540, 420, szTemp, _tcslen(szTemp));
	_stprintf_s(szTemp, sizeof(szTemp), TEXT("이미지개수: %d"), IMAGEMANAGER->getSize());
	TextOut(hdc, 540, 500, szTemp, _tcslen(szTemp));
#endif	// DEBUG_MODE
}
