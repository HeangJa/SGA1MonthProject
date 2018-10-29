#pragma once
#include "gameNode.h"

class Animation;

class Effect : public gameNode
{
protected:
	int			_x;
	int			_y;

	Image*      _effectImage;
	Animation*  _effectAnimation;

	bool		_isRunning;
	float		_elapsedTime;

public:
	Effect();
	~Effect();

	virtual HRESULT	init(Image* effectImage, int frameW, int frameH,
		int fps, float elapsedTime);

	virtual void release();
	virtual void update();
	virtual void render();

	virtual void killEffect();

	void startEffect(int x, int y);
	bool getIsRunning() { return _isRunning; }
};

