#pragma once
#include "singletonBase.h"

class Collision : public singletonBase<Collision>
{
private:
	Image * collisionEffectImage;

	typedef struct tageffectinfo
	{
		float x, y;
		int   showEffectTimer;
	}EFFECT;

	EFFECT	collisionEffect;

	typedef list<POINT>					collisionEffectInfo;
	typedef list<POINT>::iterator		collisionEffectInfo_it;

	collisionEffectInfo		c_Effect;
	collisionEffectInfo_it	c_Effect_it;

	// 다른 클래스 iterator 저장용
	typedef struct tagbulletinfo
	{
		int   state;
		float x, y;
		float diameter;
		float angle;
		float speed;
		int	  damage;
		int	  type;
	}P_BULLET;

	list<Player::tagbulletinfo>::iterator	p_Bullet_it;

	typedef struct tagenemyinfo
	{
		int	  type;
		int	  state;
		float createTime;
		float x, y;
		float diameter;
		float angle;
		float speed;
		int   hp;
		int	  imageFrameX;
		float existingTime;
		int	  moveType;
		int	  moveTimer;
		int	  bulletType;
		int   isFire;
		int	  bulletCount;
		int   bulletCountLimit;
		float lastBulletFireTime;
		float nextBulletTermTime;
		int   reloadTime;
	}E_OBJECT;

	list<EnemyObject::tagenemyinfo>::iterator	e_Object_it;

	typedef struct tagenemybulletinfo
	{
		int	  type;
		int	  state;
		float x, y;
		float diameter;
		float angle;
		float speed;
		int	  imageFrameX;
		int	  imageFrameY;
	}E_BULLET;

	list<EnemyObject::tagenemybulletinfo>::iterator	e_Bullet_it;

public:
	Collision();
	~Collision();

	void init();
	void collisionCheck();
	void effectRender(HDC hdc);
};