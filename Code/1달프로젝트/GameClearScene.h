#pragma once
#include "gameNode.h"

class GameClearScene : public gameNode
{
private:
	Image*  highscore;
	Image*	player;
	Image*	score;
	Image*	cursor;

	int		state;

	int		saveName[SAVENAMELENGTH];

	int		currentCursor;
	int		cursorAlpha;
	int		cursorTimer;

	string	filePath;

	typedef map<int, int, greater<int> >			mHighScoreInfo;
	typedef map<int, int, greater<int> >::iterator	mHighScoreInfo_it;

	mHighScoreInfo		mHighScore;
	mHighScoreInfo_it	mHighScore_it;

	int		showHighScoreName[SHOWHIGHSCORELIMIT][SAVENAMELENGTH];
	int		showHighScoreLength;

public:
	GameClearScene();
	~GameClearScene();

	HRESULT init();
	void release();
	void update();
	void render();

	void loadScore();
	void setScore();
};

