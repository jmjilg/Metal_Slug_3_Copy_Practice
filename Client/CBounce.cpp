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
	// Ÿ���� �� Player �� �i�ư���.
	CPlayer* pPlayer = (CPlayer*)CSceneMgr::GetInst()->GetCurScene()->GetPlayer();
	Vec2 vPlayerPos = pPlayer->GetPos();
	Vec2 vMonPos = GetMonster()->GetPos();

	Vec2 vMonDir = vPlayerPos - vMonPos;
	vMonDir.Normalize();
	if (vMonDir.y < 0)
		GetMonster()->SetDir(-1);
	else
		GetMonster()->SetDir(1);

	vMonPos.y = vMonPos.y + vMonDir.y * 2; // ������ 5�� �ƴ϶� GetMonster()->GetInfo().fSpeed * fDT �̰� �´°ǵ�
	// �ö���� �ӵ��� �ʹ� ������ ��������� ����������

	GetMonster()->SetPos(vMonPos);


	float fHeight = vPlayerPos.y - vMonPos.y;
	//long temp = GetMonster()->GetInfo().lAttAcc;

	// �÷��̾ ���Ϳ� ������ ���̿� ��ġ
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
