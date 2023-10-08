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

#include "CFlying_Killer.h"
#include "CBounce.h"
#include "CRush.h"

#include "CM3_Rocket_Launch_Support_Van.h"
#include "CM3_Missile.h"
#include "CFiring.h"
#include "CObstacle.h"
#include "CWoodenStool.h"

#include "CHuge_Hermit.h"
#include "CDestroyedState.h"
#include "CAppearState.h"

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
		pMon->CreateRigidBody(); // 얘를 다른 곳에서 아마 호출해줄거임. 지금은 오류가 안나지만 몬스터 복사생성할때 오류 날 수 있음
		pMon->CreateGravity();
		pMon->GetCollider()->SetScale(Vec2(40.f, 40.f));	
		pMon->GetRigidBody()->SetMass(1.f);

		// Texture 로딩하기
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
		//pMon->m_pAI->AddState(new CBubblefire); // 공격 상태
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
		
		info.vNextPos = Vec2(rand() % 210 + 2450, rand() % 20 + 40); // x축은 2450 ~ 2660 , y축은 40 ~ 60 사이에서만 패트롤함

		pMon->SetMonInfo(info);

		pMon->CreateCollider();
		pMon->CreateAnimator();
		pMon->CreateRigidBody(); // 얘를 다른 곳에서 아마 호출해줄거임. 지금은 오류가 안나지만 몬스터 복사생성할때 오류 날 수 있음
		pMon->GetCollider()->SetScale(Vec2(55.f, 30.f));
		pMon->GetRigidBody()->SetMass(1.f);

		// Texture 로딩하기
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
		//pMon->m_pAI->AddState(new CBubblefire); // 공격 상태
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
	
	case MON_TYPE::FLYING_KILLER:
	{
		pMon = new CFlying_Killer;
		pMon->SetPos(_vPos);

		tMonInfo info = {};
		info.eMonType = MON_TYPE::FLYING_KILLER;
		info.fAtt = 10.f;
		info.fAttRange = Vec2(25.f, 25.f);
		info.fRecogRange = 250.f;
		info.fHP = 1.f;
		info.fSpeed = 100.f;
		info.vOrigPos = _vPos;
		
		info.vNextPos = Vec2(rand() % 210 + 2450, rand() % 20 + 40); // x축은 2450 ~ 2660 , y축은 40 ~ 60 사이에서만 패트롤함

		pMon->SetMonInfo(info);

		pMon->CreateCollider();
		pMon->CreateAnimator();
		pMon->CreateRigidBody(); // 얘를 다른 곳에서 아마 호출해줄거임. 지금은 오류가 안나지만 몬스터 복사생성할때 오류 날 수 있음
		pMon->GetCollider()->SetScale(Vec2(25.f, 25.f));
		pMon->GetRigidBody()->SetMass(1.f);

		// Texture 로딩하기
		CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"Flying_Killer", L"texture\\Flying_Killer.bmp");


		pMon->GetAnimator()->LoadAnimation(L"animation\\FLYING_KILLER_ATTACKING.anim");
		pMon->GetAnimator()->LoadAnimation(L"animation\\FLYING_KILLER_DEATH.anim");
		pMon->GetAnimator()->LoadAnimation(L"animation\\FLYING_KILLER_JUMPING.anim");

		pMon->SetAI(new AI);
		pMon->m_pAI->AddState(new CBounce);
		pMon->m_pAI->AddState(new CRush);
		pMon->m_pAI->AddState(new CDeadState);
		//pMon->m_pAI->AddState(new CBubblefire);
		//pMon->m_pAI->AddState(new CBubblefire); // 공격 상태
		//pMon->m_pAI->AddState(new CClawing);
		pMon->m_pAI->SetCurState(MON_STATE::BOUNCE);

		pMon->SetName(L"Flying_Killer");

	}
		break;
	
	case MON_TYPE::M3_ROCKET_LAUNCH_SUPPORT_VAN:
	{
		pMon = new CM3_Rocket_Launch_Support_Van;
		pMon->SetPos(_vPos);

		tMonInfo info = {};
		info.eMonType = MON_TYPE::M3_ROCKET_LAUNCH_SUPPORT_VAN;
		info.fAtt = 0.f;
		info.fAttRange = Vec2(0.f, 0.f);
		info.fRecogRange = 250.f;
		info.fHP = 20.f;
		info.fSpeed = 100.f;
		info.vOrigPos = _vPos;
		
		pMon->SetMonInfo(info);

		pMon->CreateCollider();
		pMon->CreateAnimator();
		pMon->CreateRigidBody(); // 얘를 다른 곳에서 아마 호출해줄거임. 지금은 오류가 안나지만 몬스터 복사생성할때 오류 날 수 있음
		pMon->GetCollider()->SetScale(Vec2(100.f, 70.f));
		pMon->GetRigidBody()->SetMass(1.f);

		// Texture 로딩하기
		CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"M3_Rocket_Launch_Support_Van", L"texture\\M3_Rocket_Launch_Support_Van.bmp");


		pMon->GetAnimator()->LoadAnimation(L"animation\\M3_ROCKET_LAUNCH_SUPPORT_VAN_FIRING.anim");
		pMon->GetAnimator()->LoadAnimation(L"animation\\M3_ROCKET_LAUNCH_SUPPORT_VAN_IDLE.anim");
		pMon->GetAnimator()->LoadAnimation(L"animation\\M3_ROCKET_LAUNCH_SUPPORT_VAN_DEAD.anim");

		pMon->SetAI(new AI);
		pMon->m_pAI->AddState(new CIdleState);
		pMon->m_pAI->AddState(new CFiring);
		pMon->m_pAI->AddState(new CDeadState);
		pMon->m_pAI->SetCurState(MON_STATE::IDLE);

		pMon->SetName(L"M3_Rocket_Launch_Support_Van");


	}
		break;
	
	case MON_TYPE::M3_ROCKET_LAUNCH_SUPPORT_VAN_MISSILE:
	{
		pMon = new CM3_Missile;
		pMon->SetPos(_vPos);

		tMonInfo info = {};
		info.eMonType = MON_TYPE::M3_ROCKET_LAUNCH_SUPPORT_VAN_MISSILE;
		info.fAtt = 0.f;
		info.fAttRange = Vec2(10.f, 10.f);
		info.fRecogRange = 0.f;
		info.fHP = 1.f;
		info.fSpeed = 100.f;
		info.vOrigPos = _vPos;
		
		pMon->SetMonInfo(info);

		pMon->CreateCollider();
		pMon->CreateAnimator();
		pMon->CreateRigidBody(); // 얘를 다른 곳에서 아마 호출해줄거임. 지금은 오류가 안나지만 몬스터 복사생성할때 오류 날 수 있음
		pMon->GetCollider()->SetScale(Vec2(20.f, 30.f));
		pMon->GetRigidBody()->SetMass(1.f);

		// Texture 로딩하기
		CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"M3_Rocket_Launch_Support_Van", L"texture\\M3_Rocket_Launch_Support_Van.bmp");


		pMon->GetAnimator()->LoadAnimation(L"animation\\M3_ROCKET_LAUNCH_SUPPORT_VAN_PROJECTILES.anim");
		pMon->GetAnimator()->LoadAnimation(L"animation\\M3_ROCKET_LAUNCH_SUPPORT_VAN_DEAD.anim");

		pMon->SetAI(new AI);
		pMon->m_pAI->AddState(new CIdleState);
		pMon->m_pAI->AddState(new CDeadState);
		pMon->m_pAI->SetCurState(MON_STATE::IDLE);

		pMon->SetName(L"M3_Rocket_Launch_Support_Van_Missile");


	}
		break;
	case MON_TYPE::HUGE_HERMIT:
		pMon = new CHuge_Hermit;
		pMon->SetPos(_vPos);

		tMonInfo info = {};
		info.eMonType = MON_TYPE::HUGE_HERMIT;
		info.fAtt = 10.f;
		info.fAttRange = Vec2(70.f, 30.f);
		info.fRecogRange = 250.f;
		info.fHP = 3.f;
		info.fSpeed = 30.f;

		pMon->SetMonInfo(info);

		pMon->CreateCollider();
		pMon->CreateAnimator();
		pMon->CreateRigidBody(); // 얘를 다른 곳에서 아마 호출해줄거임. 지금은 오류가 안나지만 몬스터 복사생성할때 오류 날 수 있음
		pMon->GetCollider()->SetScale(Vec2(190.f, 200.f));
		pMon->GetRigidBody()->SetMass(1.f);

		// Texture 로딩하기
		CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"Huge_Hermit", L"texture\\Huge_Hermit.bmp");


		pMon->GetAnimator()->LoadAnimation(L"animation\\HUGE_HERMIT_IDLE.anim");
		pMon->GetAnimator()->LoadAnimation(L"animation\\HUGE_HERMIT_DESTROYED.anim");
		pMon->GetAnimator()->LoadAnimation(L"animation\\HUGE_HERMIT_DEAD.anim");

		pMon->SetAI(new AI);
		pMon->m_pAI->AddState(new CIdleState);
		pMon->m_pAI->AddState(new CDeadState);
		pMon->m_pAI->AddState(new CDestroyedState);
		pMon->m_pAI->AddState(new CAppearState);
		//pMon->m_pAI->AddState(new CBubblefire);
		//pMon->m_pAI->AddState(new CBubblefire); // 공격 상태
		//pMon->m_pAI->AddState(new CClawing);
		pMon->m_pAI->SetCurState(MON_STATE::APPEAR);

		pMon->SetName(L"Huge_Hermit");

		break;

	}


	assert(pMon);

	return pMon;
}
