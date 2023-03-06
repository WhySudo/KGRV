#include "GameObject.h"

void GameObject::Draw()
{
	for (auto component : gameComponents) {
		component->Draw();
	}
}

void GameObject::Update(float timeDeltaTime)
{
	for (auto component : gameComponents) {
		component->Update(timeDeltaTime);
	}
}

void GameObject::Initialize()
{
	for (auto component : gameComponents) {
		component->Initialize();
	}
}
