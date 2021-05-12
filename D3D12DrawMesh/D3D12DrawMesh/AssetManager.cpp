#include "AssetManager.h"

using RHI::FMesh;
using RHI::FMeshRes;
using RHI::GDynamicRHI;

FAssetManager* FAssetManager::GAssetManager = new FAssetManager;

FAssetManager* FAssetManager::Get()
{
	return GAssetManager;
}

shared_ptr<FScene> FAssetManager::LoadScene(const std::wstring& BinFileName)
{
	shared_ptr<FScene> TargetScene = make_shared<FScene>();

	std::ifstream Fin(BinFileName, std::ios::binary);

	if (!Fin.is_open())
	{
		throw std::exception("open file faild.");
	}

	uint32 ComponentNum;
	Fin.read((char*)&ComponentNum, sizeof(uint32));
	TargetScene->GetComponentArray().resize(ComponentNum);

	for (uint32 i = 0; i < ComponentNum; i++)
	{
		TargetScene->GetComponentArray()[i].SetMeshLODs(ReadMeshLODsFromIfstream(Fin));
		TargetScene->GetComponentArray()[i].SetTransform(ReadMeshTransformFromIfstream(Fin));

		// TODO: add a func to read shader file name, so different mesh can have different shader
		TargetScene->GetComponentArray()[i].SetShaderFileName(L"Shadow_SceneColor.hlsl");
	}

	// TODO: hard code
	TargetScene->GetComponentArray()[6].SetShaderFileName(L"Shadow_SceneColor_Sun.hlsl");

	Fin.close();

	return TargetScene;
}

vector<FStaticMeshLOD> FAssetManager::ReadMeshLODsFromIfstream(std::ifstream& Fin)
{
	FStaticMeshLOD MeshLOD;

	if (!Fin.is_open())
	{
		throw std::exception("open file faild.");
	}

	Fin.read((char*)&MeshLOD.GetVertexStride(), sizeof(int));

	uint32 BufferByteSize;
	uint32 BufferElementSize;
	Fin.read((char*)&BufferElementSize, sizeof(int));
	BufferByteSize = BufferElementSize * MeshLOD.GetVertexStride();

	float VerticeSize = static_cast<float>(BufferByteSize) / sizeof(float);
	assert(VerticeSize - floor(VerticeSize) == 0);
	MeshLOD.ResizeVertices(static_cast<int>(BufferByteSize / sizeof(float)));
	Fin.read((char*)MeshLOD.GetVertices().data(), BufferByteSize);

	Fin.read((char*)&BufferElementSize, sizeof(int));
	BufferByteSize = BufferElementSize * sizeof(int);

	MeshLOD.ResizeIndices(BufferElementSize);
	Fin.read((char*)MeshLOD.GetIndices().data(), BufferByteSize);

	vector<FStaticMeshLOD> MeshLODs;
	MeshLODs.push_back(MeshLOD); // TODO: default consider there is only one lod
	return MeshLODs;
}

FTransform FAssetManager::ReadMeshTransformFromIfstream(std::ifstream& Fin)
{
	FTransform Trans;
	if (!Fin.is_open())
	{
		throw std::exception("open file faild.");
	}

	Fin.read((char*)&Trans.Translation, 3 * sizeof(float));
	Fin.read((char*)&Trans.Quat, 4 * sizeof(float));
	Fin.read((char*)&Trans.Scale, 3 * sizeof(float));

	return Trans;
}

FStaticMeshComponent FAssetManager::CreateMeshComponent(uint16 VertexStride, vector<float> Vertices, vector<uint32> Indices, FTransform Transform)
{
	FStaticMeshComponent Component;
	vector<FStaticMeshLOD> Lods;
	Lods.push_back(FStaticMeshLOD(VertexStride, Vertices, Indices));
	FStaticMesh StaticMesh;
	StaticMesh.SetMeshLODs(Lods);
	Component.SetStaticMesh(StaticMesh);
	Component.SetTransform(Transform);
	return Component;
}
