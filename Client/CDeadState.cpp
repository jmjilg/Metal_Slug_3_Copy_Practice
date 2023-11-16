
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
	if (GetMonster()->GetName() == L"Huge_Hermit")  // 보스 몬스터가 죽을때 스테이지 클리어 사운드 재생
	{
		CSound* pNewSound = CResMgr::GetInst()->FindSound(L"BGM_03"); // Stage Clear 브금

		pNewSound->Play(); // 인자로 true를 주면 반복재생

		pNewSound->SetPosition(50.f); // 백분률, 소리 위치 설정
		pNewSound->PlayToBGM(false); // 인자로 true를 주면 반복재생
		pNewSound->SetVolume(60.f);

	}

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
