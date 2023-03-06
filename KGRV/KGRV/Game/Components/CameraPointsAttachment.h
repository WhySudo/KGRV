#pragma once
#include "ObjectComponent.h"
#include <vector>
#include "../DefaultObjects/EmptyRotatingPoint.h"
class CameraPointsAttachment: public ObjectComponent
{
public:
	CameraPointsAttachment(GameObject* obj) : ObjectComponent(obj) {
		targetPoints = std::vector<EmptyRotatingPoint*>();
	}	// Унаследовано через ObjectComponent
	virtual void Update(float deltaTime) override;
	virtual bool Initialization() override;

	std::vector<EmptyRotatingPoint*> targetPoints;

private:
	EmptyRotatingPoint* currentPoint = nullptr;
	int idx = 0;
	bool nextPressed = false;
	bool prevPressed = false;
	bool stopPressed = false;
	void Start();
	void Stop();
	void Next();
	void Prev();
	void UpdatePos();
};

