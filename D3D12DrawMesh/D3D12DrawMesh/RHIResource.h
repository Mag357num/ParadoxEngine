#pragma once
#include "stdafx.h"
#include "Light.h"

namespace RHI
{
	enum class FFormat;

	struct FRHIResource
	{
		virtual ~FRHIResource() = default;
	};

	struct FRasterizer : public FRHIResource
	{
		virtual ~FRasterizer() = default;
	};

	struct FCBData : public FRHIResource
	{
		FCBData() : DataBuffer(nullptr), BufferSize(256) {};
		void* DataBuffer;
		uint32 BufferSize;
	};

	struct FCB : public FRHIResource
	{
		virtual ~FCB() = default;
	};

	struct FShader : public FRHIResource
	{
		virtual ~FShader() = default;
		std::wstring FileName;
	};

	struct FMesh : public FRHIResource
	{
		FMesh() = default;
		virtual ~FMesh() = default;

		uint32 IndexNum;
	};

	struct FMeshRes : public FRHIResource
	{
		virtual ~FMeshRes() = default;

		shared_ptr<FCB> BaseCB;
		shared_ptr<FCB> ShadowCB;
		shared_ptr<FRasterizer> BaseRas;
		shared_ptr<FRasterizer> ShadowRas;
		shared_ptr<FShader> VS;
		shared_ptr<FShader> PS;
	};

	struct FRACreater
	{
		virtual void InitPsoInitializer(/*FInputLayout InputLayout, FRHIShader Shader*/) = 0;
	};

	struct FHandle : public FRHIResource
	{
	};

	enum class FSRV_DIMENSION;
	enum class FDSV_DIMENSION;
	enum class FRESOURCE_DIMENSION;
	enum class FFormat;
	enum class FTEXTURE_LAYOUT;
	enum class FRESOURCE_FLAGS;

	struct FTextureInfo
	{
		FFormat Format = FFormat::DXGI_FORMAT_R32_FLOAT;
		FFormat ResFormat = FFormat::DXGI_FORMAT_R32_FLOAT;
		FSRV_DIMENSION SRV_ViewDimension = FSRV_DIMENSION::D3D12_SRV_DIMENSION_TEXTURE2D;
		FDSV_DIMENSION DSV_ViewDimension = FDSV_DIMENSION::D3D12_DSV_DIMENSION_TEXTURE2D;
		FRESOURCE_DIMENSION RES_ViewDimension = FRESOURCE_DIMENSION::D3D12_RESOURCE_DIMENSION_TEXTURE2D;
		uint32 Texture2D_MipLevel = 1;
		uint32 Texture2D_MipSlice = 0;
		//uint32 Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING; // TODO: bug
		uint32 Width;
		uint32 Height;
		uint64 alignment;
		uint32 depthOrArraySize;
		uint32 mipLevels;
		uint32 sampleCount;
		uint32 sampleQuality;
		FTEXTURE_LAYOUT layout = FTEXTURE_LAYOUT::D3D12_TEXTURE_LAYOUT_UNKNOWN;
		FRESOURCE_FLAGS flags = FRESOURCE_FLAGS::D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;
	};

	struct FTexture : public FRHIResource
	{
		virtual ~FTexture() = default;
		
		FTextureInfo Info;
	};

	class FTexture2D : public FTexture
	{
	};

	struct FBlinnPhongCB
	{
		FMatrix World;
		FMatrix ViewProj;
		FVector4 CamEye;
		FDirectionLight Light;
	};

	struct FShadowMapCB // BlinnPhong
	{
		FMatrix World;
		FMatrix CamViewProj;
		FMatrix ShadowTransForm;
		FVector4 CamEye;
		FDirectionLight Light;
		BOOL IsShadowMap; // TODO: BOOL is win dependent?
		float padding[3];
	};

