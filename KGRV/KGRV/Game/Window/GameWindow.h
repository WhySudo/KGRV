#pragma once
#include <Windows.h>
#include "../3rdParty/Input/InputDevice.h"
class GameWindow
{
//	friend class InputDevice;
public:
	GameWindow(LPCWSTR windowName, int width, int height);
	HWND windowInstance;
	int height;
	int width;
	InputDevice* inputDevice;
	MSG GetWindowUpdate(bool& exitRequired);
	~GameWindow();
private:
	HWND CreateGameWindow(LPCWSTR windowName);
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

