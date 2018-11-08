#pragma once
#pragma warning (disable : 4996)

// <Windows.h> 는 이 안에 있음
#include "commonMacroFunction.h"	

// 시스템 헤더 추가 부분
#include <assert.h>
#include <tchar.h>
#include <math.h>

#include <functional>
#include <string>
#include <vector>
#include <list>
#include <map>

#include <fstream>
#include <algorithm>

using namespace std;
//using std::string;
//using std::list;
//using std::map;


// 사용자 정의 헤더 추가 부분
#include "randomFunction.h"
#include "timerManager.h"
#include "KeyManager.h"
#include "ImageManager.h"
#include "EffectManager.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "AniManager.h"
#include "NumberManager.h"
#include "txtData.h"
#include "Camera.h"
#include "Image.h"
#include "util.h"
#include "Player.h"
#include "EnemyObject.h"
#include "Collision.h"
#include "Items.h"
#include "Boss.h"

//
#include "MacroDefine.h"
#include "CustomDefine.h"