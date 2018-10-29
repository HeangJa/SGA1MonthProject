#pragma once
#include "gameNode.h"

class MenuScene : public gameNode
{
private:
	Image * title;
	Image * gamestart;
	Image * quit;

	int		currentMenu;
	int		titleAlpha;

public:
	MenuScene();
	~MenuScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

