#include "pch.h"
#include "CCore.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CPathMgr.h"
#include "CCollisionMgr.h"
#include "CEventMgr.h"
#include "CCamera.h"
#include "CUIMgr.h"
#include "CResMgr.h"
#include "CSound.h"
#include "CSoundMgr.h"
#include "CPlayer.h"

#include "CTexture.h"
#include "CResMgr.h"
#include "SelectGDI.h"

#include "resource.h"


CCore::CCore()
	:m_hWnd(0)
	, m_ptResolution{}
	, m_hDC(0)
	, m_arrBrush{}
	, m_arrPen{}
	, m_vPlayerPos(0.f, 0.f)
	, m_bStretchRender(false)
{

}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC);

	for (int i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}

	DestroyMenu(m_hMenu);
}

int CCore::Init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	// 해상도에 맞게 윈도우 크기 조정
	ChangeWindowSize(Vec2((float)_ptResolution.x, (float)_ptResolution.y), false);

	// 메뉴바 생성
	m_hMenu = LoadMenu(nullptr, MAKEINTRESOURCEW(IDC_CLIENT));

	m_hDC = GetDC(m_hWnd);

	// 이중 버퍼링 용도의 텍스쳐 한장을 만든다.
	m_pMemTex = CResMgr::GetInst()->CreateTexture(L"BackBuffer", (UINT)m_ptResolution.x, (UINT)m_ptResolution.y);

	// 자주 사용 할 펜 및 브러쉬 생성
	CreateBrushPen();


	// Manager 초기화
	CPathMgr::GetInst()->init();
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CCamera::GetInst()->init();
	CSceneMgr::GetInst()->init();
	CSoundMgr::GetInst()->init();

	 // Sound 로드 테스트
	 CResMgr::GetInst()->LoadSound(L"BGM_01", L"sound\\Blue_Water_Fangs.wav");
	 CResMgr::GetInst()->LoadSound(L"BGM_02", L"sound\\Steel_Beasts _6Beets.wav");
	 CResMgr::GetInst()->LoadSound(L"BGM_03", L"sound\\Stage_Clear.wav");
	 CSound* pNewSound = CResMgr::GetInst()->FindSound(L"BGM_01");
	 
	 pNewSound->Play(); // 인자로 true를 주면 반복재생
	 
	 pNewSound->SetPosition(50.f); // 백분률, 소리 위치 설정
	 pNewSound->PlayToBGM(true); // 인자로 true를 주면 반복재생
	 pNewSound->SetVolume(60.f);

	return S_OK;
}


