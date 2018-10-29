#include "Game.h"
#include "Xml.h"
#include "TestScene.h"


TestScene::TestScene()
{
}

TestScene::~TestScene()
{
}

HRESULT TestScene::init()
{
	string strPath = "";

	XmlDocument* doc = new XmlDocument;
	XmlError err = doc->LoadFile(TEXT("Metalslug.xml"));
	assert(err == Xml::XML_SUCCESS);
	
	XmlElement* player = doc->FirstChildElement(TEXT("Player"));
	XmlAttribute* path = (XmlAttribute*)player->FirstAttribute();
	strPath = path->Value();
	aaa = strPath;

	wstring fileName;
	fileName.assign(strPath.begin(), strPath.end());

	XmlElement* action = player->FirstChildElement();
	XmlAttribute* path2 = (XmlAttribute*)action->FirstAttribute();
	bbb = path2->Value();
	
	for (; action != NULL; action = action->NextSiblingElement())
	{
		vector<Action>		vAct;
		UINT repeat = action->UnsignedAttribute("Repeat");
		XmlElement* frame = action->FirstChildElement();
		
		for (; frame != NULL; frame = frame->NextSiblingElement())
		{
			unsigned int time = frame->UnsignedAttribute("Time");

			XmlElement* start = frame->FirstChildElement("Start");

			XmlElement* end = frame->FirstChildElement("End");
		}
	}
	
	return S_OK;
}

void TestScene::release()
{
}

void TestScene::update()
{
}

void TestScene::render()
{
	TCHAR szTemp[100] = { 0, };
	_stprintf_s(szTemp, sizeof(szTemp), aaa.c_str());
	TextOut(getMemDC(), 200, 200, szTemp, _tcslen(szTemp));


	_stprintf_s(szTemp, sizeof(szTemp), TEXT("%c%c%c"), 65,66,67);
	TextOut(getMemDC(), 300, 200, szTemp, _tcslen(szTemp));

	NUMBERMANAGER->DrawNumber(getMemDC(), 18543, 400, 400, 1, 6);

	string filePath = "Score.txt";

	int i = 0;
	/*
	ofstream writeFile(filePath.data(), ios_base::app);
	if (writeFile.is_open()) 
	{
		writeFile << "123456\n";
		writeFile << "123456\n";
		writeFile.close();
	}

	ifstream openFile(filePath.data());
	if (openFile.is_open())
	{
		string line;
		while (getline(openFile, line)) {
			_stprintf_s(szTemp, sizeof(szTemp), line.c_str());
			TextOut(getMemDC(), 500, 200 + i, szTemp, _tcslen(szTemp));
			i += 50;
		}
		openFile.close();
	}*/
}
