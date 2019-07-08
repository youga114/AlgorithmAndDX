#include "Mesh.h"
#include "../Library/FBXLoader.h"

Mesh::Mesh()
{
}

Mesh::Mesh(float x, float y, float z)
{
	SetPosition(x, y, z);
}

Mesh::Mesh(LPCSTR fbxName)
{
	fileName = fbxName;
}


Mesh::~Mesh()
{
	Memory::SafeRelease(vertexBuffer);
	Memory::SafeRelease(inputLayout);
}

bool Mesh::InitializeBuffers(ID3D11Device * device, ID3DBlob * vertexShaderBuffer)
{
	//// ���� �迭.
	//Vertex vertices[] = {						//ȭ�� ��� 0��ǥ(��ġ) 
	//	Vertex(
	//		XMFLOAT3(-0.5f, 0.5f, 0.5f), 
	//		//XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), 
	//		XMFLOAT2(-1.0f, -1.0f)
	//	),
	//	Vertex(
	//		XMFLOAT3(0.5f, 0.5f, 0.5f), 
	//		//XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f), 
	//		XMFLOAT2(2.0f, -1.0f)
	//	),
	//	Vertex(
	//		XMFLOAT3(0.5f, -0.5f, 0.5f), 
	//		//XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), 
	//		XMFLOAT2(2.0f, 2.0f)
	//	),
	//	Vertex(
	//		XMFLOAT3(-0.5f, -0.5f, 0.5f), 
	//		//XMFLOAT4(0.5f, 0.5f, 0.0f, 1.0f), 
	//		XMFLOAT2(-1.0f, 2.0f)
	//	)
	//};

	// FBX �ε�.
	HRESULT result = FBXLoader::LoadFBX(fileName, &vertices, &indices);
	if (IsError(result, TEXT("FBX �ε� ����")))
		return false;
	
	//// �迭 ũ�� ����.
	//nVertices = ARRAYSIZE(vertices);

	nVertices = GetVertexCount();

	D3D11_BUFFER_DESC vbDesc;
	ZeroMemory(&vbDesc, sizeof(D3D11_BUFFER_DESC));

	vbDesc.ByteWidth = sizeof(Vertex) * nVertices;
	vbDesc.CPUAccessFlags = 0;
	vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbDesc.MiscFlags = 0;
	vbDesc.Usage = D3D11_USAGE_DEFAULT;

	// ���� �迭 ���� �־��� ����ü.
	D3D11_SUBRESOURCE_DATA vbData;
	ZeroMemory(&vbData, sizeof(D3D11_SUBRESOURCE_DATA));
	vbData.pSysMem = &vertices[0];

	// ���� ���� ����.
	result = device->CreateBuffer(&vbDesc, &vbData, &vertexBuffer);
	if (IsError(result, TEXT("���� ���� ���� ����")))
	{
		return false;
	}

	//// �ε��� �迭.
	//DWORD indices[] =
	//{
	//	0, 1, 2,
	//	0, 2, 3
	//};

	//nIndices = ARRAYSIZE(indices);
	nIndices = GetIndexCount();

	// ���� ������.
	D3D11_BUFFER_DESC ibDesc;
	ZeroMemory(&ibDesc, sizeof(D3D11_BUFFER_DESC));

	ibDesc.ByteWidth = sizeof(DWORD) * nIndices;
	ibDesc.CPUAccessFlags = 0;
	ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibDesc.MiscFlags = 0;
	ibDesc.Usage = D3D11_USAGE_DEFAULT;

	// �ε��� �迭 ���� �־��� ����ü.
	D3D11_SUBRESOURCE_DATA ibData;
	ZeroMemory(&ibData, sizeof(D3D11_SUBRESOURCE_DATA));
	ibData.pSysMem = &indices[0];

	// �ε��� ���� ����.
	result = device->CreateBuffer(&ibDesc, &ibData, &indexBuffer);
	if (IsError(result, TEXT("���� ���� ���� ����")))
	{
		return false;
	}

	// �Է� ���̾ƿ� ������ ����.
	//D3D11_INPUT_ELEMENT_DESC layout[] = 
	//{
	//	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},			//32��Ʈ(4����Ʈ) * 3 = 12����Ʈ
	//	//{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
	//	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
	//};

	// �Է� ���̾ƿ� ����.
	result = device->CreateInputLayout(inputLayoutDesc, ARRAYSIZE(inputLayoutDesc), vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &inputLayout);

	if (IsError(result, TEXT("�Է� ���̾ƿ� ���� ����")))
	{
		return false;
	}

	// ��� ���� ����.
	// DX ��켱 / HLSL ���켱.
	PerObjectBuffer matrixData;
	matrixData.world = XMMatrixTranspose(GetWorldMatrix());		//���� ��� ����.

	// ��� ���� ������.
	D3D11_BUFFER_DESC cbDesc;
	ZeroMemory(&cbDesc, sizeof(D3D11_BUFFER_DESC));

	cbDesc.ByteWidth = sizeof(PerObjectBuffer);
	cbDesc.CPUAccessFlags = 0;
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.MiscFlags = 0;
	cbDesc.Usage = D3D11_USAGE_DEFAULT;

	// �ε��� �迭 ���� �־��� ����ü.
	D3D11_SUBRESOURCE_DATA cbData;
	ZeroMemory(&cbData, sizeof(D3D11_SUBRESOURCE_DATA));
	cbData.pSysMem = &matrixData;

	// ���� ����.
	result = device->CreateBuffer(&cbDesc, &cbData, &constantBuffer);
	if (IsError(result, TEXT("������Ʈ ��� ���� ���� ����")))
	{
		return false;
	}

	return true;
}

void Mesh::RenderBuffers(ID3D11DeviceContext * deviceContext)
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	// ���� ���� ����.
	deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

	// �ε��� ���� ���ε�.
	deviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// �Է� ���̾ƿ� ����.
	deviceContext->IASetInputLayout(inputLayout);

	// ���� ����.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// �׸���.
	//deviceContext->Draw(nVertices, 0);
	deviceContext->DrawIndexed(nIndices, 0, 0);
}

void Mesh::Update(ID3D11DeviceContext * deviceContext)
{
	// ��ġ(ȸ��, ������) ���� ������Ʈ.

	// ���� ��� ���� ���ε�.
	deviceContext->VSSetConstantBuffers(0, 1, &constantBuffer);
}

XMMATRIX Mesh::GetWorldMatrix()
{
	return GetScaleMatrix() * GetRotationMatrix() * GetTranslationMatrix();
}

XMMATRIX Mesh::GetTranslationMatrix()
{
	return XMMatrixTranslation(position.x, position.y, position.z);
}

XMMATRIX Mesh::GetRotationMatrix()
{
	XMMATRIX rotX = XMMatrixRotationX(XMConvertToRadians(rotation.x));
	XMMATRIX rotY = XMMatrixRotationY(XMConvertToRadians(rotation.y));
	XMMATRIX rotZ = XMMatrixRotationZ(XMConvertToRadians(rotation.z));

	return rotZ * rotX * rotY;
}

XMMATRIX Mesh::GetScaleMatrix()
{
	return XMMatrixScaling(scale.x, scale.y, scale.z);
}