void CCore::progress()
{
	// ==============
	// Manager Update
	// ==============
	CTimeMgr::GetInst()->update();
	CKeyMgr::GetInst()->update();
	CCamera::GetInst()->update();

	// ============
	// Scene Update
	// ============
	CSceneMgr::GetInst()->update();

	// 충돌체크
	CCollisionMgr::GetInst()->update();

	// UI 이벤트 체크
	CUIMgr::GetInst()->update();


	// =========
	// Rendering
	// =========
	// 화면 Clear
	Clear();

	

	CSceneMgr::GetInst()->render(m_pMemTex->GetDC());
	CCamera::GetInst()->render(m_pMemTex->GetDC());

	if (m_bStretchRender)
		StretchBlt(m_hDC, 0, 0, m_ptResolution.x * 2, m_ptResolution.y * 1.7
			, m_pMemTex->GetDC(), 0, 0, m_ptResolution.x, m_ptResolution.y, SRCCOPY);
	else
		BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y
			, m_pMemTex->GetDC(), 0, 0, SRCCOPY);


		// 실제 게임할때 비율

				// 마우스 좌표 출력 (함수가 좀 더러워 지긴 한데...)
	Vec2 vMousePos = CCamera::GetInst()->GetRealPos(CKeyMgr::GetInst()->GetMousePos());
	Vec2 vPlayerPos = GetPlayerPos();
	Vec2 vCamPos = CCamera::GetInst()->GetLookAt();
	if (m_bStretchRender)
	{
		//vMousePos /= 2.5f;
		//vPlayerPos /= 2.5f;
		//vCamPos /= 2.5f;
	}
	wstring strMouseRenderPosx = L"MousePosX : ";
	wstring strMouseRenderPosy = L"MousePosY : ";
	wstring strCamPosX = L"CamPosX : ";
	wstring strCamPosY = L"CamPosY : ";
	wstring strStretchCamPosX = L"StretchCamPosX : ";
	wstring strStretchCamPosY = L"StretchCamPosY : ";
	wstring strPlayerPosX = L"PlayerPosX : ";
	wstring strPlayerPosY = L"PlayerPosY : ";
	//wstring strFPS = L"FPS : ";

	strMouseRenderPosx.append(std::to_wstring((int)vMousePos.x));
	strMouseRenderPosy.append(std::to_wstring((int)vMousePos.y));
	strCamPosX.append(std::to_wstring((int)vCamPos.x));
	strCamPosY.append(std::to_wstring((int)vCamPos.y));
	strPlayerPosX.append(std::to_wstring((int)vPlayerPos.x));
	strPlayerPosY.append(std::to_wstring((int)vPlayerPos.y));
	//strMouseRenderPosy.append(std::to_wstring((int)vMousePos.y));
	//HDC hdc = CCore::GetInst()->GetMemTex()->GetDC();

	TextOut(m_hDC, 510, 10, strMouseRenderPosx.c_str(), strMouseRenderPosx.size());  // 1130 , 10
	TextOut(m_hDC, 510, 30, strMouseRenderPosy.c_str(), strMouseRenderPosy.size());
	TextOut(m_hDC, 510, 50, strCamPosX.c_str(), strCamPosX.size());
	TextOut(m_hDC, 510, 70, strCamPosY.c_str(), strCamPosY.size());
	//TextOut(m_hDC, 1130, 90, strStretchCamPosX.c_str(), strStretchCamPosX.size());
	//TextOut(m_hDC, 1130, 110, strStretchCamPosY.c_str(), strStretchCamPosY.size());
	TextOut(m_hDC, 510, 130, strPlayerPosX.c_str(), strPlayerPosX.size());
	TextOut(m_hDC, 510, 150, strPlayerPosY.c_str(), strPlayerPosY.size());
	//TextOut(m_hDC, 640, 384, strStretchCamPosX.c_str(), strStretchCamPosX.size());
	//TextOut(hMainDC, 100, 200, strMouseRenderPosy.c_str(), strMouseRenderPosy.size());



	

	CTimeMgr::GetInst()->render();

	// ==============
	// 이벤트 지연처리
	// ==============
	CEventMgr::GetInst()->update();
}

void CCore::Clear()
{
	SelectGDI gdi(m_pMemTex->GetDC(), BRUSH_TYPE::BLACK);
	Rectangle(m_pMemTex->GetDC(), -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);
}

void CCore::CreateBrushPen()
{
	// hollow brush
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	m_arrBrush[(UINT)BRUSH_TYPE::WHITE] = (HBRUSH)GetStockObject(WHITE_BRUSH);
	m_arrBrush[(UINT)BRUSH_TYPE::BLACK] = (HBRUSH)GetStockObject(BLACK_BRUSH);
	

	//red blue green pen
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));

}

void CCore::DockMenu()
{
	SetMenu(m_hWnd, m_hMenu);
	ChangeWindowSize(GetResolution(), true);
}

void CCore::DivideMenu()
{
	SetMenu(m_hWnd, nullptr);
	ChangeWindowSize(GetResolution(), false);
}

void CCore::ChangeWindowSize(Vec2 _vResolution, bool _bMenu)
{
	RECT rt = { 0, 0, (long)_vResolution.x, (long)_vResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, _bMenu);
	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);
}

