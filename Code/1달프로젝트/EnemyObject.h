#pragma once
#include "singletonBase.h"

class EnemyObject : public singletonBase<EnemyObject>
{
public:
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
		float reloadTime;
		float firstAngle;
	}E_OBJECT;

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

private:
	// 적 오브젝트
	Image * blueFairy;
	Image * redFairy;
	Image * greenFairy;
	Image * bigFairy;

	E_OBJECT	enemyObject[100];

	typedef list<E_OBJECT>				enemyObjectInfo;
	typedef list<E_OBJECT>::iterator	enemyObjectInfo_it;

	enemyObjectInfo		e_Object;
	enemyObjectInfo_it	e_Object_it;

	int currentObjectNum;
	int enemyStayTimer;
	float createTime;

	// 적 불릿
	Image * e_BulletImage;
	Image * e_BulletImage2;

	E_BULLET	enemyBullet[4];

	typedef list<E_BULLET>				enemyBulletInfo;
	typedef list<E_BULLET>::iterator	enemyBulletInfo_it;

	enemyBulletInfo		e_Bullet;
	enemyBulletInfo_it	e_Bullet_it;

public:
	EnemyObject();
	~EnemyObject();

	void	init();
	void	release();
	void	update(float ingameCurrentTime);
	void	render(HDC hdc);

	// 적 오브젝트
	void loadEnemyFile();
	void createEnemy(float ingameCurrentTime);
	void moveEnemy(float ingameCurrentTime);

	// 적 불릿
	void loadEnemyBulletFile();
	void createEnemyBullet(float ingameCurrentTime);
	void moveEnemyBullet();
	
	// 충돌함수에서 쓰기위한 함수
	int	 getE_ObjectSize() { return e_Object.size(); }
	enemyObjectInfo_it getE_Object_Begin() { return e_Object.begin(); }
	enemyObjectInfo_it getE_Object_End() { return e_Object.end(); }

	int	 getE_BulletSize() { return e_Bullet.size(); }
	enemyBulletInfo_it getE_Bullet_Begin() { return e_Bullet.begin(); }
	enemyBulletInfo_it getE_Bullet_End() { return e_Bullet.end(); }
};

