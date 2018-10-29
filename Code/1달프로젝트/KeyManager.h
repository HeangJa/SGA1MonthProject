#pragma once
#include "singletonBase.h"
#include <bitset>

#define KEYMAX 256

class KeyManager : public singletonBase<KeyManager>
{
private:
	std::bitset<KEYMAX> _keyUp;
	std::bitset<KEYMAX> _keyDown;

public:
	KeyManager();
	~KeyManager();

	HRESULT init();
	void	release();

	bool isOnceKeyUp(int _key);
	bool isOnceKeyDown(int _key);
	bool isStayKeyDown(int _key);
	bool isToggleKey(int _key);

	std::bitset<KEYMAX> getKeyUp() { return _keyUp; }
	std::bitset<KEYMAX> getKeyDown() { return _keyDown; }

	void setKeyUp(int _key, bool _state)
	{
		_keyUp.set(_key, _state);
	}

	void setKeyDown(int _key, bool _state)
	{
		_keyDown.set(_key, _state);
	}

};

