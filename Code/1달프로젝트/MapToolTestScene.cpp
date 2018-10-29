#include "Game.h"
#include "MapToolTestScene.h"

MapToolTestScene::MapToolTestScene()
	: currentTile({0, 0})
{
}

MapToolTestScene::~MapToolTestScene()
{
}

HRESULT MapToolTestScene::init()
{
	if (WINSIZEX < 1300)
		return E_FAIL;

	IMAGEMANAGER->addFrameImage(TEXT("Tile"), TEXT("Image/maptiles.bmp"),
		640, 288, SAMPLETILEX, SAMPLETILEY, true, RGB(255, 0, 255));

	mapToolSetup();

	currentTile.x = 2;
	currentTile.y = 0;

	return S_OK;
}

void MapToolTestScene::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		GetCursorPos(&g_ptMouse);
		ScreenToClient(g_hWnd, &g_ptMouse);
		ClickSample();
	}
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		GetCursorPos(&g_ptMouse);
		ScreenToClient(g_hWnd, &g_ptMouse);
		ClickMap();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		SaveTile();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		LoadTile();
	}
}

void MapToolTestScene::render()
{
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		IMAGEMANAGER->frameRender(TEXT("Tile"), getMemDC(),
			tile[i].rc.left, tile[i].rc.top,
			tile[i].frameX, tile[i].frameY);
	}

	IMAGEMANAGER->render(TEXT("Tile"), getMemDC(), (WINSIZEX - SAMPLETILEX * TILESIZE), 0);
}

void MapToolTestScene::release()
{
}

void MapToolTestScene::mapToolSetup()
{
	for (int i = 0; i < SAMPLETILEY; i++)
	{
		for (int j = 0; j < SAMPLETILEX; j++)
		{
			sampleTile[i*SAMPLETILEX + j].frameX = j;
			sampleTile[i*SAMPLETILEX + j].frameY = i;

			SetRect(&sampleTile[i*SAMPLETILEX + j].rc,
				(WINSIZEX - TILESIZE * SAMPLETILEX) + j * TILESIZE,
				i*TILESIZE,
				(WINSIZEX - TILESIZE * SAMPLETILEX) + j * TILESIZE + TILESIZE,
				i*TILESIZE + TILESIZE);
		}
	}

	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			SetRect(&tile[i*TILEX + j].rc,
				j*TILESIZE, i*TILESIZE,
				j*TILESIZE + TILESIZE, i*TILESIZE + TILESIZE);
		}
	}

	for (int i = 0; i < TILEX*TILEY; i++)
	{
		tile[i].frameX = 2;
		tile[i].frameY = 0;
	}
}

void MapToolTestScene::ClickSample()
{
	for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
	{
		if (PtInRect(&sampleTile[i].rc, g_ptMouse))
		{
			currentTile.x = sampleTile[i].frameX;
			currentTile.y = sampleTile[i].frameY;
			break;
		}
	}
}

void MapToolTestScene::ClickMap()
{
	for (int i = 0; i < TILEX*TILEY; i++)
	{
		if (PtInRect(&tile[i].rc, g_ptMouse))
		{
			tile[i].frameX = currentTile.x;
			tile[i].frameY = currentTile.y;
		}
	}
}

void MapToolTestScene::SaveTile()
{
	HANDLE file;
	DWORD  write;

	file = CreateFile(TEXT("mapData.map"), GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, tile, sizeof(Tile)*TILEX*TILEY, &write, NULL);

	CloseHandle(file);
}

void MapToolTestScene::LoadTile()
{
	HANDLE file;
	DWORD  read;

	file = CreateFile(TEXT("mapData.map"), GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, tile, sizeof(Tile)*TILEX*TILEY, &read, NULL);

	CloseHandle(file);
}
