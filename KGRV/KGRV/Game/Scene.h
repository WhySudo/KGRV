#pragma once
#include <vector>
#include "GameObject.h"
//#include "Components/CameraComponent.h"
using namespace std;
class GameObject;
class CameraComponent;
class Scene
{
public:
	vector<GameObject*> SceneObjects;
	CameraComponent* currentCamera;
	void Initalize();
	void AddObject(GameObject* object);
	void Update(float deltaTime);
	void RemoveObject(GameObject* object);
};

