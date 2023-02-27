#pragma once
#include "GameWindowComponent.h"
#include <chrono>
using namespace std;
class DebugWindowText: public GameWindowComponent
{
public:
	DebugWindowText(GameWindow* targetWindow) : GameWindowComponent(targetWindow) {

	}

	HRESULT Initalize() override;
	void UpdateComponentView() override;
private:
	std::chrono::time_point<std::chrono::steady_clock> PrevTime;
	float totalTime = 0;
	unsigned int frameCount = 0;
};

