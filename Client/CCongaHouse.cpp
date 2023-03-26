#include "CCongaHouse.h"
#include "CRes.h"
#include "CResMgr.h"
#include "CAnimation.h"
#include "CAnimator.h"

CCongaHouse::CCongaHouse()
	: m_pTexture(nullptr)
{
	// Texture �ε��ϱ�
	m_pTexture = CResMgr::GetInst()->LoadTexture(L"Mission1", L"texture\\Mission1.bmp");

	CreateAnimator();

	//GetAnimator()->CreateAnimation(L"Ship", m_pTexture, Vec2(569.f, 884.f), Vec2(194.f, 192.f), Vec2(198.f, 0.f), Vec2(-0.f, -0.f), 0.1f, 5);


	// Animation �����غ���
	//GetAnimator()->FindAnimation(L"Ship")->Save(L"animation\\BackGround\\Ship.anim");

	GetAnimator()->LoadAnimation(L"animation\\BackGround\\CongaHouse.anim");
}

CCongaHouse::~CCongaHouse()
{
}

void CCongaHouse::start()
{
}

void CCongaHouse::update()
{
	GetAnimator()->PlayL(L"CongaHouse", true);
}

void CCongaHouse::render(HDC _dc)
{
	component_render(_dc);
}
