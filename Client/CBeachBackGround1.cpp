#include "CBeachBackGround1.h"
#include "CRes.h"
#include "CResMgr.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CCore.h"

CBeachBackGround1::CBeachBackGround1()
	: m_pTexture(nullptr)
{
	// Texture 로딩하기
	m_pTexture = CResMgr::GetInst()->LoadTexture(L"Mission1", L"texture\\Mission1.bmp");

	CreateAnimator();

	//GetAnimator()->CreateAnimation(L"Ship", m_pTexture, Vec2(569.f, 884.f), Vec2(194.f, 192.f), Vec2(198.f, 0.f), Vec2(-0.f, -0.f), 0.1f, 5);


	// Animation 저장해보기
	//GetAnimator()->FindAnimation(L"Ship")->Save(L"animation\\BackGround\\Ship.anim");

	GetAnimator()->LoadAnimation(L"animation\\BackGround\\BeachBackGround1.anim");
}

CBeachBackGround1::~CBeachBackGround1()
{
}

void CBeachBackGround1::start()
{
}

void CBeachBackGround1::update()
{
	GetAnimator()->PlayL(L"BeachBackGround1", true);
	//Vec2 vPos = GetPos();
	//vPos.x = CCore::GetInst()->GetPlayerPos().x * 0.01f;
	//SetPos(vPos);
}

void CBeachBackGround1::render(HDC _dc)
{
	component_render(_dc);
}

