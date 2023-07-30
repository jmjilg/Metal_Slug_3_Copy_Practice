
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

	CAnimation* anim = GetAI()->GetOwner()->GetAnimator()->GetCurAnimL();
	bool temp = GetAI()->GetOwner()->GetAnimator()->GetCurAnimL()->IsFinish();
	int iCurFrame = GetAI()->GetOwner()->GetAnimator()->GetCurAnimL()->GetCurFrame();
	if (temp || iCurFrame == 29)  // 밍콩게 같은 경우에는 IsFinish() 함수가 잘 작동되는데, 거대 메뚜기같은 경우에는 작동이 잘 안됨. 그래서 일단 임시로 이렇게 해놨음
		Exit();

}

void CDeadState::Enter()
{

}

void CDeadState::Exit()
{
	DeleteObject(GetMonster());
}
