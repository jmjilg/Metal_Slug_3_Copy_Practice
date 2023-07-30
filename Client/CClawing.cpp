#include "pch.h"
#include "CClawing.h"
#include "CIdleState.h"

#include "CSceneMgr.h"
#include "CScene.h"

#include "CPlayer.h"
#include "CMonster.h"
#include "AI.h"
#include "CAnimator.h"
#include "CAnimation.h"

CClawing::CClawing()
	: CState(MON_STATE::CLAWING)
{
}

CClawing::~CClawing()
{
}

void CClawing::update()
{

	CPlayer* pPlayer = (CPlayer*)CSceneMgr::GetInst()->GetCurScene()->GetPlayer();
	Vec2 vPlayerPos = pPlayer->GetPos();
	Vec2 vMonPos = GetMonster()->GetPos();


	CAnimation* pCurAnim = GetAI()->GetOwner()->GetAnimator()->GetCurAnimL();
	if (pCurAnim->GetCurFrame() == 12)
	{
		pCurAnim->SetFrame(0);
		ChangeAIState(GetAI(), MON_STATE::IDLE);
		GetMonster()->SetAttAcc(0);
		GetMonster()->SetAttStart(clock());
	}

	if ((pCurAnim->GetCurFrame() == 8) ) // 집게발로 찍었을때, 플레이어가 그 찍는 범위 안에 있으면
	{
		float fDistanceX = (abs(vPlayerPos.x - vMonPos.x) / 2);
		float fDistanceY = (abs(vPlayerPos.y - vMonPos.y) / 2);
		float fAttRangeX = GetMonster()->GetInfo().fAttRange.x / 2;
		float fAttRangeY = GetMonster()->GetInfo().fAttRange.y / 2;
		
		if (fDistanceX < fAttRangeX && fDistanceY < fAttRangeY)
			pPlayer->SetAttacked(true);
	}

}

void CClawing::Enter()
{
}

void CClawing::Exit()
{
}
