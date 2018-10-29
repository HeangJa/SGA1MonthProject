#pragma once
#include "singletonBase.h"

class Items : public singletonBase<Items>
{
private:
	typedef struct tagiteminfo
	{
		int	  state;
		float x;
		float y;
		float speed;
		float gravity;
		float diameter;
	}ITEMINFO;

	ITEMINFO	itemInfo[2];

	typedef list<ITEMINFO>				itemInfoList;
	typedef list<ITEMINFO>::iterator	itemInfoList_it;

	itemInfoList	itemList;
	itemInfoList_it	itemList_it;

public:
	Items();
	~Items();

	void init();
	void createItem(int type, float x, float y);
	void moveItem();
	void render();
};

