#include "CBossStageTileCopy.h"
#include "CRes.h"
#include "CResMgr.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CCollider.h"
#include "CGravity.h"
#include "CRayCollider.h"
#include "CRayGround.h"

CBossStageTileCopy::CBossStageTileCopy()
	: m_pTexture(nullptr)
	, m_pRayGround(nullptr)
{
	// Texture �ε��ϱ�
	m_pTexture = CResMgr::GetInst()->LoadTexture(L"Mission1", L"texture\\Mission1.bmp");

	CreateAnimator();

	GetAnimator()->LoadAnimation(L"animation\\BackGround\\BossStageTileCopy.anim");

	CreateCollider();
	GetCollider()->SetScale(Vec2(32.f, 37.f));


}

CBossStageTileCopy::~CBossStageTileCopy()
{
}

void CBossStageTileCopy::start()
{
	CreateRayGround();
}

void CBossStageTileCopy::update()
{
	GetAnimator()->PlayL(L"BossStageTileCopy", true);
}

void CBossStageTileCopy::render(HDC _dc)
{
	component_render(_dc);
}

void CBossStageTileCopy::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Huge_Hermit")
	{
		// ���� ���Ͱ� Ÿ���� �μ��� Ÿ�� �� ���� �ٽ� �ϳ� ��������
		Vec2 vTemp = GetPos();
		vTemp.x += 320.f;
		CObject* pBossStageTileCopy = new CBossStageTileCopy;
		pBossStageTileCopy->SetName(L"BossStageTileCopy");
		pBossStageTileCopy->SetPos(vTemp);
		pBossStageTileCopy->SetScale(Vec2(50.f, 50.f));
		CBossStageTileCopy* pObj = (CBossStageTileCopy*)pBossStageTileCopy;
		pObj->CreateRayGround(); // ���� �浹ü�� �������ַ��� �ٿ�ĳ������ �ؼ� �ڽ�Ŭ������ �Լ��� ȣ���������

		CreateObject(pBossStageTileCopy, GROUP_TYPE::BOSSSTAGETILECOPY);  


		DeleteObject(m_pRayGround);
		DeleteObject(this);
	}
}

void CBossStageTileCopy::OnCollision(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Player")
	{

	}
}

void CBossStageTileCopy::OnCollisionExit(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Player")
	{
	}
}

void CBossStageTileCopy::CreateRayGround()
{
	m_pRayGround = new CRayGround;
	m_pRayGround->SetName(L"BossStageTileCopyGround");

	Vec2 vTemp = GetPos();
	m_pRayGround->GetCollider()->GetVecRay().push_back(Vec2(vTemp.x - 16.f, vTemp.y));
	m_pRayGround->GetCollider()->GetVecRay().push_back(Vec2(vTemp.x + 16.f, vTemp.y));
	CreateObject(m_pRayGround, GROUP_TYPE::GROUND);
}

