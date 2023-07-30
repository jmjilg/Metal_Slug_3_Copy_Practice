#include "CObstacle.h"

#include "CCollider.h"
#include "CGravity.h"
#include "SelectGDI.h"

CObstacle::CObstacle()
{
}

CObstacle::~CObstacle()
{
}

void CObstacle::start()
{
	CreateCollider();	
	GetCollider()->SetScale(Vec2(GetScale()));
	GetCollider()->SetObstacle(true); // 충돌체 렌더링 색을 파랑색으로 바꿈
}

void CObstacle::update()
{
	
}

void CObstacle::render(HDC _dc)
{
	component_render(_dc);
}

void CObstacle::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Player" || pOtherObj->GetName() == L"Monster" || pOtherObj->GetName() == L"Captive")
	{
		Vec2 vObjPos = _pOther->GetFinalPos();
		Vec2 vObjScale = _pOther->GetScale();

		Vec2 vPos = GetCollider()->GetFinalPos();
		Vec2 vScale = GetCollider()->GetScale();

		if (vObjPos.y + vObjScale.y / 2.f >= vPos.y - vScale.y / 2.f) // 만약 장애물 위에 있다면 리턴
			return;

		float fLen = abs(vObjPos.x - vPos.x);
		float fValue = (vObjScale.x / 2.f + vScale.x / 2.f) - fLen;

		// 충돌을 접한상태로 유지하기 위해서 일부로 1픽셀 덜 올려줌
		vObjPos = pOtherObj->GetPos();
		if(vObjPos.x < vPos.x)   // 오브젝트가 장애물 왼쪽에 있다면
			vObjPos.x -= fValue;
		else
			vObjPos.x += fValue; // 오른쪽에 있다면

		pOtherObj->SetPos(vObjPos);
	}
}

void CObstacle::OnCollision(CCollider* _pOther)
{

	CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Player" || pOtherObj->GetName() == L"Monster" || pOtherObj->GetName() == L"Captive")
	{
		Vec2 vObjPos = _pOther->GetFinalPos();
		Vec2 vObjScale = _pOther->GetScale();

		Vec2 vPos = GetCollider()->GetFinalPos();
		Vec2 vScale = GetCollider()->GetScale();

		if (vObjPos.y + vObjScale.y / 2.f <= vPos.y - vScale.y / 2.f) // 만약 장애물 위에 있다면 리턴
			return;

		float fLen = abs(vObjPos.x - vPos.x);
		float fValue = (vObjScale.x / 2.f + vScale.x / 2.f) - fLen;

		// 충돌을 접한상태로 유지하기 위해서 일부로 1픽셀 덜 올려줌
		vObjPos = pOtherObj->GetPos();
		if (vObjPos.x < vPos.x)   // 오브젝트가 장애물 왼쪽에 있다면
			vObjPos.x -= fValue;
		else
			vObjPos.x += fValue; // 오른쪽에 있다면

		pOtherObj->SetPos(vObjPos);
	}
}

void CObstacle::OnCollisionExit(CCollider* _pOther)
{
}
