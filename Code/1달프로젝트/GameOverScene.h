#pragma once
#include "gameNode.h"

class GameOverScene : public gameNode
{
private:
	Image*  gameover;
	Image*  go_retry;
	Image*	go_returntomenu;

	int		currentMenu;
	int		retryAlpha;
	int		returntomenuAlpha;

public:
	GameOverScene();
	~GameOverScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

