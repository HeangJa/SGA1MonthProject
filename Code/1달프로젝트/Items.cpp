#include "Game.h"
#include "Items.h"


Items::Items()
{
}

Items::~Items()
{
}

HRESULT Items::init()
{
	blueItem = IMAGEMANAGER->addImage(TEXT("BlueItem"), TEXT("Image\\blueitem.bmp"),
		16, 16, true, RGB(255, 255, 255));

	redItem = IMAGEMANAGER->addImage(TEXT("RedItem"), TEXT("Image\\reditem.bmp"),
		16, 16, true, RGB(255, 255, 255));

	ITEMINFO itemInfo = { 0 };

	return S_OK;
}

void Items::release()
{
	itemList.clear();
}

void Items::createItem(int type, float x, float y)
{
	itemInfo.type = type;
	itemInfo.state = ALIVE;
	itemInfo.x = x;
	itemInfo.y = y;
	itemInfo.angle = 0.f;
	itemInfo.speed = 3.f;
	itemInfo.gravity = 0.05f;
	itemInfo.diameter = 24.f;

	itemList.push_back(itemInfo);
}

void Items::moveItem()
{
	itemList_it = itemList.begin();
	for (; itemList_it != itemList.end();)
	{
		// 플레이어가 특정 위치 위에 존재하면 속성변경
		if(PLAYER->getPlayerPosY() < PLAYER_GET_ALL_ITEM_POS_Y)
			(*itemList_it).state = TOPLAYER;

		// 탐지 거리 내에 플레이어가 있으면 속성변경
		if ((UTIL::getDistance((*itemList_it).x, (*itemList_it).y, PLAYER->getPlayerPosX(), PLAYER->getPlayerPosY())) < ITEM_SCAN_RANGE)
		{
			(*itemList_it).state = TOPLAYER;
		}
		
		// 탐지 거래 내 플레이어에게로 이동
		if ((*itemList_it).state == TOPLAYER)
		{
			(*itemList_it).speed = 8.f;
			(*itemList_it).x += (cosf(UTIL::getAngle((*itemList_it).x, (*itemList_it).y, PLAYER->getPlayerPosX(), PLAYER->getPlayerPosY())) * (*itemList_it).speed);
			(*itemList_it).y += (-sinf(UTIL::getAngle((*itemList_it).x, (*itemList_it).y, PLAYER->getPlayerPosX(), PLAYER->getPlayerPosY())) * (*itemList_it).speed);

			// 아이템을 먹으면
			if ((UTIL::getDistance((*itemList_it).x, (*itemList_it).y, PLAYER->getPlayerPosX(), PLAYER->getPlayerPosY())) < 30)
			{
				if ((*itemList_it).type == BLUE_ITEM)
				{
					PLAYER->setPlayerScore(PLAYER->getPlayerScore() + BLUE_ITEM_SCORE);
				}
				else if ((*itemList_it).type == RED_ITEM)
				{
					PLAYER->setPlayerScore(PLAYER->getPlayerScore() + RED_ITEM_SCORE);
					PLAYER->setPlayerPower(PLAYER->getPlayerPower() + RED_ITEM_POWER);
				}

				itemList_it = itemList.erase(itemList_it);
			}
			else
				++itemList_it;
		}

		// 플레이어에게로가 아니면 아래로 떨어짐
		else if ((*itemList_it).state == ALIVE)
		{
			(*itemList_it).speed -= (*itemList_it).gravity;
			(*itemList_it).y -= (*itemList_it).speed;

			if ((*itemList_it).y > F_DOWN)
			{
				itemList_it = itemList.erase(itemList_it);
			}
			else
				++itemList_it;
		}
	}
}

void Items::render(HDC hdc)
{
	itemList_it = itemList.begin();
	for (; itemList_it != itemList.end(); itemList_it++)
	{
		// 필드 내 있을 때
		if ((*itemList_it).x > F_LEFT && (*itemList_it).x < F_RIGHT &&
			(*itemList_it).y > F_UP && (*itemList_it).y < F_DOWN)
		{
			if ((*itemList_it).type == BLUE_ITEM)
			{
				blueItem->render(hdc, (*itemList_it).x - 8, (*itemList_it).y - 8);
			}

			else if ((*itemList_it).type == RED_ITEM)
			{
				redItem->render(hdc, (*itemList_it).x - 8, (*itemList_it).y - 8);
			}
		}		
	}

	// 디버그용
	TCHAR szTemp[100] = { 0, };
	_stprintf_s(szTemp, sizeof(szTemp), TEXT("아이템 개수 : %d"), itemList.size());
	TextOut(hdc, 540, 390, szTemp, _tcslen(szTemp));
}
