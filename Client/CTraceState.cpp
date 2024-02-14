#include "pch.h"
#include "CTraceState.h"

#include "CSceneMgr.h"
#include "CScene.h"

#include "CPlayer.h"
#include "CMonster.h"

#include "CTimeMgr.h"

CTraceState::CTraceState()
	: CState(MON_STATE::TRACE)
{
}

CTraceState::~CTraceState()
{
}

void CTraceState::update()
{
	// 타겟팅 된 Player 를 쫒아간다.
	CPlayer* pPlayer = (CPlayer*)CSceneMgr::GetInst()->GetCurScene()->GetPlayer();
	Vec2 vPlayerPos = pPlayer->GetPos();
	Vec2 vMonPos = GetMonster()->GetPos();

	Vec2 vMonDir = vPlayerPos - vMonPos;
	vMonDir.Normalize();
	if (vMonDir.x < 0)
		GetMonster()->SetDir(-1);
	else
		GetMonster()->SetDir(1);

	vMonPos.x = vMonPos.x + vMonDir.x * GetMonster()->GetInfo().fSpeed * fDT;

	GetMonster()->SetPos(vMonPos);


	Vec2 vDiff = vPlayerPos - vMonPos;
	float fLen = vDiff.Length();
	//long temp = GetMonster()->GetInfo().lAttAcc;

	// 플레이어가 몬스터의 공격범위범위 안으로 진입
	if (fLen < GetMonster()->GetInfo().vAttRange.x && GetMonster()->GetInfo().lAttAcc > 4000)
	{
		ChangeAIState(GetAI(), MON_STATE::CLAWING);
	}
}

void CTraceState::Enter()
{
}

void CTraceState::Exit()
{
}
