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

	// AppearState�� ���� ������ ���� ����� �����ϱ� ���� ���� �����̴�.

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
