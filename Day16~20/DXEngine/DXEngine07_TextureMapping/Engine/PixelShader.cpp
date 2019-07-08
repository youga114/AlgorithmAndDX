#include "PixelShader.h"

PixelShader::PixelShader()
{

}

PixelShader::PixelShader(LPCTSTR fileName) : Shader(fileName)
{
	profile = "ps_5_0";
}

PixelShader::PixelShader(LPCTSTR fileName, LPCSTR entry, LPCSTR profile) : Shader(fileName, entry, profile)
{

}


PixelShader::~PixelShader()
{

}

bool PixelShader::CompileShader(ID3D11Device * device)
{
	// �ȼ� ���̴� ������ -> ����Ʈ �ڵ�.
	HRESULT result = D3DCompileFromFile(fileName, NULL, NULL, entryPoint, profile, NULL, NULL, &shaderBuffer, NULL);

	// ���� Ȯ��.
	if (IsError(result, TEXT("�ȼ� ���̴� ������ ����")))
		return false;

	return true;
}

bool PixelShader::CreateShader(ID3D11Device * device)
{
	// �ȼ� ���̴� ��ü ����.
	HRESULT result = device->CreatePixelShader(shaderBuffer->GetBufferPointer(), shaderBuffer->GetBufferSize(), NULL, &pixelShader);

	// ���� Ȯ��.
	if (IsError(result, TEXT("�ȼ� ���̴� ��ü ���� ����")))
		return false;

	return true;
}

void PixelShader::BindShader(ID3D11DeviceContext * deviceContext)
{
	// �ȼ� ���̴� ����(���ε�).
	deviceContext->PSSetShader(pixelShader, NULL, NULL);
}

void PixelShader::Release()
{
	// �ڿ� ����.
	Shader::Release();
	Memory::SafeRelease(pixelShader);
}

bool PixelShader::CreateSamplerState(ID3D11Device * device)
{
	// ���÷� ������Ʈ ������.
	D3D11_SAMPLER_DESC samplerDesc;
	ZeroMemory(&samplerDesc, sizeof(D3D11_SAMPLER_DESC));

	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;		// �⺻ ����.
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	// ���÷� ������Ʈ ����.
	HRESULT result = device->CreateSamplerState(&samplerDesc, &samplerState);
	if (IsError(result, TEXT("���÷� ������Ʈ ���� ����")))
		return false;

	return true;
}

void PixelShader::BindSamplerState(ID3D11DeviceContext * deviceContext)
{
	// ���÷� ������Ʈ ���ε�.
	deviceContext->PSSetSamplers(0, 1, &samplerState);
}

bool PixelShader::LoadTexture(ID3D11Device * device, LPCTSTR fileName)
{
	// �ؽ�ó �ε�.
	texture.fileName = fileName;
	if (texture.LoadTextureFromFile(device) == false)
		return false;

	return true;
}

void PixelShader::BindTexture(ID3D11DeviceContext * deviceContext)
{
	deviceContext->PSSetShaderResources(0, 1, &texture.textureResourceView);
}
