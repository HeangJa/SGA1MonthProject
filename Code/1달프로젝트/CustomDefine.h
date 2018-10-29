#pragma once

// 사용자 정의 자료형 선언
typedef void(*CALL_FUNC)();
typedef void(*CALL_FUNC_PARAM)(void*);

#if defined(_UNICODE)
typedef std::wstring		tstring;
#else
typedef std::string			tstring;
#endif // #if defined(_UNICODE)

// EXTERN 선언한 변수 추가 부분
extern HWND			g_hWnd;
extern HINSTANCE	g_hInstance;
extern POINT		g_ptMouse;
