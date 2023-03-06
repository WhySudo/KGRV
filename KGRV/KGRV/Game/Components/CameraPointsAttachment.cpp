#include "CameraPointsAttachment.h"

#include <iostream>
using namespace std;

void CameraPointsAttachment::Update(float deltaTime)
{
    if (gameObject->gameHandle->gameWindow->inputDevice->IsKeyDown(Keys::D1)) {
        currentPoint = targetPoints[0];
    }
    if (gameObject->gameHandle->gameWindow->inputDevice->IsKeyDown(Keys::D2)) {
        currentPoint = targetPoints[1];
    }
    if (gameObject->gameHandle->gameWindow->inputDevice->IsKeyDown(Keys::D3)) {
        currentPoint = targetPoints[2];
    }
    if (gameObject->gameHandle->gameWindow->inputDevice->IsKeyDown(Keys::D4)) {
        currentPoint = targetPoints[3];
    }
    if (gameObject->gameHandle->gameWindow->inputDevice->IsKeyDown(Keys::D5)) {
        currentPoint = targetPoints[4];
    }
    if (gameObject->gameHandle->gameWindow->inputDevice->IsKeyDown(Keys::D6)) {
        currentPoint = targetPoints[5];
    }
    if (gameObject->gameHandle->gameWindow->inputDevice->IsKeyDown(Keys::D0)) {
        currentPoint = nullptr;
    }
    UpdatePos();
}

void CameraPointsAttachment::UpdatePos() {
    if (currentPoint == nullptr) {
        return;
    }
    gameObject->transform->position = currentPoint->transform->position;
    gameObject->transform->LookAt({ currentPoint->transform->position.x, currentPoint->transform->position.y, currentPoint->transform->position.z });

}

bool CameraPointsAttachment::Initialization()
{
    return false;
}

void CameraPointsAttachment::Start()
{
    idx = 0;
    currentPoint = targetPoints[idx];
}

void CameraPointsAttachment::Stop()
{
    idx = 0;
    currentPoint = nullptr;
}

void CameraPointsAttachment::Next()
{
    idx = (idx + 1)%targetPoints.size();
    currentPoint = targetPoints[idx];
}

void CameraPointsAttachment::Prev()
{
    idx = (idx - 1) % targetPoints.size();
    currentPoint = targetPoints[idx];
}
