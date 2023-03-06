#include "Game.h"
#include "Game/GameHandle.h"
#include "Game/Window/GameWindow.h"
#include "Game/Graphics/DefaultMesh/DefaultRectangle.h"
#include "Game/DefaultObjects/SimpleBallObject.h"
#include "Game/DefaultObjects/SimpleWallObject.h"
#include "Game/DefaultObjects/SimplePlayerPlatform.h"
#include <iostream>
int main()
{
	GameHandle game(L"MyBestGame", 800, 800);
	game.InitializeGame();
	Shader shader(L"./Shaders/MyVeryFirstShader.hlsl");


	/*DirectX::XMFLOAT4 trianglePoints[6] = {
		DirectX::XMFLOAT4(0.8f, 0.9f, 0.5f, 1.0f),	DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
		DirectX::XMFLOAT4(0.9f, 0.9f, 0.5f, 1.0f),	DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
		DirectX::XMFLOAT4(0.8f, 0.8f, 0.5f, 1.0f),	DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
	};
	int triangleTriangles[] = { 0,1,2 };
	*/
	shader.Initalize(game.renderView->device.Get());
	SimpleBallObject ball = SimpleBallObject(&game, &shader);


	SimplePlayerPlatform left = SimplePlayerPlatform(&game, &shader, {-1, 0}, { 1, 0, 0, 1 }, { 0.2, 0.5, 1, 1}, Keys::Up, Keys::Down, {-0.74, 0.74});
	SimplePlayerPlatform right = SimplePlayerPlatform(&game, &shader, { 1, 0 }, { -1, 0, 0, 1 }, { 0.2, 0.5, 1, 1 }, Keys::W, Keys::S, { -0.74, 0.74 });
	
	
	SimpleWallObject wall3 = SimpleWallObject(&game, &shader, { 0, -1 }, { 0, 1.06, 0, 1 }, { 2, 0.2, 1, 1 });
	SimpleWallObject wall4 = SimpleWallObject(&game, &shader, { 0, 1 }, { 0, -1.06, 0, 1 }, { 2, 0.2, 1, 1 });


	

	game.loadedScene->AddObject(&left);
	game.loadedScene->AddObject(&right);
	game.loadedScene->AddObject(&wall3);
	game.loadedScene->AddObject(&wall4);

	game.loadedScene->AddObject(&ball);
	//	DefaultRectangle rectangleMesh = DefaultRectangle();
	//Mesh triangleMesh(trianglePoints, 6, triangleTriangles, 3);
	
//	RenderObject rectangle{reinterpret_cast<Mesh*>(&rectangleMesh), &shader};
	//RenderObject triangle{&triangleMesh, &shader};


//	game.renderView->AddRenderObject(&rectangle);
	//game.renderView->AddRenderObject(&triangle);
	game.ProcessGameUpdates();
	std::cout << "Hello World!\n";
	game.CleanUp();
	return 0;
}