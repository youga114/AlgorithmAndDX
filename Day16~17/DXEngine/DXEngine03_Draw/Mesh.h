#pragma once

#include "DXUtil.h"

using namespace DirectX;

class Mesh
{
private:
	struct Vertex
	{
		XMFLOAT3 position;

		Vertex(float x, float y, float z) : position(x, y, z) {}
	};

public:
	Mesh();
	~Mesh();

	bool InitializeBuffers(ID3D11Device* device, ID3DBlob* vertexShaderBuffer);

	void RenderBuffers(ID3D11DeviceContext* deviceContext);

private:

	int nVertices;			// ���� ����.
	
	ID3D11Buffer* vertexBuffer;		// ���� ���� ������ ����.
	ID3D11InputLayout* inputLayout;	// �Է� ���̾ƿ�.

};

