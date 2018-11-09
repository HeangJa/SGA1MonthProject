#pragma once
#include "singletonBase.h"

class Boss : public singletonBase<Boss>
{
public:
	typedef struct tagbossbulletinfo
	{
		int	  type;
		int	  state;
		float x, y;
		float diameter;
		float angle;
		float speed;
		int	  imageFrameX;
		int	  imageFrameY;
	}B_BULLET;

private:
	Image * bossImage;
	Image * bossbackgroundImage;
	Image * bossHpBar;
	Image * bossBullet0;
	Image * bossBullet1;

	int		bossHpBarPercent;

	float	bossPosX;
	float	bossPosY;

	int		bossState;
	int		bossPattern;
	int		bossDiameter;
	float   bossAngle;
	float	bossSpeed;
	int		bossHp;

	int		bossMotionTimer;
	int		bossStayTimer;
	int		bossBulletBreakTimer;
	int		createBossBulletTimer;
	bool	isBossBulletBreak;
	bool	isCreateBossBullet;
	bool    isBossStop;

	float	bossBackgroundAlpha;
	float	bossBackgroundAlphaSpeed;

	// Boss Bullet
	B_BULLET	bossBullet[6];

	typedef list<B_BULLET>				bossBulletInfo;
	typedef list<B_BULLET>::iterator	bossBulletInfo_it;

	bossBulletInfo		b_Bullet;
	bossBulletInfo_it	b_Bullet_it;

	int bulletCountNum;
	int bulletTermTimer;
	float changingBulletAngle;

public:
	Boss();
	~Boss();

	void init();
	void release();
	void update(float ingameCurrentTime);
	void render(HDC hdc);

	void setBullet();

	void moveBoss(float ingameCurrentTime);
	void createBossBullet(float ingameCurrentTime);
	void moveBossBullet(float ingameCurrentTime);

	void createNWayBullet(int bulletType, float startAngle, float endAngle, int num, 
		float createPosX, float createPosY, int distance = DISTANCE_BETWEEN_CREATEPOS_TO_BULLET);

	float getBossPosX() { return bossPosX; }
	float getBossPosY() { return bossPosY; }
	float getBossDiameter() { return bossDiameter; }

	void  setBossHp(int hp) { bossHp = hp; }
	int	  getBossHp() { return bossHp; }
	int	  getBossState() { return bossState; }
	int	  getBossPattern() { return bossPattern; }
};

