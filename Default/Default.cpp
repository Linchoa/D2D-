// Default.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "Default.h"
#include "MainGame.h"

#define MAX_LOADSTRING 100

// ���� ����:
HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.
HWND	g_hWnd;

// �� �ڵ� ��⿡ ��� �ִ� �Լ��� ������ �����Դϴ�.
ATOM                MyRegisterClass(HINSTANCE hInstance);		// â ���� �� ���� �ܰ����� �������� ����ϴ� �Լ�
BOOL                InitInstance(HINSTANCE, int);			// â ���� �޼���
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);	// ������ �޼����� ó���ϴ� �߾� �Լ�

// TSTR :  �����ڵ�, �ƽ�Ű�ڵ� ��� ȣȯ�ϴ� WINDOW�� TCHAR�� ���� STRING Ŭ����
// LP : �����͸� �ǹ�
// LPTSTR : ���ڿ� �����͸� �ǹ�


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,				// �޸𸮿� �Ҵ�Ǵ� ��ü, �� ��ü, ���� ���α׷��� ���� �ĺ� ��ȣ
                     _In_opt_ HINSTANCE hPrevInstance,		// ���� ����Ǿ��� �ν��Ͻ��� �ڵ��� �Ѿ�´�, ���� ��� null�� ä����(win32��ݿ����� �׻� null, ���� ȣȯ���� ���� ����)
                     _In_ LPWSTR    lpCmdLine,			//	���ڿ��� ���� ����
                     _In_ int       nCmdShow)			// ������ â�� ��Ÿ��(��� / �ּ�ȭ ���, �ִ�ȭ ��� ��)���� ���� �ڵ����� ä����
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // _DEBUG
	
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: ���⿡ �ڵ带 �Է��մϴ�.

    // ���� ���ڿ��� �ʱ�ȭ�մϴ�.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DEFAULT, szWindowClass, MAX_LOADSTRING);
   
	MyRegisterClass(hInstance);

    // ���� ���α׷� �ʱ�ȭ�� �����մϴ�.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DEFAULT));

    MSG msg;
	msg.message = WM_NULL;

	CMainGame*		pMainGame = new CMainGame;
	pMainGame->Initialize();

	DWORD		dwTime = GetTickCount();

    // �⺻ �޽��� �����Դϴ�.
    while (true)
    {
		if(PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (WM_QUIT == msg.message)
				break;

			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg); // Ű���� �޼����� �����Ͽ� ���α׷����� ���� ����� �� �ֵ��� ����
				DispatchMessage(&msg);	// �ý��� �޼��� ť���� ���� �޼����� ���α׷��� �޼��� ó�� �Լ�(WndProc)�� �����ϴ� ���
			}		
		}
		else
		{
			if (dwTime + 10 < GetTickCount())
			{
				pMainGame->Update();
				pMainGame->Render();
				dwTime = GetTickCount();
			}
		}		
    }
	if (nullptr != pMainGame)
	{
		delete pMainGame;
		pMainGame = nullptr;
	}
    return (int) msg.wParam;
}



//
//  �Լ�: MyRegisterClass()
//
//  ����: â Ŭ������ ����մϴ�.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DEFAULT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = nullptr;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   �Լ�: InitInstance(HINSTANCE, int)
//
//   ����: �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
//
//   ����:
//
//        �� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ�
//        �� ���α׷� â�� ���� ���� ǥ���մϴ�.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

   RECT	rc{ 0, 0 , WINCX, WINCY };

  //  �������� RC = rc + �⺻ �޵��� â ��Ÿ�� + �޴� �� ������ ���� ����
   AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, 
	   WS_OVERLAPPEDWINDOW,
       200, 200,	// â�� �����Ǵ� left, top�� ��ġ
	   rc.right - rc.left, 
	   rc.bottom - rc.top,	// â�� ����, ���� ������
	   nullptr, nullptr, 
	   hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   g_hWnd = hWnd;
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   return TRUE;
}

//
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����:  �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND  - ���� ���α׷� �޴��� ó���մϴ�.
//  WM_PAINT    - �� â�� �׸��ϴ�.
//  WM_DESTROY  - ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // �޴� ������ ���� �м��մϴ�.
            switch (wmId)
            {
            case IDM_EXIT:
                DestroyWindow(g_hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
