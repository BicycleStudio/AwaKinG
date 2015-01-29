cbuffer PerFrame : register(b0)	{ matrix ViewProj; };
cbuffer PerObj : register(b1)		{ matrix World; };
Texture2D texDiffuse : register(t0);
SamplerState samLinear : register(s0);
struct VS_IN
{
	float3 Pos		: POSITION;
	float2 Tex		: TEXCOORD0;
	float3 Normal	: Normal;
};
struct PS_IN
{
	float4 Pos		: SV_POSITION;
	float2 Tex		: TEXCOORD0;
	float3 Normal	: Normal;
};
struct VS_OUTPUT_PICK
{
	float4 Pos : SV_POSITION;
};
PS_IN VS(VS_IN input)
{
	PS_IN output = (PS_IN)0;
	output.Pos = mul(float4(input.Pos, 1.0f), World);
	output.Pos = mul(output.Pos, ViewProj);
	output.Tex = input.Tex;
	output.Normal = mul(input.Normal, (float3x3)World);

	return output;
}
float4 PS(PS_IN input) : SV_Target
{
	return texDiffuse.Sample(samLinear, input.Tex);
}
VS_OUTPUT_PICK VS_PICK(VS_IN input)
{
	VS_OUTPUT_PICK output = (VS_OUTPUT_PICK)0;
	output.Pos = mul(float4(input.Pos, 1.0f), World);
	output.Pos = mul(output.Pos, ViewProj);
	return output;
}
float4 PS_PICK(VS_OUTPUT_PICK input) : SV_Target
{
	return float4(1.0f,0.0f,0.0f,1.0f);//texDiffuse.Sample(samLinear, input.Tex);//Pick_Color;
}