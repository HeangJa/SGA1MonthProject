#pragma once
#include "singletonBase.h"
#include "Boss.h"

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

	list<Player::tagbulletinfo>::iterator	p_Bullet_it;

	list<EnemyObject::tagenemyinfo>::iterator	e_Object_it;

	list<EnemyObject::tagenemybulletinfo>::iterator	e_Bullet_it;

	list<Boss::tagbossbulletinfo>::iterator	b_Bullet_it;

public:
	Collision();
	~Collision();

	void init();
	void collisionCheck();
};