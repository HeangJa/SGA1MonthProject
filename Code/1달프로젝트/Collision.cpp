#include "Game.h"
#include "Collision.h"


Collision::Collision()
{
}

Collision::~Collision()
{
}

void Collision::init()
{
	collisionEffectImage = IMAGEMANAGER->addFrameImage(TEXT("CollisionEffect"), TEXT("Image\\collisioneffect.bmp"),
		52, 26, 2, 1, true, RGB(255, 255, 255));
}

void Collision::collisionCheck()
{
	if (PLAYER->getIsPlayerInvincible() == false)
	{
		// 플레이어와 적 오브젝트
		if (ENEMYOBJECT->getE_ObjectSize() > 0)
		{
			e_Object_it = ENEMYOBJECT->getE_Object_Begin();
			for (; e_Object_it != ENEMYOBJECT->getE_Object_End(); e_Object_it++)
			{
				if ((UTIL::getDistance(PLAYER->getPlayerPosX(), PLAYER->getPlayerPosY(),
					(*e_Object_it).x, (*e_Object_it).y)) < (PLAYER->getPlayerDiameter() / 2 + (*e_Object_it).diameter / 2))
				{
					PLAYER->setIsPlayerDead(true);
				}
			}
		}

		// 플레이어와 적 탄
		if (ENEMYOBJECT->getE_BulletSize() > 0)
		{
			e_Bullet_it = ENEMYOBJECT->getE_Bullet_Begin();
			for (; e_Bullet_it != ENEMYOBJECT->getE_Bullet_End(); e_Bullet_it++)
			{
				if ((UTIL::getDistance(PLAYER->getPlayerPosX(), PLAYER->getPlayerPosY(),
					(*e_Bullet_it).x, (*e_Bullet_it).y)) < (PLAYER->getPlayerDiameter() / 2 + (*e_Bullet_it).diameter / 2))
				{
					PLAYER->setIsPlayerDead(true);
				}
			}
		}

		// 플레이어와 보스 탄
		if (BOSS->getB_BulletSize() > 0)
		{
			b_Bullet_it = BOSS->getB_Bullet_Begin();
			for (; b_Bullet_it != BOSS->getB_Bullet_End(); b_Bullet_it++)
			{
				if ((UTIL::getDistance(PLAYER->getPlayerPosX(), PLAYER->getPlayerPosY(),
					(*b_Bullet_it).x, (*b_Bullet_it).y)) < ((PLAYER->getPlayerDiameter() / 2 + (*b_Bullet_it).diameter / 2) - 2))
				{
					PLAYER->setIsPlayerDead(true);
				}
			}
		}
	}

	// 플레이어 탄과 적 오브젝트
	if (PLAYER->getP_BulletSize() > 0 && ENEMYOBJECT->getE_ObjectSize() > 0)
	{
		p_Bullet_it = PLAYER->getP_Bullet_Begin();
		for (; p_Bullet_it != PLAYER->getP_Bullet_End(); p_Bullet_it++)
		{
			e_Object_it = ENEMYOBJECT->getE_Object_Begin();
			for (; e_Object_it != ENEMYOBJECT->getE_Object_End(); e_Object_it++)
			{
				if ((UTIL::getDistance((*p_Bullet_it).x, (*p_Bullet_it).y,
					(*e_Object_it).x, (*e_Object_it).y)) < (((*p_Bullet_it).diameter / 2) + ((*e_Object_it).diameter / 2)))
				{
					SOUNDMANAGER->Stop(TEXT("EnemyDamage"));
					SOUNDMANAGER->Play(TEXT("EnemyDamage"), 0.05f);
					PLAYER->setPlayerScore(PLAYER->getPlayerScore() + 10);
					(*p_Bullet_it).state = DEAD;
					(*e_Object_it).hp -= (*p_Bullet_it).damage;
					if ((*e_Object_it).hp <= 0)
					{
						if((*e_Object_it).type == 3)
							PLAYER->setPlayerScore(PLAYER->getPlayerScore() + 100);
						else
							PLAYER->setPlayerScore(PLAYER->getPlayerScore() + 50);

						(*e_Object_it).state = DEAD;
					}
						

					/* 충돌 디버그용 텍스트 출력
					string a = "  플레이어 탄 순서 : ";
					string b = to_string(i);
					string c = " 적 오브젝트 : ";
					string d = to_string((*e_Object_it).type);

					string e = a + b +c +d;
					OutputDebugString(e.c_str());*/
				}
			}
		}
	}

	// 플레이어 탄과 보스
	if (PLAYER->getP_BulletSize() > 0 && BOSS->getBossState() == ALIVE && BOSS->getBossPattern() != APPEAR)
	{
		p_Bullet_it = PLAYER->getP_Bullet_Begin();
		for (; p_Bullet_it != PLAYER->getP_Bullet_End(); p_Bullet_it++)
		{
			if ((UTIL::getDistance((*p_Bullet_it).x, (*p_Bullet_it).y,
				BOSS->getBossPosX(), BOSS->getBossPosY()) < (((*p_Bullet_it).diameter / 2) + (BOSS->getBossDiameter() / 2))))
			{
				SOUNDMANAGER->Stop(TEXT("EnemyDamage"));
				SOUNDMANAGER->Play(TEXT("EnemyDamage"), 0.05f);
				PLAYER->setPlayerScore(PLAYER->getPlayerScore() + 10);
				(*p_Bullet_it).state = DEAD;
				BOSS->setBossHp(BOSS->getBossHp() - (*p_Bullet_it).damage);
			}
		}
	}

}

void Collision::effectRender(HDC hdc)
{
}
