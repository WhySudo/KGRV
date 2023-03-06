#include "MovingPlatform.h"
#include <iostream>
using namespace std;
void MovingPlatform::Update(float deltaTime)
{
    float deltaMov = 0;
    if (gameObject->gameHandle->gameWindow->inputDevice->IsKeyDown(upKey))
        deltaMov += 1;    
    if (gameObject->gameHandle->gameWindow->inputDevice->IsKeyDown(downKey))
        deltaMov -= 1;
    float targetPos =     gameObject->transform->position.y + deltaMov * deltaTime;
    if (targetPos < movingBounds.x) {
        targetPos = movingBounds.x;
    }
    if (targetPos > movingBounds.y) {
        targetPos = movingBounds.y;
    }
    gameObject->transform->position.y = targetPos;
}

bool MovingPlatform::Initialization()
{
    return false;
}
