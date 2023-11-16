
#include "pch.h"
#include "CIdleState.h"

#include "CSceneMgr.h"
#include "CScene.h"

#include "CPlayer.h"
#include "CMonster.h"
#include "CDeadState.h"
#include "AI.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CSound.h"
#include "CSoundMgr.h"
#include "CResMgr.h"

CDeadState::CDeadState()
	: CState(MON_STATE::DEAD)
{
}

CDeadState::~CDeadState()
{
}

void CDeadState::update()
{
	if (!GetMonster()->GetGravity())
		GetMonster()->CreateGravity();  // GetMonster()->GetInfo().eMonType == MON_TYPE::LOCUST 
	if (GetMonster()->GetName() == L"Huge_Hermit")  // ���� ���Ͱ� ������ �������� Ŭ���� ���� ���
	{
		CSound* pNewSound = CResMgr::GetInst()->FindSound(L"BGM_03"); // Stage Clear ���

		pNewSound->Play(); // ���ڷ� true�� �ָ� �ݺ����

		pNewSound->SetPosition(50.f); // ��з�, �Ҹ� ��ġ ����
		pNewSound->PlayToBGM(false); // ���ڷ� true�� �ָ� �ݺ����
		pNewSound->SetVolume(60.f);

	}

	CAnimation* anim = GetAI()->GetOwner()->GetAnimator()->GetCurAnimL();
	bool temp = GetAI()->GetOwner()->GetAnimator()->GetCurAnimL()->IsFinish();
	int iCurFrame = GetAI()->GetOwner()->GetAnimator()->GetCurAnimL()->GetCurFrame();
	if (temp || iCurFrame == 29)  // ����� ���� ��쿡�� IsFinish() �Լ��� �� �۵��Ǵµ�, �Ŵ� �޶ѱⰰ�� ��쿡�� �۵��� �� �ȵ�. �׷��� �ϴ� �ӽ÷� �̷��� �س���
		Exit();

}

void CDeadState::Enter()
{

}

void CDeadState::Exit()
{
	DeleteObject(GetMonster());
}
