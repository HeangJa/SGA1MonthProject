#include "Game.h"
#include"mainGame.h"



HINSTANCE	g_hInstance;
HWND		g_hWnd;
POINT		g_ptMouse;

//==============================================

mainGame _mg;

//==============================================

LPCTSTR		_lpszClass = TEXT("동방프로젝트모작");

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowSize(int x, int y, int width, int height);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lPszCmdParam, int cmdShow)
{
	MSG							message;
	WNDCLASS					wndClass;

	g_hInstance = hInstance;


	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = (WNDPROC)WndProc;
	wndClass.lpszClassName = _lpszClass;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wndClass);

	g_hWnd = CreateWindow(
		_lpszClass,
		_lpszClass,
		WS_OVERLAPPEDWINDOW,
		WINSTARTX,
		WINSTARTY,
		WINSIZEX,
		WINSIZEY,
		NULL,
		(HMENU)NULL,
		hInstance,
		NULL
	);

	// 게임 윈도우의 클라이언트영역의 사이즈 보정
	setWindowSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);

	if (FAILED(_mg.init()))
		return false;

	ShowWindow(g_hWnd, cmdShow);

	while (true)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT)
				break;

			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			// 타이머로 FPS를 고정 시킨다. -> 고정프레임 방식
			// 60FPS = 1/60 = 0.01666666667 => 이 시간 간격으로 업데이트와 랜더를 하겠다
			// 와 같은 고정프레임 처리 방식을 프레임 스키핑...
			TIMEMANAGER->update(60.f);

			// 게임 로직이 위치
			_mg.update();
			_mg.render();
		}
	}
	// 게임루프가 위치하고 게임루프안에서 mainGame의 update(), render()가 호출

	_mg.release();
		
	return message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return _mg.MainProc(hWnd, iMessage, wParam, lParam);
}

void setWindowSize(int x, int y, int width, int height)
{
	RECT winRect;
	winRect.left = 0;
	winRect.top = 0;
	winRect.right = width;
	winRect.bottom = height;

	AdjustWindowRect(&winRect, WS_CAPTION | WS_SYSMENU, false);

	SetWindowPos(g_hWnd, NULL, x, y, (winRect.right - winRect.left),
		(winRect.bottom - winRect.top), SWP_NOZORDER | SWP_NOMOVE);
}