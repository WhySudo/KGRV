#include "GameHandle.h"
#include <chrono>
GameHandle::GameHandle(LPCWSTR windowName, int width, int height) {

	gameWindow = new GameWindow(windowName, width, height);
	renderView = new RenderView(gameWindow, this);
	inputDevice = new InputDevice(&gameWindow->windowInstance);
	gameWindow->inputDevice = inputDevice;
	debugWindowText = new DebugWindowText(gameWindow);
	loadedScene = new Scene();
}
void GameHandle::CleanUp() {

}
GameHandle::~GameHandle() {
	delete loadedScene;
	delete renderView;
	delete debugWindowText;
	delete gameWindow;
	delete inputDevice;
}
HRESULT GameHandle::InitializeGame() {
	renderView->Initalize();
	debugWindowText->Initalize();
	loadedScene->Initalize();
	return S_OK;
}
void GameHandle::ProcessGameUpdates() {
	bool isExitRequested = false;
	MSG message = {};
	auto curTime = std::chrono::steady_clock::now();
	auto prevUpdateTime = std::chrono::steady_clock::now();

	while (!isExitRequested) {
		curTime = std::chrono::steady_clock::now();
		float deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(curTime - prevUpdateTime).count() / 1000000.0f;
		prevUpdateTime = curTime;
		loadedScene->Update(deltaTime);
		message = gameWindow->GetWindowUpdate(isExitRequested);
		renderView->UpdateComponentView();
		debugWindowText->UpdateComponentView();
	}
}