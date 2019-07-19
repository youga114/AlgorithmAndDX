#include "Engine.h"

Engine::Engine(HINSTANCE hinstance) : DXApp(hinstance)
{

}

Engine::~Engine()
{
	//Memory::SafeDelete(mesh);
	//Memory::SafeDelete(mesh2);

	for (auto mesh = meshes.begin(); mesh != meshes.end(); ++mesh)
	{
		Memory::SafeDelete((*mesh));
	}

	//material->Release();
	//Memory::SafeDelete(material);

	//material2->Release();
	//Memory::SafeDelete(material2);

	Memory::SafeDelete(camera);
	Memory::SafeDelete(input);

	Memory::SafeRelease(constantBuffer);
}

int Engine::Run()
{
	return window->Run(this);
}

bool Engine::Init()
{
	if (DXApp::Init() == false)
		return false;

	// Ÿ�̸� �ʱ�ȭ.
	InitializeTimer();

	// �Է� �ʱ�ȭ.
	InitializeInput();

	// ��� �ʱ�ȭ.
	if (InitializeScene() == false)
		return false;

	// ��� �ʱ�ȭ.
	if (InitializeTransformation() == false)
		return false;

	return true;
}

void Engine::Update(float deltaTime)
{
	// ���� ��� ���ε�.
	//mesh->Update(deviceContext);
	camera->UpdateCamera();

	PerSceneBuffer matrixData;
	matrixData.viewProjection = XMMatrixTranspose(
		camera->GetViewMatrix() * camera->GetProjectionMatrix()
	);
	matrixData.worldLightPosition = XMFLOAT3(500.0f, 500.0f, -500.0f);
	matrixData.worldCameraPosition = camera->GetPosition();

	deviceContext->UpdateSubresource(constantBuffer, 0, NULL, &matrixData, 0, 0);

	// ��/���� ��� ���ε�.
	deviceContext->VSSetConstantBuffers(1, 1, &constantBuffer);
}

void Engine::Render(float deltaTime)
{
	float color[] = { 0.0f, 0.25f, 0.25f, 1.0f };

	// ���� Ÿ���� ������ �������� ĥ�ϱ�.
	deviceContext->ClearRenderTargetView(renderTargetView, color);

	// ����/���ٽ� �� �����.
	deviceContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	for (auto mesh = meshes.begin(); mesh != meshes.end(); ++mesh)
	{
		// ���� ��� ���ε�.
		(*mesh)->Update(deviceContext);

		// ���̴� ���ε�.
		(*mesh)->BindShaders(deviceContext);

		// �ؽ�ó/���÷� ������Ʈ ���ε�.
		(*mesh)->BindTextures(deviceContext);
		(*mesh)->BindSamplerState(deviceContext);

		// �����Ͷ����� ������Ʈ ���ε�.
		(*mesh)->BindRasterizerState(deviceContext);

		// �޽� ���� �׸���.
		(*mesh)->RenderBuffers(deviceContext);
	}
	
	// ����� <-> ����Ʈ ���� ��ȯ.
	swapChain->Present(1, 0);
}

