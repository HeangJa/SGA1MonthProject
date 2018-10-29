#pragma once
#include "singletonBase.h"

class Player : public singletonBase<Player>
{
private:
	// 플레이어 관련
	Image * playerImage;
	Image *	playerShiftImage;
	Image * playerShiftMaskImage;
	POINT	playerPos;

	int		playerDiameter;
	int		playerType;
	float	playerSpeed;
	int		playerAlpha;
	int		playerLife;
	int		playerPower;

	int		playerMotionTimer;

	bool	isPlayerDead;
	bool	isPlayerInvincible;
	int		playerInvincibleTimer;

	// 탄 관련
	typedef struct tagloadbulletinfo
	{
		float diameter;
		float angle1;
		float angle2;
		float speed;
		int	  damage;
		int	  type;
	}LOAD_P_BULLET;

	typedef struct tagbulletinfo
	{
		float x, y;
		float diameter;
		float angle;
		float speed;
		int	  damage;
		int	  type;
	}P_BULLET;

	LOAD_P_BULLET	load_bullet[2];
	P_BULLET		bullet;

	Image*	bulletImage;
	Image*	supporter;
	Image*	supportBulletImage;

	POINT	supporterPos[PLAYER_SPECIALSUPPORTER_NUMLIMIT];

	typedef list<P_BULLET>				bulletInfo;
	typedef list<P_BULLET>::iterator	bulletInfo_it;

	bulletInfo		p_Bullet;
	bulletInfo_it	p_Bullet_it;

	int		createBulletTimer;
	int		createSupportBulletTimer;

	// 회전변환을 위한 변수들
	POINT	vertices[3];
	float	fAnchorX;
	float	fAnchorY;
	float	fAngle;

public:
	Player();
	~Player();

	void init();
	void release();
	void update();
	void render(HDC hdc);

	void setPlayerPos(POINT point) { playerPos = point; }
	POINT getPlayerPos() { return playerPos; }

	void setPlayerType(int type) { playerType = type; }
	int	 getPlayerType() { return playerType; }

	void setPlayerLife(int life) { playerLife = life; }
	int  getPlayerLife() { return playerLife; }

	void setPlayerPower(bool power) { playerPower = power; }
	int  getPlayerPower() { return playerPower; }

	void setIsPlayerDead(bool b) { isPlayerDead = b; }
	bool getIsPlayerDead() { return isPlayerDead; }

	void setIsPlayerInvincible(bool b) { isPlayerInvincible = b; }
	bool getIsPlayerInvincible() { return isPlayerInvincible; }

	void ifPlayerDead();
	void rotate(float angle);

	void loadBulletFile();
	void createBullet();
	void moveBullet();
	void renderBullet(HDC hdc);
};

