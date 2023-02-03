#include "pch.h"
#include "CPlayer.h"

#include "CSceneMgr.h"
#include "CScene.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CMissile.h"

#include "CResMgr.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "CRigidBody.h"
#include "CGravity.h"

CPlayer::CPlayer()
	: m_eCurStateUpper(PLAYER_STATE::IDLE)
	, m_eCurStateLower(PLAYER_STATE::IDLE)
	, m_ePrevStateUpper(PLAYER_STATE::IDLE)
	, m_ePrevStateLower(PLAYER_STATE::IDLE)
	, m_eCurWeapon(WEAPON::HAND_GUN)
	, m_ePrevWeapon(WEAPON::HAND_GUN)
	, m_iDir(1)
	, m_iPrevDir(1)
	, m_bAttack(false)
	, m_iGrenade(10)
	, m_iGrenadeCount(0)
{
	// Texture 로딩하기
	//m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\Player.bmp");


	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 15.f));
	GetCollider()->SetScale(Vec2(20.f, 20.f));

	CreateRigidBody();

	// Texture 로딩하기
	CTexture* pLeftTex = CResMgr::GetInst()->LoadTexture(L"PlayerLeft", L"texture\\Marco_Rossi_Left.bmp"); 
	CTexture* pRightTex = CResMgr::GetInst()->LoadTexture(L"PlayerRight", L"texture\\Marco_Rossi_Right.bmp");

	CreateAnimator();	

	GetAnimator()->LoadAnimation(L"animation\\PLAYER_GRENADE_THROW_UPPER_PART_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\PLAYER_GRENADE_THROW_UPPER_PART_RIGHT.anim");
	GetAnimator()->LoadAnimation(L"animation\\PLAYER_IDLE_JUMP_LOWER_PART_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\PLAYER_IDLE_JUMP_LOWER_PART_RIGHT.anim");
	GetAnimator()->LoadAnimation(L"animation\\PLAYER_IDLE_JUMP_UPPER_PART_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\PLAYER_IDLE_JUMP_UPPER_PART_RIGHT.anim");
	GetAnimator()->LoadAnimation(L"animation\\PLAYER_IDLE_LOWER_PART_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\PLAYER_IDLE_LOWER_PART_RIGHT.anim");
	GetAnimator()->LoadAnimation(L"animation\\PLAYER_IDLE_SIT_DOWN_GRENADE_THROW_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\PLAYER_IDLE_SIT_DOWN_GRENADE_THROW_RIGHT.anim");
	GetAnimator()->LoadAnimation(L"animation\\PLAYER_IDLE_SIT_DOWN_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\PLAYER_IDLE_SIT_DOWN_MELEE_ATTACK_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\PLAYER_IDLE_SIT_DOWN_MELEE_ATTACK_RIGHT.anim");
	GetAnimator()->LoadAnimation(L"animation\\PLAYER_IDLE_SIT_DOWN_MOTION_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\PLAYER_IDLE_SIT_DOWN_MOTION_RIGHT.anim");
	GetAnimator()->LoadAnimation(L"animation\\PLAYER_IDLE_SIT_DOWN_RIGHT.anim");
	GetAnimator()->LoadAnimation(L"animation\\PLAYER_IDLE_SIT_DOWN_SHOOT_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\PLAYER_IDLE_SIT_DOWN_SHOOT_RIGHT.anim");
	GetAnimator()->LoadAnimation(L"animation\\PLAYER_IDLE_SIT_DOWN_WALK_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\PLAYER_IDLE_SIT_DOWN_WALK_RIGHT.anim");
	GetAnimator()->LoadAnimation(L"animation\\PLAYER_IDLE_UPPER_PART_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\PLAYER_IDLE_UPPER_PART_RIGHT.anim");
	GetAnimator()->LoadAnimation(L"animation\\PLAYER_IDLE_UPPER_PART_UP.anim");
	GetAnimator()->LoadAnimation(L"animation\\PLAYER_LOOK_DOWN_UPPER_PART_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\PLAYER_LOOK_DOWN_UPPER_PART_RIGHT.anim");
	GetAnimator()->LoadAnimation(L"animation\\PLAYER_LOOK_UP_UPPER_PART_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\PLAYER_LOOK_UP_UPPER_PART_RIGHT.anim");
	GetAnimator()->LoadAnimation(L"animation\\PLAYER_MELEE_ATTACK_UPPER_PART_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\PLAYER_MELEE_ATTACK_UPPER_PART_LEFT2.anim");
	GetAnimator()->LoadAnimation(L"animation\\PLAYER_MELEE_ATTACK_UPPER_PART_RIGHT.anim");
	GetAnimator()->LoadAnimation(L"animation\\PLAYER_MELEE_ATTACK_UPPER_PART_RIGHT2.anim");
	GetAnimator()->LoadAnimation(L"animation\\PLAYER_SHOOT_UP_UPPER_PART_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\PLAYER_SHOOT_UP_UPPER_PART_RIGHT.anim");
	GetAnimator()->LoadAnimation(L"animation\\PLAYER_SHOOT_UPPER_PART_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\PLAYER_SHOOT_UPPER_PART_RIGHT.anim");
	GetAnimator()->LoadAnimation(L"animation\\PLAYER_WALK_JUMP_LOWER_PART_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\PLAYER_WALK_JUMP_LOWER_PART_RIGHT.anim");
	GetAnimator()->LoadAnimation(L"animation\\PLAYER_WALK_JUMP_UPPER_PART_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\PLAYER_WALK_JUMP_UPPER_PART_RIGHT.anim");
	GetAnimator()->LoadAnimation(L"animation\\PLAYER_WALK_LOWER_PART_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\PLAYER_WALK_LOWER_PART_RIGHT.anim");
	GetAnimator()->LoadAnimation(L"animation\\PLAYER_WALK_UPPER_PART_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\PLAYER_WALK_UPPER_PART_RIGHT.anim");






	//GetAnimator()->CreateAnimation(L"PLAYER_SHOOT_UPPER_PART_LEFT", pLeftTex, Vec2(1758.f, 1047.f), Vec2(52.f, 25.f), Vec2(-34.f, 0.f), Vec2(3.f, -5.f), 0.1f, 10);
	//GetAnimator()->CreateAnimation(L"PLAYER_SHOOT_UPPER_PART_RIGHT", pRightTex, Vec2(9.f, 1047.f), Vec2(52.f, 25.f), Vec2(34.f, 0.f), Vec2(-7.f, -5.f), 0.1f, 10);


	// Animation 저장해보기
	//GetAnimator()->FindAnimation(L"PLAYER_SHOOT_UPPER_PART_LEFT")->Save(L"animation\\PLAYER_SHOOT_UPPER_PART_LEFT.anim");
	//GetAnimator()->FindAnimation(L"PLAYER_SHOOT_UPPER_PART_RIGHT")->Save(L"animation\\PLAYER_SHOOT_UPPER_PART_RIGHT.anim"); 


	CreateGravity();
}

