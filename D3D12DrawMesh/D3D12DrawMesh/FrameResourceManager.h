#pragma once
#include "RHIResource.h"
#include "FScene.h"
#include "stdafx.h"

using namespace RHI;

struct FFrameMesh
{
	shared_ptr<FMesh> Mesh;
	shared_ptr<FMeshRes> MeshRes;

	vector<FTexture> Textures;
};

class FFrameResource
{
private:
	const uint32 ShadowMapSize = 8192;
	shared_ptr<FMesh> PostProcessTriangle;
	shared_ptr<FMeshRes> PostProcessTriangleRes;
	vector<FFrameMesh> FrameMeshArray;

	shared_ptr<FTexture> NullTexture;
	shared_ptr<FTexture> ShadowMap;
	shared_ptr<FTexture> DepthStencilMap;
	shared_ptr<FSampler> ClampSampler;
	shared_ptr<FSampler> WarpSampler;
	shared_ptr<FTexture> SceneColorMap;
	shared_ptr<FTexture> BloomSetupMap;
	shared_ptr<FTexture> SunMergeMap;
	vector<shared_ptr<FTexture>> BloomDownMapArray;
	vector<shared_ptr<FTexture>> BloomUpMapArray;

public:
	const uint32& GetShadowMapSize() const { return ShadowMapSize; }
	void SetPostProcessTriangle(shared_ptr<FMesh>& Mesh) { PostProcessTriangle = Mesh; }
	void SetPostProcessTriangleRes(shared_ptr<FMeshRes>& MeshRes) { PostProcessTriangleRes = MeshRes; }
	const shared_ptr<FMesh>& GetPostProcessTriangle() const { return PostProcessTriangle; }
	const shared_ptr<FMeshRes>& GetPostProcessTriangleRes() const { return PostProcessTriangleRes; }
	vector<FFrameMesh>& GetFrameMeshArray() { return FrameMeshArray; }

	void SetNullTexture(const shared_ptr<FTexture>& Tex) { NullTexture = Tex; }
	void SetShadowMap(const shared_ptr<FTexture>& Tex) { ShadowMap = Tex; }
	void SetDsMap(const shared_ptr<FTexture>& Tex) { DepthStencilMap = Tex; }
	void SetSceneColorMap(const shared_ptr<FTexture>& Tex) { SceneColorMap = Tex; }
	void SetClampSampler(const shared_ptr<FSampler>& Sam) { ClampSampler = Sam; }
	void SetWarpSampler(const shared_ptr<FSampler>& Sam) { WarpSampler = Sam; }
	const shared_ptr<FTexture>& GetNullTexture() const { return NullTexture; }
	const shared_ptr<FTexture>& GetShadowMap() const { return ShadowMap; }
	const shared_ptr<FTexture>& GetDsMap() const { return DepthStencilMap; }
	const shared_ptr<FTexture>& GetSceneColorMap() const { return SceneColorMap; }
	const shared_ptr<FSampler>& GetClampSampler() const { return ClampSampler; }
	const shared_ptr<FSampler>& GetWarpSampler() const { return WarpSampler; }

	void SetBloomSetupMap(const shared_ptr<FTexture>& Tex) { BloomSetupMap = Tex; }
	void SetSunMergeMap(const shared_ptr<FTexture>& Tex) { SunMergeMap = Tex; }
	const shared_ptr<FTexture>& GetBloomSetupMap() const { return BloomSetupMap; }
	const shared_ptr<FTexture>& GetSunMergeMap() const { return SunMergeMap; }

	vector<shared_ptr<FTexture>>& GetBloomDownMapArray() { return BloomDownMapArray; }
	vector<shared_ptr<FTexture>>& GetBloomUpMapArray() { return BloomUpMapArray; }
};

class FFrameResourceManager
{
private:
	vector<FFrameResource> FrameResArray; // every frame own a FFrameResource
public:
	vector<FFrameResource>& GetFrameRes() { return FrameResArray; }
	void InitFrameResource(const uint32& FrameCount);
	void CreateFrameResourcesFromScene(const shared_ptr<FScene> Scene, const uint32& FrameCount);
	void UpdateFrameResources(FScene* Scene, const uint32& FrameIndex);
	FFrameMesh CreateFrameMesh(const FMeshActor& MeshActor);
	void CreateMapsForShadow(FFrameResource& FrameRes);
	void CreateSamplers(FFrameResource& FrameRes);
	void CreateMapsForScene(FFrameResource& FrameRes);
	void CreateMapsForPostProcess(FFrameResource& FrameRes);
	void CreatePostProcessTriangle(FFrameResource& FrameRes);
	void CreatePostProcessMaterials(FFrameResource& FrameRes);
	void CreatePostProcessPipelines(FFrameResource& FrameRes);


};