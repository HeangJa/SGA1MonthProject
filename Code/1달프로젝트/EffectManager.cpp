#include "Game.h"
#include "EffectManager.h"
#include "Effect.h"

EffectManager::EffectManager()
{
}

EffectManager::~EffectManager()
{
}

bool EffectManager::Init()
{
	return true;
}

void EffectManager::Release()
{
	iTotalEffect it = _mTotalEffect.begin();
	for (; it != _mTotalEffect.end(); ++it)
	{
		iEffects vit = (it->second).begin();
		for (; vit != (it->second).end(); ++vit)
		{
			(*vit)->release();
			SAFE_DELETE(*vit);
		}
		(it->second).clear();
	}
}

void EffectManager::Update()
{
	iTotalEffect it = _mTotalEffect.begin();
	for (; it != _mTotalEffect.end(); ++it)
	{
		for (int i = 0; i < (it->second).size(); i++)
		{
			(it->second)[i]->update();
		}
	}
}

void EffectManager::Render()
{
	iTotalEffect it = _mTotalEffect.begin();
	for (; it != _mTotalEffect.end(); ++it)
	{
		for (int i = 0; i < (it->second).size(); i++)
		{
			(it->second)[i]->render();
		}
	}
}

void EffectManager::AddEffect(string effectName, const TCHAR * imageName, int imageWidth, int imageHeight, int effectWidth, int effectHeight, int fps, float elapsedTime, int buffer, COLORREF color)
{
	Image* img;
	if (IMAGEMANAGER->findImage(effectName))
		img = IMAGEMANAGER->findImage(effectName);
	else
		img = IMAGEMANAGER->addImage(effectName, imageName, imageWidth, imageHeight, true, color);

	vEffects vEffectBuffer;
	for (int i = 0; i < buffer; i++)
	{
		vEffectBuffer.push_back(new Effect);
		vEffectBuffer[i]->init(img, effectWidth, effectHeight, fps, elapsedTime);
	}

	_mTotalEffect.insert(pair<string, vEffects>(effectName, vEffectBuffer));
}

void EffectManager::Play(string effectName, int x, int y)
{
	iTotalEffect it = _mTotalEffect.find(effectName);

	if (it != _mTotalEffect.end())
	{
		for (int i = 0; i < (it->second).size(); i++)
		{
			if ((it->second)[i]->getIsRunning())
				continue;

			(it->second)[i]->startEffect(x, y);
			return;
		}
	}
}

void EffectManager::Play(string effectName, POINT p)
{
	Play(effectName, p.x, p.y);
}
