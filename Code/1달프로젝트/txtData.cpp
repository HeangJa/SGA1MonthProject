#include "Game.h"
#include "txtData.h"

txtData::txtData()
{
}

txtData::~txtData()
{
}

HRESULT txtData::init()
{
	return S_OK;
}

void txtData::release()
{
}

void txtData::txtSave(const TCHAR * saveFileName, vector<string> vStr)
{
	HANDLE	file;
	TCHAR	str[128];
	DWORD	write;

	_tcsncpy_s(str, 128, vectorArrayCombine(vStr), 126);
	file = CreateFile(saveFileName, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, str, 128, &write, NULL);

	CloseHandle(file);
}

TCHAR * txtData::vectorArrayCombine(vector<string> vArray)
{
	TCHAR str[128];
	ZeroMemory(str, sizeof(str));
	
	for (int i = 0; i < vArray.size(); i++)
	{
		_tcsncat_s(str, 128, vArray[i].c_str(), 126);

		if (i + 1 < vArray.size())
			_tcscat(str, ",");
	}
	
	return str;
}

vector<string> txtData::txtLoad(const TCHAR * loadFileName)
{
	HANDLE	file;
	TCHAR	str[128];
	DWORD	read;
	file = CreateFile(loadFileName, GENERIC_READ, FALSE, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, str, 128, &read, NULL);

	CloseHandle(file);

	return charArraySeparation(str);
}

vector<string> txtData::charArraySeparation(TCHAR charArray[])
{
	vector<string> vArray;

	TCHAR* temp;
	const TCHAR* seperator = TEXT(",");
	TCHAR* token;

	token = _tcstok(charArray, seperator);
	vArray.push_back(token);

	while (NULL != (token = _tcstok(NULL, seperator)))
	{
		vArray.push_back(token);
	}

	return vArray;
}

bool txtData::INIFilePathSetting()
{
	TCHAR szTemp[MAX_PATH] = { 0, };
	GetModuleFileName(NULL, szTemp, MAX_PATH);

	string strTemp(szTemp, szTemp + _tcslen(szTemp));

	size_t size = strTemp.rfind(TEXT("\\"), strTemp.size());
	string::iterator it = strTemp.begin();
	string::iterator itEnd = it + size;

	strTemp.assign(it, itEnd);

	strPath = strTemp;

	return true;
}

string txtData::GetINIFileInfo(const TCHAR * pszSection, const TCHAR * pszKey, const TCHAR * pszFile)
{
	size_t nsize = 0;

	INIMap_it it = mINIData.find(make_pair<string, string>(pszSection, pszKey));
	if (it != mINIData.end())
		return (it->second);

	INIFilePathSetting();

	string strTemp;
	string strTempPath = strPath + TEXT("\\") + pszFile;

	TCHAR szTemp[100] = { 0, };
	GetPrivateProfileString(pszSection, pszKey, TEXT("None"), szTemp,
		sizeof(szTemp), strTempPath.c_str());

	//GetPrivateProfileInt
	//GetPrivateProfileStruct

	if (!_tcscmp(strTemp.c_str(), TEXT("None")))
		return TEXT("None");
	else
		strTemp = szTemp;

	// 여기는 순서가 잘 못 되었으니 추후 각자 수정.
	mINIData.insert(INIMap::value_type(make_pair<string, string>(pszSection, pszKey), strTemp));

	return string();
}

void txtData::SetINIFileInfo(const TCHAR * pszSection, const TCHAR * pszKey, const TCHAR * pszData, const TCHAR * pszFile)
{
	INIFilePathSetting();

	string strTempPath = strPath + TEXT("\\") + pszFile;

	if (!WritePrivateProfileString(pszSection, pszKey, pszData, strTempPath.c_str()))
	{
		// 실패 처리.....각자...

	}
}


// XML(Extensible Markup Language)
// HTML 등 .....
// 이 기종간, 다른 시스템간의 데이터 전달이 목적(서로 데이터를 주고 받는 것)
// XML tag라고 하는 부분들이 사용자에 의해 정의
// HTML은 tag 부분이 이미 정의 되어있다.
// XML은 자료구조가 tree 를 사용

/*
<?xml version = "" encoding = "UTF-8"?> //유니코드 기반
<Shop>
	<Item>
		<Potion>
		
		</Potion>

		<Weapon>
			<Sword Name = "청동검">
			</Sword>

		</Weapon>

		<Armor>

		</Armor>
	</Item>
</Shop>
*/

#include "Xml.h"

struct Frame
{
	float time;
	int	  index;
	POINT start;
	POINT end;
};

struct Action
{
	int		actionType;
	bool	repeat;
	vector<Frame>	vFrame;
};

void txtData::LoadXML()
{
	string strPath = "";

	XmlDocument* doc = new XmlDocument;
	XmlError err = doc->LoadFile(TEXT("경로명"));
	assert(err == Xml::XML_SUCCESS);

	XmlElement* player = doc->FirstChildElement(TEXT("Player"));
	XmlAttribute* path = (XmlAttribute*)player->FirstAttribute();
	strPath = path->Value();

	wstring fileName;
	fileName.assign(strPath.begin(), strPath.end());

	XmlElement* action = NULL;
	action = player->FirstChildElement();
	for (; action != NULL; action = action->NextSiblingElement())
	{
		vector<Action>		vAct;
		UINT repeat = action->UnsignedAttribute("Repeat");
		XmlElement* frame = action->FirstChildElement();

		for (; frame != NULL; frame->NextSiblingElement())
		{
			unsigned int time = frame->UnsignedAttribute("Time");

			XmlElement* start = frame->FirstChildElement("Start");

			XmlElement* end = frame->FirstChildElement("End");
		}
	}
}