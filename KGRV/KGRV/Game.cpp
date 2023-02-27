#include "Game.h"
#include "Game/GameHandle.h"
#include "Rendering/Window/GameWindow.h"
#include <iostream>

int main()
{
	GameHandle game(L"MyBestGame", 800, 800);
	game.InitializeGame();
	Shader shader(L"./Shaders/MyVeryFirstShader.hlsl");

	DirectX::XMFLOAT4 rectanglePoints[8] = {
		DirectX::XMFLOAT4(0.1f, 0.1f, 0.5f, 1.0f),	DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),
		DirectX::XMFLOAT4(-0.1f, -0.1f, 0.5f, 1.0f),	DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f),
		DirectX::XMFLOAT4(0.1f, -0.1f, 0.5f, 1.0f),	DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f),
		DirectX::XMFLOAT4(-0.1f, 0.1f, 0.5f, 1.0f),	DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
	};
	int rectangleTriangles[] = { 0,1,2, 1,0,3 };


	DirectX::XMFLOAT4 trianglePoints[6] = {
		DirectX::XMFLOAT4(0.8f, 0.9f, 0.5f, 1.0f),	DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
		DirectX::XMFLOAT4(0.9f, 0.9f, 0.5f, 1.0f),	DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
		DirectX::XMFLOAT4(0.8f, 0.8f, 0.5f, 1.0f),	DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
	};
	int triangleTriangles[] = { 0,1,2 };
	
	
	Mesh rectangleMesh(rectanglePoints, 8, rectangleTriangles, 6);
	Mesh triangleMesh(trianglePoints, 6, triangleTriangles, 3);
	
	RenderObject rectangle{&rectangleMesh, &shader};
	RenderObject triangle{&triangleMesh, &shader};


	game.renderView->AddRenderObject(&rectangle);
	game.renderView->AddRenderObject(&triangle);
	game.ProcessGameUpdates();
	std::cout << "Hello World!\n";
	game.CleanUp();
	return 0;
}