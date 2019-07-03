#include "Engine.h"



Engine::Engine(HINSTANCE hinstance) : DXApp(hinstance)
{

}


Engine::~Engine()
{
	Memory::SafeDelete(mesh);

	vertexShader->Release();
	Memory::SafeDelete(vertexShader);

	pixelShader->Release();
	Memory::SafeDelete(pixelShader);
}

int Engine::Run()
{
	return window->Run(this);
}

bool Engine::Init()
{
	if (DXApp::Init() == false)
		return false;

	// ��� �ʱ�ȭ.
	if (InitializeScene() == false)
		return false;

	// ��� �ʱ�ȭ.
	if (InitializeTransformation() == false)
		return false;

	return true;
}

void Engine::Update()
{
	// ���� ��� ���ε�.
	mesh->Update(deviceContext);

	// ��/���� ��� ���ε�.
	deviceContext->VSSetConstantBuffers(1, 1, &constantBuffer);
}

void Engine::Render()
{
	float color[]{ 0.0f, 0.0f,0.0f,1.0f };

	// ���� Ÿ���� ������ �������� ĥ�ϱ�.
	deviceContext->ClearRenderTargetView(renderTargetView, color);

	// ���ε�.
	vertexShader->BindShader(deviceContext);
	pixelShader->BindShader(deviceContext);

	// �޽� ���� �׸���.
	mesh->RenderBuffers(deviceContext);

	// ����� <-> ����Ʈ ���� ��ȯ.
	swapChain->Present(1, 0);
	
}

bool Engine::InitializeScene()
{
	// ���� ���̴� ����.
	vertexShader = new VertexShader(TEXT("Shader//VS.fx"));
	// ���� ���̴� ������.
	if (vertexShader->CompileShader(device) == false)
		return false;
	// ���� ���̴� ��ü ����.
	if (vertexShader->CreateShader(device) == false)
		return false;

	// �ȼ� ���̴� ����.
	pixelShader = new PixelShader(TEXT("Shader//PS.fx"));
	// �ȼ� ���̴� ������.
	if (pixelShader->CompileShader(device) == false)
		return false;
	// �ȼ� ���̴� ��ü ����.
	if (pixelShader->CreateShader(device) == false)
		return false;

	// �޽� ����.
	mesh = new Mesh(0.7f, 0.0f, 0.0f);
	// �ʱ�ȭ.
	if (mesh->InitializeBuffers(device, vertexShader->GetShaderBuffer()) == false)
		return false;

	return true;
}

bool Engine::InitializeTransformation()
{
	// ī�޶� ���� ����.
	cameraPosition = XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f);
	cameraView = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	cameraUpVector = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	// �� ���.
	XMMATRIX view = XMMatrixLookAtLH(cameraPosition, cameraView, cameraUpVector);

	// ���� ���.
	// �þ߰� / ��Ⱦ�� ����.
	float fovY = XMConvertToRadians(70.0f);
	float aspectRatio = static_cast<float>(window->GetScreenWidth()) / static_cast<float>(window->GetScreenHeight());

	XMMATRIX projection = XMMatrixPerspectiveFovLH(fovY, aspectRatio, 1.0f, 100.0f);

	// ���ۿ� ���� ����ü ���� ����.
	PerSceneBuffer matrixData;
	matrixData.view = XMMatrixTranspose(view);
	matrixData.projection = XMMatrixTranspose(projection);

	// ���� ����.
	// ���� ������.
	D3D11_BUFFER_DESC cbDesc;
	ZeroMemory(&cbDesc, sizeof(D3D11_BUFFER_DESC));

	cbDesc.ByteWidth = sizeof(PerSceneBuffer);
	cbDesc.CPUAccessFlags = 0;
	cbDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	cbDesc.MiscFlags = 0;
	cbDesc.Usage = D3D11_USAGE_DEFAULT;

	// �ε��� �迭 ���� �־��� ����ü.
	D3D11_SUBRESOURCE_DATA cbData;
	ZeroMemory(&cbData, sizeof(D3D11_SUBRESOURCE_DATA));
	cbData.pSysMem = &matrixData;

	// ��� ���� ����.
	HRESULT result = device->CreateBuffer(&cbDesc, &cbData, &constantBuffer);
	if (IsError(result, TEXT("�� ��� ���� ���� ����")))
	{
		return false;
	}

	return true;
}
