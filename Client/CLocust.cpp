#include "pch.h"
#include "CMonster.h"

#include "AI.h"

#include "CCollider.h"
#include "CTimeMgr.h"
#include "CAnimator.h"
#include "CIdleState.h"
#include "CState.h"
#include "CRes.h"
#include "CResMgr.h"
#include "CLocust.h"

CLocust::CLocust()
	:m_vNextPos(Vec2(0.f, 0.f))
{
	
}

CLocust::~CLocust()
{
}

void CLocust::update_animation()
{
	MON_STATE eCurState = m_pAI->GetCurState()->GetType();

	switch (eCurState)
	{

	case MON_STATE::FLYING:
		if (m_tInfo.iDir == -1)
			GetAnimator()->PlayL(L"LOCUST_FLYING_LEFT", true);
		else
			GetAnimator()->PlayL(L"LOCUST_FLYING_RIGHT", true);		
		break;

	case MON_STATE::KIDNAPPING:
		if (m_tInfo.iDir == -1)
			GetAnimator()->PlayL(L"LOCUST_ATTACK_LEFT", true);
		else
			GetAnimator()->PlayL(L"LOCUST_ATTACK_RIGHT", true);
		break;

	case MON_STATE::DEAD:
		if (m_tInfo.iDir == -1)
			GetAnimator()->PlayL(L"LOCUST_DIE_LEFT", true);
		else
			GetAnimator()->PlayL(L"LOCUST_DIE_RIGHT", true);
		break;

	}

}