	enum class FFormat
	{
		DXGI_FORMAT_UNKNOWN = 0,
		DXGI_FORMAT_R32G32B32A32_TYPELESS = 1,
		DXGI_FORMAT_R32G32B32A32_FLOAT = 2,
		DXGI_FORMAT_R32G32B32A32_UINT = 3,
		DXGI_FORMAT_R32G32B32A32_SINT = 4,
		DXGI_FORMAT_R32G32B32_TYPELESS = 5,
		DXGI_FORMAT_R32G32B32_FLOAT = 6,
		DXGI_FORMAT_R32G32B32_UINT = 7,
		DXGI_FORMAT_R32G32B32_SINT = 8,
		DXGI_FORMAT_R16G16B16A16_TYPELESS = 9,
		DXGI_FORMAT_R16G16B16A16_FLOAT = 10,
		DXGI_FORMAT_R16G16B16A16_UNORM = 11,
		DXGI_FORMAT_R16G16B16A16_UINT = 12,
		DXGI_FORMAT_R16G16B16A16_SNORM = 13,
		DXGI_FORMAT_R16G16B16A16_SINT = 14,
		DXGI_FORMAT_R32G32_TYPELESS = 15,
		DXGI_FORMAT_R32G32_FLOAT = 16,
		DXGI_FORMAT_R32G32_UINT = 17,
		DXGI_FORMAT_R32G32_SINT = 18,
		DXGI_FORMAT_R32G8X24_TYPELESS = 19,
		DXGI_FORMAT_D32_FLOAT_S8X24_UINT = 20,
		DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS = 21,
		DXGI_FORMAT_X32_TYPELESS_G8X24_UINT = 22,
		DXGI_FORMAT_R10G10B10A2_TYPELESS = 23,
		DXGI_FORMAT_R10G10B10A2_UNORM = 24,
		DXGI_FORMAT_R10G10B10A2_UINT = 25,
		DXGI_FORMAT_R11G11B10_FLOAT = 26,
		DXGI_FORMAT_R8G8B8A8_TYPELESS = 27,
		DXGI_FORMAT_R8G8B8A8_UNORM = 28,
		DXGI_FORMAT_R8G8B8A8_UNORM_SRGB = 29,
		DXGI_FORMAT_R8G8B8A8_UINT = 30,
		DXGI_FORMAT_R8G8B8A8_SNORM = 31,
		DXGI_FORMAT_R8G8B8A8_SINT = 32,
		DXGI_FORMAT_R16G16_TYPELESS = 33,
		DXGI_FORMAT_R16G16_FLOAT = 34,
		DXGI_FORMAT_R16G16_UNORM = 35,
		DXGI_FORMAT_R16G16_UINT = 36,
		DXGI_FORMAT_R16G16_SNORM = 37,
		DXGI_FORMAT_R16G16_SINT = 38,
		DXGI_FORMAT_R32_TYPELESS = 39,
		DXGI_FORMAT_D32_FLOAT = 40,
		DXGI_FORMAT_R32_FLOAT = 41,
		DXGI_FORMAT_R32_UINT = 42,
		DXGI_FORMAT_R32_SINT = 43,
		DXGI_FORMAT_R24G8_TYPELESS = 44,
		DXGI_FORMAT_D24_UNORM_S8_UINT = 45,
		DXGI_FORMAT_R24_UNORM_X8_TYPELESS = 46,
		DXGI_FORMAT_X24_TYPELESS_G8_UINT = 47,
		DXGI_FORMAT_R8G8_TYPELESS = 48,
		DXGI_FORMAT_R8G8_UNORM = 49,
		DXGI_FORMAT_R8G8_UINT = 50,
		DXGI_FORMAT_R8G8_SNORM = 51,
		DXGI_FORMAT_R8G8_SINT = 52,
		DXGI_FORMAT_R16_TYPELESS = 53,
		DXGI_FORMAT_R16_FLOAT = 54,
		DXGI_FORMAT_D16_UNORM = 55,
		DXGI_FORMAT_R16_UNORM = 56,
		DXGI_FORMAT_R16_UINT = 57,
		DXGI_FORMAT_R16_SNORM = 58,
		DXGI_FORMAT_R16_SINT = 59,
		DXGI_FORMAT_R8_TYPELESS = 60,
		DXGI_FORMAT_R8_UNORM = 61,
		DXGI_FORMAT_R8_UINT = 62,
		DXGI_FORMAT_R8_SNORM = 63,
		DXGI_FORMAT_R8_SINT = 64,
		DXGI_FORMAT_A8_UNORM = 65,
		DXGI_FORMAT_R1_UNORM = 66,
		DXGI_FORMAT_R9G9B9E5_SHAREDEXP = 67,
		DXGI_FORMAT_R8G8_B8G8_UNORM = 68,
		DXGI_FORMAT_G8R8_G8B8_UNORM = 69,
		DXGI_FORMAT_BC1_TYPELESS = 70,
		DXGI_FORMAT_BC1_UNORM = 71,
		DXGI_FORMAT_BC1_UNORM_SRGB = 72,
		DXGI_FORMAT_BC2_TYPELESS = 73,
		DXGI_FORMAT_BC2_UNORM = 74,
		DXGI_FORMAT_BC2_UNORM_SRGB = 75,
		DXGI_FORMAT_BC3_TYPELESS = 76,
		DXGI_FORMAT_BC3_UNORM = 77,
		DXGI_FORMAT_BC3_UNORM_SRGB = 78,
		DXGI_FORMAT_BC4_TYPELESS = 79,
		DXGI_FORMAT_BC4_UNORM = 80,
		DXGI_FORMAT_BC4_SNORM = 81,
		DXGI_FORMAT_BC5_TYPELESS = 82,
		DXGI_FORMAT_BC5_UNORM = 83,
		DXGI_FORMAT_BC5_SNORM = 84,
		DXGI_FORMAT_B5G6R5_UNORM = 85,
		DXGI_FORMAT_B5G5R5A1_UNORM = 86,
		DXGI_FORMAT_B8G8R8A8_UNORM = 87,
		DXGI_FORMAT_B8G8R8X8_UNORM = 88,
		DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM = 89,
		DXGI_FORMAT_B8G8R8A8_TYPELESS = 90,
		DXGI_FORMAT_B8G8R8A8_UNORM_SRGB = 91,
		DXGI_FORMAT_B8G8R8X8_TYPELESS = 92,
		DXGI_FORMAT_B8G8R8X8_UNORM_SRGB = 93,
		DXGI_FORMAT_BC6H_TYPELESS = 94,
		DXGI_FORMAT_BC6H_UF16 = 95,
		DXGI_FORMAT_BC6H_SF16 = 96,
		DXGI_FORMAT_BC7_TYPELESS = 97,
		DXGI_FORMAT_BC7_UNORM = 98,
		DXGI_FORMAT_BC7_UNORM_SRGB = 99,
		DXGI_FORMAT_AYUV = 100,
		DXGI_FORMAT_Y410 = 101,
		DXGI_FORMAT_Y416 = 102,
		DXGI_FORMAT_NV12 = 103,
		DXGI_FORMAT_P010 = 104,
		DXGI_FORMAT_P016 = 105,
		DXGI_FORMAT_420_OPAQUE = 106,
		DXGI_FORMAT_YUY2 = 107,
		DXGI_FORMAT_Y210 = 108,
		DXGI_FORMAT_Y216 = 109,
		DXGI_FORMAT_NV11 = 110,
		DXGI_FORMAT_AI44 = 111,
		DXGI_FORMAT_IA44 = 112,
		DXGI_FORMAT_P8 = 113,
		DXGI_FORMAT_A8P8 = 114,
		DXGI_FORMAT_B4G4R4A4_UNORM = 115,