CPlayer::~CPlayer()
{

}

void CPlayer::update()
{
	update_move();

	update_state();

	update_animation();

	if (KEY_TAP(KEY::ENTER))
	{
		SetPos(Vec2(640.f, 384.f));
	}

	GetAnimator()->update();

	m_ePrevStateLower = m_eCurStateLower;
	m_ePrevStateUpper = m_eCurStateUpper;
	m_iPrevDir = m_iDir;
}

void CPlayer::render(HDC _dc)
{
	//int iWidth = (int)m_pTex->Width();
	//int iHeight = (int)m_pTex->Height();

	//Vec2 vPos = GetPos();

	//BitBlt(_dc
	//	, (int)vPos.x - (float)(iWidth / 2)
	//	, (int)vPos.y - (float)(iHeight / 2)
	//	, iWidth, iHeight
	//	, m_pTex->GetDC()
	//	, 0, 0, SRCCOPY);

	//TransparentBlt(_dc
	//	, (int)vPos.x - (float)(iWidth / 2)
	//	, (int)vPos.y - (float)(iHeight / 2)
	//	, iWidth, iHeight  
	//	, m_pTex->GetDC()
	//	, 0, 0, iWidth, iHeight
	//	, RGB(255, 255, 255));

	// 컴포넌트(충돌체, etc...) 가 있는 경우 렌더
	component_render(_dc);


	// 알파블렌드 테스트 코드(비행기 스프라이트)
	/*CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"Plane", L"texture\\Player_A.bmp");

	Vec2 vPos = GetPos();
	vPos = CCamera::GetInst()->GetRenderPos(vPos);

	float width = (float)pTex->Width();
	float height = (float)pTex->Height();

	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = AC_SRC_ALPHA;
	bf.SourceConstantAlpha = 127;

	AlphaBlend(_dc
		, int(vPos.x - width / 2.f)
		, int(vPos.y - height / 2.f)
		, int(width), int(height)
		, pTex->GetDC()
		, 0, 0
		, int(width), int(height)
		, bf);*/
}

