#include "pch.h"
#include "CAppearState.h"

#include "CSceneMgr.h"
#include "CScene.h"

#include "CPlayer.h"
#include "CMonster.h"

#include "CTimeMgr.h"

CAppearState::CAppearState()
	: CState(MON_STATE::APPEAR)
{

}

CAppearState::~CAppearState()
{
}

void CAppearState::update()
{

	// AppearState은 보스 몬스터의 등장 모션을 정의하기 위해 만든 상태이다.

	wstring wstr = GetMonster()->GetName();


	if (GetMonster()->GetName() == L"Huge_Hermit")
	{
		Vec2 vMonPos = GetMonster()->GetPos();
		vMonPos.y = vMonPos.y - GetMonster()->GetInfo().fSpeed * 7.f * fDT;

		GetMonster()->SetPos(vMonPos);

		if (vMonPos.y <= 134.f)
		{
			ChangeAIState(GetAI(), MON_STATE::IDLE);
		}
	}

}

void CAppearState::Enter()
{
}

void CAppearState::Exit()
{
}
