#pragma once

#include <Windows.h>

class Engine;

class AppWindow
{
public:
	AppWindow(HINSTANCE hinstance);
	~AppWindow();

	int Run(Engine* engine);
	bool InitializeWindow();
	virtual LRESULT MessageProcessor(
		HWND hwnd,
		UINT msg,
		WPARAM wParam,
		LPARAM IParam
	);

protected:

	HWND hwnd;				//������ �ڵ�.
	HINSTANCE hinstance;	//â �ν��Ͻ�.
	UINT screenWidth;		//ȭ�� ����ũ��.
	UINT screenHeight;		//����ũ��.
	LPCTSTR applicationName;//â �̸�.
	DWORD windowStyle;		//â ���.
};

