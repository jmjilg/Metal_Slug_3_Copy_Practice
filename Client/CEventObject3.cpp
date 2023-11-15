#include "pch.h"
#include "CEventObject3.h"
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
#include "CCameraBox.h"


CEventObject3::CEventObject3()
	: bIsEnterEvent(false)
	, m_iMonsterRespawnCount(2)
	, IsMonsterClear(false)
{
	memset(m_bannihilation, false, 4);
}

CEventObject3::~CEventObject3()
{
}

void CEventObject3::start()
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(GetScale()));
}

void CEventObject3::render(HDC _dc)
{
	component_render(_dc);
}

void CEventObject3::update()
{
	if (!bIsEnterEvent)
		return;

	if (!IsMonsterClear)
	{
		if (m_arrMonster1->IsDead())
			m_bannihilation[0] = true;
		if (m_arrMonster2->IsDead())
			m_bannihilation[1] = true;
		if (m_arrMonster3->IsDead())
			m_bannihilation[2] = true;
		if (m_arrMonster4->IsDead())
			m_bannihilation[3] = true;

		for (int i = 0; i < 4; ++i)
		{
			if (!m_bannihilation[i])
				return;
		}

		// 생성된 몬스터가 다죽었을 때.
		IsMonsterClear = !IsMonsterClear;
	}

	if (GetCameraBox() != nullptr)
	{
		GetCameraBox()->SetTracePlayer(true);
	}

	DeleteObject(this);
}

void CEventObject3::OnCollisionEnter(CCollider* _pOther)
{
	if (_pOther->GetObj()->GetName() == L"Player")
	{
		if (!bIsEnterEvent)
		{
			CCameraBox* pCameraBox = GetCameraBox();
			if (pCameraBox != nullptr)
			{
				pCameraBox->SetTracePlayer(false);
			}

			m_arrMonster1 = CMonFactory::CreateMonster(MON_TYPE::LOCUST, Vec2(2450, 40));
			CreateObject(m_arrMonster1, GROUP_TYPE::MONSTER);

			m_arrMonster2 = CMonFactory::CreateMonster(MON_TYPE::LOCUST, Vec2(2550, 40));
			CreateObject(m_arrMonster2, GROUP_TYPE::MONSTER);
			
			m_arrMonster3 = CMonFactory::CreateMonster(MON_TYPE::LOCUST, Vec2(2600, 50));
			CreateObject(m_arrMonster3, GROUP_TYPE::MONSTER);
			
			m_arrMonster4 = CMonFactory::CreateMonster(MON_TYPE::LOCUST, Vec2(2570, 40));
			CreateObject(m_arrMonster4, GROUP_TYPE::MONSTER);


			bIsEnterEvent = true;
		}
	
	}

}

