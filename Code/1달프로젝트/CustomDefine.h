#pragma once

// ����� ���� �ڷ��� ����
typedef void(*CALL_FUNC)();
typedef void(*CALL_FUNC_PARAM)(void*);

#if defined(_UNICODE)
typedef std::wstring		tstring;
#else
typedef std::string			tstring;
#endif // #if defined(_UNICODE)

// EXTERN ������ ���� �߰� �κ�
extern HWND			g_hWnd;
extern HINSTANCE	g_hInstance;
extern POINT		g_ptMouse;
