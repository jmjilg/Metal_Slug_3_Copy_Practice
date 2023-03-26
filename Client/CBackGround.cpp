#include "CBackGround.h"
#include "CResMgr.h"
#include "CRes.h"
#include "CTexture.h"


CBackGround::CBackGround()
	: m_pBackground(nullptr)
{
	// Texture 로딩하기
	m_pBackground = CResMgr::GetInst()->LoadTexture(L"BackGround", L"texture\\BackGround.bmp");
}

CBackGround::~CBackGround()
{
}

void CBackGround::start()
{
}

void CBackGround::update()
{
	// 카메라 의 위치를 따라간다.
	m_vFinalPos = CCamera::GetInst()->GetLookAt();
}

void CBackGround::render(HDC _dc)
{
	int iWidth = 2889;
	int iHeight = 274;

	//BitBlt(_dc
	//	, (int)vPos.x - (float)(iWidth / 2)
	//	, (int)vPos.y - (float)(iHeight / 2)
	//	, iWidth, iHeight
	//	, m_pTex->GetDC()
	//	, 0, 0, SRCCOPY);

	//TransparentBlt(_dc
	//	, (int)vPos.x
	//	, (int)vPos.y
	//	, iWidth, iHeight
	//	, m_pBackground->GetDC()
	//	, (int)vPos.x, (int)vPos.y, iWidth, iHeight
	//	, RGB(248, 0, 248));

	// 렌더링 좌표로 변환
	Vec2 vRenderPos = CCamera::GetInst()->GetRealPos(m_vFinalPos);

//	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(m_vFinalPos);

	TransparentBlt(_dc
		, 0
		, 0
		, 1280
		, 274
		, m_pBackground->GetDC()
		, (int)(vRenderPos.x - 640)
		, (int)(vRenderPos.y - 384)
		, 1280
		, 274
		, RGB(248, 0, 248)
	);

	//StretchBlt(_dc
	//	, 0
	//	, 0
	//	, 1280
	//	, 274
	//	, m_pBackground->GetDC()
	//	, (int)(vRenderPos.x - 640)
	//	, (int)(vRenderPos.y - 384)
	//	, 1280
	//	, 274
	//	, RGB(248, 0, 248)
	//);
}
