#include "Game.h"
#include "AniManager.h"
#include "Animation.h"


AniManager::AniManager()
{
}

AniManager::~AniManager()
{
}

void AniManager::Init()
{
}

void AniManager::Update()
{
	for (it = totalAni.begin(); it != totalAni.end(); it++)
	{
		if (it->second->isPlay())
		{
			it->second->frameUpdate(TIMEMANAGER->getElapsedTime());
		}
	}
}

void AniManager::Release()
{
	for (it = totalAni.begin(); it != totalAni.end(); it++)
	{
		SAFE_DELETE(it->second);
	}
	totalAni.clear();
}

void AniManager::AddDefAni(string keyName, string imageName, int fps, bool reverse, bool loop)
{
	Image* img = IMAGEMANAGER->findImage(imageName);
	assert(img != NULL);
	Animation* ani = new Animation;
	assert(ani != NULL);

	ani->init(img);
	ani->setDefPlayFrame(reverse, loop);
	ani->setFPS(fps);

	//totalAni.insert(pair<string, Animation*>(keyName, ani));
	//totalAni.insert(make_pair(keyName, ani));
	it = totalAni.find(keyName);
	if(it == totalAni.end())
		totalAni.insert({ keyName, ani });

	//pair<map<string, Animation*>::iterator, bool> pr = totalAni.insert({ keyName, ani });
	//if (pr.second == false)
	//{
		//예외처리
	//}
}

void AniManager::AddDefAni(string keyName, string imageName, int fps, void * func, bool reverse, bool loop)
{
	Image* img = IMAGEMANAGER->findImage(imageName);
	assert(img != NULL);
	Animation* ani = new Animation;
	assert(ani != NULL);

	ani->init(img);
	ani->setDefPlayFrame((CALL_FUNC)func, reverse, loop);
	ani->setFPS(fps);

	it = totalAni.find(keyName);
	if (it == totalAni.end())
		totalAni.insert({ keyName, ani });
}

void AniManager::AddDefAni(string keyName, string imageName, int fps, void * func, void * val, bool reverse, bool loop)
{
	Image* img = IMAGEMANAGER->findImage(imageName);
	assert(img != NULL);
	Animation* ani = new Animation;
	assert(ani != NULL);

	ani->init(img);
	ani->setDefPlayFrame((CALL_FUNC_PARAM)func, val, reverse, loop);
	ani->setFPS(fps);

	it = totalAni.find(keyName);
	if (it == totalAni.end())
		totalAni.insert({ keyName, ani });
}

void AniManager::AddArrAni(string keyName, string imageName, int * arr, int arrLen, int fps, bool loop)
{
	Image* img = IMAGEMANAGER->findImage(imageName);
	assert(img != NULL);
	Animation* ani = new Animation;
	assert(ani != NULL);

	ani->init(img);
	ani->setPlayFrame(arr, arrLen, loop);
	ani->setFPS(fps);

	it = totalAni.find(keyName);
	if (it == totalAni.end())
		totalAni.insert({ keyName, ani });
}

void AniManager::AddArrAni(string keyName, string imageName, int * arr, int arrLen, int fps, void * func, bool loop)
{
	Image* img = IMAGEMANAGER->findImage(imageName);
	assert(img != NULL);
	Animation* ani = new Animation;
	assert(ani != NULL);

	ani->init(img);
	ani->setPlayFrame((CALL_FUNC)func, arr, arrLen, loop);
	ani->setFPS(fps);

	it = totalAni.find(keyName);
	if (it == totalAni.end())
		totalAni.insert({ keyName, ani });
}

void AniManager::AddArrAni(string keyName, string imageName, int * arr, int arrLen, int fps, void * func, void * val, bool loop)
{
	Image* img = IMAGEMANAGER->findImage(imageName);
	assert(img != NULL);
	Animation* ani = new Animation;
	assert(ani != NULL);

	ani->init(img);
	ani->setPlayFrame((CALL_FUNC_PARAM)func, val, arr, arrLen, loop);
	ani->setFPS(fps);

	it = totalAni.find(keyName);
	if (it == totalAni.end())
		totalAni.insert({ keyName, ani });
}

void AniManager::AddCoordAni(string keyName, string imageName, int start, int end, int fps, bool loop)
{
	Image* img = IMAGEMANAGER->findImage(imageName);
	assert(img != NULL);
	Animation* ani = new Animation;
	assert(ani != NULL);

	ani->init(img);
	ani->setPlayFrame(start, end, false, loop);
	ani->setFPS(fps);

	it = totalAni.find(keyName);
	if (it == totalAni.end())
		totalAni.insert({ keyName, ani });
}

void AniManager::AddCoordAni(string keyName, string imageName, int start, int end, int fps, void * func, bool loop)
{
	Image* img = IMAGEMANAGER->findImage(imageName);
	assert(img != NULL);
	Animation* ani = new Animation;
	assert(ani != NULL);

	ani->init(img);
	ani->setPlayFrame((CALL_FUNC)func, start, end, false, loop);
	ani->setFPS(fps);

	it = totalAni.find(keyName);
	if (it == totalAni.end())
		totalAni.insert({ keyName, ani });
}

void AniManager::AddCoordAni(string keyName, string imageName, int start, int end, int fps, void * func, void * val, bool loop)
{
	Image* img = IMAGEMANAGER->findImage(imageName);
	assert(img != NULL);
	Animation* ani = new Animation;
	assert(ani != NULL);

	ani->init(img);
	ani->setPlayFrame((CALL_FUNC_PARAM)func, val, start, end, false, loop);
	ani->setFPS(fps);

	it = totalAni.find(keyName);
	if (it == totalAni.end())
		totalAni.insert({ keyName, ani });
}

void AniManager::Start(string key)
{
	it = totalAni.find(key);
	if (it != totalAni.end())
		it->second->start();
}

void AniManager::Stop(string key)
{
	it = totalAni.find(key);
	if (it != totalAni.end())
		it->second->stop();
}

void AniManager::Pause(string key)
{
	it = totalAni.find(key);
	if (it != totalAni.end())
		it->second->pause();
}

void AniManager::Resume(string key)
{
	it = totalAni.find(key);
	if (it != totalAni.end())
		it->second->resume();
}

Animation * AniManager::FindAni(string key)
{
	it = totalAni.find(key);
	if (it != totalAni.end())
		return it->second;

	return NULL;
}
