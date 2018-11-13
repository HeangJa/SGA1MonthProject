#pragma once
#include "singletonBase.h"
#include "EnemyObject.h"

class Player : public singletonBase<Player>
{
public:
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
		int   state;
		float x, y;
		float diameter;
		float angle;
		float speed;
		int	  damage;
		int	  type;
	}P_BULLET;

	typedef struct tagspecialbulletinfo
	{
		float x, y;
		float diameter;
		float speed;
	}P_SPECIALBULLET;

private:
	// 플레이어 관련
	Image * playerImage;
	Image *	playerShiftImage;
	Image * playerShiftMaskImage;
	
	float	playerPosX;
	float	playerPosY;

	int		playerDiameter;
	int		playerType;
	float	playerSpeed;
	int		playerAlpha;
	int		playerLife;
	int		playerPower;
	int		playerScore;

	int		playerMotionTimer;

	bool	isPlayerDead;
	bool	isPlayerInvincible;
	int		playerInvincibleTimer;

	// 탄 관련
	LOAD_P_BULLET	load_bullet[2];
	P_BULLET		bullet;

	Image*	bulletImage;
	Image*	supporter;
	Image*	supportBulletImage;
	Image*	specialBulletImage;

	POINT	supporterPos[PLAYER_SPECIALSUPPORTER_NUMLIMIT];

	typedef list<P_BULLET>				bulletInfo;
	typedef list<P_BULLET>::iterator	bulletInfo_it;

	list<EnemyObject::tagenemyinfo>::iterator	e_Object_it;
	map<float, POINT>			e_Object_distance;
	map<float, POINT>::iterator	e_Object_distance_it;

	bulletInfo		p_Bullet;
	bulletInfo_it	p_Bullet_it;

	P_SPECIALBULLET	specialBullet[PLAYER_SPECIALBULLET_NUMLIMIT];

	int		createBulletTimer;
	int		createSupportBulletTimer;
	int		specialBulletDuration;
	int		specialBulletAlpha;
	bool	specialBulletOn;

	// 회전변환을 위한 변수들
	POINT	vertices[3];
	float	fAnchorX;
	float	fAnchorY;
	float	fAngle;

	// 마스크용 비트맵과 DC
	HBITMAP hBitmapMask;
	HDC		hdcMask;
	HBITMAP mask;

public:
	Player();
	~Player();

	void init();
	void release();
	void update();
	void render(HDC hdc);

	void  setplayerPosX(float x) { playerPosX = x; }
	float getPlayerPosX() { return playerPosX; }

	void  setplayerPosY(float y) { playerPosY = y; }
	float getPlayerPosY() { return playerPosY; }

	void setPlayerType(int type) { playerType = type; }
	int	 getPlayerType() { return playerType; }

	void setPlayerScore(int score) { playerScore = score; }
	int	 getPlayerScore() { return playerScore; }

	void setPlayerLife(int life) { playerLife = life; }
	int  getPlayerLife() { return playerLife; }

	void setPlayerPower(int power) { 
		playerPower = power;

		if (playerPower > 40)
			playerPower = 40;
	}
	int  getPlayerPower() { return playerPower; }

	void setIsPlayerDead(bool b) { isPlayerDead = b; }
	bool getIsPlayerDead() { return isPlayerDead; }

	void setIsPlayerInvincible(bool b) { isPlayerInvincible = b; }
	bool getIsPlayerInvincible() { return isPlayerInvincible; }

	void ifPlayerDead();
	void rotate(float angle);

	void loadBulletFile();
	void createBullet();
	void createSpecialBullet();
	void moveBullet();
	void renderBullet(HDC hdc);

	HBITMAP createMask(HDC hdcBitmap, int width, int height);

	// 충돌함수에서 쓰기위한 함수
	float getPlayerDiameter() { return playerDiameter; }
	int	 getP_BulletSize() { return p_Bullet.size(); }
	bulletInfo_it getP_Bullet_Begin() { return p_Bullet.begin(); }
	bulletInfo_it getP_Bullet_End() { return p_Bullet.end(); }
	float getSpecialBulletPosX(int index) { return specialBullet[index].x; }
	float getSpecialBulletPosY(int index) { return specialBullet[index].y; }
	float getSpecialBulletDiameter(int index) { return specialBullet[index].diameter; }
	bool  getSpecialBulletOn() { return specialBulletOn; }
};

