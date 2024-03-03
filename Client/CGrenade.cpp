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
	: m_iDir(0)
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
	if (IsCollision)
	{
		DeleteObject(this);
		return;
	}

	update_animation();

	Vec2 vPos = GetPos();

	vPos.x += m_fSpeed * m_iDir * fDT;
	//vPos.y += m_fSpeed * sinf(m_fTheta) * fDT;

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

	wstring ObjName = pOtherObj->GetName();


		if (ObjName == L"Chowmein_Conga" || ObjName == L"Locust" || ObjName == L"Flying_Killer" || ObjName == L"M3_Rocket_Launch_Support_Van" || ObjName == L"M3_Rocket_Launch_Support_Van_Missile" || ObjName == L"Huge_Hermit" || ObjName == L"CongaHouse" || ObjName == L"BrokenShip")
		{
			IsCollision = true;
		}

		
		else if (ObjName == L"Ground")
		{
			m_iBounceCount++;
			if (m_iBounceCount >= 2)
				IsCollision = true;

			if (GetRigidBody())
			{
				SetSpeed(120.f);
				GetRigidBody()->SetVelocity(Vec2(GetRigidBody()->GetVelocity().x, -200.f));
			}
		}
}

void CGrenade::OnCollision(CCollider* _pOther)
{
}

void CGrenade::OnCollisionExit(CCollider* _pOther)
{

}

void CGrenade::update_animation()
{
	GetAnimator()->SetTransParentColor(0, 248, 0);

	if (m_iDir == -1)
		GetAnimator()->PlayL(L"Grenade_Left", true);
	else
		GetAnimator()->PlayL(L"Grenade_Right", true);
}
