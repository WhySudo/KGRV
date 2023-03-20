#include "KatamariObject.h"

void KatamariObject::Update(float deltaTime)
{
}

void KatamariObject::PhysicsUpdate(float deltaTime)
{
	sphere->Center.x = gameObject->transform->position.x;
	sphere->Center.y = gameObject->transform->position.y;
	sphere->Center.z = gameObject->transform->position.z;

//	sphere->Radius = 1 * gameObject->transform->scale.x;

}

bool KatamariObject::Initialization()
{
	return false;
}