		DXGI_FORMAT_P208 = 130,
		DXGI_FORMAT_V208 = 131,
		DXGI_FORMAT_V408 = 132,


		DXGI_FORMAT_SAMPLER_FEEDBACK_MIN_MIP_OPAQUE = 189,
		DXGI_FORMAT_SAMPLER_FEEDBACK_MIP_REGION_USED_OPAQUE = 190,


		DXGI_FORMAT_FORCE_UINT = 0xffffffff
	};

	enum class FSRV_DIMENSION
	{
		D3D12_SRV_DIMENSION_UNKNOWN = 0,
		D3D12_SRV_DIMENSION_BUFFER = 1,
		D3D12_SRV_DIMENSION_TEXTURE1D = 2,
		D3D12_SRV_DIMENSION_TEXTURE1DARRAY = 3,
		D3D12_SRV_DIMENSION_TEXTURE2D = 4,
		D3D12_SRV_DIMENSION_TEXTURE2DARRAY = 5,
		D3D12_SRV_DIMENSION_TEXTURE2DMS = 6,
		D3D12_SRV_DIMENSION_TEXTURE2DMSARRAY = 7,
		D3D12_SRV_DIMENSION_TEXTURE3D = 8,
		D3D12_SRV_DIMENSION_TEXTURECUBE = 9,
		D3D12_SRV_DIMENSION_TEXTURECUBEARRAY = 10,
		D3D12_SRV_DIMENSION_RAYTRACING_ACCELERATION_STRUCTURE = 11
	};

