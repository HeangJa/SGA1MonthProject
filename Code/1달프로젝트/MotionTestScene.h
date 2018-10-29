#pragma once
#include "gameNode.h"

class Player;

class MotionTestScene : public gameNode
{
	Player* player;

public:
	MotionTestScene();
	~MotionTestScene();

	HRESULT init();
	void	release();
	void	update();
	void	render();
};

