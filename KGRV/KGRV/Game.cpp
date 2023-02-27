#include "Game.h"
#include "Game/GameHandle.h"
#include "Game/Window/GameWindow.h"
#include "Game/Graphics/DefaultMesh/DefaultRectangle.h"
#include <iostream>
int main()
{
	GameHandle game(L"MyBestGame", 800, 800);
	game.InitializeGame();
	Shader shader(L"./Shaders/MyVeryFirstShader.hlsl");


	DirectX::XMFLOAT4 trianglePoints[6] = {
		DirectX::XMFLOAT4(0.8f, 0.9f, 0.5f, 1.0f),	DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
		DirectX::XMFLOAT4(0.9f, 0.9f, 0.5f, 1.0f),	DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
		DirectX::XMFLOAT4(0.8f, 0.8f, 0.5f, 1.0f),	DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
	};
	int triangleTriangles[] = { 0,1,2 };
	
	
	
	DefaultRectangle rectangleMesh = DefaultRectangle();
	Mesh triangleMesh(trianglePoints, 6, triangleTriangles, 3);
	
	RenderObject rectangle{reinterpret_cast<Mesh*>(&rectangleMesh), &shader};
	RenderObject triangle{&triangleMesh, &shader};


	game.renderView->AddRenderObject(&rectangle);
	game.renderView->AddRenderObject(&triangle);
	game.ProcessGameUpdates();
	std::cout << "Hello World!\n";
	game.CleanUp();
	return 0;
}