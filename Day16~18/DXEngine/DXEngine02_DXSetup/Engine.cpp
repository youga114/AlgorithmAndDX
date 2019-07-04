#include "Engine.h"



Engine::Engine(HINSTANCE hinstance) : DXApp(hinstance)
{

}


Engine::~Engine()
{
}

int Engine::Run()
{
	return window->Run(this);
}

bool Engine::Init()
{
	if (DXApp::Init() == false)
		return false;

	return true;
}

void Engine::Update()
{
}

void Engine::Render()
{
	float color[]{ 0.0f, 0.0f,0.0f,1.0f };

	// ���� Ÿ���� ������ �������� ĥ�ϱ�.
	deviceContext->ClearRenderTargetView(renderTargetView, color);

	// ����� <-> ����Ʈ ���� ��ȯ.
	swapChain->Present(1, 0);
	
}
