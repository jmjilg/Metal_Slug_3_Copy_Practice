#include "CBossStageTile.h"
#include "CRes.h"
#include "CResMgr.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CCollider.h"
#include "CGravity.h"
#include "CRayCollider.h"
#include "CRayGround.h"

CBossStageTile::CBossStageTile()
	: m_pTexture(nullptr)
	, m_pRayGround(nullptr)
{
	// Texture 로딩하기
	m_pTexture = CResMgr::GetInst()->LoadTexture(L"Mission1", L"texture\\Mission1.bmp");

	CreateAnimator();

	CreateCollider();
	GetCollider()->SetScale(Vec2(35.f, 37.f));

	GetAnimator()->LoadAnimation(L"animation\\BackGround\\BossStageTile.anim");
}

CBossStageTile::~CBossStageTile()
{
}

void CBossStageTile::start()
{
	m_pRayGround = new CRayGround;
	m_pRayGround->SetName(L"BossStageTileGround");

	Vec2 vTemp = GetPos();
	m_pRayGround->GetCollider()->GetVecRay().push_back(Vec2(vTemp.x - 16.f, vTemp.y - 12.f));
	m_pRayGround->GetCollider()->GetVecRay().push_back(Vec2(vTemp.x + 25.f, vTemp.y - 12.f));
	CreateObject(m_pRayGround, GROUP_TYPE::GROUND);
}

void CBossStageTile::update()
{
	GetAnimator()->PlayL(L"BossStageTile", true);
}

void CBossStageTile::render(HDC _dc)
{
	component_render(_dc);
}



void CBossStageTile::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Huge_Hermit")
	{
		DeleteObject(m_pRayGround);
		DeleteObject(this);
	}
}

void CBossStageTile::OnCollision(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Player")
	{

	}
}

void CBossStageTile::OnCollisionExit(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Player")
	{

	}
}
