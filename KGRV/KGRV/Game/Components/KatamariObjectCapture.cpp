#include "KatamariObjectCapture.h"
#include <iostream>
using namespace std;
void KatamariObjectCapture::SearchForObjectCapture()
{
	for (auto object : gameObject->gameHandle->loadedScene->SceneObjects) {
		for (auto component : object->gameComponents) {
			KatamariObject* katamariObj = dynamic_cast<KatamariObject*>(component);
			if (katamariObj != nullptr) {
				if (katamariObj->IsCaptured()) {
					break;
				}

				bool intersects = katamariObj->sphere->Intersects(*sphere);
				if (intersects) {
					CaptureObject(katamariObj);
				}


				break;
			}

		}
	}
}

void KatamariObjectCapture::CaptureObject(KatamariObject* obj)
{
	cout << "Captured Object" << endl; 
	obj->CaptureObject();
	capturedObjects.push_back(obj);
	auto storedPos = obj->gameObject->transform->GlobalPosition();
	obj->gameObject->transform->SetParent(targetView);
	auto newPos = obj->gameObject->transform->position;
	cout << "Capture global: " << storedPos.x << " " << storedPos.y << " " << storedPos.z << " " << " to local " << newPos.x << " " << newPos.y << " " << newPos.z << " " << endl;
	

}

void KatamariObjectCapture::Update(float deltaTime)
{
	SearchForObjectCapture();
}

bool KatamariObjectCapture::Initialization()
{
	return false;
}

void KatamariObjectCapture::PhysicsUpdate(float deltaTime)
{
	sphere->Center.x = gameObject->transform->position.x;
	sphere->Center.y = gameObject->transform->position.y;
	sphere->Center.z = gameObject->transform->position.z;
}
