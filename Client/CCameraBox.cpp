#include "CCameraBox.h"

#include "CCollider.h"
#include "CGravity.h"
#include "CCamera.h"

CCameraBox::CCameraBox()
	: m_fCorrection_Value_X(257.f) 
	, m_fCorrection_Value_Y(186.f)
	, m_bTracePlayer(true)
{
	CreateCollider();
}

CCameraBox::~CCameraBox()
{
}

void CCameraBox::start()
{
	GetCollider()->SetScale(Vec2(GetScale()));
	
}

void CCameraBox::update()
{
	
}

void CCameraBox::render(HDC _dc)
{
	component_render(_dc);
}

void CCameraBox::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Player")
	{
		Vec2 vObjPos = _pOther->GetFinalPos();
		Vec2 vObjScale = _pOther->GetScale();

		Vec2 vPos = GetCollider()->GetFinalPos();
		Vec2 vScale = GetCollider()->GetScale();

		float fLen = abs(vObjPos.x - vPos.x);

		// 플레이어가 박스 바깥으로 이동한 만큼 카메라도 움직임. 단, x축으로만
		if (vObjPos.x > vPos.x)
		{
			if (m_bTracePlayer)
			{
				Vec2 vCameraBoxPos = GetPos();
				vCameraBoxPos.x += fLen;
				SetPos(vCameraBoxPos);
				CCamera::GetInst()->SetLookAt(Vec2(vCameraBoxPos.x + m_fCorrection_Value_X, m_fCorrection_Value_Y)); // 417인데 변수로 해서 바뀔수 있도록
			}
		}
	}
}

void CCameraBox::OnCollision(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Player")
	{
		Vec2 vObjPos = _pOther->GetFinalPos();
		Vec2 vObjScale = _pOther->GetScale();

		Vec2 vPos = GetCollider()->GetFinalPos();
		Vec2 vScale = GetCollider()->GetScale();

		float fLen = abs(vObjPos.x - vPos.x);

		// 플레이어가 박스 바깥으로 이동한 만큼 카메라도 움직임. 단, x축으로만
		if (vObjPos.x > vPos.x)
		{
			if (m_bTracePlayer)
			{
				Vec2 vCameraBoxPos = GetPos();
				vCameraBoxPos.x += fLen;
				SetPos(vCameraBoxPos);
				CCamera::GetInst()->SetLookAt(Vec2(vCameraBoxPos.x + m_fCorrection_Value_X, m_fCorrection_Value_Y)); // 417인데 변수로 해서 바뀔수 있도록
			}
		}
	}

}

void CCameraBox::OnCollisionExit(CCollider* _pOther)
{
}
