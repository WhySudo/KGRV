#include "GameObject.h"

void GameObject::Draw()
{
	for (auto component : gameComponents) {
		component->Draw();
	}
}
void GameObject::PhysicsUpdate(float timeDeltaTime) {
	for (auto component : gameComponents) {
		component->PhysicsUpdate(timeDeltaTime);
	}
}
void GameObject::Update(float timeDeltaTime)
{
	transform->UpdateValues();
	for (auto component : gameComponents) {
		component->Update(timeDeltaTime);
	}
	for (auto component : gameComponents) {
		component->LateUpdate(timeDeltaTime);
	}
}

void GameObject::Initialize()
{
	for (auto component : gameComponents) {
		component->Initialize();
	}
}
