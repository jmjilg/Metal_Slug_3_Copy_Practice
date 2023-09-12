#include "pch.h"
#include "CBounce.h"
#include "CSceneMgr.h"
#include "CScene.h"

#include "CPlayer.h"
#include "CMonster.h"

#include "CTimeMgr.h"

CBounce::CBounce()
	: CState(MON_STATE::BOUNCE)
{
}

CBounce::~CBounce()
{
}

void CBounce::update()
{
	// 타겟팅 된 Player 를 쫒아간다.
	CPlayer* pPlayer = (CPlayer*)CSceneMgr::GetInst()->GetCurScene()->GetPlayer();
	Vec2 vPlayerPos = pPlayer->GetPos();
	Vec2 vMonPos = GetMonster()->GetPos();

	Vec2 vMonDir = vPlayerPos - vMonPos;
	vMonDir.Normalize();
	if (vMonDir.y < 0)
		GetMonster()->SetDir(-1);
	else
		GetMonster()->SetDir(1);

	vMonPos.y = vMonPos.y + vMonDir.y * 2; // 원래는 5가 아니라 GetMonster()->GetInfo().fSpeed * fDT 이게 맞는건데
	// 올라오는 속도가 너무 느려서 상수값으로 조정시켰음

	GetMonster()->SetPos(vMonPos);


	float fHeight = vPlayerPos.y - vMonPos.y;
	//long temp = GetMonster()->GetInfo().lAttAcc;

	// 플레이어가 몬스터와 동일한 높이에 위치
	if (abs(fHeight) <= 15.f)
	{
		ChangeAIState(GetAI(), MON_STATE::RUSH);
	}
}

void CBounce::Enter()
{
}

void CBounce::Exit()
{
}
