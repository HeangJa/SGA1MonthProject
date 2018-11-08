#pragma once
#include "singletonBase.h"

class Boss : public singletonBase<Boss>
{
public:

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
	bool    isBossStop;

	float	bossBackgroundAlpha;
	float	bossBackgroundAlphaSpeed;

public:
	Boss();
	~Boss();

	void	init();
	void	release();
	void	update(float ingameCurrentTime);
	void	render(HDC hdc);

	void createBoss(float ingameCurrentTime);
	void moveBoss(float ingameCurrentTime);

	void createBossBullet(float ingameCurrentTime);
	void moveBossBullet(float ingameCurrentTime);
};

