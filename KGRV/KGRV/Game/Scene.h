#pragma once
#include <vector>
#include "GameObject.h"
using namespace std;
class GameObject;
class Scene
{
public:
	vector<GameObject*> SceneObjects;
	void Initalize();
	void AddObject(GameObject* object);
	void Update(float deltaTime);
	void RemoveObject(GameObject* object);
};

