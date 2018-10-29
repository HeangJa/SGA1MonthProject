#include "Game.h"
#include "KeyManager.h"

KeyManager::KeyManager()
{
}

KeyManager::~KeyManager()
{
}

HRESULT KeyManager::init()
{
	this->getKeyDown().reset();
	this->getKeyUp().reset();
	
	return S_OK;
}

void KeyManager::release()
{

}

bool KeyManager::isOnceKeyDown(int _key)
{	//         안눌림       현재 눌린것 이전에도 현재에도 눌린 것
	// Return : 0x0000,		0x8000,		0x8001
	if (GetAsyncKeyState(_key) & 0x8000)
	{
		if (!this->getKeyDown()[_key])
		{
			this->setKeyDown(_key, true);
			return true;
		}
	}
	else
		this->setKeyDown(_key, false);

	return false;
}

bool KeyManager::isOnceKeyUp(int _key)
{
	if (GetAsyncKeyState(_key) & 0x8000)
	{
		this->setKeyUp(_key, true);
	}
	else
	{
		if (this->getKeyUp()[_key])
		{
			this->setKeyUp(_key, false);
			return true;
		}
	}
	return false;
}

bool KeyManager::isStayKeyDown(int _key)
{
	if (GetAsyncKeyState(_key) & 0x8000)
		return true;

	return false;
}

bool KeyManager::isToggleKey(int _key)
{
	if (GetKeyState(_key) && 0x0001)
		return true;

	return false;
}
