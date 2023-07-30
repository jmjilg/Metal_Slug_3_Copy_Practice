#include "pch.h"
#include "CEventObject5.h"
#include "CShipDoor.h"
#include "CCollider.h"
#include "CCamera.h"
#include "CTimeMgr.h"
#include "SelectGDI.h"
#include "time.h"
#include "CMonster.h"
#include "CMonFactory.h"
#include "CRayGround.h"
#include "CChowmein_Conga.h"
#include "CScene.h"
#include "CSceneMgr.h"


CEventObject5::CEventObject5()
	: bIsEnterEvent(false)
	, m_iMonsterRespawnCount(2)
	, IsMonsterClear(false)
{
	m_arrMonster[0] = CMonFactory::CreateMonster(MON_TYPE::CHOWMEIN_CONGA, Vec2(1480, 60));
	m_arrMonster[1] = CMonFactory::CreateMonster(MON_TYPE::CHOWMEIN_CONGA, Vec2(1626, 60));
	m_arrMonster[2] = CMonFactory::CreateMonster(MON_TYPE::CHOWMEIN_CONGA, Vec2(1580, 83));
	m_arrMonster[2] = CMonFactory::CreateMonster(MON_TYPE::CHOWMEIN_CONGA, Vec2(1580, 83));
}

CEventObject5::~CEventObject5()
{
}

void CEventObject5::start()
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(GetScale()));
}

void CEventObject5::render(HDC _dc)
{
	component_render(_dc);
}

void CEventObject5::update()
{
	if (!IsMonsterClear)
	{
		for (int i = 0; i < 4; ++i)
		{
			if (!m_arrMonster[i]->IsDead())
				return;
		}
		// 배에서 생성된 몬스터가 다죽었을 때, 한번 더 리스폰한다.
		IsMonsterClear = !IsMonsterClear;
		return;
	}

	for (int i = 0; i < 4; ++i)
	{
		if (!m_arrMonster[i]->IsDead())
			return;
	}

	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	pCurScene->SetShip(false); // Ship 오브젝트가 파괴됨에 따라 직선충돌체를 재배치함

	DeleteObject(this);

}

void CEventObject5::OnCollisionEnter(CCollider* _pOther)
{
	if (_pOther->GetObj()->GetName() == L"Player")
	{
		Vec2 vPos = Vec2(1390, 118);
		vPos.x += 385;
		vPos.y += 232;
		CCamera::GetInst()->SetLookAt(vPos);

	}

}

