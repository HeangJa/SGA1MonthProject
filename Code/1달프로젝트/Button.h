#pragma once
//delegate pattern


enum BUTTONDIR
{
	BUTTONDIR_NULL,
	BUTTONDIR_UP,
	BUTTONDIR_DOWN,
};

//�Լ�������
// ��ȯ�� (*�Լ��������̸�)(�Ű�����) // �ڷ���* ������
// �Լ��������̸� = �Լ���
// �Լ��������̸�(�Ű�����);

typedef void(*FUNC)();
//typedef std::function<void()> FUNC;


/*
class AAA
{
	static int a;
public:
	int Add(int a) { return (a + 1); }
	static int GetA() { return a;}

	operator()
};

typedef int(*PTRFUNC)(void);
PTRFUNC ptr = &AAA::GetA;
int a = ptr();

typedef int (AAA::*PTRMEMFUNC)(int);
PTRMEMFUNC ptr1 = &AAA::Add;

AAA aa;
int b = (aa.*ptr1)(10);
*/



class Button
{
	BUTTONDIR	_direction;
	
	string		_imageName;
	Image*		_image;
	RECT		_rc;
	float		_x, _y;
	POINT		_btnDownFramePoint;
	POINT		_btnUpFramePoint;

	FUNC		_callBackFunc;

public:
	Button();
	~Button();

	bool Init(const string imageName, int x, int y,
		POINT btnDownFramePoint, POINT btnUpFramePoint,
		FUNC pFunc);

	void Release();
	void Update();
	void Render(HDC hdc);
};

