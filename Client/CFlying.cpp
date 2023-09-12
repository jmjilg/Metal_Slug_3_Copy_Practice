#include "pch.h"

#include "CSceneMgr.h"
#include "CScene.h"

#include "CPlayer.h"
#include "CMonster.h"

#include "CTimeMgr.h"
#include "CFlying.h"


CFlying::CFlying()
	: CState(MON_STATE::FLYING)
{
	srand((unsigned int)time(NULL));
}

CFlying::~CFlying()
{
}

void CFlying::update()
{
	// Player 의 위치 체크
	CPlayer* pPlayer = (CPlayer*)CSceneMgr::GetInst()->GetCurScene()->GetPlayer();
	Vec2 vPlayerPos = pPlayer->GetPos();

	// 몬스터의 범위 안에 들어오면 추적상태로 전환
	CMonster* pMonster = GetMonster();
	Vec2 vMonPos = pMonster->GetPos();

	Vec2 vDiff = vPlayerPos - vMonPos;
	float fLen = vDiff.Length();

	// 일정시간 후 플레이어에게 공격하러 다가감
	if (GetMonster()->GetInfo().lAttAcc > 5000 && (vPlayerPos.x >= 2450 && vPlayerPos.x <= 2660))
	{
		//x축은 2450 ~2660, y축은 40 ~60 사이에서만 패트롤함
		pMonster->SetSpeed(200.f); // 공격할땐 속도가 2배 빨라짐
		pMonster->SetOrigPos(vMonPos); // 공격후 돌아올 원래 위치 저장
		pMonster->SetKidnappingPos(vPlayerPos); // 공격후 돌아올 원래 위치 저장
		ChangeAIState(GetAI(), MON_STATE::KIDNAPPING);
	}

	Vec2 vNextPos = pMonster->GetInfo().vNextPos;

	if ((vNextPos - vMonPos).Length() <= 4.f && GetMonster()->GetInfo().lAttAcc > 1000) // 몬스터가 목적지 패트롤에 도착했을 때, 그리고 그곳에 몇초간 가만히 있었을 때
	{
		vNextPos = Vec2(rand() % 210 + 2450, rand() % 20 + 40); // x축은 2450 ~ 2660 , y축은 40 ~ 60 사이에서만 패트롤함
		pMonster->SetNextPos(vNextPos);
	}

	else
	{
		Vec2 vMonDir = vNextPos - vMonPos;
		vMonDir.Normalize();

		vMonPos = vMonPos + vMonDir * GetMonster()->GetInfo().fSpeed * fDT;
		
		GetMonster()->SetPos(vMonPos);
	}


}

void CFlying::Enter()
{
}

void CFlying::Exit()
{
}
