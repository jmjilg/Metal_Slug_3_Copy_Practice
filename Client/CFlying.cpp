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
	// Player �� ��ġ üũ
	CPlayer* pPlayer = (CPlayer*)CSceneMgr::GetInst()->GetCurScene()->GetPlayer();
	Vec2 vPlayerPos = pPlayer->GetPos();

	// ������ ���� �ȿ� ������ �������·� ��ȯ
	CMonster* pMonster = GetMonster();
	Vec2 vMonPos = pMonster->GetPos();

	Vec2 vDiff = vPlayerPos - vMonPos;
	float fLen = vDiff.Length();

	// �����ð� �� �÷��̾�� �����Ϸ� �ٰ���
	if (GetMonster()->GetInfo().lAttAcc > 5000 && (vPlayerPos.x >= 2450 && vPlayerPos.x <= 2660))
	{
		//x���� 2450 ~2660, y���� 40 ~60 ���̿����� ��Ʈ����
		pMonster->SetSpeed(200.f); // �����Ҷ� �ӵ��� 2�� ������
		pMonster->SetOrigPos(vMonPos); // ������ ���ƿ� ���� ��ġ ����
		pMonster->SetKidnappingPos(vPlayerPos); // ������ ���ƿ� ���� ��ġ ����
		ChangeAIState(GetAI(), MON_STATE::KIDNAPPING);
	}

	Vec2 vNextPos = pMonster->GetInfo().vNextPos;

	if ((vNextPos - vMonPos).Length() <= 4.f && GetMonster()->GetInfo().lAttAcc > 1000) // ���Ͱ� ������ ��Ʈ�ѿ� �������� ��, �׸��� �װ��� ���ʰ� ������ �־��� ��
	{
		vNextPos = Vec2(rand() % 210 + 2450, rand() % 20 + 40); // x���� 2450 ~ 2660 , y���� 40 ~ 60 ���̿����� ��Ʈ����
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
