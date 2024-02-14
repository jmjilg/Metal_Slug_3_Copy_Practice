#include "pch.h"
#include "CGrenade.h"

#include "CTimeMgr.h"
#include "CCollider.h"
#include "CCore.h"
#include "CCamera.h"
#include "CRes.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CAnimator.h"
#include "CRigidBody.h"


CGrenade::CGrenade()
	: m_fTheta(PI / 180.f)
	, m_pTex(nullptr)
	, IsCollision(false)
	, m_fSpeed(200.f)
	, m_iBounceCount(0)
{

	CreateAnimator();
	CreateRigidBody();
	CreateGravity();

	CreateCollider();
	GetCollider()->SetScale(Vec2(10.f, 10.f));

	m_pTex = CResMgr::GetInst()->LoadTexture(L"WeaponSFX", L"texture\\WeaponSFX.bmp");
	
	GetAnimator()->LoadAnimation(L"animation\\Grenade_Left.anim");
	GetAnimator()->LoadAnimation(L"animation\\Grenade_Right.anim");

}

CGrenade::~CGrenade()
{
}

void CGrenade::update()
{
	update_animation();

	Vec2 vPos = GetPos();

	vPos.x += m_fSpeed * cosf(m_fTheta) * fDT;
	vPos.y += m_fSpeed * sinf(m_fTheta) * fDT;

	//vPos.x += m_fSpeed * m_vDir.x * fDT;
	//vPos.y += m_fSpeed * m_vDir.y * fDT;  // 위와 결과는 같지만 좀 더 직관적임

	SetPos(vPos);

	Vec2 vResolution = CCore::GetInst()->GetResolution();
	vPos = CCamera::GetInst()->GetRenderPos(vPos);


	if ((vPos.x < 0) || (vPos.x > vResolution.x) || (vPos.y < 0) || (vPos.y > vResolution.y))
		DeleteObject(this);
}

void CGrenade::render(HDC _dc)
{
	//Vec2 vPos = GetPos();
	//Vec2 vScale = GetScale();


	//Ellipse(_dc, (int)(vPos.x - vScale.x / 2.f), (int)(vPos.y - vScale.y / 2.f)
	//	, (int)(vPos.x + vScale.x / 2.f), (int)(vPos.y + vScale.y / 2.f));

	//vPos = CCamera::GetInst()->GetRenderPos(vPos);  // 필요함. 이게 아니면 실제 좌표가 아닌 렌더링 좌표에서만 출력이 됨

	//vPos = GetCollider()->GetFinalPos();

	component_render(_dc);
}

void CGrenade::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (!IsCollision)
	{
		if (pOtherObj->GetName() == L"Chowmein_Conga" || pOtherObj->GetName() == L"Locust" || pOtherObj->GetName() == L"Flying_Killer" || pOtherObj->GetName() == L"M3_Rocket_Launch_Support_Van" || pOtherObj->GetName() == L"M3_Rocket_Launch_Support_Van_Missile" || pOtherObj->GetName() == L"Huge_Hermit")
		{
			DeleteObject(this);
		}
		else if (pOtherObj->GetName() == L"CongaHouse")
		{
			DeleteObject(this);
		}
		else if (pOtherObj->GetName() == L"BrokenShip")
		{
			DeleteObject(this);
		}
		
		else if (pOtherObj->GetName() == L"Ground")
		{
			m_iBounceCount++;
			if (m_iBounceCount >= 2)
				DeleteObject(this);

			if (GetRigidBody())
			{
				GetRigidBody()->SetVelocity(Vec2(GetRigidBody()->GetVelocity().x, -350.f));
			}
		}

		IsCollision = !IsCollision;
	}
}

void CGrenade::update_animation()
{
	GetAnimator()->SetTransParentColor(0, 248, 0);

	//case PLAYER_STATE::IDLE:
	//	if (m_iDir.x == -1)
			GetAnimator()->PlayL(L"Grenade_Right", true);
	//	else
	//		GetAnimator()->PlayL(L"PLAYER_IDLE_LOWER_PART_RIGHT", true);
}
