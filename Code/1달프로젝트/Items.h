#pragma once
#include "singletonBase.h"

class Items : public singletonBase<Items>
{
private:
	Image * blueItem;
	Image * redItem;

	typedef struct tagiteminfo
	{
		int   type;
		int	  state;
		float x, y;
		float angle;
		float speed;
		float gravity;
		float diameter;
	}ITEMINFO;

	ITEMINFO	itemInfo;

	typedef list<ITEMINFO>				itemInfoList;
	typedef list<ITEMINFO>::iterator	itemInfoList_it;

	itemInfoList	itemList;
	itemInfoList_it	itemList_it;

public:
	Items();
	~Items();

	HRESULT init();
	void release();
	void createItem(int type, float x, float y);
	void moveItem();
	void render(HDC hdc);
};

