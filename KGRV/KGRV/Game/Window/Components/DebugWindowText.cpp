#include "DebugWindowText.h"


HRESULT DebugWindowText::Initalize()
{
	PrevTime = std::chrono::steady_clock::now();
	totalTime = 0;
	frameCount = 0;
	return S_OK;
}

void DebugWindowText::UpdateComponentView()
{
	auto	curTime = std::chrono::steady_clock::now();
	float	deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(curTime - PrevTime).count() / 1000000.0f;
	PrevTime = curTime;
	totalTime += deltaTime;
	frameCount++;

	if (totalTime > 1.0f) {
		float fps = frameCount / totalTime;

		totalTime -= 1.0f;

		WCHAR text[256];
		swprintf_s(text, TEXT("FPS: %f"), fps);
		SetWindowText(targetWindow->windowInstance, text);
		frameCount = 0;
	}
}
