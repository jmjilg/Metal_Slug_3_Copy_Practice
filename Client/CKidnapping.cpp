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
	// Ÿ���� �� Player �� �i�ư���.
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


	// ���Թ߷� �������, �÷��̾ �� ��� ���� �ȿ� ������

		float fDistanceX = (abs(vPlayerPos.x - vMonPos.x) / 2);
		float fDistanceY = (abs(vPlayerPos.y - vMonPos.y) / 2);
		float fAttRangeX = GetMonster()->GetInfo().vAttRange.x / 2;
		float fAttRangeY = GetMonster()->GetInfo().vAttRange.y / 2;


		if (fDistanceX < fAttRangeX && fDistanceY < fAttRangeY) // �÷��̾ ������ ���� ���� �ȿ� ������
		{
			pPlayer->SetAttacked(true);
			ChangeAIState(GetAI(), MON_STATE::FLYING); // ���� �� �ٽ� �⺻ ���·� ���ư���
			GetMonster()->SetAttAcc(0);
			GetMonster()->SetAttStart(clock());
			pMonster->SetSpeed(100.f); 
		}		
		else if (vDiff.Length() <= 0.5f) // ���Ͱ� ���� �������� �������� ��
		{
			ChangeAIState(GetAI(), MON_STATE::FLYING); // �⺻ ���·� ���ư���
			GetMonster()->SetAttAcc(0);
			GetMonster()->SetAttStart(clock());
			pMonster->SetSpeed(100.f);
		}




	// �÷��̾ ������ ���ݹ������� ������ ����
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
