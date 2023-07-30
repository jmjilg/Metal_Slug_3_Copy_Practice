#include "CCongaHouse.h"
#include "CRes.h"
#include "CResMgr.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CCollider.h"
#include "CGravity.h"
#include "CRayGround.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CObstacle.h"


CCongaHouse::CCongaHouse()
	: m_pTexture(nullptr)
	, m_iHP(10)
{
	// Texture 로딩하기
	m_pTexture = CResMgr::GetInst()->LoadTexture(L"Mission1", L"texture\\Mission1.bmp");

	CreateAnimator();

	//GetAnimator()->CreateAnimation(L"Ship", m_pTexture, Vec2(569.f, 884.f), Vec2(194.f, 192.f), Vec2(198.f, 0.f), Vec2(-0.f, -0.f), 0.1f, 5);


	// Animation 저장해보기
	//GetAnimator()->FindAnimation(L"Ship")->Save(L"animation\\BackGround\\Ship.anim");

	GetAnimator()->LoadAnimation(L"animation\\BackGround\\CongaHouse.anim");
	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(80.f, -55.f));
	GetCollider()->SetScale(Vec2(107.f, 124.f));
	SetName(L"CongaHouse");	
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

void CCongaHouse::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Missile_Player")
	{
		m_iHP--;		
		if (m_iHP < 0)
		{
			CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
			pCurScene->SetCongaHouse(false);
			//CRayGround* pRayGround = new CRayGround;
			//pRayGround->GetCollider()->SetIsRay(true);
			//pRayGround->GetCollider()->GetVecRay().push_back(Vec2(2240, 93));
			//pRayGround->GetCollider()->GetVecRay().push_back(Vec2(2240, 500));
			//CreateObject(pRayGround, GROUP_TYPE::GROUND);
			DeleteObject(GetObstacle());
			DeleteObject(this);
			
		}
	}

}


