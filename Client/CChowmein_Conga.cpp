#include "CChowmein_Conga.h"
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

void CChowmein_Conga::update_animation()
{
	MON_STATE eCurState = m_pAI->GetCurState()->GetType();

	switch (eCurState)
	{

	case MON_STATE::IDLE:
		if (m_tInfo.iDir == -1)
			GetAnimator()->PlayL(L"CHOWMEIN_CONGA_IDLE_LEFT", true);
		else
			GetAnimator()->PlayL(L"CHOWMEIN_CONGA_IDLE_RIGHT", true);

		break;
		
	case MON_STATE::TRACE:
		if (m_tInfo.iDir == -1)
			GetAnimator()->PlayL(L"CHOWMEIN_CONGA_WALKING_LEFT", true);
		else
			GetAnimator()->PlayL(L"CHOWMEIN_CONGA_WALKING_RIGHT", true);

		break;
		
	case MON_STATE::CLAWING:
		if (m_tInfo.iDir == -1)
			GetAnimator()->PlayL(L"CHOWMEIN_CONGA_ATTACK_LEFT", true);
		else
			GetAnimator()->PlayL(L"CHOWMEIN_CONGA_ATTACK_RIGHT", true);

		break;
		
	case MON_STATE::BUBBLE_FIRE:
		if (m_tInfo.iDir == -1)
			GetAnimator()->PlayL(L"CHOWMEIN_CONGA_SPIT_LEFT", true);
		else
			GetAnimator()->PlayL(L"CHOWMEIN_CONGA_SPIT_RIGHT", true);

		break;

	case MON_STATE::DEAD:
		if (m_tInfo.iDir == -1)
			GetAnimator()->PlayL(L"CHOWMEIN_CONGA_DEATH_LEFT", false);
		else
			GetAnimator()->PlayL(L"CHOWMEIN_CONGA_DEATH_RIGHT", false);

		break;
	}

}
