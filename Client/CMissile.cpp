#include "pch.h"
#include "CMissile.h"

#include "CTimeMgr.h"
#include "CCollider.h"
#include "CCore.h"
#include "CCamera.h"
#include "CRes.h"
#include "CResMgr.h"
#include "CTexture.h"

CMissile::CMissile()
	: m_fTheta( PI / 4.f)
	, m_vDir(Vec2(1.f, 0.f))
	, m_pTex(nullptr)
{
	m_vDir.Normalize();
	CreateCollider();
	GetCollider()->SetScale(Vec2(15.f, 15.f));


	CTexture* pHandGunTex = CResMgr::GetInst()->LoadTexture(L"BulletSFX", L"texture\\HandGunSFX10x10.bmp"); // 핸드건의 총알만 여기서 따옴
	CTexture* pWeaponTex = CResMgr::GetInst()->LoadTexture(L"WeaponSFX", L"texture\\WeaponSFX.bmp"); 

	m_pTex = pHandGunTex;
}

CMissile::~CMissile()
{
}

void CMissile::update()
{
	Vec2 vPos = GetPos();

	//vPos.x += 600.f * cosf(m_fTheta) * fDT;
	//vPos.y -= 600.f * sinf(m_fTheta) * fDT;

	vPos.x += 600.f * m_vDir.x * fDT;
	vPos.y += 600.f * m_vDir.y * fDT;  // 위와 결과는 같지만 좀 더 직관적임

	SetPos(vPos);

	Vec2 vResolution = CCore::GetInst()->GetResolution();
	vPos = CCamera::GetInst()->GetRenderPos(vPos);
	

	if ( (vPos.x < 0) || (vPos.x > vResolution.x) || (vPos.y < 0 ) || (vPos.y > vResolution.y) )
		DeleteObject(this);

}

void CMissile::render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();


	//Ellipse(_dc, (int)(vPos.x - vScale.x / 2.f), (int)(vPos.y - vScale.y / 2.f)
	//	, (int)(vPos.x + vScale.x / 2.f), (int)(vPos.y + vScale.y / 2.f));

	// vPos = CCamera::GetInst()->GetRenderPos(vPos); 필요한가?

	TransparentBlt(_dc
		, (int)(vPos.x - 10 / 2.f)
		, (int)(vPos.y - 10 / 2.f)
		, 10
		, 10
		, m_pTex->GetDC()
		, 0
		, 0
		, 10
		, 10
		, RGB(0, 0, 0)
	);


	component_render(_dc);
}

void CMissile::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Monster")
	{
		DeleteObject(this);
	}
}
