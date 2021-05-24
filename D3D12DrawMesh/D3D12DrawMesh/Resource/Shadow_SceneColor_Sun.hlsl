//*********************************************************
//
// Copyright (c) Microsoft. All rights reserved.
// This code is licensed under the MIT License (MIT).
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
//*********************************************************

Texture2D shadowMap : register(t0);
SamplerState sampleClamp : register(s0);


struct LightState
{
    float3 DirectionLightColor;
	float DirectionLightIntensity;
    float3 DirectionLightDir;
};

cbuffer SceneConstantBuffer : register(b0)
{
    float4x4 World;
    float4x4 CameraVP;
	float4x4 ShadowWorldToScreen;
    float4 CamEye;
	LightState Light;
	bool IsShadowPass;
};

float CalcUnshadowedAmountPCF2x2(float4 ScreenSpacePos, float bias)
{
    float2 TexCoord = ScreenSpacePos.xy;
    float ActualDepth = ScreenSpacePos.z - bias;

	uint width, height, numMips;
    shadowMap.GetDimensions(0, width, height, numMips);
    float2 ShadowMapDims = float2(width, height);

    float4 PixelCoordFrac = float4(1.0f, 1.0f, 1.0f, 1.0f);
    PixelCoordFrac.xy = frac(ShadowMapDims * TexCoord);
    PixelCoordFrac.zw = 1.0f - PixelCoordFrac.xy;
    float4 BilinearWeights = PixelCoordFrac.zxzx * PixelCoordFrac.wwyy;

    float2 TexelUnits = 1.0f / ShadowMapDims;
    float4 SampleDepths;
    SampleDepths.x = shadowMap.Sample(sampleClamp, TexCoord);
    SampleDepths.y = shadowMap.Sample(sampleClamp, TexCoord + float2(TexelUnits.x, 0.0f));
    SampleDepths.z = shadowMap.Sample(sampleClamp, TexCoord + float2(0.0f, TexelUnits.y));
    SampleDepths.w = shadowMap.Sample(sampleClamp, TexCoord + TexelUnits);

    float4 ShadowTests = (SampleDepths > ActualDepth) ? 1.0f : 0.0f;
    return dot(BilinearWeights, ShadowTests);
}

struct VSInput
{
    float3 position    : POSITION;
    float3 normal    : NORMAL;
    float2 uv0        : TEXCOORD0;
    float4 color    : COLOR;
};

struct PSInput
{
    float4 position : SV_POSITION;
    float4 worldpos : POSITION;
	float4 shadowPosH :POSITION1;
	float3 normal : NORMAL;
    float4 color : COLOR;
};

PSInput VSMain(VSInput input)
{
    PSInput result;

    result.position = mul(float4(input.position, 1.0f), World);
	result.worldpos = result.position;
    result.position = mul(result.worldpos, CameraVP);
    result.normal = normalize(mul(float4(input.normal, 0.0f), World).xyz);
	result.color = float4(200.f, 200.f, 200.f, 1.f);

	if(!IsShadowPass)
	{
		result.shadowPosH = mul(result.worldpos, ShadowWorldToScreen);
	}

    return result;
}

float4 PSMain(PSInput input) : SV_TARGET
{
	return float4(200.f, 200.f, 200.f, 1.f);
}