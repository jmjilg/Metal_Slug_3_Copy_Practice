#include "pch.h"
#include "CEventObject4.h"
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


CEventObject4::CEventObject4()
	: bIsEnterEvent(false)
	, m_iMonsterRespawnCount(2)
	, IsMonsterClear(false)
{
	m_arrMonster[0] = CMonFactory::CreateMonster(MON_TYPE::CHOWMEIN_CONGA, Vec2(1480, 60));
	m_arrMonster[1] = CMonFactory::CreateMonster(MON_TYPE::CHOWMEIN_CONGA, Vec2(1626, 60));
	m_arrMonster[2] = CMonFactory::CreateMonster(MON_TYPE::CHOWMEIN_CONGA, Vec2(1580, 83));
	m_arrMonster[2] = CMonFactory::CreateMonster(MON_TYPE::CHOWMEIN_CONGA, Vec2(1580, 83));
}

CEventObject4::~CEventObject4()
{
}

void CEventObject4::start()
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(GetScale()));
}

void CEventObject4::render(HDC _dc)
{
	component_render(_dc);
}

void CEventObject4::update()
{
	if (!IsMonsterClear)
	{
		for (int i = 0; i < 4; ++i)
		{
			if (!m_arrMonster[i]->IsDead())
				return;
		}
		// �迡�� ������ ���Ͱ� ���׾��� ��, �ѹ� �� �������Ѵ�.
		IsMonsterClear = !IsMonsterClear;
		return;
	}

	for (int i = 0; i < 4; ++i)
	{
		if (!m_arrMonster[i]->IsDead())
			return;
	}

	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	pCurScene->SetShip(false); // Ship ������Ʈ�� �ı��ʿ� ���� �����浹ü�� ���ġ��

	DeleteObject(this);

}

void CEventObject4::OnCollisionEnter(CCollider* _pOther)
{
	if (_pOther->GetObj()->GetName() == L"Player")
	{
		Vec2 vPos = Vec2(1390, 118);
		vPos.x += 385;
		vPos.y += 232;
		CCamera::GetInst()->SetLookAt(vPos);

	}

}