void CPlayer::CreateMissile()
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2.f;

	// Missile Object
	CMissile* pMissile = new CMissile;
	pMissile->SetName(L"Missile_Player");
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetDir(Vec2(0.f, -1.f));
	
	CreateObject(pMissile, GROUP_TYPE::PROJ_PLAYER); // 앞으로 생성될 모든 종류의 오브젝트를 커버할 수 있어야함
}

void CPlayer::update_state()
{
	LOWERPART_update();
	UPPERPART_update();


	GetAnimator()->StopAnimationL(false);
	GetAnimator()->StopAnimationU(false);

	if (KEY_TAP(KEY::K))
	{
		//CreateMissile();
		m_eMoveState = PLAYER_STATE::JUMP;
		m_eCurStateUpper = PLAYER_STATE::JUMP;
		m_eCurStateLower = PLAYER_STATE::JUMP;
		if (GetRigidBody())
		{
			GetRigidBody()->SetVelocity(Vec2(GetRigidBody()->GetVelocity().x, -350.f));
		}
	}

	if (0.f == GetRigidBody()->GetSpeed() && PLAYER_STATE::JUMP != m_eCurStateLower)
	{
		m_eMoveState = PLAYER_STATE::IDLE;
		m_eCurStateUpper = PLAYER_STATE::IDLE;
		m_eCurStateLower = PLAYER_STATE::IDLE;
	}

	if (KEY_HOLD(KEY::S))
	{
		// 점프중일때 아래를 본다
		if (PLAYER_STATE::JUMP == m_eCurStateLower)
		{
			m_eMoveState = PLAYER_STATE::LOOK_DOWN;
			m_eCurStateUpper = PLAYER_STATE::LOOK_DOWN;
		}
		// 점프중이 아닐땐 플레이어 캐릭터가 앉는다
		else
		{
			GetAnimator()->StopAnimationU(true);
			m_eMoveState = PLAYER_STATE::SIT_DOWN;
			m_eCurStateLower = PLAYER_STATE::SIT_DOWN;
		}
	}

	if (KEY_HOLD(KEY::A))
	{
		m_iDir = -1;

		if (PLAYER_STATE::SIT_DOWN == m_eMoveState)
		{
			m_eMoveState = PLAYER_STATE::SIT_DOWN_WALK;
			m_eCurStateLower = PLAYER_STATE::SIT_DOWN_WALK;
			GetAnimator()->StopAnimationU(true);

		}
		else if (PLAYER_STATE::JUMP != m_eCurStateLower)
		{
			m_eMoveState = PLAYER_STATE::WALK;
			m_eCurStateUpper = PLAYER_STATE::WALK;
			m_eCurStateLower = PLAYER_STATE::WALK;
		}
	}

	if (KEY_HOLD(KEY::D))
	{
		m_iDir = 1;

		if (PLAYER_STATE::SIT_DOWN == m_eMoveState)
		{
			m_eMoveState = PLAYER_STATE::SIT_DOWN_WALK;
			m_eCurStateLower = PLAYER_STATE::SIT_DOWN_WALK;
			GetAnimator()->StopAnimationU(true);
		}

		else if (PLAYER_STATE::JUMP != m_eCurStateLower)
		{
			m_eMoveState = PLAYER_STATE::WALK;
			m_eCurStateUpper = PLAYER_STATE::WALK;
			m_eCurStateLower = PLAYER_STATE::WALK;
		}
	}

	if (KEY_HOLD(KEY::W))
	{
		m_eMoveState = PLAYER_STATE::LOOK_UP;
		m_eCurStateUpper = PLAYER_STATE::LOOK_UP;
	}

	if (KEY_TAP(KEY::J))
	{		
		if (PLAYER_STATE::LOOK_UP == m_eCurStateUpper)
		{
			m_eCurStateUpper = PLAYER_STATE::LOOK_UP;
			m_eCurAttackState = ATTACK_KIND::SHOOT_UP;
			if (-1 == m_iDir)
				GetAnimator()->FindAnimation(L"PLAYER_SHOOT_UP_UPPER_PART_LEFT")->SetFrame(0);
			else
				GetAnimator()->FindAnimation(L"PLAYER_SHOOT_UP_UPPER_PART_RIGHT")->SetFrame(0);
		}
		else if (PLAYER_STATE::SIT_DOWN == m_eCurStateLower || PLAYER_STATE::SIT_DOWN_WALK == m_eCurStateLower)
		{
			GetAnimator()->StopAnimationU(true);
			m_eCurAttackState = ATTACK_KIND::SIT_DOWN_SHOOT;
			m_eCurStateLower = PLAYER_STATE::SIT_DOWN;
			if (-1 == m_iDir)
				GetAnimator()->FindAnimation(L"PLAYER_IDLE_SIT_DOWN_SHOOT_LEFT")->SetFrame(0);
			else
				GetAnimator()->FindAnimation(L"PLAYER_IDLE_SIT_DOWN_SHOOT_RIGHT")->SetFrame(0);

		}
		else
		{
			m_eCurStateUpper = PLAYER_STATE::ATTACK;
			m_eCurAttackState = ATTACK_KIND::SHOOT;
			// 공격 모션 진행중에 또다시 공격 키를 눌렀을 때. 공격 모션을 처음부터 초기화한다.
			if (-1 == m_iDir)
				GetAnimator()->FindAnimation(L"PLAYER_SHOOT_UPPER_PART_LEFT")->SetFrame(0);
			else
				GetAnimator()->FindAnimation(L"PLAYER_SHOOT_UPPER_PART_RIGHT")->SetFrame(0);
		}

		SetIsAttack(true);
		m_eAttackState = PLAYER_STATE::ATTACK;
	}

	if (KEY_TAP(KEY::L))
	{
		m_eAttackState = PLAYER_STATE::ATTACK;
		m_eCurStateUpper = PLAYER_STATE::ATTACK;
		m_eCurAttackState = ATTACK_KIND::GRENADE_THROW;
		SetIsAttack(true);
		// 공격 모션 진행중에 또다시 공격 키를 눌렀을 때. 공격 모션을 처음부터 초기화한다.
		if (-1 == m_iDir)
			GetAnimator()->FindAnimation(L"PLAYER_GRENADE_THROW_UPPER_PART_LEFT")->SetFrame(0);
		else
			GetAnimator()->FindAnimation(L"PLAYER_GRENADE_THROW_UPPER_PART_RIGHT")->SetFrame(0);
	}

	if (IsAttack())
	{
		m_eCurStateUpper = m_eAttackState;
		if (GetAnimator()->GetCurAnimU()->IsFinish())
		{
			SetIsAttack(false);
			m_eCurStateUpper = m_eMoveState;
		}
	}


	//if (KEY_HOLD(KEY::K))
	//{
	//	m_iDir = 1;
	//	if (PLAYER_STATE::JUMP != m_eCurState)
	//		m_eCurState = PLAYER_STATE::WALK;
	//}

	//if (KEY_HOLD(KEY::L))
	//{
	//	m_iDir = 1;
	//	if (PLAYER_STATE::JUMP != m_eCurState)
	//		m_eCurState = PLAYER_STATE::WALK;
	//}

	
}

