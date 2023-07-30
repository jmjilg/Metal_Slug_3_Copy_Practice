
#include "pch.h"
#include "CAttackState.h"
#include "CIdleState.h"

#include "CSceneMgr.h"
#include "CScene.h"

#include "CPlayer.h"
#include "CMonster.h"

CAttackState::CAttackState()
	: CState(MON_STATE::ATT)
{
}

CAttackState::~CAttackState()
{
}

void CAttackState::update()
{
}

void CAttackState::Enter()
{
}

void CAttackState::Exit()
{
}