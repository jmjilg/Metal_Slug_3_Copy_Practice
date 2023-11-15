#include "pch.h"
#include "CIdleState.h"

#include "CSceneMgr.h"
#include "CScene.h"

#include "CPlayer.h"
#include "CMonster.h"

#include "CTimeMgr.h"

CIdleState::CIdleState()
	: CState(MON_STATE::IDLE)
{
}

CIdleState::~CIdleState()
{
}

void CIdleState::update()
{
	wstring wstr = GetMonster()->GetName();

	
	if (GetMonster()->GetName() == L"Huge_Hermit")
	{
		Vec2 vMonPos = GetMonster()->GetPos();
		vMonPos.x = vMonPos.x + GetMonster()->GetInfo().fSpeed * fDT;

		GetMonster()->SetPos(vMonPos);

		Vec2 vRenderCamera = vMonPos;
		vRenderCamera.x += 257.f;//257.f; // m_fCorrection_Value_X
		vRenderCamera.y += 80.f; //25.f; // m_fCorrection_Value_Y
		CCamera::GetInst()->SetLookAt(vRenderCamera); // 카메라의 위치가 일정한 속도로 좌측으로 이동함
	}

	if (GetMonster()->GetName() == L"M3_Rocket_Launch_Support_Van")
	{
		if (GetMonster()->GetInfo().lAttAcc > 5000 && GetMonster()->GetInfo().bContact)
		{
			GetMonster()->SetAttAcc(0);
			GetMonster()->SetAttStart(clock());
			ChangeAIState(GetAI(), MON_STATE::FIRING);
		}
	}
	else if (GetMonster()->GetName() == L"Chowmein_Conga") // 중밍콩게의 경우
	{
		// Player 의 위치 체크
		CPlayer* pPlayer = (CPlayer*)CSceneMgr::GetInst()->GetCurScene()->GetPlayer();
		Vec2 vPlayerPos = pPlayer->GetPos();

		// 몬스터의 범위 안에 들어오면 추적상태로 전환
		CMonster* pMonster = GetMonster();
		Vec2 vMonPos = pMonster->GetPos();

		Vec2 vDiff = vPlayerPos - vMonPos;
		float fLen = vDiff.Length();

		// 플레이어가 몬스터의 인식범위 안으로 진입
		if (fLen < pMonster->GetInfo().fRecogRange && GetMonster()->GetInfo().lAttAcc > 2000)
		{
			ChangeAIState(GetAI(), MON_STATE::TRACE);
		}
	}
}

void CIdleState::Enter()
{
}

void CIdleState::Exit()
{
}
