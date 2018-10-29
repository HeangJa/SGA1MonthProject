#pragma once
#include "singletonBase.h"

class Effect;

class EffectManager : public singletonBase<EffectManager>
{
private:
	typedef vector<Effect*>					vEffects;
	typedef vector<Effect*>::iterator		iEffects;

	typedef map<string, vEffects>			TotalEffect;
	typedef map<string, vEffects>::iterator iTotalEffect;

private:
	TotalEffect								_mTotalEffect;

public:
	EffectManager();
	~EffectManager();

	bool Init();
	void Release();
	void Update();
	void Render();

	void AddEffect(string effectName, const TCHAR* imageName,
		int imageWidth, int imageHeight, int effectWidth, int effctHeight,
		int fps, float elapsedTime, int buffer, COLORREF color = RGB(255, 0, 255));

	void Play(string effectName, int x, int y);
	void Play(string effectName, POINT p);

};

