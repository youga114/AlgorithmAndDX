// 픽셀 셰이더 입력.
// 셰이더/쉐이더 (Shader) 같음.
struct ps_input
{
	float4 position : SV_POSITION;
	float2 texCoord : TEXCOORD;
	float3 diffuse : TEXCOORD1;
};

// 텍스처 / 샘플러 스테이트.
Texture2D diffuseMap;
SamplerState diffuseSampler;

// 픽셀 셰이더.
float4 main(ps_input input) : SV_TARGET
{
	// 텍스처 색상 읽어오기.
	float4 textureColor = diffuseMap.Sample(diffuseSampler, input.texCoord);
	
	// 음영처리 (디퓨즈).
	float3 diffuse = input.diffuse;				//0~1사이로 자르는 함수 saturate()
	//diffuse = diffuse * textureColor.rgb;

	float3 red = float3(1.0f, 1.0f, 1.0f);
	float3 gray = float3(0.4f, 0.4f, 0.4f);
	float3 black = float3(0.0f, 0.0f, 0.0f);

	float3 toon = 0;
	if (diffuse.x > 0)
		toon = red;
	else if (diffuse.x > -0.5f)
		toon = gray;
	else
		toon = black;
	
	return float4(toon, 1.0f);
}