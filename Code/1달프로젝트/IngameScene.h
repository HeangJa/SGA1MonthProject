#pragma once
#include "gameNode.h"

class InGameScene : public gameNode
{
private:
	Image*  info;
	Image*	battleField[2];
	Image*	lifeImage;
	Image*	stage1Image;
	Image*  ig_returntogame;
	Image*  ig_retry;
	Image*	ig_returntomenu;

	int		pauseImageAlpha[3];

	int		state;
	int		currentSelected;

	int		highScore;

	float	ingameStartTime;

	int		stage1ImageAlpha;
	int		changingAlphaValue;
	int		stage1ImageTimer;

	string	filePath;

	vector<int>				scoreStorage;
	vector<int>::iterator	scoreStorage_it;

public:
	InGameScene();
	~InGameScene();

	HRESULT init();
	void	release();
	void	update();
	void	render();

	void	setHighScore();
	void	stageAlphaControl();
};
