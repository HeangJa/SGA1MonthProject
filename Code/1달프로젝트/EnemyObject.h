#pragma once
#include "singletonBase.h"

class EnemyObject : public singletonBase<EnemyObject>
{
private:
	Image * blueFairy;
	Image * redFairy;
	Image * greenFairy;
	Image * bigFairy;

	typedef struct tagenemyinfo
	{
		int	  type;
		int	  state;
		float appearanceTime;
		float x, y;
		float diameter;
		float angle;
		float speed;
		int   hp;
		int	  imageFrameX;
		int	  moveType;
		int	  moveTimer;
		int	  bulletType;		
	}E_OBJECT;

	E_OBJECT	enemyObject[100];

	typedef list<E_OBJECT>				enemyObjectInfo;
	typedef list<E_OBJECT>::iterator	enemyObjectInfo_it;

	enemyObjectInfo		e_Object;
	enemyObjectInfo_it	e_Object_it;

	int currentObjectNum;
	int enemyStayTimer;

public:
	EnemyObject();
	~EnemyObject();

	void init();
	void loadEnemyFile();
	void createEnemy(float ingameTime);
	void moveEnemy();
	void render(HDC hdc);
};

