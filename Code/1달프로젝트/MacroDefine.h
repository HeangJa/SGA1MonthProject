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
#define COLLISION		Collision::getSingleton()
#define ITEMS			Items::getSingleton()
#define BOSS			Boss::getSingleton()


#define SAFE_DELETE(p)	{ if(p) { delete(p); (p) = NULL; }}
#define SAFE_RELEASE(p) { if(p) { (p)->release(); (p) = NULL; }}

//#define DEBUG_MODE
// 사용자 정의
#define NUMBERLIMIT								6
#define	SAVENAMELENGTH							3
#define SHOWHIGHSCORELIMIT						5
#define STAGE1IMAGEDELAY						120
#define MOTION_DELAY							6
#define PLAYER_INVINCIBLE_DELAY					240
#define PLAYER_SPECIALSUPPORTER_NUMLIMIT		4
#define PLAYER_SPECIALBULLET_NUMLIMIT			3
#define PLAYER_SPECIALBULLET_DURATION			180
#define CREATEBULLETDELAY						4
#define CREATESUPPORTBULLETDELAY				3
#define ITEM_SCAN_RANGE							120
#define RED_ITEM_POWER							2
#define ENEMY_TOTALNUM							100
#define CREATE_ENEMY_BULLET_DISTANCE			20
#define FIRST_BULLET_TIME_AFTER_CREATE			2
#define PLAYER_GET_ALL_ITEM_POS_Y				200
#define DISTANCE_BETWEEN_CREATEPOS_TO_BULLET	30
#define BOSS_PATTERN_NUM						7
#define BOSS_PATTERN_HP							500
#define BOSS_MAXHP								BOSS_PATTERN_NUM * BOSS_PATTERN_HP


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
	PAUSE,
	STOP
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
	NORMAL_SPEED = 5,
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

enum ENEMY_BULLET_TYPE
{
	ONCE_SHOT,
	INTERVAL_SHOT,
	RAPID_SHOT,
	MULTIPLE_SHOT
};

enum BOSS_PATTERN
{
	APPEAR,
	PATTERN0,
	PATTERN1,
	PATTERN2,
	PATTERN3,
	PATTERN4,
	PATTERN5,
	PATTERN6,
	BOSS_DEAD
};

enum BOSS_PATTERN_SCORE
{
	PATTERN0_SCORE = 10000,
	PATTERN1_SCORE = 20000,
	PATTERN2_SCORE = 30000,
	PATTERN3_SCORE = 50000,
	PATTERN4_SCORE = 70000,
	PATTERN5_SCORE = 100000,
	PATTERN6_SCORE = 150000,
};
