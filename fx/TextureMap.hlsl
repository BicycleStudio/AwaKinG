cbuffer PerFrame : register(b0)	{ matrix ViewProj; };
cbuffer PerObj : register(b1)		{ matrix World; };
cbuffer PerObj : register(b2)		{ float4 PerObjColor; };
Texture2D texDiffuse : register(t0);
SamplerState samLinear : register(s0);

struct VS_SystemModelInput
{
	float3 Pos		: POSITION;
};
struct PS_SystemModelInput
{
	float4 Pos		: SV_POSITION;
};

struct VS_Input
{
	float3 Pos		: POSITION;
	float2 Tex		: TEXCOORD0;
	float3 Normal	: Normal;
};
struct PS_Input
{
	float4 Pos		: SV_POSITION;
	float2 Tex		: TEXCOORD0;
	float3 Normal	: Normal;
};

PS_Input VS(VS_Input input)
{
	PS_Input output = (PS_Input)0;
	output.Pos = mul(float4(input.Pos, 1.0f), World);
	output.Pos = mul(output.Pos, ViewProj);
	output.Tex = input.Tex;
	output.Normal = mul(input.Normal, (float3x3)World);

	return output;
}
float4 PS(PS_Input input) : SV_Target
{
	return texDiffuse.Sample(samLinear, input.Tex);
}
PS_Input VSTerrain(VS_Input input)
{
	PS_Input output = (PS_Input)0;
	output.Pos = mul(float4(input.Pos, 1.0f), ViewProj);
	output.Tex = input.Tex;
	output.Normal = input.Normal;

	return output;
}
float4 PSTerrain(PS_Input input) : SV_Target
{
	return texDiffuse.Sample(samLinear, input.Tex);
}
PS_SystemModelInput VSSystemModel(VS_SystemModelInput input)
{
	PS_SystemModelInput output = (PS_SystemModelInput)0;
	output.Pos = mul(float4(input.Pos, 1.0f), World);
	output.Pos = mul(output.Pos, ViewProj);

	return output;
}
float4 PSSystemModel(PS_SystemModelInput input) : SV_Target
{
	return PerObjColor;
}