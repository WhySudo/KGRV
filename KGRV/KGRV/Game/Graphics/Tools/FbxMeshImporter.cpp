#include "FbxMeshImporter.h"

#include <DirectXMath.h>
#include <iostream>
#include <vector>

#include "../../ThirdParty/SimpleMath.h"
#include "assimp/Importer.hpp"
//#include "assimp/cimport.h"
#include "assimp/postprocess.h"
#include "assimp/scene.h"


static void ImportVertexesAndIndecesFromNode(std::vector<Vertex>* vertexTarget, std::vector<DirectX::XMFLOAT4>* pointsTarget, std::vector<int>* indeciesTarget, aiNode* currentNode, const aiScene* scene) {
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
			aiVector3D aiNormal = mesh->mNormals[i];

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
			//loadVertex
			Vertex vertex;
			vertex.position.x = aiVertex.x;
			vertex.position.y = aiVertex.y;
			vertex.position.z = aiVertex.z;
			vertex.position.w = 1;
			vertex.normal.x = aiNormal.x;
			vertex.normal.y = aiNormal.y;
			vertex.normal.z = aiNormal.z;
			vertex.normal.w = 0;
			if (mesh->mTextureCoords[0] != nullptr)
			{
				auto texCord = mesh->mTextureCoords[0][i];
				vertex.texturePos.x = (float)texCord.x;
				vertex.texturePos.y = (float)texCord.y;
			}
			vertexTarget->push_back(vertex);

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
		ImportVertexesAndIndecesFromNode(vertexTarget, pointsTarget, indeciesTarget, currentNode->mChildren[i], scene);
	}

}

Mesh* FbxMeshImporter::Import(std::string filepath, bool textured)
{
	Assimp::Importer importer;
	const aiScene* objectScene = importer.ReadFile(filepath, aiProcess_Triangulate | aiProcess_ConvertToLeftHanded);
	if (!objectScene)
	{
		std::cerr << "File wasnt't loaded: " << filepath << std::endl;
		return nullptr;
	}

	auto resultMesh = new Mesh();

	ImportVertexesAndIndecesFromNode(&resultMesh->vertex,&resultMesh->points, &resultMesh->indeces, objectScene->mRootNode, objectScene);

	resultMesh->indecesCount = resultMesh->indeces.size();
	resultMesh->pointCount = textured? resultMesh->vertex.size() :resultMesh->points.size();
	std::cout << filepath << " imported " << resultMesh->indecesCount << " " << resultMesh->vertex.size() << std::endl;
	resultMesh->InitalizeMesh(textured);
	return resultMesh;
}
