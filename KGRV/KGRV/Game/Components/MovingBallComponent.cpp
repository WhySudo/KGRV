#include "MovingBallComponent.h"
#include "WallComponent.h"
#include "RoundWall.h"
void MovingBallComponent::Update(float deltaTime)
{
    direction.Normalize();
    for (auto object : gameObject->gameHandle->loadedScene->SceneObjects) {
        for (auto component : object->gameComponents) {
            WallComponent* wall = dynamic_cast<WallComponent*>(component);
            //RoundWallComponent* roundWall = dynamic_cast<RoundWallComponent*>(component);
            //if (roundWall != nullptr) {

            //}
             if (wall != nullptr) {
                float dist;
                DirectX::XMVECTOR pos = { gameObject->transform->position.x, gameObject->transform->position.y, gameObject->transform->position.z, 1 };
                DirectX::XMVECTOR dir = { direction.x,direction.y, 0, 1 };
                bool intersects = wall->boundingBox->Intersects(pos, dir, dist);
                if (intersects && dist < gameObject->transform->scale.x/4){

                    if (wall->boundingBox != nullptr) {

                    }
                    
                    auto newPos = gameObject->transform->position + direction * (dist);
                    auto newDirect = wall->CalculateReflection(newPos, direction);
                    gameObject->transform->position = newPos;
                    direction = newDirect;
                    direction.Normalize();
                    speed *= 1.05;
                    break;
                }
            }
        }
    }


    gameObject->transform->position.x += (direction.x * deltaTime * speed);
    gameObject->transform->position.y += (direction.y * deltaTime * speed);
}

bool MovingBallComponent::Initialization()
{
    return false;
}
