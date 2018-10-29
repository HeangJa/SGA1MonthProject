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

	loadEnemyFile();
}

void EnemyObject::loadEnemyFile()
{
	int i = 0;

	XmlDocument* doc = new XmlDocument;
	XmlError err = doc->LoadFile(TEXT("EnemyObject.xml"));
	assert(err == Xml::XML_SUCCESS);

	XmlElement* EnemyObject = doc->FirstChildElement(TEXT("EnemyObject"));
	XmlElement* wave = EnemyObject->FirstChildElement(TEXT("Wave1"));
	XmlElement* fairy = wave->FirstChildElement(TEXT("Fairy0"));

	XmlAttribute* value;

	for (; fairy != NULL; fairy = fairy->NextSiblingElement(), i++)
	{
		XmlElement* type = fairy->FirstChildElement();
		value = (XmlAttribute*)type->FirstAttribute();
		enemyObject[i].type = atoi(value->Value());

		XmlElement* state = type->NextSiblingElement();
		value = (XmlAttribute*)state->FirstAttribute();
		enemyObject[i].state = atoi(value->Value());

		XmlElement* appearanceTime = state->NextSiblingElement();
		value = (XmlAttribute*)appearanceTime->FirstAttribute();
		enemyObject[i].appearanceTime = strtod(value->Value(), 0);

		XmlElement* x = appearanceTime->NextSiblingElement();
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

		XmlElement* hp = angle->NextSiblingElement();
		value = (XmlAttribute*)hp->FirstAttribute();
		enemyObject[i].hp = atoi(value->Value());

		XmlElement* imageFrameX = hp->NextSiblingElement();
		value = (XmlAttribute*)imageFrameX->FirstAttribute();
		enemyObject[i].imageFrameX = atoi(value->Value());

		XmlElement* moveType = imageFrameX->NextSiblingElement();
		value = (XmlAttribute*)moveType->FirstAttribute();
		enemyObject[i].moveType = atoi(value->Value());

		XmlElement* moveTimer = moveType->NextSiblingElement();
		value = (XmlAttribute*)moveTimer->FirstAttribute();
		enemyObject[i].moveTimer = atoi(value->Value());

		XmlElement* bulletType = moveTimer->NextSiblingElement();
		value = (XmlAttribute*)bulletType->FirstAttribute();
		enemyObject[i].bulletType = atoi(value->Value());
	}
}

void EnemyObject::createEnemy(float ingameTime)
{
	for (int i = 0; i < 8; i++)
	{
		if (enemyObject[i].appearanceTime < ingameTime && enemyObject[i].state == NOTCREATE)
		{
			e_Object.push_back(enemyObject[i]);
			enemyObject[i].state = CREATE;
		}		
	}
}

void EnemyObject::moveEnemy()
{
	e_Object_it = e_Object.begin();
	for (; e_Object_it != e_Object.end();)
	{
		// 움직임 타입에 따른 이동
		if ((*e_Object_it).moveType == 0)
		{
			if ((*e_Object_it).y > 150)
			{
				(*e_Object_it).speed = 0;
				if(!(enemyStayTimer == 1000))
					enemyStayTimer++;
			}

			if (enemyStayTimer == 1000)
			{
				if((*e_Object_it).x < 280)
					(*e_Object_it).angle = PI * 3 / 4;
				else
					(*e_Object_it).angle = PI / 4;
				(*e_Object_it).speed = 2;
			}
			else
				(*e_Object_it).angle = PI * 3 / 2;
			
			(*e_Object_it).x += (cosf((*e_Object_it).angle) * (*e_Object_it).speed);
			(*e_Object_it).y += (-sinf((*e_Object_it).angle) * (*e_Object_it).speed);
		}

		// 필드 내 존재 시 상태변경
		if ((*e_Object_it).x > F_LEFT && (*e_Object_it).x < F_RIGHT &&
			(*e_Object_it).y > F_UP && (*e_Object_it).y < F_DOWN)
		{
			(*e_Object_it).state = ALIVE;
		}

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

				if ((*e_Object_it).moveTimer == MOTION_DELAY)
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
		else if ( !((*e_Object_it).angle > (PI / 2) && (*e_Object_it).angle < (3 * PI / 2))
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

				if ((*e_Object_it).moveTimer == MOTION_DELAY)
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

				if ((*e_Object_it).moveTimer == MOTION_DELAY)
				{
					(*e_Object_it).moveTimer = 0;
					(*e_Object_it).imageFrameX++;

					if ((*e_Object_it).imageFrameX == 5)
						(*e_Object_it).imageFrameX = 0;
				}

				(*e_Object_it).moveTimer++;
			}
		}

		// 필드 밖으로 이동 시 제거
		if (!((*e_Object_it).x > F_LEFT && (*e_Object_it).x < F_RIGHT &&
			(*e_Object_it).y > F_UP && (*e_Object_it).y < F_DOWN) && (*e_Object_it).state == ALIVE)
			e_Object_it = e_Object.erase(e_Object_it);
		else
			++e_Object_it;
	}
}

