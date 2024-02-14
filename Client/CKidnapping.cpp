#include "pch.h"
#include "CSceneMgr.h"
#include "CScene.h"

#include "CPlayer.h"
#include "CMonster.h"

#include "CTimeMgr.h"
#include "CKidnapping.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "AI.h"

CKidnapping::CKidnapping()
	: CState(MON_STATE::KIDNAPPING)
{
}

CKidnapping::~CKidnapping()
{
}


void CKidnapping::update()
{
	// 타겟팅 된 Player 를 쫒아간다.
	CPlayer* pPlayer = (CPlayer*)CSceneMgr::GetInst()->GetCurScene()->GetPlayer();
	Vec2 vPlayerPos = pPlayer->GetPos();
	Vec2 vMonPos = GetMonster()->GetPos();

	CMonster* pMonster = GetMonster();


	Vec2 vOrigPos = pMonster->GetInfo().vOrigPos;
	Vec2 vKidnappingPos = pMonster->GetInfo().vKidnappingPos;

	Vec2 vMonDir = vKidnappingPos - vMonPos;
	vMonDir.Normalize();

	if (vMonDir.x < 0)
		GetMonster()->SetDir(-1);
	else
		GetMonster()->SetDir(1);

	vMonPos = vMonPos + vMonDir * GetMonster()->GetInfo().fSpeed * fDT;

	GetMonster()->SetPos(vMonPos);


	Vec2 vDiff = vKidnappingPos - vMonPos;
	float fLen = vDiff.Length();
	//long temp = GetMonster()->GetInfo().lAttAcc;


	// 집게발로 찍었을때, 플레이어가 그 찍는 범위 안에 있으면

		float fDistanceX = (abs(vPlayerPos.x - vMonPos.x) / 2);
		float fDistanceY = (abs(vPlayerPos.y - vMonPos.y) / 2);
		float fAttRangeX = GetMonster()->GetInfo().vAttRange.x / 2;
		float fAttRangeY = GetMonster()->GetInfo().vAttRange.y / 2;


		if (fDistanceX < fAttRangeX && fDistanceY < fAttRangeY) // 플레이어가 몬스터의 공격 범위 안에 있을때
		{
			pPlayer->SetAttacked(true);
			ChangeAIState(GetAI(), MON_STATE::FLYING); // 공격 후 다시 기본 상태로 돌아간다
			GetMonster()->SetAttAcc(0);
			GetMonster()->SetAttStart(clock());
			pMonster->SetSpeed(100.f); 
		}		
		else if (vDiff.Length() <= 0.5f) // 몬스터가 공격 목적지에 도착했을 때
		{
			ChangeAIState(GetAI(), MON_STATE::FLYING); // 기본 상태로 돌아간다
			GetMonster()->SetAttAcc(0);
			GetMonster()->SetAttStart(clock());
			pMonster->SetSpeed(100.f);
		}




	// 플레이어가 몬스터의 공격범위범위 안으로 진입
	//if (fLen < GetMonster()->GetInfo().fAttRange.x && GetMonster()->GetInfo().lAttAcc > 4000)
	//{
	//	ChangeAIState(GetAI(), MON_STATE::CLAWING);
	//}
}

void CKidnapping::Enter()
{
}

void CKidnapping::Exit()
{
}
