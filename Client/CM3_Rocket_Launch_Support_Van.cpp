#include "CM3_Rocket_Launch_Support_Van.h"
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

CM3_Rocket_Launch_Support_Van::CM3_Rocket_Launch_Support_Van()
{
}

CM3_Rocket_Launch_Support_Van::~CM3_Rocket_Launch_Support_Van()
{
	DeleteObject(m_pRelatedObj);
}


void CM3_Rocket_Launch_Support_Van::update_animation()
{
	MON_STATE eCurState = m_pAI->GetCurState()->GetType();

	GetAnimator()->SetTransParentColor(248, 0, 248); // 무시할 RGB값 설정

	switch (eCurState)
	{
	case MON_STATE::IDLE:
		GetAnimator()->PlayL(L"M3_ROCKET_LAUNCH_SUPPORT_VAN_IDLE", true);
		break;
	case MON_STATE::FIRING:
		GetAnimator()->PlayL(L"M3_ROCKET_LAUNCH_SUPPORT_VAN_FIRING", true);
		break;
	case MON_STATE::DEAD:
		GetAnimator()->PlayL(L"M3_ROCKET_LAUNCH_SUPPORT_VAN_DEAD", false);
		break;
	}

}

void CM3_Rocket_Launch_Support_Van::OnCollision(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();


	if (pOtherObj->GetName() == L"SlugTransport") // 로켓 런쳐 벤과 부딪혔을 때
	{
		SetContact(true);
	}
}
