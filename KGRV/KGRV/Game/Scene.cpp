#include "Scene.h"

void Scene::Initalize()
{
}

void Scene::AddObject(GameObject* object)
{
	SceneObjects.push_back(object);
	object->Initialize();
}

void Scene::Update(float deltaTime)
{
	for (auto gameObject : SceneObjects) {
		gameObject->Update(deltaTime);
	}
}

void Scene::RemoveObject(GameObject* object)
{
	//
}
