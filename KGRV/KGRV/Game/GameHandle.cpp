#include "GameHandle.h"
GameHandle::GameHandle(LPCWSTR windowName, int width, int height) {
	gameWindow = new GameWindow(windowName, width, height);
	renderView = new RenderView(gameWindow);
	debugWindowText = new DebugWindowText(gameWindow);
}
void GameHandle::CleanUp() {

}
GameHandle::~GameHandle() {
	delete renderView;
	delete debugWindowText;
	delete gameWindow;
}
HRESULT GameHandle::InitializeGame() {
	renderView->Initalize();
	debugWindowText->Initalize();
	return S_OK;
}
void GameHandle::ProcessGameUpdates() {
	bool isExitRequested = false;
	MSG message = {};
	while (!isExitRequested) {
		message = gameWindow->GetWindowUpdate(isExitRequested);
		renderView->UpdateComponentView();
		debugWindowText->UpdateComponentView();
	}
}