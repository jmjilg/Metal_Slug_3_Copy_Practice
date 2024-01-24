#include "CSupplies.h"
#include "CRes.h"
#include "CResMgr.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CCollider.h"
#include "CScene.h"
#include "CMonster.h"
#include "AI.h"
#include "CState.h"
#include "CSceneMgr.h"
#include "CPlayer.h"
#include "CTimeMgr.h"
#include "CCore.h"
#include "CCamera.h"

CSupplies::CSupplies()
	: m_pTexture(nullptr)
{
	// Texture 로딩하기
	m_pTexture = CResMgr::GetInst()->LoadTexture(L"Mission1", L"texture\\WeaponSFX.bmp");

	CreateAnimator();
	CreateCollider();
	CreateRigidBody();
	CreateGravity();
	GetCollider()->SetScale(Vec2(22.f, 20.f));

	//GetAnimator()->CreateAnimation(L"Ship", m_pTexture, Vec2(569.f, 884.f), Vec2(194.f, 192.f), Vec2(198.f, 0.f), Vec2(-0.f, -0.f), 0.1f, 5);


	// Animation 저장해보기
	//GetAnimator()->FindAnimation(L"Ship")->Save(L"animation\\BackGround\\Ship.anim");

	GetAnimator()->LoadAnimation(L"animation\\BackGround\\HeavyMachinGunSupplies.anim");

}

CSupplies::~CSupplies()
{
}

void CSupplies::start()
{
}

void CSupplies::update()
{
	GetAnimator()->SetTransParentColor(0, 248, 0);
	GetAnimator()->PlayL(L"HeavyMachinGunSupplies", true);
}

void CSupplies::render(HDC _dc)
{
	component_render(_dc);
}


void CSupplies::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Player")
	{
		// 여러가지 기능 추가하면 됨
		DeleteObject(this);
	}
}



