#include "Game.h"
#include "MotionTestScene.h"
#include "Player.h"


MotionTestScene::MotionTestScene()
{
}

MotionTestScene::~MotionTestScene()
{
}

HRESULT MotionTestScene::init()
{
	player = new Player;

	return S_OK;
}

void MotionTestScene::release()
{
	SAFE_DELETE(player);
}

void MotionTestScene::update()
{
	player->Update();
}

void MotionTestScene::render()
{
	player->Render(getMemDC());
}
