
#include "framework.h"
#include "NumManip.h"
#include <string>
#include <iostream>   


#define MAX_LOADSTRING 100
#define ID_BTNCONVERT 54

// Zmienne globalne:
HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];

struct Render_state
{
	int height, width;
	void* memory;
	BITMAPINFO bitmapinfo;
};

const int WINHEIGHT = 1000;
const int WINWIDTH = 1000;
const int WINFOOT = 250;

std::string answer;

char textBase[8];
char textBase2[8];
char textSaved[20];


Render_state render_state;
#include "renderer.cpp"

ATOM                MyRegisterClass(HINSTANCE hInstance);
HWND                InitInstance(HINSTANCE, int, int, int, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


class Vector2
{
public:
	float x;
	float y;

};

class Vector2Int
{

private:
	int x;
	int y;
public:
	int getX() { return x; }
	int getY() { return y; }
	void SetX(int x1) { x = x1; }
	void SetY(int y1) { y = y1; }
};


HWND TextBox1;
HWND TextBox2;
HWND TextBox3;


Vector2Int TextBox1Pos;
Vector2Int TextBox2Pos;
Vector2Int TextBox3Pos;

HWND Button;

Vector2Int ButtonPos;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	TextBox1Pos.SetX(400);
	TextBox1Pos.SetY(800);

	TextBox2Pos.SetX(400);
	TextBox2Pos.SetY(600);

	TextBox3Pos.SetX(400);
	TextBox3Pos.SetY(500);

	ButtonPos.SetX(800);
	ButtonPos.SetY(700);

	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_NUMMANIP, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	u32 WINWIDTH, WINHEIGHT, WINFOOT;

	WINWIDTH = 1000;
	WINHEIGHT = 1000;
	WINFOOT = 250;

	HWND window = InitInstance(hInstance, nCmdShow, WINWIDTH, WINHEIGHT, WINFOOT);


	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_NUMMANIP));

	MSG msg;

	HDC hdc = GetDC(window);

	//Main Loop
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//INPUT


		//SIMULATE
		Color(30, 40, 100);

		DrawPixelText("NUMBER :", 20, 800, 5, 50, 200, 50, 6.f);
		DrawPixelText("FROM BASE :", 20, 600, 5, 50, 200, 50, 6.f);
		DrawPixelText("TO BASE :", 20, 500, 5, 50, 200, 50, 6.f);
		DrawPixelText("CONVERT", 750, 800, 5, 200, 150, 100, 6.f);
		DrawPixelText("RESULT", WINWIDTH * 0.35f, 250, 5, 200, 150, 100, 6.f);
		DrawPixelText(answer.c_str(), 50, 200, 5, 200, 250, 200, 6.f);
		//RENDER


		StretchDIBits(hdc, 0, 0, render_state.width, render_state.height, 0, 0, render_state.width, render_state.height, render_state.memory,
			&render_state.bitmapinfo,
			DIB_RGB_COLORS,
			SRCCOPY);
	}



	return (int)msg.wParam;
}


