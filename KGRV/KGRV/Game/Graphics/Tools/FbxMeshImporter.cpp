#include "FbxMeshImporter.h"

#include <DirectXMath.h>
#include <iostream>
#include <vector>

#include "../../3rdParty/SimpleMath.h"
#include "assimp/Importer.hpp"
//#include "assimp/cimport.h"
#include "assimp/postprocess.h"
#include "assimp/scene.h"


static void ImportVertexesAndIndecesFromNode(std::vector<DirectX::XMFLOAT4>* pointsTarget, std::vector<int>* indeciesTarget, aiNode* currentNode, const aiScene* scene) {
	for (size_t i = 0; i < currentNode->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[currentNode->mMeshes[i]];
		DirectX::XMFLOAT4 color = { 1.0f, 0.0f, 1.0f, 1.0f };
		//Get vertices
		for (size_t i = 0; i < mesh->mNumVertices; i++)
		{

			auto cureNode = currentNode;
			auto parent = currentNode->mParent;
			aiVector3D aiVertex = mesh->mVertices[i];

			while (parent != nullptr)
			{
				aiVertex = cureNode->mTransformation * aiVertex;
				cureNode = parent;
				parent = parent->mParent;
			}

			pointsTarget->push_back({
				aiVertex.x,
				aiVertex.y,
				aiVertex.z,
				1,
				});

			//color
			pointsTarget->push_back(color);

		}

		//Get indices
		for (size_t i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];

			for (size_t j = 0; j < face.mNumIndices; j++)
				indeciesTarget->push_back(face.mIndices[j]);
		}

	}
	for (size_t i = 0; i < currentNode->mNumChildren; i++)
	{
		ImportVertexesAndIndecesFromNode(pointsTarget, indeciesTarget, currentNode->mChildren[i], scene);
	}

}

Mesh* FbxMeshImporter::Import(std::string filepath)
{
	Assimp::Importer importer;
	const aiScene* objectScene = importer.ReadFile(filepath, aiProcess_Triangulate | aiProcess_ConvertToLeftHanded);
	if (!objectScene)
	{
		std::cerr << "File wasnt't loaded: " << filepath << std::endl;
		return nullptr;
	}

	auto resultMesh = new Mesh();

	std::vector<DirectX::XMFLOAT4> points;
	std::vector<int> indecies;
	ImportVertexesAndIndecesFromNode(&points, &indecies, objectScene->mRootNode, objectScene);

	resultMesh->indecesCount = indecies.size();
	resultMesh->pointCount = points.size();
	resultMesh->points = new DirectX::XMFLOAT4[points.size()]();
	resultMesh->indeces = new int[indecies.size()]();
	std::copy(indecies.begin(), indecies.end(), resultMesh->indeces);
	std::copy(points.begin(), points.end(), resultMesh->points);
	std::cout << filepath << " imported " << resultMesh->indecesCount << " " << resultMesh->pointCount << std::endl;
	resultMesh->InitalizeMesh();
	return resultMesh;
}
