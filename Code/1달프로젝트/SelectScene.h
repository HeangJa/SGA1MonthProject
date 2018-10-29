#pragma once
#include "gameNode.h"

class SelectScene : public gameNode
{
private:
	Image*  reimu;
	Image*	marisa;

	int		reimuAlpha;
	int		marisaAlpha;

	int		currentCharacter;

public:
	SelectScene();
	~SelectScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