//
//  FUNKCJA: MyRegisterClass()
//
//  PRZEZNACZENIE: Rejestruje klasę okna.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_NUMMANIP));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 3);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_NUMMANIP);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   FUNKCJA: InitInstance(HINSTANCE, int)
//
//   PRZEZNACZENIE: Zapisuje dojście wystąpienia i tworzy okno główne
//
//   KOMENTARZE:
//
//        W tej funkcji dojście wystąpienia jest zapisywane w zmiennej globalnej i
//        jest tworzone i wyświetlane okno główne programu.
//
HWND InitInstance(HINSTANCE hInstance, int nCmdShow, int w, int h, int f)
{
	hInst = hInstance; // Przechowuj dojście wystąpienia w naszej zmiennej globalnej


	__int32 WINWIDTH, WINHEIGHT, WINFOOT;

	WINWIDTH = w;
	WINHEIGHT = h;
	WINFOOT = f;

	RECT rect;


	rect.left = WINFOOT;
	rect.top = WINFOOT;
	rect.bottom = rect.top + WINHEIGHT;
	rect.right = rect.left + WINWIDTH;


	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_CLIPCHILDREN,
		rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

//
//  FUNKCJA: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PRZEZNACZENIE: Przetwarza komunikaty dla okna głównego.
//
//  WM_COMMAND  - przetwarzaj menu aplikacji
//  WM_PAINT    - Maluj okno główne
//  WM_DESTROY  - opublikuj komunikat o wyjściu i wróć
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	char* number = &textSaved[0];
	char* base1 = &textBase[0];
	char* base2 = &textBase2[0];
	std::string strang;
	std::string base1str;
	int base1Int = 0;
	std::string base2str;
	int base2Int = 0;

	int gwStat;
	int i=0;
	int nu;
	switch (message)
	{
	case WM_CREATE:
	{

		HFONT hFont = CreateFont(36, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET,
			OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
			DEFAULT_PITCH | FF_DONTCARE, TEXT("Tahoma"));

		int fieldHeight = 50;

		TextBox1 = CreateWindowW(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER,
			TextBox1Pos.getX(), (WINHEIGHT - TextBox1Pos.getY()) - fieldHeight * 1.5,
			300, fieldHeight, hWnd, nullptr, nullptr, nullptr);

		TextBox2 = CreateWindowW(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER,
			TextBox2Pos.getX(), (WINHEIGHT - TextBox2Pos.getY()) - fieldHeight * 1.5,
			100, fieldHeight, hWnd, nullptr, nullptr, nullptr);

		TextBox3 = CreateWindowW(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER,
			TextBox3Pos.getX(), (WINHEIGHT - TextBox3Pos.getY()) - fieldHeight * 1.5,
			100, fieldHeight, hWnd, nullptr, nullptr, nullptr);

		Button = CreateWindowW(L"BUTTON", L"_CONVERT_", WS_VISIBLE | WS_CHILD | WS_BORDER,
			ButtonPos.getX() - 50, (1000 - ButtonPos.getY()) - fieldHeight * 1.5, 200, fieldHeight,
			hWnd, (HMENU)ID_BTNCONVERT, nullptr, nullptr);



		SendMessage(TextBox1, WM_SETFONT, (LPARAM)hFont, TRUE);
		SendMessage(TextBox2, WM_SETFONT, (LPARAM)hFont, TRUE);
		SendMessage(TextBox3, WM_SETFONT, (LPARAM)hFont, TRUE);
		SendMessage(Button, WM_SETFONT, (LPARAM)hFont, TRUE);

		break;
	}


	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Analizuj zaznaczenia menu:
		switch (wmId)
		{

		case ID_BTNCONVERT:

			


			gwStat = GetWindowText(TextBox1, (LPWSTR)number, 20);

			for(int x = 0; x < gwStat;x ++)
			{
				strang += &number[x*2];
			}

			gwStat = GetWindowText(TextBox2, (LPWSTR)base1, 8);

			for (int x = 0; x < gwStat; x++)
			{
				base1str+= (base1[x * 2]);
				
			}

			gwStat = GetWindowText(TextBox3, (LPWSTR)base2, 8);

			
			for (int x = 0; x < gwStat; x++)
			{
				base2str+= (base2[x * 2]);
				
			}
			base1Int = stoi(base1str);
			base2Int = stoi(base2str);

			answer = convertBase(strang, base1Int, base2Int);
			

			break;

		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		EndPaint(hWnd, &ps);
	}
	break;

	case WM_SIZE:
	{
		RECT rect;
		GetClientRect(hWnd, &rect);
		render_state.width = rect.right - rect.left;
		render_state.height = rect.bottom - rect.top;

		int size = render_state.width * render_state.height * sizeof(unsigned __int64);
		if (render_state.memory) VirtualFree(render_state.memory, 0, MEM_RELEASE);



		render_state.memory = VirtualAlloc(0, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

		//render_state.bitmap_info  
		render_state.bitmapinfo.bmiHeader.biSize = sizeof(render_state.bitmapinfo.bmiHeader);
		render_state.bitmapinfo.bmiHeader.biWidth = render_state.width;
		render_state.bitmapinfo.bmiHeader.biHeight = render_state.height;
		render_state.bitmapinfo.bmiHeader.biPlanes = 1;
		render_state.bitmapinfo.bmiHeader.biBitCount = 32;
		render_state.bitmapinfo.bmiHeader.biCompression = BI_RGB;


	}break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;

}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
