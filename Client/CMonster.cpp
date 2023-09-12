#include "pch.h"
#include "CMonster.h"

#include "AI.h"

#include "CCollider.h"
#include "CTimeMgr.h"
#include "CAnimator.h"
#include "CIdleState.h"
#include "AI.h"
#include "CState.h"
#include "CRes.h"
#include "CResMgr.h"
#include "SelectGDI.h"
#include "time.h"

CMonster::CMonster()
	: m_tInfo{}
	, m_pRelatedObj(nullptr)
{

}

CMonster::~CMonster()
{
	if (nullptr != m_pAI)
		delete m_pAI;
}

void CMonster::update()
{	
	m_tInfo.lAttAcc = clock() - m_tInfo.lAttStart; // 공격을 한 시점으로부터 얼마나 지났나

	if(nullptr != m_pAI)
		m_pAI->update();

	GetAnimator()->SetTransParentColor(255, 255, 255); // 무시할 RGB값 설정

	GetAnimator()->update();

	update_animation();
}

void CMonster::render(HDC _dc)
{
	component_render(_dc);


	if (m_bColliderRender)
	{
		PEN_TYPE ePen = PEN_TYPE::BLUE;

		//if (m_iCol)
		//	ePen = PEN_TYPE::RED;

		SelectGDI p(_dc, ePen);
		SelectGDI b(_dc, BRUSH_TYPE::HOLLOW);

		Vec2 vFinalPos = GetCollider()->GetFinalPos();

		Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(vFinalPos);


		Rectangle(_dc
			, (int)(vRenderPos.x - m_tInfo.fAttRange.x / 2.f)
			, (int)(vRenderPos.y - m_tInfo.fAttRange.y / 2.f)
			, (int)(vRenderPos.x + m_tInfo.fAttRange.x / 2.f)
			, (int)(vRenderPos.y + m_tInfo.fAttRange.y / 2.f));
	}

}


void CMonster::SetAI(AI* _AI)
{
	m_pAI = _AI;
	m_pAI->m_pOwner = this;
}

void CMonster::update_animation()
{
}

void CMonster::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Missile_Player")
	{
		m_tInfo.fHP -= 1;
		if (m_tInfo.fHP < 0 && !(m_pAI->GetCurState()->GetType() == MON_STATE::DEAD))
		{
			m_pAI->GetOwner()->GetCollider()->SetDead(true);
			if (nullptr != GetObstacle())
			{
				DeleteObject(GetObstacle());
			}
			ChangeAIState(m_pAI, MON_STATE::DEAD);
		}
	}

}
