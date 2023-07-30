#include "pch.h"
#include "CEventObject2.h"
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


CEventObject2::CEventObject2()
	: bIsEnterEvent(false)
	, m_iMonsterRespawnCount(2)
	, IsMonsterClear(false)
{
}

CEventObject2::~CEventObject2()
{
}

void CEventObject2::start()
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(GetScale()));
}

void CEventObject2::render(HDC _dc)
{
	component_render(_dc);
}

void CEventObject2::update()
{
}

void CEventObject2::OnCollisionEnter(CCollider* _pOther)
{
	if (_pOther->GetObj()->GetName() == L"Player")
	{
		if (!bIsEnterEvent)
		{
			GetCameraBox()->SetPos(Vec2(_pOther->GetFinalPos().x, _pOther->GetFinalPos().y + 30.f));
			//GetCameraBox()->SetCorrectionValueX(_pOther->GetFinalPos().x);
			//GetCameraBox()->SetCorrectionValueY(_pOther->GetFinalPos().y);
			bIsEnterEvent = true;
		}

	}

}

