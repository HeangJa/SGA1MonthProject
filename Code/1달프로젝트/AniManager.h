#pragma once

class Image;
class Animation;

class AniManager : public singletonBase<AniManager>
{
	typedef map<string, Animation*>				AniMap;
	typedef map<string, Animation*>::iterator   iAniMap;

private:
	AniMap				totalAni;
	iAniMap				it;

public:
	AniManager();
	~AniManager();

	void Init();
	void Update();
	void Release();

	void AddDefAni(string keyName, string imageName, int fps, bool reverse = false, bool loop = false);
	void AddDefAni(string keyName, string imageName, int fps, void* func, bool reverse = false, bool loop = false);
	void AddDefAni(string keyName, string imageName, int fps, void* func, void* val, bool reverse = false, bool loop = false);

	void AddArrAni(string keyName, string imageName, int* arr, int arrLen, int fps, bool loop = false);
	void AddArrAni(string keyName, string imageName, int* arr, int arrLen, int fps, void* func, bool loop = false);
	void AddArrAni(string keyName, string imageName, int* arr, int arrLen, int fps, void* func, void* val, bool loop = false);

	void AddCoordAni(string keyName, string imageName, int start, int end, int fps, bool loop = false);
	void AddCoordAni(string keyName, string imageName, int start, int end, int fps, void* func, bool loop = false);
	void AddCoordAni(string keyName, string imageName, int start, int end, int fps, void* func, void* val, bool loop = false);

	void Start(string key);
	void Stop(string key);
	void Pause(string key);
	void Resume(string key);

	Animation* FindAni(string key);

};

