#include "Game.h"
#include "mainGame.h"
#include "LoadingScene.h"
#include "MenuScene.h"
#include "SelectScene.h"
#include "InGameScene.h"
#include "GameClearScene.h"
#include "GameOverScene.h"
#include "TestScene.h"

mainGame::mainGame()
{
}

mainGame::~mainGame()
{
}

//===========================================================================

HRESULT mainGame::init()
{
	gameNode::init(true);

	//if (SOUNDMANAGER->Init() == false)
		//return S_FALSE;

	SOUNDMANAGER->AddSound(TEXT("Menu"), TEXT("Sound\\Menu.wav"), true, true);
	SOUNDMANAGER->AddSound(TEXT("Select"), TEXT("Sound\\Select.wav"), false, false);
	SOUNDMANAGER->AddSound(TEXT("Ok"), TEXT("Sound\\Ok.wav"), false, false);
	SOUNDMANAGER->AddSound(TEXT("Field"), TEXT("Sound\\Field.wav"), true, true);
	SOUNDMANAGER->AddSound(TEXT("Pause"), TEXT("Sound\\Pause.wav"), false, false);
	SOUNDMANAGER->AddSound(TEXT("PlayerAttack"), TEXT("Sound\\PlayerAttack.wav"), false, false);
	SOUNDMANAGER->AddSound(TEXT("PlayerDead"), TEXT("Sound\\PlayerDead.wav"), false, false);
	SOUNDMANAGER->AddSound(TEXT("EnemyAttack"), TEXT("Sound\\EnemyAttack.wav"), false, false);
	SOUNDMANAGER->AddSound(TEXT("EnemyDead"), TEXT("Sound\\EnemyDead.wav"), false, false);
	SOUNDMANAGER->AddSound(TEXT("Boss"), TEXT("Sound\\Boss.wav"), false, false);
	SOUNDMANAGER->AddSound(TEXT("End"), TEXT("Sound\\End.wav"), false, false);
	
	//���Ŵ��� �ʱ�ȭ �� �� ���
	SCENEMANAGER->AddScene(TEXT("LoadingScene"), new LoadingScene);
	SCENEMANAGER->AddScene(TEXT("MenuScene"), new MenuScene);
	SCENEMANAGER->AddScene(TEXT("SelectScene"), new SelectScene);
	SCENEMANAGER->AddScene(TEXT("InGameScene"), new InGameScene);
	SCENEMANAGER->AddScene(TEXT("GameClearScene"), new GameClearScene);
	SCENEMANAGER->AddScene(TEXT("GameOverScene"), new GameOverScene);
	SCENEMANAGER->AddScene(TEXT("TestScene"), new TestScene);

	SCENEMANAGER->ChangeScene(TEXT("TestScene"));

	return S_OK;
}

void mainGame::release()
{
	gameNode::release();

	SCENEMANAGER->Release();
}

void mainGame::update()
{
	gameNode::update();

	if (KEYMANAGER->isOnceKeyDown(VK_F1))
		SCENEMANAGER->ChangeScene(TEXT("LoadingScene"));

	if (KEYMANAGER->isOnceKeyDown(VK_F2))
		SCENEMANAGER->ChangeScene(TEXT("MenuScene"));

	if (KEYMANAGER->isOnceKeyDown(VK_F3))
		SCENEMANAGER->ChangeScene(TEXT("SelectScene"));

	if (KEYMANAGER->isOnceKeyDown(VK_F4))
		SCENEMANAGER->ChangeScene(TEXT("InGameScene"));

	if (KEYMANAGER->isOnceKeyDown(VK_F5))
		SCENEMANAGER->ChangeScene(TEXT("GameClearScene"));

	if (KEYMANAGER->isOnceKeyDown(VK_F6))
		SCENEMANAGER->ChangeScene(TEXT("GameOverScene"));

	SCENEMANAGER->Update();
}

void mainGame::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);

	SCENEMANAGER->Render(getMemDC());
	TIMEMANAGER->render(getMemDC());
	this->getBackBuffer()->render(getHDC(), 0, 0);
}