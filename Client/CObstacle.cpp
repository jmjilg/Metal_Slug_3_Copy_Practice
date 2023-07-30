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
	GetCollider()->SetObstacle(true); // �浹ü ������ ���� �Ķ������� �ٲ�
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

		if (vObjPos.y + vObjScale.y / 2.f >= vPos.y - vScale.y / 2.f) // ���� ��ֹ� ���� �ִٸ� ����
			return;

		float fLen = abs(vObjPos.x - vPos.x);
		float fValue = (vObjScale.x / 2.f + vScale.x / 2.f) - fLen;

		// �浹�� ���ѻ��·� �����ϱ� ���ؼ� �Ϻη� 1�ȼ� �� �÷���
		vObjPos = pOtherObj->GetPos();
		if(vObjPos.x < vPos.x)   // ������Ʈ�� ��ֹ� ���ʿ� �ִٸ�
			vObjPos.x -= fValue;
		else
			vObjPos.x += fValue; // �����ʿ� �ִٸ�

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

		if (vObjPos.y + vObjScale.y / 2.f <= vPos.y - vScale.y / 2.f) // ���� ��ֹ� ���� �ִٸ� ����
			return;

		float fLen = abs(vObjPos.x - vPos.x);
		float fValue = (vObjScale.x / 2.f + vScale.x / 2.f) - fLen;

		// �浹�� ���ѻ��·� �����ϱ� ���ؼ� �Ϻη� 1�ȼ� �� �÷���
		vObjPos = pOtherObj->GetPos();
		if (vObjPos.x < vPos.x)   // ������Ʈ�� ��ֹ� ���ʿ� �ִٸ�
			vObjPos.x -= fValue;
		else
			vObjPos.x += fValue; // �����ʿ� �ִٸ�

		pOtherObj->SetPos(vObjPos);
	}
}

void CObstacle::OnCollisionExit(CCollider* _pOther)
{
}
