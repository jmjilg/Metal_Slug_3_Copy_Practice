#include "CFlying_Killer.h"
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

void CFlying_Killer::update_animation()
{
	MON_STATE eCurState = m_pAI->GetCurState()->GetType();

	GetAnimator()->SetTransParentColor(153, 217, 234); // 무시할 RGB값 설정

	switch (eCurState)
	{

	case MON_STATE::BOUNCE:
			GetAnimator()->PlayL(L"FLYING_KILLER_JUMPING", true);

		break;
	case MON_STATE::RUSH:
			GetAnimator()->PlayL(L"FLYING_KILLER_ATTACKING", true);

		break;
	case MON_STATE::DEAD:
			GetAnimator()->PlayL(L"FLYING_KILLER_DEATH", false);

		break;
	}

}