void Engine::ProcessInput(float deltaTime)
{
	// ESC ���� ó��.
	if (input->IsKeyDown(Keyboard::Keys::Escape))
	{
		if (MessageBox(NULL, TEXT("�����Ͻðڽ��ϱ�?"), TEXT("����"), MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			DestroyWindow(window->GetWindowHandle());
		}
	}

	float moveSpeed = 200.0f;
	// ī�޶� �̵�/ȸ��.
	if (input->IsKeyDown(Keyboard::Keys::A) || input->IsKeyDown(Keyboard::Keys::Left))
	{
		camera->MoveRight(-1.0f * moveSpeed * deltaTime);
	}

	if (input->IsKeyDown(Keyboard::Keys::D) || input->IsKeyDown(Keyboard::Keys::Right))
	{
		camera->MoveRight(1.0f * moveSpeed * deltaTime);
	}

	if (input->IsKeyDown(Keyboard::Keys::W) || input->IsKeyDown(Keyboard::Keys::Up))
	{
		camera->MoveForward(1.0f * moveSpeed * deltaTime);
	}

	if (input->IsKeyDown(Keyboard::Keys::S) || input->IsKeyDown(Keyboard::Keys::Down))
	{
		camera->MoveForward(-1.0f * moveSpeed * deltaTime);
	}

	if (input->IsKeyDown(Keyboard::Keys::Q))
	{
		camera->MoveUp(1.0f * moveSpeed * deltaTime);
	}

	if (input->IsKeyDown(Keyboard::Keys::E))
	{
		camera->MoveUp(-1.0f * moveSpeed * deltaTime);
	}

	float rotationSpeed = 5.0f;
	// ���콺 ���� ��ư ���� ���� �̵�.
	Mouse::State state = input->GetMouseState();
	if (state.leftButton)
	{
		camera->Yaw(state.x * rotationSpeed * deltaTime);
		camera->Pitch(state.y * rotationSpeed * deltaTime);
	}
}

bool Engine::InitializeScene()
{
	// FBX �̸� ����.
	LPCSTR fbxTPP = "Resources/Models/HeroTPP.FBX";
	LPCSTR fbxBox = "Resources/Models/SK_CharM_Cardboard.FBX";
	LPCSTR fbxCube = "Resources/Models/cube.FBX";
	LPCSTR fbxSphere = "Resources/Models/sphere.FBX";
	LPCSTR fbxBarbarous = "Resources/Models/SK_CharM_Barbarous.FBX";
	LPCSTR fbxBear = "Resources/Models/Enemy_Bear.FBX";

	// �ؽ�ó �̸� ����.
	LPCTSTR tppDiffuseTexture = TEXT("Resources/Textures/T_Chr_FPS_D.png");
	LPCTSTR tppNormalTexture = TEXT("Resources/Textures/T_Chr_FPS_N.png");

	LPCTSTR boxDiffuseTexture = TEXT("Resources/Textures/Char_M_Cardboard_D.png");
	LPCTSTR boxNormalTexture = TEXT("Resources/Textures/Char_M_Cardboard_D.png");

	LPCTSTR barbarousDiffuseTexture = TEXT("Resources/Textures/T_Barbarous_D.TGA");
	LPCTSTR barbarousNormalTexture = TEXT("Resources/Textures/T_Barbarous_N.TGA");

	LPCTSTR bearDiffuseTexture = TEXT("Resources/Textures/T_Enemy_Bear_D.TGA");
	LPCTSTR bearNormalTexture = TEXT("Resources/Textures/T_Enemy_Bear_N.TGA");

	LPCTSTR lightStepTexture = TEXT("Resources/Textures/LightStep.png");
	LPCTSTR warpTexture = TEXT("Resources/Textures/Warp.png");

	LPCTSTR areskutanTexture = TEXT("Resources/Textures/Areskutan.dds");

	// ���̴� �̸� ����.
	LPCTSTR warpDiffuseShader = TEXT("Shader/WarpDiffuse");
	LPCTSTR normalMappingShader = TEXT("Shader/NormalMapping");
	LPCTSTR normalMappingShader2 = TEXT("Shader/NormalMapping2");

	LPCTSTR cubemappingShader = TEXT("Shader/CubeMapping");

	Mesh* sphere = new Mesh(fbxSphere, cubemappingShader, D3D11_FILL_SOLID, D3D11_CULL_NONE);
	sphere->SetPosition(0.0f, 0.0f, 0.0f);
	sphere->SetScale(20.0f, 20.0f, 20.0f);
	sphere->AddTexture(areskutanTexture);
	meshes.push_back(sphere);

	// �޽� ����.
	//mesh = new Mesh(0.0f, 0.0f, 0.0f);
	Mesh* tppWarp = new Mesh(fbxTPP, warpDiffuseShader);
	tppWarp->SetPosition(-70.0f, -90.0f, 0.0f);
	tppWarp->SetRotation(-90.0f, 180.0f, 0.0f);
	tppWarp->SetScale(1.0f, 1.0f, 1.0f);

	tppWarp->AddTexture(lightStepTexture);
	tppWarp->AddTexture(tppDiffuseTexture);

	// �迭�� �߰�.
	meshes.push_back(tppWarp);

	Mesh* tppNormal = new Mesh(fbxTPP, normalMappingShader2, D3D11_FILL_WIREFRAME, D3D11_CULL_NONE);
	tppNormal->SetPosition(70.0f, -90.0f, 0.0f);
	tppNormal->SetRotation(-90.0f, 180.0f, 0.0f);

	tppNormal->AddTexture(tppDiffuseTexture);
	tppNormal->AddTexture(tppNormalTexture);

	// �迭�� �߰�.
	meshes.push_back(tppNormal);

	Mesh* tppNormal2 = new Mesh(fbxBarbarous, normalMappingShader2);
	tppNormal2->SetPosition(210.0f, -90.0f, 0.0f);
	tppNormal2->SetRotation(-90.0f, 180.0f, 0.0f);

	tppNormal2->AddTexture(barbarousDiffuseTexture);
	tppNormal2->AddTexture(barbarousNormalTexture);

	// �迭�� �߰�.
	meshes.push_back(tppNormal2);

	Mesh* tppNormal3 = new Mesh(fbxBear, normalMappingShader2);
	tppNormal3->SetPosition(-210.0f, -90.0f, 0.0f);
	tppNormal3->SetRotation(-90.0f, 180.0f, 0.0f);

	tppNormal3->AddTexture(bearDiffuseTexture);
	tppNormal3->AddTexture(bearNormalTexture);

	// �迭�� �߰�.
	meshes.push_back(tppNormal3);

	// �޽� �ʱ�ȭ.
	if (InitializeMeshes() == false)
		return false;

	return true;
}

bool Engine::InitializeTransformation()
{
	// �þ߰� / ��Ⱦ�� ����.
	float fovY = XMConvertToRadians(60.0f);
	float aspectRatio = static_cast<float>(window->GetScreenWidth()) / static_cast<float>(window->GetScreenHeight());

	// ī�޶� ��ü ����.
	camera = new Camera(fovY, aspectRatio, 1.0f, 100000.0f);

	// ���ۿ� ���� ����ü ���� ����.
	PerSceneBuffer matrixData;
	matrixData.viewProjection = XMMatrixTranspose(
		camera->GetViewMatrix() * camera->GetProjectionMatrix()
	);
	matrixData.worldLightPosition = XMFLOAT3(500.0f, 500.0f, -500.0f);
	matrixData.worldCameraPosition = camera->GetPosition();

	// ���� ����.
	// ���� ������.
	D3D11_BUFFER_DESC cbDesc;
	ZeroMemory(&cbDesc, sizeof(D3D11_BUFFER_DESC));

	cbDesc.ByteWidth = sizeof(PerSceneBuffer);
	cbDesc.CPUAccessFlags = 0;
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
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

void Engine::InitializeInput()
{
	input = new InputClass();
	input->InitializeInput(window->GetWindowHandle());
}

void Engine::InitializeTimer()
{
	gameTimer = new GameTimer();
	gameTimer->StartTimer();
}

bool Engine::InitializeMeshes()
{
	for (auto mesh = meshes.begin(); mesh != meshes.end(); ++mesh)
	{
		// ��Ƽ���� ������.
		if ((*mesh)->CompileShaders(device) == false)
			return false;

		// �� ���̴� ��ü ����.
		if ((*mesh)->CreateShaders(device) == false)
			return false;

		// �ؽ�ó �ε�.
		if ((*mesh)->LoadTextures(device) == false)
			return false;

		// ���÷� ������Ʈ ����.
		if ((*mesh)->CreateSamplerState(device) == false)
			return false;

		// ���� �ʱ�ȭ.
		if ((*mesh)->InitializeBuffers(device) == false)
			return false;

		// �����Ͷ����� ������Ʈ ����.
		if ((*mesh)->CreateRasterizerState(device) == false)
			return false;
	}

	return true;
}
