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
#include "CCameraBox.h"
#include "CSound.h"
#include "CSoundMgr.h"
#include "CResMgr.h"

CEventObject4::CEventObject4()
	: m_bIsEnterEvent(false)
	, m_bIsHugeHermitRespawn(false)

{
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
	if (m_bIsEnterEvent)
	{
		m_lEventAcc = clock() - m_lEventStart; // �̺�Ʈ�� ������ �������� �󸶳� ������

		if (!m_bIsHugeHermitRespawn && m_lEventAcc >= 3000.f)
		{
			m_bIsHugeHermitRespawn = true;
			CMonster* pMon = CMonFactory::CreateMonster(MON_TYPE::HUGE_HERMIT, Vec2(4650.f, 204.f)); // ���Ͱ� �÷��̾ ó�� �Ѿư����� ��ġ Vec2(4650.f, 134.f)
			CreateObject(pMon, GROUP_TYPE::MONSTER);

			CSound* pNewSound = CResMgr::GetInst()->FindSound(L"BGM_02"); // ���� �������� ���

			pNewSound->Play(); // ���ڷ� true�� �ָ� �ݺ����

			pNewSound->SetPosition(50.f); // ��з�, �Ҹ� ��ġ ����
			pNewSound->PlayToBGM(true); // ���ڷ� true�� �ָ� �ݺ����
			pNewSound->SetVolume(60.f);

		}
	}



	//if (!IsMonsterClear)
	//{
	//	for (int i = 0; i < 4; ++i)
	//	{
	//		if (!m_arrMonster[i]->IsDead())
	//			return;
	//	}
	//	// �迡�� ������ ���Ͱ� ���׾��� ��, �ѹ� �� �������Ѵ�.
	//	IsMonsterClear = !IsMonsterClear;
	//	return;
	//}

	//for (int i = 0; i < 4; ++i)
	//{
	//	if (!m_arrMonster[i]->IsDead())
	//		return;
	//}

	//CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	//pCurScene->SetShip(false); // Ship ������Ʈ�� �ı��ʿ� ���� �����浹ü�� ���ġ��

	//DeleteObject(this);

}

void CEventObject4::OnCollisionEnter(CCollider* _pOther)
{
	if (_pOther->GetObj()->GetName() == L"SlugTransport" && !m_bIsEnterEvent) // L"Player"
	{
		m_lEventStart = clock();
		m_bIsEnterEvent = true;
	}

}

