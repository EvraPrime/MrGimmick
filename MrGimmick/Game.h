#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <string>

class Game
{
public:
	Game(HINSTANCE hInstance);
	virtual ~Game(void);

	//Main loop
	int Run();

	//Framework method
	virtual bool Init();
	virtual void Update(float dt) = 0;
	virtual void Render(float dt) = 0;
	static LRESULT CALLBACK MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

protected:
	//WIN32 Attributes
	HWND				m_hGameWnd;
	HINSTANCE			m_hGameInstance;
	UINT				m_ClientWidth;
	UINT				m_ClientHeight;
	const wchar_t*		m_GameTitle;
	DWORD				m_WndStyle;

protected:
	//Init window
	bool InitWindow();
};