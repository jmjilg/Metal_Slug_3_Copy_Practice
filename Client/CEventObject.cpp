#include "pch.h"
#include "CEventObject.h"
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
#include "CR724.h"
#include "CShip.h"
#include "CScene.h"
#include "CSceneMgr.h"
#include "CCameraBox.h"


CEventObject::CEventObject()
	:bIsEnterEvent(false)
	, m_iMonsterRespawnCount(2)
	, m_pRayGround(nullptr)
	, IsMonsterClear(false)
	, m_pShipDoor(nullptr)
	, m_pShip(nullptr)
	, m_pR724(nullptr)
{
	memset(m_bannihilation, false, 8);
}

CEventObject::~CEventObject()
{
}

void CEventObject::start()
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(GetScale()));
}

void CEventObject::render(HDC _dc)
{
	component_render(_dc);
}

void CEventObject::update()
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

		// 배에서 생성된 몬스터가 다죽었을 때, 한번 더 리스폰한다.
		RespawnMonster(m_arrMonster1, Vec2(1600, 10), 1);
		RespawnMonster(m_arrMonster2, Vec2(1590, 10), 2);
		RespawnMonster(m_arrMonster3, Vec2(1600, 83), 3);
		RespawnMonster(m_arrMonster4, Vec2(1570, 83), 4);
		IsMonsterClear = !IsMonsterClear;
		for (int i = 0; i < 4; ++i)
			m_bannihilation[i] = false;
		return;
	}
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

	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	pCurScene->SetShip(false); // Ship 오브젝트가 파괴됨에 따라 직선충돌체를 재배치함

	if (GetCameraBox() != nullptr)
	{
		GetCameraBox()->SetTracePlayer(true);
	}

	DeleteObject(m_pRayGround);
	DeleteObject(m_pShipDoor);
	DeleteObject(m_pR724);
	DeleteObject(m_pShip);
	DeleteObject(this);

}

void CEventObject::OnCollisionEnter(CCollider* _pOther)
{
	if (_pOther->GetObj()->GetName() == L"Player")
	{
		//Vec2 vPos = Vec2(1390, 118);
		//vPos.x += 385;
		//vPos.y += 232;
		//CCamera::GetInst()->SetLookAt(vPos);


		if (!bIsEnterEvent)
		{
			if (GetCameraBox() != nullptr)
			{
				GetCameraBox()->SetTracePlayer(false);
			}

			m_pShipDoor = new CShipDoor;
			m_pShipDoor->SetName(L"ShipDoor");
			m_pShipDoor->SetPos(Vec2(1550.f, 130.f));
			m_pShipDoor->SetScale(Vec2(705.f, 48.f));
			CreateObject(m_pShipDoor, GROUP_TYPE::SHIPDOOR);
			bIsEnterEvent = true;


			m_pRayGround = new CRayGround;
			m_pRayGround->SetName(L"Ground");
			m_pRayGround->SetPos(Vec2(100.f, 400.f));
			m_pRayGround->SetScale(Vec2(100.f, 10.f));
			m_pRayGround->GetCollider()->GetVecRay().push_back(Vec2(1480, 60));
			m_pRayGround->GetCollider()->GetVecRay().push_back(Vec2(1626, 60));
			m_pRayGround->GetCollider()->GetVecRay().push_back(Vec2(1478, 180));
			m_pRayGround->GetCollider()->GetVecRay().push_back(Vec2(1565, 153)); // CShip 바로 다음

			CreateObject(m_pRayGround, GROUP_TYPE::GROUND);


			//CreateObject(m_arrMonster[0], GROUP_TYPE::MONSTER);
			//CreateObject(m_arrMonster[1], GROUP_TYPE::MONSTER);
			//CreateObject(m_arrMonster[2], GROUP_TYPE::MONSTER);
			//CreateObject(m_arrMonster[3], GROUP_TYPE::MONSTER);

			RespawnMonster(m_arrMonster1, Vec2(1600, 10), 1);
			RespawnMonster(m_arrMonster2, Vec2(1590, 10), 2);
			RespawnMonster(m_arrMonster3, Vec2(1600, 83), 3);
			RespawnMonster(m_arrMonster4, Vec2(1570, 83), 4);
		}
	}

}

void CEventObject::RespawnMonster(CMonster* _arrMonster, Vec2 _v, int i)
{
	_arrMonster = CMonFactory::CreateMonster(MON_TYPE::CHOWMEIN_CONGA, _v);
	CreateObject(_arrMonster, GROUP_TYPE::MONSTER);
	ChangeAIState(_arrMonster->GetAI(), MON_STATE::TRACE);
	switch (i)
	{
	case 1:
		m_arrMonster1 = _arrMonster;
		break;
	case 2:
		m_arrMonster2 = _arrMonster;
		break;
	case 3:
		m_arrMonster3 = _arrMonster;
		break;
	case 4:
		m_arrMonster4 = _arrMonster;
		break;
	}
}