void EnemyObject::render(HDC hdc)
{
	TCHAR szTemp[100] = { 0, };
	int i = 0;
	e_Object_it = e_Object.begin();
	for (; e_Object_it != e_Object.end(); e_Object_it++, i++)
	{
		_stprintf_s(szTemp, sizeof(szTemp), TEXT("%d"), (*e_Object_it).imageFrameX);
		TextOut(hdc, 540 + i*10, 390, szTemp, _tcslen(szTemp));

		if ((*e_Object_it).state == ALIVE)
		{
			if ((*e_Object_it).type == BLUEFAIRY)
			{
				blueFairy->frameRender(hdc, (*e_Object_it).x - 16, (*e_Object_it).y - 16, (*e_Object_it).imageFrameX, blueFairy->getFrameY());

				// 디버그용
				if (KEYMANAGER->isStayKeyDown(VK_LSHIFT))
					EllipseMakeCenter(hdc, (*e_Object_it).x, (*e_Object_it).y, (*e_Object_it).diameter, (*e_Object_it).diameter);
			}

			if ((*e_Object_it).type == REDFAIRY)
			{
				redFairy->frameRender(hdc, (*e_Object_it).x - 16, (*e_Object_it).y - 16, (*e_Object_it).imageFrameX, redFairy->getFrameY());

				// 디버그용
				if (KEYMANAGER->isStayKeyDown(VK_LSHIFT))
					EllipseMakeCenter(hdc, (*e_Object_it).x, (*e_Object_it).y, (*e_Object_it).diameter, (*e_Object_it).diameter);
			}

			if ((*e_Object_it).type == GREENFAIRY)
			{
				greenFairy->frameRender(hdc, (*e_Object_it).x - 16, (*e_Object_it).y - 16, (*e_Object_it).imageFrameX, greenFairy->getFrameY());

				// 디버그용
				if (KEYMANAGER->isStayKeyDown(VK_LSHIFT))
					EllipseMakeCenter(hdc, (*e_Object_it).x, (*e_Object_it).y, (*e_Object_it).diameter, (*e_Object_it).diameter);
			}

			if ((*e_Object_it).type == BIGFAIRY)
			{
				bigFairy->frameRender(hdc, (*e_Object_it).x - 32, (*e_Object_it).y - 30, (*e_Object_it).imageFrameX, greenFairy->getFrameY());

				// 디버그용
				if (KEYMANAGER->isStayKeyDown(VK_LSHIFT))
					EllipseMakeCenter(hdc, (*e_Object_it).x, (*e_Object_it).y, (*e_Object_it).diameter, (*e_Object_it).diameter);
			}
		}
	}

	// 디버그용
	_stprintf_s(szTemp, sizeof(szTemp), TEXT("적 오브젝트 개수 : %d"), e_Object.size());
	TextOut(hdc, 540, 360, szTemp, _tcslen(szTemp));
}
