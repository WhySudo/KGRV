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
#include "Game/DefaultObjects/TexturedKatamariBall.h"
#include "Game/DefaultObjects/TexturedLightedKatamariBall.h"
#include "Game/DefaultObjects/DirectionLightObject.h"
#include "Game/Graphics/Shaders/TextureShader.h"
#include "Game/Assets/Texture.h"
#include <iostream>
int main()
{
	GameHandle game(L"MyBestGame", 800, 800);
	game.InitializeGame();
	Shader shader(L"./Shaders/MyVeryFirstShader.hlsl");
	TextureShader texShader = TextureShader();
	TextureLightedShader texLightedShader = TextureLightedShader();


	/*DirectX::XMFLOAT4 trianglePoints[6] = {
		DirectX::XMFLOAT4(0.8f, 0.9f, 0.5f, 1.0f),	DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
		DirectX::XMFLOAT4(0.9f, 0.9f, 0.5f, 1.0f),	DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
		DirectX::XMFLOAT4(0.8f, 0.8f, 0.5f, 1.0f),	DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
	};
	int triangleTriangles[] = { 0,1,2 };
	*/
	shader.Initalize(game.renderView->device.Get());
	texShader.Initalize(game.renderView->device.Get());
	Texture simpleTex;
	Texture simpleTex2;
	Texture colorTex;
	Texture colorTex2;
	colorTex.InitFromColor(game.renderView->device.Get(), { 1.0f, 1.0f, 1.0f, 1.0f });
	colorTex2.InitFromColor(game.renderView->device.Get(), { 0.5f, 1.0f, 0.0f, 1.0f });
	simpleTex.LoadFromFile(game.renderView->device.Get(), "./Textures/sampleTex.png");
	simpleTex2.LoadFromFile(game.renderView->device.Get(), "./Textures/maxwell.jpg");

	BaseCameraObject camera = BaseCameraObject(&game);
	DirectionLightObject lightSource = DirectionLightObject(&game);
	lightSource.transform->position = { 50.0f, 50.0f, 50.0f };
	lightSource.transform->LookAt({ 0.0f, 0.0f, 0.0f });
	
	//SimpleBallObject ball = SimpleBallObject(&game, &shader);


	//SimplePlayerPlatform left = SimplePlayerPlatform(&game, &shader, {-1, 0}, { 1, 0, 0, 1 }, { 0.2, 0.5, 1, 1}, Keys::Up, Keys::Down, {-0.74, 0.74});
	//SimplePlayerPlatform right = SimplePlayerPlatform(&game, &shader, { 1, 0 }, { -1, 0, 0, 1 }, { 0.2, 0.5, 1, 1 }, Keys::W, Keys::S, { -0.74, 0.74 });
	
	
	//SimpleWallObject wall3 = SimpleWallObject(&game, &shader, { 0, -1 }, { 0, 1.06, 0, 1 }, { 2, 0.2, 1, 1 });
	//SimpleWallObject wall4 = SimpleWallObject(&game, &shader, { 0, 1 }, { 0, -1.06, 0, 1 }, { 2, 0.2, 1, 1 });

	SimpleCubeObject CentralPlanet = SimpleCubeObject(&game, &shader);
	KatamariBall movingBall = KatamariBall(&game, &shader);

	SimpleKatamariObject testObj = SimpleKatamariObject(&game, &shader);
	TexturedKatamariObject testObj2 = TexturedKatamariObject(&game, &texShader, "./Models/horse.fbx", .5f, .01f, &simpleTex);
	TexturedKatamariObject maxwellHorse = TexturedKatamariObject(&game, &texShader, "./Models/horse.fbx", .5f, .01f, &simpleTex2);
	TexturedLightedKatamariObject lightColorHorse = TexturedLightedKatamariObject(&game, &texLightedShader, "./Models/maxwell.fbx", .5f, .0005f, &colorTex2);
	TexturedLightedKatamariObject lightHorse = TexturedLightedKatamariObject(&game, &texLightedShader, "", .5f, 1.0f, &colorTex);
	lightHorse.rendererComponent->phongMaterialData.ambient = 0.23125;
	lightHorse.rendererComponent->phongMaterialData.difuse = 0.2775;
	lightHorse.rendererComponent->phongMaterialData.specularAbsorption = 0.7739;
	lightHorse.rendererComponent->phongMaterialData.specularShininess = 90;

	lightColorHorse.rendererComponent->phongMaterialData.ambient = 0.3;
	lightColorHorse.rendererComponent->phongMaterialData.difuse = 0.8;
	lightColorHorse.rendererComponent->phongMaterialData.specularAbsorption = 0.9;
	lightColorHorse.rendererComponent->phongMaterialData.specularShininess = 28;



	TexturedKatamariObject maxwell = TexturedKatamariObject(&game, &texShader, "./Models/maxwell.fbx", .5f, .0005f, &simpleTex2);
	TexturedLightedKatamariObject lightMaxwell = TexturedLightedKatamariObject(&game, &texLightedShader, "./Models/maxwell.fbx", .5f, .0005f, &simpleTex2);
	TexturedKatamariObject maxwellSamle = TexturedKatamariObject(&game, &texShader, "./Models/maxwell.fbx", .5f, .0005f, &simpleTex);
	TexturedKatamariObject ballon = TexturedKatamariObject(&game, &texShader, "./Models/ballon.fbx", .5f, .1f, &simpleTex);
	TexturedKatamariObject maxwellBallon = TexturedKatamariObject(&game, &texShader, "./Models/ballon.fbx", .5f, .1f, &simpleTex2);
	SimpleKatamariObject testObj3 = SimpleKatamariObject(&game, &shader);
	TexturedKatamariObject testObj4 = TexturedKatamariObject(&game, &texShader, "", .5f, 1.0f, &simpleTex);



	lightMaxwell.rendererComponent->phongMaterialData.ambient = 0.3;
	lightMaxwell.rendererComponent->phongMaterialData.difuse = 0.8;
	lightMaxwell.rendererComponent->phongMaterialData.specularAbsorption = 0.9;
	lightMaxwell.rendererComponent->phongMaterialData.specularShininess = 28;

	CentralPlanet.transform->scale = { 20.0f, 1.0f, 20.0f };
	movingBall.transform->position = { 0.0f ,1.0f, 0.0f };


	camera.transform->position.y = 3;
	camera.transform->position.x = 0;
	camera.transform->position.z = -1;

	testObj.transform->position = { 10.0f, 1.5f, 3.0f };
	testObj2.transform->position = { -10.0f, 0.5f, -3.0f };
	testObj3.transform->position = { 5.0f, 1.0f, 10.0f };
	testObj4.transform->position = { 0.0f, 1.0f, 10.0f };
	maxwell.transform->position = { 3.0f, 1.0f, 3.0f };
	lightHorse.transform->position = { 0.0f, 1.0f, 3.0f };
	lightMaxwell.transform->position = { -3.0f, 1.0f, 3.0f };
	lightColorHorse.transform->position = { 0.0f, 1.0f, 6.0f };

	maxwellHorse.transform->position = { 10.0f, 1.0f, 10.0f };
	maxwellBallon.transform->position = { -10.0f, 1.0f, -10.0f };
	maxwellSamle.transform->position = { 10.0f, 1.0f, -10.0f };


	ballon.transform->position = { 5.0f, 1.0f, 5.0f };


	//RotateAroundComponent rotComponent((GameObject*)&cube2, (GameObject*) &CentralPlanet, { 1.0f, 0.0f, 0.0f }, { 0.0f, 3.0f, 0.0f }, 3.14159f);
	//cube2.gameComponents.push_back(&rotComponent);
	
	game.loadedScene->currentCamera = camera.GetCamera();
	game.loadedScene->directionLight = lightSource.lightComponent;
	XMFLOAT3 LookAt{ movingBall.transform->position.x, movingBall.transform->position.y, movingBall.transform->position.z };
	camera.GetCamera()->LookAt(LookAt);
	game.loadedScene->AddObject(&camera);
	game.loadedScene->AddObject(&lightSource);
	game.loadedScene->AddObject(&CentralPlanet);
	game.loadedScene->AddObject(&movingBall);
	game.loadedScene->AddObject(movingBall.view);
	//game.loadedScene->AddObject(movingBall.view1);
	//game.loadedScene->AddObject(movingBall.view2);
	//game.loadedScene->AddObject(movingBall.view3);
	//game.loadedScene->AddObject(movingBall.view4);
	//game.loadedScene->AddObject(movingBall.view5);
	//game.loadedScene->AddObject(movingBall.view6);
	game.loadedScene->AddObject(&testObj);
	game.loadedScene->AddObject(testObj.view);
	game.loadedScene->AddObject(&testObj2);
	game.loadedScene->AddObject(testObj2.view);
	game.loadedScene->AddObject(&testObj3);
	game.loadedScene->AddObject(testObj3.view);
	game.loadedScene->AddObject(&testObj4);
	game.loadedScene->AddObject(testObj4.view);
	game.loadedScene->AddObject(&maxwell);
	game.loadedScene->AddObject(&ballon);
	game.loadedScene->AddObject(maxwell.view);
	game.loadedScene->AddObject(ballon.view);


	game.loadedScene->AddObject(&maxwellHorse);
	game.loadedScene->AddObject(maxwellHorse.view);
	game.loadedScene->AddObject(&lightHorse);
	game.loadedScene->AddObject(lightHorse.view);
	game.loadedScene->AddObject(&lightColorHorse);
	game.loadedScene->AddObject(lightColorHorse.view);

	game.loadedScene->AddObject(&lightMaxwell);
	game.loadedScene->AddObject(lightMaxwell.view);

	game.loadedScene->AddObject(&maxwellBallon);
	game.loadedScene->AddObject(maxwellBallon.view);
	game.loadedScene->AddObject(&maxwellSamle);
	game.loadedScene->AddObject(maxwellSamle.view);
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