#pragma once
#include "gameNode.h"

class mainGame : public gameNode
{
private:

public:
	mainGame();
	~mainGame();

	virtual HRESULT init();
	virtual void	update();
	virtual void	render();
	virtual void	release();
};

