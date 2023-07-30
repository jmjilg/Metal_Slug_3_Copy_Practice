#include "CShipDoor.h"
#include "CRes.h"
#include "CResMgr.h"
#include "CAnimation.h"
#include "CAnimator.h"

CShipDoor::CShipDoor()
	: m_pTexture(nullptr)
	, m_IsFinish(false)
{
	// Texture �ε��ϱ�
	m_pTexture = CResMgr::GetInst()->LoadTexture(L"Mission1", L"texture\\Mission1.bmp");

	CreateAnimator();

	//GetAnimator()->CreateAnimation(L"Ship", m_pTexture, Vec2(569.f, 884.f), Vec2(194.f, 192.f), Vec2(198.f, 0.f), Vec2(-0.f, -0.f), 0.1f, 5);


	// Animation �����غ���
	//GetAnimator()->FindAnimation(L"Ship")->Save(L"animation\\BackGround\\Ship.anim");

	GetAnimator()->LoadAnimation(L"animation\\BackGround\\ShipDoor.anim");
	//GetAnimator()->StopAnimationL(true);
}

CShipDoor::~CShipDoor()
{
}

void CShipDoor::start()
{
}

void CShipDoor::update()
{
	//if (m_IsFinish)
	//	GetAnimator()->GetCurAnimL()->SetFrame(6);

	// Ư�� ������ �����ϸ� �ѹ��� ����ϵ��� �ϱ�
	GetAnimator()->PlayL(L"ShipDoor", true);

	if (GetAnimator()->GetCurAnimL()->GetCurFrame() == 6)
		GetAnimator()->GetCurAnimL()->SetFrame(6);

}

void CShipDoor::render(HDC _dc)
{
	component_render(_dc);
}
