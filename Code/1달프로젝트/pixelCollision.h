#pragma once
#include "gameNode.h"

class pixelCollision : public gameNode
{
private:
	Image *		_background;
	Image*		_ball;

	RECT		_rc;
	float		_x, _y;
	int			_probeY;

public:
	pixelCollision();
	~pixelCollision();

	HRESULT    init();
	void       release();
	void	   update();
	void	   render();

	bool GetLandY(Image* pImage, RECT& _rc,
		int _depth, COLORREF _color);
};

