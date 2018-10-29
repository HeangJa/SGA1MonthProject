#pragma once

// 윈도우 사이즈 매크로
#define WINSTARTX		50
#define WINSTARTY		50
#define WINSIZEX		800
#define WINSIZEY		600


// 각종 매크로 디파인 추가 부분
#define IMAGEMANAGER	ImageManager::getSingleton()
#define KEYMANAGER		KeyManager::getSingleton()
#define RND				randomFunction::getSingleton()
#define CAMERA			Camera::getSingleton()
#define TXTDATA			txtData::getSingleton()
#define TIMEMANAGER		timerManager::getSingleton()
#define EFFECTMANAGER	EffectManager::getSingleton() 
#define SCENEMANAGER    SceneManager::getSingleton()
#define SOUNDMANAGER	SoundManager::getSingleton()
#define ANIMANAGER		AniManager::getSingleton()
#define NUMBERMANAGER	NumberManager::getSingleton()
#define PLAYER			Player::getSingleton()
#define ENEMYOBJECT		EnemyObject::getSingleton()
#define ENEMYBULLET		EnemyBullet::getSingleton()
#define COLLISION		Collision::getSingleton()
#define ITEMS			Items::getSingleton()


#define SAFE_DELETE(p)	{ if(p) { delete(p); (p) = NULL; }}
#define SAFE_RELEASE(p) { if(p) { (p)->release(); (p) = NULL; }}


// 사용자 정의
#define NUMBERLIMIT							6
#define	SAVENAMELENGTH						3
#define SHOWHIGHSCORELIMIT					5
#define STAGE1IMAGEDELAY					120
#define MOTION_DELAY						6
#define PLAYER_INVINCIBLE_DELAY				150
#define PLAYER_SPECIALSUPPORTER_NUMLIMIT	4
#define CREATEBULLETDELAY					4
#define CREATESUPPORTBULLETDELAY			3
#define ITEM_SCAN_RANGE						120
#define RED_ITEM_POWER						2


enum SELECT_STATE
{
	ON,
	OFF
};

enum MENU_OPTION
{
	GAME_START,
	QUIT
};

enum CHARACTER_SELECT
{
	REIMU,
	MARISA
};

enum TRANSPARENCY
{
	TRANSPARENT_ = 0,
	TRANSLUCENT_ = 130,
	OPAQUE_		 = 255
};

enum PAUSE_OPTION
{
	RETURNTOGAME,
	RETRY,
	RETURNTOMENU
};

enum CLEARSCENE_STATE
{
	SAVESCORE,
	SHOWHIGHSCORE
};

enum INGAME_STATE
{
	PLAYING,
	PAUSE
};

enum BATTLEFIELD_BOUNDARY
{
	F_LEFT = 40,
	F_RIGHT = 520,
	F_UP = 36,
	F_DOWN = 564
};

enum PLAYER_SIZE
{
	P_SIZE_X = 32,
	P_SIZE_Y = 48
};

enum PLAYER_SPEED
{
	NORMAL_SPEED = 4,
	SHIFT_SPEED = 2
};

enum PLAYER_ANIMATION
{
	P_ANI_NORMAL,
	P_ANI_LEFT,
	P_ANI_RIGHT
};

enum PLAYER_BULLET_TYPE
{
	NORMAL,
	SUPPORT
};

enum OBJECT_STATE
{
	DEAD,
	ALIVE,
	CREATE,
	NOTCREATE,
	TOPLAYER
};

enum ENEMY_TYPE
{
	BLUEFAIRY,
	REDFAIRY,
	GREENFAIRY,
	BIGFAIRY
};

enum ITEM_TYPE
{
	BLUE_ITEM,
	RED_ITEM	
};

enum ITEM_SCORE
{
	BLUE_ITEM_SCORE = 200,
	RED_ITEM_SCORE = 100
};
