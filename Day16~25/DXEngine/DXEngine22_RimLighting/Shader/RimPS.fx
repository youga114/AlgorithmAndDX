struct ps_input
{
	float4 position : SV_POSITION;
	float2 texCoord : TEXCOORD;
	float3 diffuse : TEXCOORD1;

	float3 viewDir : TEXCOORD2;
	float3 normal : TEXCOORD3;
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
	//float3 diffuse = saturate(input.diffuse);	//0~1���̷� �ڸ��� �Լ� saturate()			
	float3 diffuse = input.diffuse;	//Lambert.
	diffuse = diffuse * 0.5f + 0.5f;			// Half Lambert.
	diffuse = pow(diffuse, 2.0f);				// Half Lambert Update.
	diffuse = diffuse * textureColor.rgb;

	float3 normal = normalize(input.normal);
	float3 rimColor = float3(1.0f, 1.0f, 0.0f);
	float3 rim = abs(dot(-input.viewDir, normal));
	rim = pow(1.0f - rim, 10.0f) * rimColor;

	return float4(rim, 1.0f);
}