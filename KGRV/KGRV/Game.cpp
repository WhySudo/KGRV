#include "Game.h"
#include "Game/GameHandle.h"
#include "Game/Window/GameWindow.h"
#include "Game/Graphics/DefaultMesh/DefaultRectangle.h"
#include "Game/DefaultObjects/SimpleCubeObject.h"
#include "Game/DefaultObjects/SimpleWallObject.h"
#include "Game/DefaultObjects/SimplePlayerPlatform.h"
#include "Game/DefaultObjects/BaseCameraObject.h"
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

	BaseCameraObject camera = BaseCameraObject(&game);
	camera.transform->position.y = 5;
	camera.transform->position.x = 5;
	camera.transform->position.z = 5;
	//SimpleBallObject ball = SimpleBallObject(&game, &shader);


	//SimplePlayerPlatform left = SimplePlayerPlatform(&game, &shader, {-1, 0}, { 1, 0, 0, 1 }, { 0.2, 0.5, 1, 1}, Keys::Up, Keys::Down, {-0.74, 0.74});
	//SimplePlayerPlatform right = SimplePlayerPlatform(&game, &shader, { 1, 0 }, { -1, 0, 0, 1 }, { 0.2, 0.5, 1, 1 }, Keys::W, Keys::S, { -0.74, 0.74 });
	
	
	//SimpleWallObject wall3 = SimpleWallObject(&game, &shader, { 0, -1 }, { 0, 1.06, 0, 1 }, { 2, 0.2, 1, 1 });
	//SimpleWallObject wall4 = SimpleWallObject(&game, &shader, { 0, 1 }, { 0, -1.06, 0, 1 }, { 2, 0.2, 1, 1 });

	SimpleCubeObject CentralPlanet = SimpleCubeObject(&game, &shader);
	SimpleCubeObject cube2 = SimpleCubeObject(&game, &shader);
	SimpleCubeObject cube3 = SimpleCubeObject(&game, &shader);
	SimpleCubeObject cube4 = SimpleCubeObject(&game, &shader);
	SimpleCubeObject cube5 = SimpleCubeObject(&game, &shader);
	SimpleCubeObject cube6 = SimpleCubeObject(&game, &shader);
	SimpleCubeObject cube7 = SimpleCubeObject(&game, &shader);
	SimpleCubeObject cube8 = SimpleCubeObject(&game, &shader);
	SimpleCubeObject cube9 = SimpleCubeObject(&game, &shader);


	CentralPlanet.transform->scale = { 2, 2, 2 };
	cube3.transform->position.x = 3;
	cube2.transform->position.y = 3;
	cube4.transform->position.z = 3;

	cube5.transform->position.x = 3;
	cube5.transform->position.y = 3;
	cube5.transform->position.z = 3;

	cube6.transform->position.x = -5;
	cube6.transform->position.y = 10;
	cube6.transform->position.z = 0;

	cube7.transform->position.x = -5;
	cube7.transform->position.y = -10;
	cube7.transform->position.z = -3;

	cube8.transform->position.x = 5;
	cube8.transform->position.y = 10;
	cube8.transform->position.z = -3;

	cube9.transform->position.x = 5;
	cube9.transform->position.y = -10;
	cube9.transform->position.z = 3;

	
	game.loadedScene->currentCamera = camera.GetCamera();
	XMFLOAT3 LookAt{ CentralPlanet.transform->position.x, CentralPlanet.transform->position.y, CentralPlanet.transform->position.z };
	camera.GetCamera()->LookAt(LookAt);
	game.loadedScene->AddObject(&camera);
	game.loadedScene->AddObject(&CentralPlanet);
	game.loadedScene->AddObject(&cube2);
	game.loadedScene->AddObject(&cube3);
	game.loadedScene->AddObject(&cube4);
	game.loadedScene->AddObject(&cube5);
	game.loadedScene->AddObject(&cube6);
	game.loadedScene->AddObject(&cube7);
	game.loadedScene->AddObject(&cube8);
	game.loadedScene->AddObject(&cube9);
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