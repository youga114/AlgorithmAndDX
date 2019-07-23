struct ps_input
{
	float4 position : SV_POSITION;
	float2 texCoord : TEXCOORD;
	float3 diffuse : TEXCOORD1;
};

// �ؽ�ó / ���÷� ������Ʈ.
Texture2D diffuseMap;
SamplerState diffuseSampler;

// �ȼ� ���̴�.
float4 main(ps_input input) : SV_TARGET
{
	// �ؽ�ó ���� �о����.
	float4 textureColor = diffuseMap.Sample(diffuseSampler, input.texCoord);
	
	// ����ó�� (��ǻ��).
	float3 diffuse = saturate(input.diffuse);				//0~1���̷� �ڸ��� �Լ� saturate()
	diffuse = diffuse * textureColor.rgb;

	return float4(diffuse, 1.0f);
}