#include "CRayGround.h"

#include "CCollider.h"
#include "CGravity.h"

CRayGround::CRayGround()
{
	CreateCollider();
	GetCollider()->SetIsRay(true);

}

CRayGround::~CRayGround()
{
}

void CRayGround::start()
{
	GetCollider()->SetScale(Vec2(GetScale()));
	GetCollider()->SetIsRay(true);
}

void CRayGround::update()
{

}

void CRayGround::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Player")// || 직선 충돌체와 부딪혓을때)
	{
		pOtherObj->GetGravity()->SetGround(true);

		Vec2 vObjPos = _pOther->GetFinalPos();
		Vec2 vObjScale = _pOther->GetScale();

		Vec2 vPos = GetCollider()->GetH();
		Vec2 vScale = GetCollider()->GetScale();

		float fLen = abs(vObjPos.y - vPos.y);
		float fValue = (vObjScale.y / 2.f) - fLen + 1;

		// 충돌을 접한상태로 유지하기 위해서 일부로 1픽셀 덜 올려줌
		vObjPos = pOtherObj->GetPos();
		vObjPos.y -= fValue;

		pOtherObj->SetPos(vObjPos);
	}
}

void CRayGround::OnCollision(CCollider* _pOther)
{

	CObject* pOtherObj = _pOther->GetObj();

	wstring temp = pOtherObj->GetName();
	
	if (temp == L"Player" || temp == L"Chowmein_Conga" || temp == L"Locust" ||  temp == L"Captive" || temp == L"Supplies")// || 직선 충돌체와 부딪혓을때)
	{
		pOtherObj->GetGravity()->SetGround(true);

		Vec2 vObjPos = _pOther->GetFinalPos();
		Vec2 vObjScale = _pOther->GetScale();

		Vec2 vPos = GetCollider()->GetH();
		Vec2 vScale = GetCollider()->GetScale();

		float fLen = abs(vObjPos.y - vPos.y);
		float fValue = (vObjScale.y / 2.f) - fLen + 1;

		// 충돌을 접한상태로 유지하기 위해서 일부로 1픽셀 덜 올려줌
		vObjPos = pOtherObj->GetPos();
		vObjPos.y -= fValue;

		pOtherObj->SetPos(vObjPos);

	}

}

void CRayGround::OnCollisionExit(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Player")
	{
		pOtherObj->GetGravity()->SetGround(false);

	}
}

bool CRayGround::IsOnRay()
{
	return false;
}
