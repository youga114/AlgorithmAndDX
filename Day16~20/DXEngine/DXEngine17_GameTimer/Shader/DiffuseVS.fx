// ��� ����.
cbuffer perObjectBuffer : register(b0)
{
	matrix world;
};

cbuffer perSceneBuffer : register(b1)
{
	matrix viewProjection;
}

// ���� ���̴� �Է�.
struct vs_input
{
	float4 position : POSITION;
	float2 texCoord : TEXCOORD;
	float3 normal : NORMAL;
};

// ���� ���̴� ���.
struct vs_output
{
	float4 position : SV_POSITION;
	float2 texCoord : TEXCOORD;
	float3 diffuse : TEXCOORD1;
};

// Entry Point(���� �Լ�).
vs_output main(vs_input input)
{
	vs_output output;

	// ���� ��ȯ.
	// ����-��-���� ��ȯ.
	output.position = mul(input.position, world);

	// �ӽ÷� ����Ʈ ��ġ ����.
	float3 worldLightPosition = float3(-500.0f, 500.0f, -500.0f);

	// ����Ʈ ���� ���ϱ�.
	float3 lightDir = normalize(output.position.xyz - worldLightPosition);

	// ���� ��ǥ����� ���.
	float3 worldNormal = normalize(mul(input.normal, (float3x3)world));

	// ���� ����(�ڻ��� ���ϱ�).
	output.diffuse = dot(-lightDir, worldNormal);

	output.position = mul(output.position, viewProjection);

	//output.color = input.color;
	output.texCoord = input.texCoord;

	return output;
}