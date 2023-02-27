#pragma once
#include <Windows.h>
class GameWindow
{
public:
	GameWindow(LPCWSTR windowName, int width, int height);
	HWND windowInstance;
	int height;
	int width;
	MSG GetWindowUpdate(bool& exitRequired);
	
	~GameWindow();
private:
	HWND CreateGameWindow(LPCWSTR windowName);

};

