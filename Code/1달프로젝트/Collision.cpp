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
	}	

	// 플레이어 탄과 적 오브젝트
	if (PLAYER->getP_BulletSize() > 0 && ENEMYOBJECT->getE_ObjectSize() > 0)
	{
		p_Bullet_it = PLAYER->getP_Bullet_Begin();
		e_Object_it = ENEMYOBJECT->getE_Object_Begin();

		for (; e_Object_it != ENEMYOBJECT->getE_Object_End(); e_Object_it++)
		{
			for (; p_Bullet_it != PLAYER->getP_Bullet_End(); p_Bullet_it++)
			{
				if ((UTIL::getDistance((*p_Bullet_it).x, (*p_Bullet_it).y,
					(*e_Object_it).x, (*e_Object_it).y)) < ((*p_Bullet_it).diameter / 2 + (*e_Object_it).diameter / 2))
				{
					SOUNDMANAGER->Stop(TEXT("EnemyDamage"));
					SOUNDMANAGER->Play(TEXT("EnemyDamage"), 0.2f);
					(*p_Bullet_it).state = DEAD;
					//(*e_Object_it).hp -= (*p_Bullet_it).damage;
					//if ((*e_Object_it).hp <= 0)
						//(*e_Object_it).state = DEAD;
					(*e_Object_it).state = DEAD;
				}
					
			}
		}
	}

}

void Collision::effectRender(HDC hdc)
{
}
