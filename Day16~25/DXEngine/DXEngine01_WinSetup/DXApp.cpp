#include "DXApp.h"

DXApp::DXApp(HINSTANCE hinstance)
{
	// ������ ��ü ����.
	window = new AppWindow(hinstance);
}


DXApp::~DXApp()
{
	delete window;
}

bool DXApp::Init()
{
	if (window->InitializeWindow() == false)
		return false;

	return true;
}
