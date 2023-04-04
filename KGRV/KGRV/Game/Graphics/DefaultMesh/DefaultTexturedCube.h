#pragma once

#include "../Mesh.h"
class DefaultTexturedCube : public Mesh {
public:

	DefaultTexturedCube() {

		/*vertex.push_back(Vertex({-0.5, -0.5, -0.5}, {0.0f, 0.0f})); //0
		vertex.push_back(Vertex({ 0.5, -0.5, -0.5 }, {0.0f, 0.0f})); //1
		vertex.push_back(Vertex({ 0.5, 0.5, -0.5}, {0.0f, 0.0f})); //2
		vertex.push_back(Vertex({ -0.5, 0.5, -0.5}, {0.0f, 0.0f})); //3

		vertex.push_back(Vertex({ -0.5, 0.5, 0.5 }, {0.0f, 0.0f})); //4
		vertex.push_back(Vertex({ 0.5, 0.5, 0.5 }, { 0.0f, 0.0f })); //5
		vertex.push_back(Vertex({ 0.5, -0.5, 0.5 }, {0.0f, 0.0f})); //6
		vertex.push_back(Vertex({-0.5, -0.5, 0.5 }, {0.0f, 0.0f})); //7
		*/
		//Face Front
		vertex.push_back(Vertex({ -0.5, -0.5, -0.5 }, { 0.0f, 1.0f }, {0.0f, 0.0f, -1.0f})); //0 //0
		vertex.push_back(Vertex({ 0.5, -0.5, -0.5 }, { 1.0f, 1.0f }, {0.0f, 0.0f, -1.0f })); //1 //1
		vertex.push_back(Vertex({ 0.5, 0.5, -0.5 }, { 1.0f, 0.0f }, {0.0f, 0.0f, -1.0f })); //2 //2
		vertex.push_back(Vertex({ -0.5, 0.5, -0.5 }, { 0.0f, 0.0f }, {0.0f, 0.0f, -1.0f })); //3 //3

		//Face Top
		vertex.push_back(Vertex({ 0.5, 0.5, -0.5 }, { 1.0f, 0.0f }, {0.0f, 1.0f, 0.0f})); //2 //4
		vertex.push_back(Vertex({ -0.5, 0.5, -0.5 }, { 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f })); //3 //5
		vertex.push_back(Vertex({ -0.5, 0.5, 0.5 }, { 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f })); //4 //6
		vertex.push_back(Vertex({ 0.5, 0.5, 0.5 }, { 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f })); //5 //7

		//Face Right
		vertex.push_back(Vertex({ 0.5, -0.5, -0.5 }, { 0.0f, 0.0f }, {1.0f, 0.0f, 0.0f})); //1 //8
		vertex.push_back(Vertex({ 0.5, 0.5, -0.5 }, { 1.0f, 0.0f }, { 1.0f, 0.0f, 0.0f })); //2 //9
		vertex.push_back(Vertex({ 0.5, 0.5, 0.5 }, { 1.0f, 1.0f }, { 1.0f, 0.0f, 0.0f })); //5 //10
		vertex.push_back(Vertex({ 0.5, -0.5, 0.5 }, { 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f })); //6 //11

		//Face Left
		vertex.push_back(Vertex({ -0.5, -0.5, -0.5 }, { 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f })); //0 //12
		vertex.push_back(Vertex({ -0.5, 0.5, -0.5 }, { 1.0f, 0.0f }, { -1.0f, 0.0f, 0.0f })); //3 //13
		vertex.push_back(Vertex({ -0.5, 0.5, 0.5 }, { 1.0f, 1.0f }, { -1.0f, 0.0f, 0.0f })); //4 //14
		vertex.push_back(Vertex({ -0.5, -0.5, 0.5 }, { 0.0f, 1.0f }, { -1.0f, 0.0f, 0.0f })); //7 //15

		//Face Back
		vertex.push_back(Vertex({ -0.5, 0.5, 0.5 }, { 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f })); //4 //16
		vertex.push_back(Vertex({ 0.5, 0.5, 0.5 }, { 1.0f, 1.0f }, { 0.0f, 0.0f, 1.0f })); //5 //17
		vertex.push_back(Vertex({ 0.5, -0.5, 0.5 }, { 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f })); //6 //18
		vertex.push_back(Vertex({ -0.5, -0.5, 0.5 }, { 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f })); //7 //19

		//Face Bottom
		vertex.push_back(Vertex({ -0.5, -0.5, -0.5 }, { 0.0f, 0.0f }, { 0.0f, -1.0f, 0.0f })); //0 //20
		vertex.push_back(Vertex({ 0.5, -0.5, -0.5 }, { 1.0f, 0.0f }, { 0.0f, -1.0f, 0.0f })); //1 //21
		vertex.push_back(Vertex({ 0.5, -0.5, 0.5 }, { 1.0f, 1.0f }, { 0.0f, -1.0f, 0.0f })); //6 //22
		vertex.push_back(Vertex({ -0.5, -0.5, 0.5 }, { 0.0f, 1.0f }, { 0.0f, -1.0f, 0.0f })); //7 //23

		pointCount = 24;
		indecesCount = 36;
		auto pushIndeces = new int[36] {
			/*0, 2, 1, //face front
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
			0, 1, 6,*/

			0, 2, 1, //face front
			0, 3, 2,
			4, 5, 6, //face top
			4, 6, 7,
			8, 9, 10, //face right
			8, 10, 11,
			12, 15, 14, //face left
			12, 14, 13,
			17, 16, 19, //face back
			17, 19, 18,
			20, 22, 23, //face bottom
			20, 21, 22,
		};
		for (size_t i = 0; i < indecesCount; i++)
		{
			indeces.push_back(pushIndeces[i]);
		}
		delete[] pushIndeces;
		InitalizeMesh(true);

	}
};