void CPlayer::update_move()
{
	CRigidBody* pRigid = GetRigidBody();

	if (KEY_HOLD(KEY::A))
	{
		pRigid->AddForce(Vec2(-300.f, 0.f));
	}

	if (KEY_HOLD(KEY::D))
	{
		pRigid->AddForce(Vec2(300.f, 0.f));
	}

	if (KEY_TAP(KEY::A))
	{		
		pRigid->SetVelocity(Vec2(-100.f, pRigid->GetVelocity().y));
	}

	if (KEY_TAP(KEY::D))
	{
		pRigid->SetVelocity(Vec2(100.f, pRigid->GetVelocity().y));
	}
}

void CPlayer::update_animation()
{	

	switch (m_eCurStateLower)
	{
		if (m_ePrevStateLower == m_eCurStateLower && m_iPrevDir == m_iDir)
			break;

	case PLAYER_STATE::IDLE:
		if (m_iDir == -1)
			GetAnimator()->PlayL(L"PLAYER_IDLE_LOWER_PART_LEFT", true);
		else
			GetAnimator()->PlayL(L"PLAYER_IDLE_LOWER_PART_RIGHT", true);

		break;
	case PLAYER_STATE::WALK:
		if (m_iDir == -1)
			GetAnimator()->PlayL(L"PLAYER_WALK_LOWER_PART_LEFT", true);
		else
			GetAnimator()->PlayL(L"PLAYER_WALK_LOWER_PART_RIGHT", true);

		break;

	case PLAYER_STATE::JUMP:
		if (m_iDir == -1)
			GetAnimator()->PlayL(L"PLAYER_IDLE_JUMP_LOWER_PART_LEFT", true);
		else
			GetAnimator()->PlayL(L"PLAYER_IDLE_JUMP_LOWER_PART_RIGHT", true);

		break;

	case PLAYER_STATE::SIT_DOWN:
		if (m_iDir == -1)
			GetAnimator()->PlayL(L"PLAYER_IDLE_SIT_DOWN_LEFT", true);
		else
			GetAnimator()->PlayL(L"PLAYER_IDLE_SIT_DOWN_RIGHT", true);

		break;
		
	case PLAYER_STATE::SIT_DOWN_WALK:
		if (m_iDir == -1)
			GetAnimator()->PlayL(L"PLAYER_IDLE_SIT_DOWN_WALK_LEFT", true);
		else
			GetAnimator()->PlayL(L"PLAYER_IDLE_SIT_DOWN_WALK_RIGHT", true);

		break;

	//case PLAYER_STATE::STAND_UP:
	//	if (m_iDir == -1)
	//		GetAnimator()->PlayL(L"PLAYER_IDLE_LOWER_PART_LEFT", true);
	//	else
	//		GetAnimator()->PlayL(L"PLAYER_IDLE_LOWER_PART_RIGHT", true);

	//	break;

	case PLAYER_STATE::DEAD:

		break;
	}
	

	switch (m_eCurStateUpper)
	{
		if (m_ePrevStateUpper == m_eCurStateUpper && m_iPrevDir == m_iDir)
			break;

	case PLAYER_STATE::IDLE:
		if (m_iDir == -1)
			GetAnimator()->PlayU(L"PLAYER_IDLE_UPPER_PART_LEFT", true);
		else
			GetAnimator()->PlayU(L"PLAYER_IDLE_UPPER_PART_RIGHT", true);

		break;
	case PLAYER_STATE::WALK:
		if (m_iDir == -1)
			GetAnimator()->PlayU(L"PLAYER_WALK_UPPER_PART_LEFT", true);
		else
			GetAnimator()->PlayU(L"PLAYER_WALK_UPPER_PART_RIGHT", true);
	
		break;

	case PLAYER_STATE::JUMP:
		if (m_iDir == -1)
			GetAnimator()->PlayU(L"PLAYER_IDLE_JUMP_UPPER_PART_LEFT", true);
		else
			GetAnimator()->PlayU(L"PLAYER_IDLE_JUMP_UPPER_PART_RIGHT", true);
	
		break;

	case PLAYER_STATE::ATTACK:
	{
		switch (m_eCurAttackState)
		{
		case ATTACK_KIND::NONE:

			break;

		case ATTACK_KIND::SHOOT:
			if (m_iDir == -1)
				GetAnimator()->PlayU(L"PLAYER_SHOOT_UPPER_PART_LEFT", false);
			else
				GetAnimator()->PlayU(L"PLAYER_SHOOT_UPPER_PART_RIGHT", false);

			break;
			
		case ATTACK_KIND::SHOOT_UP:
			if (m_iDir == -1)
				GetAnimator()->PlayU(L"PLAYER_SHOOT_UP_UPPER_PART_LEFT", false);
			else
				GetAnimator()->PlayU(L"PLAYER_SHOOT_UP_UPPER_PART_RIGHT", false);

			break;
			
		case ATTACK_KIND::SHOOT_DOWN:
			if (m_iDir == -1)
				GetAnimator()->PlayU(L"PLAYER_SHOOT_UPPER_PART_LEFT", false);
			else
				GetAnimator()->PlayU(L"PLAYER_SHOOT_UPPER_PART_RIGHT", false);

			break;

		case ATTACK_KIND::MELEE_ATTACK:

			break;

		case ATTACK_KIND::GRENADE_THROW:
			if (m_iDir == -1)
				GetAnimator()->PlayU(L"PLAYER_GRENADE_THROW_UPPER_PART_LEFT", false);
			else
				GetAnimator()->PlayU(L"PLAYER_GRENADE_THROW_UPPER_PART_RIGHT", false);

			break;

		case ATTACK_KIND::SIT_DOWN_SHOOT:
			if (m_iDir == -1)
				GetAnimator()->PlayU(L"PLAYER_IDLE_SIT_DOWN_SHOOT_LEFT", false);
			else
				GetAnimator()->PlayU(L"PLAYER_IDLE_SIT_DOWN_SHOOT_RIGHT", false);

			break;

		case ATTACK_KIND::SIT_DOWN_MELEE_ATTACK:

			break;

		case ATTACK_KIND::SIT_DOWN_GRENADE_THROW:
			if (m_iDir == -1)
				GetAnimator()->PlayU(L"PLAYER_IDLE_SIT_DOWN_GRENADE_THROW_LEFT", false);
			else
				GetAnimator()->PlayU(L"PLAYER_IDLE_SIT_DOWN_GRENADE_THROW_RIGHT", false);

			break;

		case ATTACK_KIND::SKILL_ATT_1:
			
			break;
		}

		//case PLAYER_STATE::STAND_UP:
		//	if (m_iDir == -1)
		//		GetAnimator()->PlayL(L"PLAYER_IDLE_LOWER_PART_LEFT", true);
		//	else
		//		GetAnimator()->PlayL(L"PLAYER_IDLE_LOWER_PART_RIGHT", true);

		//	break;

	}
		break;

	case PLAYER_STATE::LOOK_UP:
		if (m_iDir == -1)
			GetAnimator()->PlayU(L"PLAYER_LOOK_UP_UPPER_PART_LEFT", true);
		else
			GetAnimator()->PlayU(L"PLAYER_LOOK_UP_UPPER_PART_RIGHT", true);

		break;

	case PLAYER_STATE::LOOK_DOWN:
		if (m_iDir == -1)
			GetAnimator()->PlayU(L"PLAYER_LOOK_DOWN_UPPER_PART_LEFT", false);
		else
			GetAnimator()->PlayU(L"PLAYER_LOOK_DOWN_UPPER_PART_RIGHT", false);

		break;

	case PLAYER_STATE::DEAD:

		break;
	}


}

void CPlayer::update_gravity()
{
	GetRigidBody()->AddForce(Vec2(0.f, 500.f));
}

void CPlayer::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (L"Ground" == _pOther->GetObj()->GetName())
	{
		Vec2 vPos = GetPos();
		if (vPos.y < pOtherObj->GetPos().y)
		{
			m_eCurStateLower = PLAYER_STATE::IDLE;
		}
	}
}
