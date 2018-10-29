#pragma once
#include "gameNode.h"

class LoadingScene : public gameNode
{
private:
	Image*	loading;
	int		loadingAlpha;
	int		alphaSpeed;
	int		loadingTime;

public:
	LoadingScene();
	~LoadingScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

