#include "CHuge_Hermit.h"
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

void CHuge_Hermit::update_animation()
{
	MON_STATE eCurState = m_pAI->GetCurState()->GetType();

	GetAnimator()->SetTransParentColor(248, 0, 248); // 무시할 RGB값 설정

	switch (eCurState)
	{
	case MON_STATE::APPEAR:
			GetAnimator()->PlayL(L"HUGE_HERMIT_IDLE", true);
		break;
		
	case MON_STATE::IDLE:
			GetAnimator()->PlayL(L"HUGE_HERMIT_IDLE", true);
		break;
		
	case MON_STATE::DESTROYED:
			GetAnimator()->PlayL(L"HUGE_HERMIT_DESTROYED", true);
		break;

	case MON_STATE::DEAD:
			GetAnimator()->PlayL(L"HUGE_HERMIT_DEAD", false);
		break;
	}

}


