#include "pch.h"
#include "CDestroyedState.h"

#include "CSceneMgr.h"
#include "CScene.h"

#include "CPlayer.h"
#include "CMonster.h"
#include "CDeadState.h"
#include "AI.h"
#include "CAnimator.h"
#include "CAnimation.h"

CDestroyedState::CDestroyedState()
	: CState(MON_STATE::DESTROYED)
{
}

CDestroyedState::~CDestroyedState()
{
}

void CDestroyedState::update()
{

}

void CDestroyedState::Enter()
{

}

void CDestroyedState::Exit()
{
}

