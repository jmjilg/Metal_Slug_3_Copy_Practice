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

			CMonster* pMonster = CMonFactory::CreateMonster(MON_TYPE::LOCUST, Vec2(2450, 40));
			CreateObject(pMonster, GROUP_TYPE::MONSTER);

			pMonster = CMonFactory::CreateMonster(MON_TYPE::LOCUST, Vec2(2550, 40));
			CreateObject(pMonster, GROUP_TYPE::MONSTER);
			
			pMonster = CMonFactory::CreateMonster(MON_TYPE::LOCUST, Vec2(2600, 50));
			CreateObject(pMonster, GROUP_TYPE::MONSTER);
			
			pMonster = CMonFactory::CreateMonster(MON_TYPE::LOCUST, Vec2(2570, 40));
			CreateObject(pMonster, GROUP_TYPE::MONSTER);


			bIsEnterEvent = true;
		}
	
	}

}

