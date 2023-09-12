#include "CM3_Missile.h"
#include "CRes.h"
#include "CResMgr.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CCollider.h"
#include "CScene.h"
#include "CMonster.h"
#include "AI.h"
#include "CState.h"
#include "CSceneMgr.h"
#include "CPlayer.h"
#include "CTimeMgr.h"
#include "CCore.h"
#include "CCamera.h"

void CM3_Missile::update()
{
	Vec2 vPos = GetPos();
	vPos.y += GetInfo().fSpeed * fDT;
	SetPos(vPos);

	m_tInfo.lAttAcc = clock() - m_tInfo.lAttStart; // 공격을 한 시점으로부터 얼마나 지났나

	if (nullptr != m_pAI)
		m_pAI->update();

	GetAnimator()->SetTransParentColor(248, 0, 248); // 무시할 RGB값 설정

	GetAnimator()->update();

	update_animation();

	Vec2 vResolution = CCore::GetInst()->GetResolution();
	vPos = CCamera::GetInst()->GetRenderPos(vPos);


	if ((vPos.x < 0) || (vPos.x > vResolution.x) || (vPos.y < 0) || (vPos.y > vResolution.y))
		DeleteObject(this);

}

void CM3_Missile::update_animation()
{
	MON_STATE eCurState = m_pAI->GetCurState()->GetType();

	GetAnimator()->SetTransParentColor(248, 0, 248); // 무시할 RGB값 설정

	switch (eCurState)
	{
	case MON_STATE::IDLE:
		GetAnimator()->PlayL(L"M3_ROCKET_LAUNCH_SUPPORT_VAN_PROJECTILES", true);
		break;
	case MON_STATE::DEAD:
		GetAnimator()->PlayL(L"M3_ROCKET_LAUNCH_SUPPORT_VAN_DEAD", false);
		break;
	}

}

void CM3_Missile::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Player")
	{
		CPlayer* pPlayer = (CPlayer*)CSceneMgr::GetInst()->GetCurScene()->GetPlayer();
		pPlayer->SetAttacked(true);
		ChangeAIState(m_pAI, MON_STATE::DEAD);
	}

	if (pOtherObj->GetName() == L"Missile_Player")
	{
		m_tInfo.fHP -= 1;
		if (m_tInfo.fHP <= 0)
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
