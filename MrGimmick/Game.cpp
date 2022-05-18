#include "Game.h"

Game::Game(HINSTANCE hInstance)
{
	m_hGameInstance = hInstance;
	m_hGameWnd = NULL;
	m_ClientWidth = 800;
	m_ClientHeight = 600;
	m_GameTitle = L"Mr. Gimmick";
	m_WndStyle = WS_OVERLAPPEDWINDOW;
}

Game::~Game(void)
{
}

int Game::Run()
{
    //Main message loop
	MSG msg = { 0 };

    while (TRUE)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            if (msg.message == WM_QUIT)
                break;
        }

        Update(0.0f);
        Render(0.0f);
    }

	return msg.wParam;
}

bool Game::Init()
{
    if (!InitWindow())
        return false;

    return true;
}

bool Game::InitWindow()
{
    WNDCLASSEX wc;

    ZeroMemory(&wc, sizeof(WNDCLASSEX));

    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = (WNDPROC)MsgProc;
    wc.hInstance = m_hGameInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = L"GameWndClass";

    if (!RegisterClassEx(&wc))
    {
        OutputDebugString(L"FAILED TO CREATE WINDOW CLASS");
        return  false;
    }

    RECT wr = { 0, 0, m_ClientWidth, m_ClientHeight };
    AdjustWindowRect(&wr, m_WndStyle, FALSE);

    UINT width = wr.right - wr.left;
    UINT height = wr.bottom - wr.top;

    UINT x = GetSystemMetrics(SM_CXSCREEN) / 2 - width / 2;
    UINT y = GetSystemMetrics(SM_CYSCREEN) / 2 - height / 2;

    m_hGameWnd = CreateWindowEx(NULL,
        L"GameWndClass",
        m_GameTitle,
        WS_OVERLAPPEDWINDOW,
        x,
        y,
        width,
        height,
        NULL,
        NULL,
        m_hGameInstance,
        NULL);

    if (!m_hGameWnd)
    {
        OutputDebugString(L"FAILED TO CREATE WINDOW");
        return  false;
    }

    ShowWindow(m_hGameWnd, SW_SHOW);

    return true;
}

LRESULT CALLBACK Game::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}

