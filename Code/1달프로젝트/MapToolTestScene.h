#pragma once
#include "gameNode.h"

class MapToolTestScene : public gameNode
{
	POINT				currentTile;
	Tile				sampleTile[SAMPLETILEX * SAMPLETILEY];
	Tile				tile[TILEX * TILEY];

	int					pos[2];

public:
	MapToolTestScene();
	~MapToolTestScene();

	virtual HRESULT init();
	virtual void	update();
	virtual void	render();
	virtual void	release();

	void			mapToolSetup();

	void			ClickSample();
	void			ClickMap();

	void			SaveTile();
	void			LoadTile();
};

