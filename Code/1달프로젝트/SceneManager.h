#pragma once
#include "singletonBase.h"

class gameNode;

class SceneManager : public singletonBase<SceneManager>
{
private:
	static gameNode* currentScene;		// ÇöÀç ¾À
	static gameNode* readyScene;		// ¹Ù²ð ¾À(´ë±â ¾À)

	map<string, gameNode*> sceneList;

public:
	SceneManager();
	~SceneManager();

	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	gameNode* AddScene(string sceneName, gameNode* scene);

	bool      ChangeScene(string sceneName);
};

