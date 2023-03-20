#pragma once

#include "../Mesh.h"
class DefaultTexturedCube : public Mesh {
public:

	DefaultTexturedCube() {

		vertex.push_back(Vertex({-0.5, -0.5, -0.5}, {0.0f, 0.0f}));
		vertex.push_back(Vertex({ 0.5, -0.5, -0.5 }, {0.0f, 0.0f}));
		vertex.push_back(Vertex({ 0.5, 0.5, -0.5}, {0.0f, 0.0f}));
		vertex.push_back(Vertex({ -0.5, 0.5, -0.5}, {0.0f, 0.0f}));

		vertex.push_back(Vertex({ -0.5, 0.5, 0.5 }, {0.0f, 0.0f}));
		vertex.push_back(Vertex({ 0.5, 0.5, 0.5 }, { 0.0f, 0.0f }));
		vertex.push_back(Vertex({ 0.5, -0.5, 0.5 }, {0.0f, 0.0f}));
		vertex.push_back(Vertex({-0.5, -0.5, 0.5 }, {0.0f, 0.0f}));

		vertex.push_back(Vertex({ 0.5, 0.5, -0.5 }, { 1.0f, 0.0f })); // 2 - 8
		vertex.push_back(Vertex({ -0.5, 0.5, -0.5 }, { 0.0f, 0.0f })); // 3 - 9
		vertex.push_back(Vertex({ -0.5, 0.5, 0.5 }, { 0.0f, 1.0f })); // 4 - 10
		vertex.push_back(Vertex({ 0.5, 0.5, 0.5 }, { 1.0f, 1.0f })); // 5 - 11

		pointCount = 12;
		indecesCount = 42;
		auto pushIndeces = new int[42] {
			0, 2, 1, //face front
				0, 3, 2,
				2, 3, 4, //face top
				2, 4, 5,
				1, 2, 5, //face right
				1, 5, 6,
				0, 7, 4, //face left
				0, 4, 3,
				5, 4, 7, //face back
				5, 7, 6,
				0, 6, 7, //face bottom
				0, 1, 6,

				8, 9, 10, //face top
				8, 10, 11,
		};
		for (size_t i = 0; i < indecesCount; i++)
		{
			indeces.push_back(pushIndeces[i]);
		}
		delete[] pushIndeces;
		InitalizeMesh(true);

	}
};