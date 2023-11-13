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
	: m_fTheta( PI / 180.f)
	, m_vDir(Vec2(1.f, 0.f))
	, m_pTex(nullptr)
	, IsCollision(false)
	, m_fSpeed(600.f)
	, m_wDest(0)
	, m_hDest(0)
	, m_xoriginSrc(0)
	, m_yoriginSrc(0)
	, m_wSrc(0)
	, m_hSrc(0)
{
	m_vDir.Normalize();
	CreateCollider();
	GetCollider()->SetScale(Vec2(10.f, 10.f));


	pHandGunTex = CResMgr::GetInst()->LoadTexture(L"BulletSFX", L"texture\\HandGunSFX15x15.bmp"); // 핸드건의 총알만 여기서 따옴
	pWeaponTex = CResMgr::GetInst()->LoadTexture(L"WeaponSFX", L"texture\\WeaponSFX.bmp"); 


	m_pTex = pHandGunTex;
}

CMissile::~CMissile()
{
}

void CMissile::SetDir(MISSILE_DIR _eDir)
{
	Vec2 vPos = GetPos();
	m_eDir = _eDir;

	switch (m_eDir)
	{
	case RIGHT:
		m_fTheta = PI / 180.f;
		SetRenderInfo( (int)(15 / 2.f), (int)(10 / 2.f), 30, 5, 4, 20, 30, 5); // 일단 임시
		break;
	case DEGREES_22:
		m_fTheta = PI / 8.f;
		break;
	case DEGREES_55:
		m_fTheta = PI / 3.2f;
		break;
	case DEGREES_77:
		m_fTheta = PI / 2.3f;
		break;
	case DOWN:
		m_fTheta = PI / 2.f;
		SetRenderInfo((int)(15 / 2.f), (int)(10 / 2.f), 5, 30, 52, 39, 5, 30);
		break;
	case DEGREES_112:
		m_fTheta = PI / 1.6f;
		break;
	case DEGREES_135:
		m_fTheta = PI / 1.33f;
		break;
	case DEGREES_157:
		m_fTheta = PI / 1.14;
		break;
	case LEFT:
		SetRenderInfo((int)(15 / 2.f), (int)(10 / 2.f), 30, 5, 439, 48, 30, 5);
		m_fTheta = PI / 1.f;
		break;
	case DEGREES_202:
		m_fTheta = 2 * PI / 1.77f;
		break;
	case DEGREES_225:
		m_fTheta = 2 * PI / 1.6f;
		break;
	case DEGREES_247:
		m_fTheta = 2 * PI / 1.45f;
		break;
	case UP:
		m_fTheta = 2 * PI / 1.33f;
		SetRenderInfo((int)(15 / 2.f), (int)(10 / 2.f), 5, 30, 21, 400, 5, 30);
		break;
	case DEGREES_292:
		m_fTheta = 2 * PI / 1.23f;
		break;
	case DEGREES_315:
		m_fTheta = 2 * PI / 1.14f;
		break;
	case DEGREES_337:
		m_fTheta = 2 * PI / 1.06f;
		break;
	}
}

void CMissile::update()
{
	if (m_bHMG) // 한번만 실행하면 되긴 하는데 좀 아쉽네 이거.. 근데 바꾸기가 귀찮다..
	{
		GetCollider()->SetScale(Vec2(30.f, 10.f));
		m_pTex = pWeaponTex;
	}

	Vec2 vPos = GetPos();

	vPos.x += m_fSpeed * cosf(m_fTheta) * fDT;
	vPos.y += m_fSpeed * sinf(m_fTheta) * fDT;

	//vPos.x += m_fSpeed * m_vDir.x * fDT;
	//vPos.y += m_fSpeed * m_vDir.y * fDT;  // 위와 결과는 같지만 좀 더 직관적임

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

	vPos = CCamera::GetInst()->GetRenderPos(vPos);  // 필요함. 이게 아니면 실제 좌표가 아닌 렌더링 좌표에서만 출력이 됨

	//vPos = GetCollider()->GetFinalPos();



	if (m_bHMG)
	{
		int xoriginDest, yoriginDest, wDest, hDest, xoriginSrc, yoriginSrc, wSrc, hSrc;
		TransparentBlt(_dc
			, (int)(vPos.x - m_xoriginDest)
			, (int)(vPos.y - m_yoriginDest)
			, m_wDest
			, m_hDest
			, m_pTex->GetDC()
			, m_xoriginSrc
			, m_yoriginSrc
			, m_wSrc
			, m_hSrc
			, RGB(0, 248, 0)
		);
	}
	else
		TransparentBlt(_dc
			, (int)(vPos.x - 15 / 2.f)
			, (int)(vPos.y - 10 / 2.f)
			, 15
			, 10
			, m_pTex->GetDC()
			, 0
			, 0
			, 15
			, 10
			, RGB(0, 0, 0)
		);

	component_render(_dc);
}

void CMissile::OnCollisionEnter(CCollider* _pOther)
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

		IsCollision = !IsCollision;
	}

}
