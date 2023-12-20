// Client.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//
#include "global.h"
#include "framework.h"
#include "Client.h"

#include "CCore.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
HWND    g_hWnd; //메인윈도우 핸들
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
HWND hMDlg;		// 모달리스 대화상자
HWND hList_AnimFile_Name1, hList_AnimFile_Name2, hList_Frame_Info1, hList_Frame_Info2, hList_PlayList;
HWND hEdit_StartX, hEdit_StartY, hEdit_EndX, hEdit_EndY, hEdit_OffsetX, hEdit_OffsetY, hEdit_Duration, hEdit_PlayTime, hEdit_PlayScale, hEdit_Frame_Count;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	// 메모리 릭(누수) 체크

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(215);

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// 전역 문자열을 초기화합니다.
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_CLIENT, szWindowClass, MAX_LOADSTRING);

	// 윈도우 정보 등록
	MyRegisterClass(hInstance);

	// 윈도우 생성
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	// Core 초기화
	if (FAILED(CCore::GetInst()->Init(g_hWnd, POINT{ 1280, 768 })))  // 1280, 768 | 640, 384
	{
		MessageBox(nullptr, L"Core 객체 초기화 실패", L"ERROR", MB_OK);

		return FALSE;
	}


	// 단축키 테이블 정보 로딩
	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));

	MSG msg;
	//GetMessage
	// 메세지큐에서 메세지 확인 될 때까지 대기
	// msg.message == WM_QUIT 인 경우 false 를 반환 -> 프로그램 종료

	// PeekMessage
	// 메세지 유무와 관계없이 반환
	// 메세지큐에서 메세지를 확인한 경우 true, 메세지큐에 메세지가 없는 경우 false 를 반환한다.
	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (WM_QUIT == msg.message)
				break;

			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				if (!IsWindow(hMDlg) || !IsDialogMessage(hMDlg, &msg))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}
		}

		// 메세지가 발생하지 않는 대부분의 시간
		else
		{
			// Game 코드 수행
			// 디자인 패턴(설계 유형)
			// 싱글톤 패턴
			CCore::GetInst()->progress();
		}
	}

	return (int)msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
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
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLIENT));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr; // MAKEINTRESOURCEW(IDC_CLIENT);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	g_hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!g_hWnd)
	{
		return FALSE;
	}

	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);

	return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//

INT_PTR CALLBACK TileCountProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK AnimationToolProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// 메뉴 선택을 구문 분석합니다:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case ID_MENU_TILE:
		{
			INT_PTR iRet = DialogBox(hInst, MAKEINTRESOURCE(IDD_TILE_COUNT), hWnd, TileCountProc);

			if (iRet == IDOK)
			{

			}
		}
		break;
		case ID_MENU_ANIMATION_TOOL:
		{
			if (!IsWindow(hMDlg))
			{
				hMDlg = CreateDialog(hInst, MAKEINTRESOURCE(IDD_ANIMATION_TOOL), hWnd, AnimationToolProc);
				hList_AnimFile_Name1 = GetDlgItem(hMDlg, IDC_LIST_AnimFile_Name1);
				hList_AnimFile_Name2 = GetDlgItem(hMDlg, IDC_LIST_AnimFile_Name2);
				hList_Frame_Info1 = GetDlgItem(hMDlg, IDC_LIST_Frame_Info1);
				hList_Frame_Info2 = GetDlgItem(hMDlg, IDC_LIST_Frame_Info2);
				hList_PlayList = GetDlgItem(hMDlg, IDC_LIST_PlayList);
				hEdit_StartX = GetDlgItem(hMDlg, IDC_EDIT_StartX);
				hEdit_StartY = GetDlgItem(hMDlg, IDC_EDIT_StartY);
				hEdit_EndX = GetDlgItem(hMDlg, IDC_EDIT_EndX);
				hEdit_EndY = GetDlgItem(hMDlg, IDC_EDIT_EndY);
				hEdit_OffsetX = GetDlgItem(hMDlg, IDC_EDIT_OffsetX);
				hEdit_OffsetY = GetDlgItem(hMDlg, IDC_EDIT_OffsetY);
				hEdit_PlayTime = GetDlgItem(hMDlg, IDC_EDIT_PlayTime);
				hEdit_PlayScale = GetDlgItem(hMDlg, IDC_EDIT_PlayScale);
				hEdit_Duration = GetDlgItem(hMDlg, IDC_EDIT_Duration);
				hEdit_Frame_Count = GetDlgItem(hMDlg, IDC_EDIT_Frame_Count);
				// SendMessage(hList_AnimFile_Name1, LB_ADDSTRING, 0, (LPARAM)str);
				ShowWindow(hMDlg, SW_SHOW);
			}
			else
				SetFocus(hMDlg);
		}
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
		//Device Context 만들어서 ID를 반환
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...

		//Rectangle(hdc, 1180, 0, 1280, 100);

		// 그리기 종료
		EndPaint(hWnd, &ps);
	}
	break;

	case WM_KEYDOWN:
	{
		
	}
		break;

	case WM_LBUTTONDOWN:

		break;

	case WM_MOUSEMOVE:

		break;

	case WM_LBUTTONUP:
	
	break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
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



// 1. 플레이어 미사일 종류 추가
// 2. 몬스터도 미사일 패턴 추가
