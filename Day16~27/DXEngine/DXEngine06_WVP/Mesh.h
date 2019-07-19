#pragma once

#include "DXUtil.h"

using namespace DirectX;

class Mesh
{
private:
	struct Vertex
	{
		XMFLOAT3 position;
		XMFLOAT4 color;

		Vertex(float x, float y, float z) : position(x, y, z) {}
		Vertex(XMFLOAT3 position) : position(position) {}
		Vertex(XMFLOAT3 position, XMFLOAT4 color) : position(position), color(color) {}
	};

	struct PerObjectBuffer
	{
		PerObjectBuffer() { ZeroMemory(this, sizeof(this)); }

		XMMATRIX world;
	};

public:
	Mesh();
	Mesh(float x, float y, float z);
	~Mesh();

	bool InitializeBuffers(ID3D11Device* device, ID3DBlob* vertexShaderBuffer);

	void RenderBuffers(ID3D11DeviceContext* deviceContext);

	void Update(ID3D11DeviceContext* deviceContext);

	// Getter.
	XMFLOAT3 GetPosition() const { return position; }
	XMMATRIX GetWorldMatrix() const;

	// Setter.
	void SetPosition(float x, float y, float z)
	{
		position = XMFLOAT3(x, y, z);
	}

private:

	int nVertices;			// ���� ����.
	int nIndices;			// �ε��� ����.
	
	ID3D11Buffer* vertexBuffer;		// ���� ���� ������ ����.
	ID3D11Buffer* indexBuffer;		// �ε��� ������ ����.
	ID3D11InputLayout* inputLayout;	// �Է� ���̾ƿ�.

	ID3D11Buffer* constantBuffer;	// ��� ���� (���� ���).

	XMFLOAT3 position;				// ��ġ ����.
};

