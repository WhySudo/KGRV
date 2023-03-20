#pragma once
#include <string>
#include "../Mesh.h"
class FbxMeshImporter
{
public:
	static Mesh* Import(std::string filepath,  bool textured = false);
};

