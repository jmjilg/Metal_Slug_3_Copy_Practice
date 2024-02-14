#include "pch.h"
#include "CSceneMgr.h"
#include "CScene.h"

#include "CPlayer.h"
#include "CMonster.h"

#include "CTimeMgr.h"
#include "CRush.h"

CRush::CRush()
	: CState(MON_STATE::RUSH)
{
}

CRush::~CRush()
{
}

void CRush::update()
{
	Vec2 vMonPos = GetMonster()->GetPos();

	vMonPos.x = vMonPos.x + GetMonster()->GetInfo().iDir * GetMonster()->GetInfo().fSpeed * fDT;

	GetMonster()->SetPos(vMonPos);



	CPlayer* pPlayer = (CPlayer*)CSceneMgr::GetInst()->GetCurScene()->GetPlayer();
	Vec2 vPlayerPos = pPlayer->GetPos();

	float fDistanceX = (abs(vPlayerPos.x - vMonPos.x) / 2);
	float fDistanceY = (abs(vPlayerPos.y - vMonPos.y) / 2);
	float fAttRangeX = GetMonster()->GetInfo().vAttRange.x / 2;
	float fAttRangeY = GetMonster()->GetInfo().vAttRange.y / 2;


	if (fDistanceX < fAttRangeX && fDistanceY < fAttRangeY) // 플레이어가 몬스터의 공격 범위 안에 있을때
	{
		pPlayer->SetAttacked(true);
		ChangeAIState(GetAI(), MON_STATE::DEAD);
	}
}

void CRush::Enter()
{
}

void CRush::Exit()
{
}
