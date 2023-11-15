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
		CCamera::GetInst()->SetLookAt(vRenderCamera); // ī�޶��� ��ġ�� ������ �ӵ��� �������� �̵���
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
	else if (GetMonster()->GetName() == L"Chowmein_Conga") // �߹������ ���
	{
		// Player �� ��ġ üũ
		CPlayer* pPlayer = (CPlayer*)CSceneMgr::GetInst()->GetCurScene()->GetPlayer();
		Vec2 vPlayerPos = pPlayer->GetPos();

		// ������ ���� �ȿ� ������ �������·� ��ȯ
		CMonster* pMonster = GetMonster();
		Vec2 vMonPos = pMonster->GetPos();

		Vec2 vDiff = vPlayerPos - vMonPos;
		float fLen = vDiff.Length();

		// �÷��̾ ������ �νĹ��� ������ ����
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