	enum class FRESOURCE_DIMENSION
	{
		D3D12_RESOURCE_DIMENSION_UNKNOWN = 0,
		D3D12_RESOURCE_DIMENSION_BUFFER = 1,
		D3D12_RESOURCE_DIMENSION_TEXTURE1D = 2,
		D3D12_RESOURCE_DIMENSION_TEXTURE2D = 3,
		D3D12_RESOURCE_DIMENSION_TEXTURE3D = 4
	};

	enum class FDSV_DIMENSION
	{
		D3D12_DSV_DIMENSION_UNKNOWN = 0,
		D3D12_DSV_DIMENSION_TEXTURE1D = 1,
		D3D12_DSV_DIMENSION_TEXTURE1DARRAY = 2,
		D3D12_DSV_DIMENSION_TEXTURE2D = 3,
		D3D12_DSV_DIMENSION_TEXTURE2DARRAY = 4,
		D3D12_DSV_DIMENSION_TEXTURE2DMS = 5,
		D3D12_DSV_DIMENSION_TEXTURE2DMSARRAY = 6
	};

	enum class FTEXTURE_LAYOUT
	{
		D3D12_TEXTURE_LAYOUT_UNKNOWN = 0,
		D3D12_TEXTURE_LAYOUT_ROW_MAJOR = 1,
		D3D12_TEXTURE_LAYOUT_64KB_UNDEFINED_SWIZZLE = 2,
		D3D12_TEXTURE_LAYOUT_64KB_STANDARD_SWIZZLE = 3
	};

	enum class FRESOURCE_FLAGS
	{
		D3D12_RESOURCE_FLAG_NONE = 0,
		D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET = 0x1,
		D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL = 0x2,
		D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS = 0x4,
		D3D12_RESOURCE_FLAG_DENY_SHADER_RESOURCE = 0x8,
		D3D12_RESOURCE_FLAG_ALLOW_CROSS_ADAPTER = 0x10,
		D3D12_RESOURCE_FLAG_ALLOW_SIMULTANEOUS_ACCESS = 0x20,
		D3D12_RESOURCE_FLAG_VIDEO_DECODE_REFERENCE_ONLY = 0x40
	};

	#define D3D12_SHADER_COMPONENT_MAPPING_MASK 0x7 
	#define D3D12_SHADER_COMPONENT_MAPPING_SHIFT 3 
	#define D3D12_SHADER_COMPONENT_MAPPING_ALWAYS_SET_BIT_AVOIDING_ZEROMEM_MISTAKES (1<<(D3D12_SHADER_COMPONENT_MAPPING_SHIFT*4)) 
	#define D3D12_ENCODE_SHADER_4_COMPONENT_MAPPING(Src0,Src1,Src2,Src3) ((((Src0)&D3D12_SHADER_COMPONENT_MAPPING_MASK)| \
													(((Src1)&D3D12_SHADER_COMPONENT_MAPPING_MASK)<<D3D12_SHADER_COMPONENT_MAPPING_SHIFT)| \
													(((Src2)&D3D12_SHADER_COMPONENT_MAPPING_MASK)<<(D3D12_SHADER_COMPONENT_MAPPING_SHIFT*2))| \
													(((Src3)&D3D12_SHADER_COMPONENT_MAPPING_MASK)<<(D3D12_SHADER_COMPONENT_MAPPING_SHIFT*3))| \
													D3D12_SHADER_COMPONENT_MAPPING_ALWAYS_SET_BIT_AVOIDING_ZEROMEM_MISTAKES))
	#define D3D12_DECODE_SHADER_4_COMPONENT_MAPPING(ComponentToExtract,Mapping) ((D3D12_SHADER_COMPONENT_MAPPING)(Mapping >> (D3D12_SHADER_COMPONENT_MAPPING_SHIFT*ComponentToExtract) & D3D12_SHADER_COMPONENT_MAPPING_MASK))
	#define D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING D3D12_ENCODE_SHADER_4_COMPONENT_MAPPING(0,1,2,3) 

}
