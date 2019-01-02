//*****************************************************************************
// �n�[�t�����o�[�g [HalfLambert.hlsl]
//*****************************************************************************

//=============================================================================
// �萔�o�b�t�@
//=============================================================================
cbuffer ConstantBuffer : register( b0 )
{
	matrix World;
	matrix WorldViewProjection;
	float3 DirectionalLight;
}

//=============================================================================
// ���_�V�F�[�_�[
//=============================================================================
void VertexShaderPolygon( in  float4 inPosition : POSITION0,
						  in  float2 inTexCoord : TEXCOORD0,
						  in  float4 inColor : COLOR0,
						  in  float4 inNormal : NORMAL0,
						  out float4 outPosition : SV_POSITION,
						  out float2 outTexCoord : TEXCOORD0,
						  out float4 outColor : COLOR0)
{
	float3 normal;
	float color;

	outPosition = mul( inPosition, WorldViewProjection );
	outTexCoord = inTexCoord;

	normal = normalize(inNormal);

	color = saturate(dot(normal, -(float3)DirectionalLight)) *0.5f + 0.5f;
	outColor =  color * inColor;
	outColor.a = 1.0f;
}

Texture2D		g_Texture : register( t0 );
SamplerState	g_SamplerState : register( s0 );

//=============================================================================
// �s�N�Z���V�F�[�_�[
//=============================================================================
void PixelShaderPolygon( in  float4 inPosition : POSITION0,
						 in  float2 inTexCoord : TEXCOORD0,
						in float4 inColor : COLOR0,
						 out float4 outDiffuse : SV_Target )
{
	outDiffuse = inColor;
    //outDiffuse = g_Texture.Sample( g_SamplerState, inTexCoord );
}
