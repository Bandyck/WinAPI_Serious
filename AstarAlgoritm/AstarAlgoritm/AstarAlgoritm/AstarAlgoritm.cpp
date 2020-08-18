#include "stdafx.h"
#include "AstarAlgoritm.h"
#include <stdio.h>
#include <iostream>
using namespace std; 

#define MAX_LOADSTRING 100
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_ASTARALGORITM, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance (hInstance, nCmdShow))
    {	return FALSE;    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ASTARALGORITM));
    MSG msg;

    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {   TranslateMessage(&msg);
            DispatchMessage(&msg);      }
    }
    return (int) msg.wParam;
}
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ASTARALGORITM));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_ASTARALGORITM);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    return RegisterClassExW(&wcex);
}
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 1200, 800, nullptr, nullptr, hInstance, nullptr);
   if (!hWnd)
   {      return FALSE;   }
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   return TRUE;
}
// >> : A* Algorithm Start
#define ROW 5
#define COL 6
typedef struct Grid
{
	int G;
	int H;
	int F;
}Grid;
static Grid Astar[ROW][COL];

#define GRIDSIZE 36
POINT checkboard[ROW][COL];
// >> : A* Algorithm End
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	
    switch (message)
    {
	case WM_CREATE:
		// 콘솔 출력
		AllocConsole();
		freopen("CONOUT$", "wt", stdout);
		// Grid 초기화
		int i, j;
		for (i = 0; i < ROW; i++)
		{
			for (j = 0; j < COL; j++)
			{
				Astar[i][j].G = 0;
				Astar[i][j].H = 0;
				Astar[i][j].F = Astar[i][j].G + Astar[i][j].H;
			}
		}
		for (i = 0; i < ROW; i++)
		{
			for (j = 0; j < COL; j++)
			{
				cout << Astar[i][j].G << ' ' << Astar[i][j].H << ' ' << Astar[i][j].F << "   ";
			}
			cout << endl;
		}
		cout << endl;
		for (i = 0; i <= ROW; i++)
		{
			for (j = 0; j <= COL; j++)
			{
				checkboard[i][j].x = 30 + GRIDSIZE * i;
				checkboard[i][j].y = 30 + GRIDSIZE * j;
			}
		}
		for (i = 0; i < ROW; i++)
		{
			for (j = 0; j < COL; j++)
			{
				cout << checkboard[i][j].x << ' ' << checkboard[i][j].y << "   ";
			}
			cout << endl;
		}
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
		FreeConsole();
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}