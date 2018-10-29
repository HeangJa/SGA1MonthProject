#pragma once
#include "singletonBase.h"

class txtData : public singletonBase<txtData>
{
	typedef map<pair<string, string>, string>			INIMap;
	typedef map<pair<string, string>, string>::iterator INIMap_it;

	INIMap												mINIData;
	INIMap_it											miINIData;

	string												strPath;

public:
	txtData();
	~txtData();

	HRESULT			init();
	void			release();

	// Save
	void			txtSave(const TCHAR* saveFileName, vector<string> vStr);
	TCHAR*			vectorArrayCombine(vector<string> vArray);

	//Load
	vector<string>	txtLoad(const TCHAR* loadFileName);
	vector<string>	charArraySeparation(TCHAR charArray[]);

	//INI
	bool			INIFilePathSetting();
	string			GetINIFileInfo(const TCHAR* pszSection, const TCHAR* pszKey, const TCHAR* pszFile);
	void			SetINIFileInfo(const TCHAR* pszSection, const TCHAR* pszKey, const TCHAR* pszData, const TCHAR* pszFile);

	void			LoadXML();
};

