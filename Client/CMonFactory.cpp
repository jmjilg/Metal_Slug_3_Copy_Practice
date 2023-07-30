#include "pch.h"
#include "CMonFactory.h"

#include "CRigidBody.h"

#include "CMonster.h"
#include "AI.h"

#include "CIdleState.h"
#include "CTraceState.h"

#include "CBubblefire.h"
#include "CClawing.h"

#include "CCollider.h"
#include "CAnimation.h"
#include "CRes.h"
#include "CResMgr.h"
#include "CAnimator.h"
#include "CDeadState.h"
#include "CChowmein_Conga.h"

#include "CLocust.h"
#include "CFlying.h"
#include "CKidnapping.h"


CMonster* CMonFactory::CreateMonster(MON_TYPE _eType, Vec2 _vPos)
{
	CMonster* pMon = nullptr;

	switch (_eType)
	{
	case MON_TYPE::CHOWMEIN_CONGA:
	{
		pMon = new CChowmein_Conga;
		pMon->SetPos(_vPos);

		tMonInfo info = {};
		info.eMonType = MON_TYPE::CHOWMEIN_CONGA;
		info.fAtt = 10.f;
		info.fAttRange = Vec2(70.f, 30.f);
		info.fRecogRange = 250.f;
		info.fHP = 3.f;
		info.fSpeed = 50.f;

		pMon->SetMonInfo(info);

		pMon->CreateCollider();
		pMon->CreateAnimator();
		pMon->CreateRigidBody(); // �긦 �ٸ� ������ �Ƹ� ȣ�����ٰ���. ������ ������ �ȳ����� ���� ��������Ҷ� ���� �� �� ����
		pMon->CreateGravity();
		pMon->GetCollider()->SetScale(Vec2(40.f, 40.f));	
		pMon->GetRigidBody()->SetMass(1.f);

		// Texture �ε��ϱ�
		CTexture* pLeftTex = CResMgr::GetInst()->LoadTexture(L"Chowmein_Conga_Left", L"texture\\Chowmein_Conga_Left.bmp");
		CTexture* pRightTex = CResMgr::GetInst()->LoadTexture(L"Chowmein_Conga_Right", L"texture\\Chowmein_Conga_Right.bmp");


		pMon->GetAnimator()->LoadAnimation(L"animation\\CHOWMEIN_CONGA_ATTACK_LEFT.anim");
		pMon->GetAnimator()->LoadAnimation(L"animation\\CHOWMEIN_CONGA_ATTACK_RIGHT.anim");
		pMon->GetAnimator()->LoadAnimation(L"animation\\CHOWMEIN_CONGA_DEATH_LEFT.anim");
		pMon->GetAnimator()->LoadAnimation(L"animation\\CHOWMEIN_CONGA_DEATH_RIGHT.anim");
		pMon->GetAnimator()->LoadAnimation(L"animation\\CHOWMEIN_CONGA_IDLE_LEFT.anim");
		pMon->GetAnimator()->LoadAnimation(L"animation\\CHOWMEIN_CONGA_IDLE_RIGHT.anim");
		pMon->GetAnimator()->LoadAnimation(L"animation\\CHOWMEIN_CONGA_SPIT_LEFT.anim");
		pMon->GetAnimator()->LoadAnimation(L"animation\\CHOWMEIN_CONGA_SPIT_RIGHT.anim");
		pMon->GetAnimator()->LoadAnimation(L"animation\\CHOWMEIN_CONGA_WALKING_LEFT.anim");
		pMon->GetAnimator()->LoadAnimation(L"animation\\CHOWMEIN_CONGA_WALKING_RIGHT.anim");

		pMon->SetAI(new AI);
		pMon->m_pAI->AddState(new CIdleState);
		pMon->m_pAI->AddState(new CTraceState);
		pMon->m_pAI->AddState(new CDeadState);
		pMon->m_pAI->AddState(new CAttackState);
		pMon->m_pAI->AddState(new CClawing);
		//pMon->m_pAI->AddState(new CBubblefire);
		//pMon->m_pAI->AddState(new CBubblefire); // ���� ����
		//pMon->m_pAI->AddState(new CClawing);
		pMon->m_pAI->SetCurState(MON_STATE::IDLE);

		pMon->SetName(L"Chowmein_Conga");


		/*AI* pAI = new AI;
		pAI->AddState(new CIdleState);
		pAI->AddState(new CTraceState);
		pAI->SetCurState(MON_STATE::IDLE);
		pMon->SetAI(pAI);*/

	}
		break;
	case MON_TYPE::LOCUST:
	{
		pMon = new CLocust;
		pMon->SetPos(_vPos);

		tMonInfo info = {};
		info.eMonType = MON_TYPE::LOCUST;
		info.fAtt = 10.f;
		info.fAttRange = Vec2(10.f, 10.f);
		info.fRecogRange = 250.f;
		info.fHP = 3.f;
		info.fSpeed = 100.f;
		info.vOrigPos = _vPos;
		
		info.vNextPos = Vec2(rand() % 210 + 2450, rand() % 20 + 40); // x���� 2450 ~ 2660 , y���� 40 ~ 60 ���̿����� ��Ʈ����

		pMon->SetMonInfo(info);

		pMon->CreateCollider();
		pMon->CreateAnimator();
		pMon->CreateRigidBody(); // �긦 �ٸ� ������ �Ƹ� ȣ�����ٰ���. ������ ������ �ȳ����� ���� ��������Ҷ� ���� �� �� ����
		pMon->GetCollider()->SetScale(Vec2(55.f, 30.f));
		pMon->GetRigidBody()->SetMass(1.f);

		// Texture �ε��ϱ�
		CTexture* pLeftTex = CResMgr::GetInst()->LoadTexture(L"Locust_Left", L"texture\\Locust_Left.bmp");
		CTexture* pRightTex = CResMgr::GetInst()->LoadTexture(L"Locust_Right", L"texture\\Locust_Right.bmp");


		pMon->GetAnimator()->LoadAnimation(L"animation\\LOCUST_ATTACK_LEFT.anim");
		pMon->GetAnimator()->LoadAnimation(L"animation\\LOCUST_ATTACK_RIGHT.anim");
		pMon->GetAnimator()->LoadAnimation(L"animation\\LOCUST_DIE_LEFT.anim");
		pMon->GetAnimator()->LoadAnimation(L"animation\\LOCUST_DIE_RIGHT.anim");
		pMon->GetAnimator()->LoadAnimation(L"animation\\LOCUST_FLYING_LEFT.anim");
		pMon->GetAnimator()->LoadAnimation(L"animation\\LOCUST_FLYING_RIGHT.anim");

		pMon->SetAI(new AI);
		pMon->m_pAI->AddState(new CFlying);
		pMon->m_pAI->AddState(new CKidnapping);
		pMon->m_pAI->AddState(new CDeadState);
		//pMon->m_pAI->AddState(new CBubblefire);
		//pMon->m_pAI->AddState(new CBubblefire); // ���� ����
		//pMon->m_pAI->AddState(new CClawing);
		pMon->m_pAI->SetCurState(MON_STATE::FLYING);

		pMon->SetName(L"Locust");

		/*AI* pAI = new AI;
		pAI->AddState(new CIdleState);
		pAI->AddState(new CTraceState);
		pAI->SetCurState(MON_STATE::IDLE);
		pMon->SetAI(pAI);*/
	}
		break;
	case MON_TYPE::HUGE_HERMIT:
		break;

	}


	assert(pMon);

	return pMon;
}
