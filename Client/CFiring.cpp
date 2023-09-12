#include "pch.h"
#include "CSceneMgr.h"
#include "CScene.h"

#include "CPlayer.h"
#include "CMonster.h"

#include "CTimeMgr.h"
#include "CFiring.h"

#include "CAnimation.h"
#include "CAnimator.h"
#include "AI.h"



CFiring::CFiring()
	: CState(MON_STATE::FIRING)
	, lRespawnStart(0.f)
	, lRespawnAcc(0.f)
	, m_bRespawn(false)
	, m_iRespawnCount(0)
{
	srand((unsigned int)time(NULL));
}

CFiring::~CFiring()
{
}

void CFiring::update()
{
	CAnimation* pCurAnim = GetAI()->GetOwner()->GetAnimator()->GetCurAnimL();


	lRespawnAcc = clock();

	if (lRespawnAcc - lRespawnStart >= 500.f) // 0.5段原陥 持失
	{

		// Vec2(200.f, 200.f) SlugTransport Collider Size
		// Vec2(100.f, 70.f) M3 Collider Size

		Vec2 vTemp = GetMonster()->GetPos();
		vTemp.x = vTemp.x - 245 + (rand() / 200);
		vTemp.y -= 150;
		CMonster* pMon = CMonFactory::CreateMonster(MON_TYPE::M3_ROCKET_LAUNCH_SUPPORT_VAN_MISSILE, vTemp);
		CreateObject((CObject*)pMon, GROUP_TYPE::MONSTER);

		lRespawnStart = lRespawnAcc;
	}

	if (GetMonster()->GetInfo().lAttAcc > 5000) // pCurAnim->GetCurFrame() == 12
	{
		pCurAnim->SetFrame(0);
		ChangeAIState(GetAI(), MON_STATE::IDLE);
		GetMonster()->SetAttAcc(0);
		GetMonster()->SetAttStart(clock());
	}
}

void CFiring::Enter()
{
}

void CFiring::Exit()
{
}
