#include "CSlugTransport.h"
#include "CRes.h"
#include "CResMgr.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CCollider.h"
#include "CRayGround.h"
#include "CScene.h"
#include "CCamera.h"
#include "CCameraBox.h"
#include "CMonster.h"
#include "CCollider.h"

CSlugTransport::CSlugTransport()
	: m_pTexture(nullptr)
	, m_fVelocity(0.40f)
	, m_bContact(false)
	, m_lRespawnStart(0.f)
	, m_lRespawnAcc(0.f)
	, m_bRespawn(false)
	, m_iRespawnCount(0)
	, m_bRespawnEvent(false)
	, m_IBossEventStart(0.f)
	, m_IBossEventAcc(0.f)
	, m_bStop(false)
	, m_bBossEvent(false)
	, m_pRayGround(nullptr)
{
	// Texture �ε��ϱ�
	m_pTexture = CResMgr::GetInst()->LoadTexture(L"Mission1", L"texture\\Mission1.bmp");

	CreateAnimator();

	SetRayGround(new CRayGround);
	GetRayGround()->SetName(L"SlugTransPortGround");

	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2(200.f, 200.f));


	GetAnimator()->LoadAnimation(L"animation\\BackGround\\SlugTransport.anim");
}

CSlugTransport::~CSlugTransport()
{
}

void CSlugTransport::start()
{
	m_pRayGround = new CRayGround;
	m_pRayGround->SetName(L"SlugTransportGround");

	m_pRayGround->GetCollider()->GetVecRay().push_back(Vec2(2855.f, 215.f));
	m_pRayGround->GetCollider()->GetVecRay().push_back(Vec2(2966.f, 215.f));
	
	m_pRayGround->GetCollider()->GetVecRay().push_back(Vec2(2966.f, 215.f));
	m_pRayGround->GetCollider()->GetVecRay().push_back(Vec2(2984.f, 202.f));
	
	m_pRayGround->GetCollider()->GetVecRay().push_back(Vec2(2984.f, 202.f));
	m_pRayGround->GetCollider()->GetVecRay().push_back(Vec2(3018.f, 202.f));
	
	m_pRayGround->GetCollider()->GetVecRay().push_back(Vec2(2886.f, 174.f));
	m_pRayGround->GetCollider()->GetVecRay().push_back(Vec2(2957.f, 174.f));

	CreateObject(m_pRayGround, GROUP_TYPE::GROUND);
}

void CSlugTransport::update()
{
	GetAnimator()->PlayL(L"SlugTransport", true);
	
	if (m_bContact)
	{
		Vec2 vTemp = GetPos();
		vTemp.x += m_fVelocity;
		SetPos(vTemp);

		int size = m_pRayGround->GetCollider()->GetVecRay().size();

		for (int i = 0; i < size; ++i)
		{
			m_pRayGround->GetCollider()->GetVecRay()[i].x += m_fVelocity;
		}
	}

}

void CSlugTransport::render(HDC _dc)
{
	component_render(_dc);
}


void CSlugTransport::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Player")
	{
		m_bContact = true; // �÷��̾�� �����ϰ� �Ǹ� �谡 �����̱� ������
		
		Vec2 vTemp = pOtherObj->GetPos();
		vTemp.x += m_fVelocity;
		pOtherObj->SetPos(vTemp);
		m_lRespawnStart = clock();
		m_bRespawn = true;
	}

	if (pOtherObj->GetName() == L"Ground") // ��ֹ� ������Ʈ�� �ε����� ��
	{
		m_bContact = false;
	}
	
	if (pOtherObj->GetName() == L"EventObject4") // ���� �̺�Ʈ ������Ʈ�� �ε����� ��
	{
		m_bContact = false;
		m_bBossEvent = true;
		m_IBossEventStart = clock();
	}


}

void CSlugTransport::OnCollision(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();


	if (pOtherObj->GetName() == L"Player" && m_bContact)
	{
		Vec2 vRenderCamera = GetPos();
		vRenderCamera.x += 257.f; // m_fCorrection_Value_X
		vRenderCamera.y += 25.f; // m_fCorrection_Value_Y
		CCamera::GetInst()->SetLookAt(vRenderCamera); // �̶� ī�޶� ����ؼ� �踦 �ٶ󺸵��� ������ 
		Vec2 vTemp = pOtherObj->GetPos();
		vTemp.x += m_fVelocity;
		pOtherObj->SetPos(vTemp);


		m_lRespawnAcc = clock();
		
		if (m_bRespawnEvent)
		{
			if (m_bRespawn && m_iRespawnCount <= 10)
			{
				if (m_lRespawnAcc - m_lRespawnStart >= 500.f) // 0.5�ʸ��� ����
				{
					Vec2 vLength = Vec2(200.f, 50.f);
					CMonster* pMon = CMonFactory::CreateMonster(MON_TYPE::FLYING_KILLER, GetPos() + vLength);
					CreateObject((CObject*)pMon, GROUP_TYPE::MONSTER);

					m_iRespawnCount++;
					m_lRespawnStart = m_lRespawnAcc;
				}
			}
		}
		else if (m_lRespawnAcc - m_lRespawnStart >= 30000.f) // �÷��̾ �迡 ž���ϰ� 30�� ���� �Ŀ� �ö��� ų�� ���� ���� ����
		{
			m_bRespawnEvent = true;
		}

		
	}

	if (m_bBossEvent)
	{
		m_IBossEventAcc = clock() - m_IBossEventStart;
		if (m_IBossEventAcc >= 3000.f)
		{
			DeleteObject(m_pRayGround);
			DeleteObject(this);
		}
	}

}

void CSlugTransport::OnCollisionExit(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Ground") 
	{
		m_bContact = true;
	}
}
