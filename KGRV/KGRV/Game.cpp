#include "Game.h"
#include "Game/GameHandle.h"
#include "Game/Window/GameWindow.h"
#include "Game/Graphics/DefaultMesh/DefaultRectangle.h"
#include "Game/DefaultObjects/SimpleCubeObject.h"
#include "Game/DefaultObjects/SimpleWallObject.h"
#include "Game/DefaultObjects/SimplePlayerPlatform.h"
#include "Game/DefaultObjects/BaseCameraObject.h"
#include "Game/Components/RotateAroundComponent.h"
#include "Game/DefaultObjects/EmptyRotatingPoint.h"
#include "Game/DefaultObjects/KatamariBall.h"
#include "Game/DefaultObjects/SimpleKatamariObject.h"
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
	
	//SimpleBallObject ball = SimpleBallObject(&game, &shader);


	//SimplePlayerPlatform left = SimplePlayerPlatform(&game, &shader, {-1, 0}, { 1, 0, 0, 1 }, { 0.2, 0.5, 1, 1}, Keys::Up, Keys::Down, {-0.74, 0.74});
	//SimplePlayerPlatform right = SimplePlayerPlatform(&game, &shader, { 1, 0 }, { -1, 0, 0, 1 }, { 0.2, 0.5, 1, 1 }, Keys::W, Keys::S, { -0.74, 0.74 });
	
	
	//SimpleWallObject wall3 = SimpleWallObject(&game, &shader, { 0, -1 }, { 0, 1.06, 0, 1 }, { 2, 0.2, 1, 1 });
	//SimpleWallObject wall4 = SimpleWallObject(&game, &shader, { 0, 1 }, { 0, -1.06, 0, 1 }, { 2, 0.2, 1, 1 });

	SimpleCubeObject CentralPlanet = SimpleCubeObject(&game, &shader);
	KatamariBall movingBall = KatamariBall(&game, &shader);

	SimpleKatamariObject testObj = SimpleKatamariObject(&game, &shader);
	SimpleKatamariObject testObj2 = SimpleKatamariObject(&game, &shader);
	SimpleKatamariObject testObj3 = SimpleKatamariObject(&game, &shader);

	CentralPlanet.transform->scale = { 20.0f, 1.0f, 20.0f };
	movingBall.transform->position = { 0.0f ,1.0f, 0.0f };


	camera.transform->position.y = 3;
	camera.transform->position.x = 0;
	camera.transform->position.z = -1;

	testObj.transform->position = { 10.0f, 1.5f, 3.0f };
	testObj2.transform->position = { -10.0f, 0.5f, -3.0f };
	testObj3.transform->position = { 5.0f, 1.0f, 10.0f };


	//RotateAroundComponent rotComponent((GameObject*)&cube2, (GameObject*) &CentralPlanet, { 1.0f, 0.0f, 0.0f }, { 0.0f, 3.0f, 0.0f }, 3.14159f);
	//cube2.gameComponents.push_back(&rotComponent);
	
	game.loadedScene->currentCamera = camera.GetCamera();
	XMFLOAT3 LookAt{ movingBall.transform->position.x, movingBall.transform->position.y, movingBall.transform->position.z };
	camera.GetCamera()->LookAt(LookAt);
	game.loadedScene->AddObject(&camera);
	game.loadedScene->AddObject(&CentralPlanet);
	game.loadedScene->AddObject(&movingBall);
	game.loadedScene->AddObject(movingBall.view);
	game.loadedScene->AddObject(&testObj);
	game.loadedScene->AddObject(&testObj2);
	game.loadedScene->AddObject(&testObj3);
//	game.loadedScene->AddObject(&cube3);

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