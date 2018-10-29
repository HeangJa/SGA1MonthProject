#pragma once
#include "gameNode.h"

struct Frame
{
	float time;
	int	  index;
	POINT start;
	POINT end;
};

struct Action
{
	int		actionType;
	bool	repeat;
	vector<Frame>	vFrame;
};

class TestScene : public gameNode
{
private:
	string aaa, bbb, ccc;

public:
	TestScene();
	~TestScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

