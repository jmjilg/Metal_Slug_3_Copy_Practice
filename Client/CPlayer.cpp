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
	, m_eBefore_The_Change_Upper(PLAYER_STATE::IDLE)
	, m_eBefore_The_Change_Lower(PLAYER_STATE::IDLE)
	, m_eCurWeapon(WEAPON::HAND_GUN)
	, m_ePrevWeapon(WEAPON::HAND_GUN)
	, m_iDir(1)
	, m_iPrevDir(1)
	, m_iGrenade(10)
	, m_iGrenadeCount(0)
	, m_bJump(false)
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
	GetAnimator()->LoadAnimation(L"animation\\PLAYER_HAND_GUN_LOOK_DOWN_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\PLAYER_HAND_GUN_LOOK_DOWN_RIGHT.anim");

	m_stkStateLower.push(PLAYER_STATE::IDLE);
	m_stkStateUpper.push(PLAYER_STATE::IDLE);




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

	if (m_ePrevStateLower != m_stkStateLower.top())
		m_eBefore_The_Change_Lower = m_ePrevStateLower;

	if (m_ePrevStateUpper != m_stkStateUpper.top())
		m_eBefore_The_Change_Upper = m_ePrevStateUpper;

	m_ePrevStateLower = m_stkStateLower.top();
	m_ePrevStateUpper = m_stkStateUpper.top();
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

void CPlayer::LOWERPART_update()
{
	switch (m_stkStateLower.top())
	{
	case PLAYER_STATE::IDLE:
		update_IDLE(m_stkStateLower); 
		break;
		
	case PLAYER_STATE::JUMP:
		update_JUMP(m_stkStateLower); // JUMP_WALK와의 상호작용 구현 필요
		break;		
		
	case PLAYER_STATE::WALK:
		update_WALK(m_stkStateLower);
		break;
		
	case PLAYER_STATE::WALK_JUMP:
		update_WALK_JUMP(m_stkStateLower);
		break;
		
	case PLAYER_STATE::SIT_DOWN:
		update_SIT_DOWN(m_stkStateLower);
		break;
		
	case PLAYER_STATE::HAND_GUN_SIT_DOWN:
		update_HAND_GUN_SIT_DOWN(m_stkStateLower);
		break;
		
	case PLAYER_STATE::SIT_DOWN_WALK:
		update_SIT_DOWN_WALK(m_stkStateLower);
		break;

	}
}

void CPlayer::UPPERPART_update()
{
	switch (m_stkStateUpper.top())
	{
	case PLAYER_STATE::NONE:
		update_NONE(m_stkStateUpper);
		break;
		
	case PLAYER_STATE::IDLE:
		update_IDLE(m_stkStateUpper);
		break;

	case PLAYER_STATE::JUMP:
		update_JUMP(m_stkStateUpper); // JUMP_WALK와의 상호작용 구현 필요
		break;		

	case PLAYER_STATE::WALK:
		update_WALK(m_stkStateUpper);
		break;

	case PLAYER_STATE::WALK_JUMP:
		update_WALK_JUMP(m_stkStateUpper);
		break;
		
	case PLAYER_STATE::HAND_GUN_SHOOT:
		update_HAND_GUN_SHOOT(m_stkStateUpper);
		break;
		
	case PLAYER_STATE::LOOK_DOWN:
		update_LOOK_DOWN(m_stkStateUpper);
		break;
		
	case PLAYER_STATE::HAND_GUN_LOOK_DOWN:
		update_HAND_GUN_LOOK_DOWN(m_stkStateUpper);
		break;
		
	case PLAYER_STATE::LOOK_UP: 
		update_LOOK_UP(m_stkStateUpper);
		break;
		
	case PLAYER_STATE::HAND_GUN_LOOK_UP: 
		update_HAND_GUN_LOOK_UP(m_stkStateUpper);
		break;

	}
}

void CPlayer::update_NONE(stack<PLAYER_STATE>& _stkState)
{
	if (KEY_AWAY(KEY::S))
	{
		if (PLAYER_STATE::IDLE == m_eBefore_The_Change_Upper)
		{
			_stkState.pop();
			_stkState.push(PLAYER_STATE::IDLE);
		}	
		else if (PLAYER_STATE::WALK == m_eBefore_The_Change_Upper)
		{
			_stkState.pop();
			_stkState.push(PLAYER_STATE::WALK);
		}
		else
		{
			_stkState.pop();
			_stkState.push(PLAYER_STATE::IDLE);
		}
		GetAnimator()->StopAnimationU(false);
	}
	else
	{
		GetAnimator()->StopAnimationU(true);
	}

}

void CPlayer::update_IDLE(stack<PLAYER_STATE>& _stkState)
{
	if (KEY_TAP(KEY::K))
	{
		if (GetRigidBody())
		{
			GetRigidBody()->SetVelocity(Vec2(GetRigidBody()->GetVelocity().x, -350.f));
		}
		_stkState.pop();
		_stkState.push(PLAYER_STATE::JUMP);
	} 
	else if (KEY_HOLD(KEY::A))
	{
		m_iDir = -1;
		_stkState.pop();
		_stkState.push(PLAYER_STATE::WALK);
	}
	else if (KEY_HOLD(KEY::D))
	{
		m_iDir = 1;
		_stkState.pop();
		_stkState.push(PLAYER_STATE::WALK);
	}
	else if (KEY_HOLD(KEY::S) && GetGravity()->GetGround())
	{
		if (&_stkState == &m_stkStateUpper)
		{
			_stkState.pop();
			_stkState.push(PLAYER_STATE::NONE);
		}
		else
		{
			_stkState.pop();
			_stkState.push(PLAYER_STATE::SIT_DOWN);
		}

	}	
	else if (KEY_HOLD(KEY::W) && (&_stkState == &m_stkStateUpper) )
	{
		_stkState.pop();
		_stkState.push(PLAYER_STATE::LOOK_UP);
	}

	else if (KEY_TAP(KEY::J) && (&_stkState == &m_stkStateUpper))
	{
		_stkState.push(PLAYER_STATE::HAND_GUN_SHOOT);
	}

}

void CPlayer::update_JUMP(stack<PLAYER_STATE>& _stkState)
{
	if (GetGravity()->GetGround()) // RigidBody에 대한 내용 수정 필요.
	{
		_stkState.pop();
		_stkState.push(PLAYER_STATE::IDLE);
	}

	else if (KEY_HOLD(KEY::S) && (&_stkState == &m_stkStateUpper))
	{
		_stkState.pop();
		_stkState.push(PLAYER_STATE::LOOK_DOWN);
	}

	else if (KEY_TAP(KEY::J) && (&_stkState == &m_stkStateUpper))
	{
		_stkState.push(PLAYER_STATE::HAND_GUN_SHOOT);
	}

	
}

void CPlayer::update_WALK(stack<PLAYER_STATE>& _stkState)
{
	if (0.f == GetRigidBody()->GetSpeed())
	{
		_stkState.pop();
		_stkState.push(PLAYER_STATE::IDLE);
	}

	else if (KEY_AWAY(KEY::A))
	{
		_stkState.pop();
		_stkState.push(PLAYER_STATE::IDLE);
	}	

	else if (KEY_AWAY(KEY::D))
	{
		_stkState.pop();
		_stkState.push(PLAYER_STATE::IDLE);
	}

	else if (KEY_HOLD(KEY::S))
	{		
		if (&_stkState == &m_stkStateUpper)
		{
			_stkState.pop();
			_stkState.push(PLAYER_STATE::NONE);
		}	
		else
		{
			_stkState.pop();
			_stkState.push(PLAYER_STATE::SIT_DOWN_WALK);

		}
	}

	else if (KEY_TAP(KEY::J) && (&_stkState == &m_stkStateUpper))
	{
		_stkState.push(PLAYER_STATE::HAND_GUN_SHOOT);
	}

	else if (KEY_TAP(KEY::K))
	{
		if (GetRigidBody())
		{
			GetRigidBody()->SetVelocity(Vec2(GetRigidBody()->GetVelocity().x, -350.f));
		}
		_stkState.pop();
		_stkState.push(PLAYER_STATE::WALK_JUMP);
	}

	else if (KEY_HOLD(KEY::W) && (&_stkState == &m_stkStateUpper))
	{
		_stkState.pop();
		_stkState.push(PLAYER_STATE::LOOK_UP);
	}

}

void CPlayer::update_WALK_JUMP(stack<PLAYER_STATE>& _stkState)
{
	if (GetGravity()->GetGround())
	{
		_stkState.pop();
		_stkState.push(PLAYER_STATE::WALK);
	}


	else if (KEY_TAP(KEY::J) && (&_stkState == &m_stkStateUpper))
	{
		_stkState.push(PLAYER_STATE::HAND_GUN_SHOOT);
	}

}

void CPlayer::update_SIT_DOWN(stack<PLAYER_STATE>& _stkState)
{
	if (KEY_AWAY(KEY::S))
	{
		_stkState.pop();
		_stkState.push(PLAYER_STATE::IDLE);
	}

	else if (KEY_HOLD(KEY::A))
	{
		m_iDir = -1;
		_stkState.pop();
		_stkState.push(PLAYER_STATE::SIT_DOWN_WALK);
	}

	else if (KEY_HOLD(KEY::D))
	{
		m_iDir = 1;
		_stkState.pop();
		_stkState.push(PLAYER_STATE::SIT_DOWN_WALK);
	}
}

void CPlayer::update_SIT_DOWN_WALK(stack<PLAYER_STATE>& _stkState)
{
	if (KEY_AWAY(KEY::A))
	{
		_stkState.pop();
		_stkState.push(PLAYER_STATE::SIT_DOWN);
		return;
	}
	
	else if (KEY_AWAY(KEY::D))
	{
		_stkState.pop();
		_stkState.push(PLAYER_STATE::SIT_DOWN);
	}

	else if (KEY_AWAY(KEY::S))
	{
		_stkState.pop();
		_stkState.push(PLAYER_STATE::WALK);
	}

}

void CPlayer::update_LOOK_DOWN(stack<PLAYER_STATE>& _stkState)
{
	if (KEY_AWAY(KEY::S) && !GetGravity()->GetGround())
	{
		_stkState.pop();
		_stkState.push(PLAYER_STATE::JUMP);
	}
	else if (GetGravity()->GetGround())
	{
		_stkState.pop();
		_stkState.push(PLAYER_STATE::JUMP);
	}
	
}

void CPlayer::update_LOOK_UP(stack<PLAYER_STATE>& _stkState)
{
	if (KEY_AWAY(KEY::W))
	{
		if (PLAYER_STATE::IDLE == m_eBefore_The_Change_Upper) // 이전 상태가 LOOK_UP이라서 안돌아옴
		{
			_stkState.pop();
			_stkState.push(PLAYER_STATE::IDLE);
		}
		else if (PLAYER_STATE::WALK == m_eBefore_The_Change_Upper)
		{
			_stkState.pop();
			_stkState.push(PLAYER_STATE::WALK);
		}	
		else
		{
			_stkState.pop();
			_stkState.push(PLAYER_STATE::IDLE);
		} // 키를 마구잡이로 연타하다 보면 특정 상태로 고정될 때가 있음.(재생을 멈췄다 재생시켰다 하다보니 UPPER part가 특정상태로 고정되버림) 정확한 원인을 아는게 아니라 살짝 불안정하지만 임시방편으로 이렇게 함		
	}
	else if (KEY_TAP(KEY::J) && (&_stkState == &m_stkStateUpper) && KEY_HOLD(KEY::W))
		//|| KEY_TAP(KEY::J) && (&_stkState == &m_stkStateUpper) && KEY_HOLD(KEY::A)
		//|| KEY_TAP(KEY::J) && (&_stkState == &m_stkStateUpper) && KEY_HOLD(KEY::D)) // 모르겠네... 왜 안재생되는 거냐
	{
		_stkState.push(PLAYER_STATE::HAND_GUN_LOOK_UP);
	}
}

void CPlayer::update_HAND_GUN_SHOOT(stack<PLAYER_STATE>& _stkState)
{
	if (GetAnimator()->GetCurAnimU()->IsFinish()) // 애니메이션이 끝났을 때
	{
		if (-1 == m_iDir)
			GetAnimator()->FindAnimation(L"PLAYER_SHOOT_UPPER_PART_LEFT")->SetFrame(0);
		else
			GetAnimator()->FindAnimation(L"PLAYER_SHOOT_UPPER_PART_RIGHT")->SetFrame(0);

		_stkState.pop(); // 원래 상태로 돌아간다
	}
	else // 애니메이션이 안끝났을 때
	{
		if (KEY_TAP(KEY::J)) // 공격 모션 진행중에 또다시 공격 키를 눌렀을 때. 공격 모션을 처음부터 초기화한다.
		{
			if (-1 == m_iDir)
				GetAnimator()->FindAnimation(L"PLAYER_SHOOT_UPPER_PART_LEFT")->SetFrame(0);
			else
				GetAnimator()->FindAnimation(L"PLAYER_SHOOT_UPPER_PART_RIGHT")->SetFrame(0);
		}
	}

}

void CPlayer::update_HAND_GUN_LOOK_UP(stack<PLAYER_STATE>& _stkState)
{
	if (KEY_AWAY(KEY::W))
	{
		if (PLAYER_STATE::IDLE == m_eBefore_The_Change_Upper) // 이전 상태가 LOOK_UP이라서 안돌아옴
		{
			_stkState.pop();
			_stkState.pop();
			_stkState.push(PLAYER_STATE::IDLE);
			_stkState.push(PLAYER_STATE::HAND_GUN_LOOK_UP);
		}
		else if (PLAYER_STATE::WALK == m_eBefore_The_Change_Upper)
		{
			_stkState.pop();
			_stkState.pop();
			_stkState.push(PLAYER_STATE::WALK);
			_stkState.push(PLAYER_STATE::HAND_GUN_LOOK_UP);
		}
		else
		{
			_stkState.pop();
			_stkState.pop();
			_stkState.push(PLAYER_STATE::IDLE);
			_stkState.push(PLAYER_STATE::HAND_GUN_LOOK_UP);
		}
	}


	if (GetAnimator()->GetCurAnimU()->IsFinish()) // 애니메이션이 끝났을 때
	{
		if (-1 == m_iDir)
			GetAnimator()->FindAnimation(L"PLAYER_SHOOT_UP_UPPER_PART_LEFT")->SetFrame(0);
		else
			GetAnimator()->FindAnimation(L"PLAYER_SHOOT_UP_UPPER_PART_RIGHT")->SetFrame(0);

		_stkState.pop(); // 원래 상태로 돌아간다
	}
	else // 애니메이션이 안끝났을 때
	{
		if (KEY_TAP(KEY::J)) // 공격 모션 진행중에 또다시 공격 키를 눌렀을 때. 공격 모션을 처음부터 초기화한다.
		{
			if (-1 == m_iDir)
				GetAnimator()->FindAnimation(L"PLAYER_SHOOT_UP_UPPER_PART_LEFT")->SetFrame(0);
			else
				GetAnimator()->FindAnimation(L"PLAYER_SHOOT_UP_UPPER_PART_RIGHT")->SetFrame(0);
		}
	}

}

void CPlayer::update_HAND_GUN_LOOK_DOWN(stack<PLAYER_STATE>& _stkState)
{

	if (GetAnimator()->GetCurAnimU()->IsFinish()) // 애니메이션이 끝났을 때
	{
		if (-1 == m_iDir)
			GetAnimator()->FindAnimation(L"PLAYER_HAND_GUN_LOOK_DOWN_LEFT")->SetFrame(0);
		else
			GetAnimator()->FindAnimation(L"PLAYER_HAND_GUN_LOOK_DOWN_RIGHT")->SetFrame(0);

		_stkState.pop(); // 원래 상태로 돌아간다
	}
	else // 애니메이션이 안끝났을 때
	{
		if (KEY_TAP(KEY::J)) // 공격 모션 진행중에 또다시 공격 키를 눌렀을 때. 공격 모션을 처음부터 초기화한다.
		{
			if (-1 == m_iDir)
				GetAnimator()->FindAnimation(L"PLAYER_HAND_GUN_LOOK_DOWN_LEFT")->SetFrame(0);
			else
				GetAnimator()->FindAnimation(L"PLAYER_HAND_GUN_LOOK_DOWN_RIGHT")->SetFrame(0);
		}
	}
}

void CPlayer::update_HAND_GUN_SIT_DOWN(stack<PLAYER_STATE>& _stkState)
{
}


void CPlayer::update_state()
{
	LOWERPART_update();
	UPPERPART_update();


	//GetAnimator()->StopAnimationL(false);
	//GetAnimator()->StopAnimationU(false);

	//if (KEY_TAP(KEY::K))
	//{
	//	//CreateMissile();
	//	m_eMoveState = PLAYER_STATE::JUMP;
	//	m_eCurStateUpper = PLAYER_STATE::JUMP;
	//	m_eCurStateLower = PLAYER_STATE::JUMP;
	//	if (GetRigidBody())
	//	{
	//		GetRigidBody()->SetVelocity(Vec2(GetRigidBody()->GetVelocity().x, -350.f));
	//	}
	//}

	//if (0.f == GetRigidBody()->GetSpeed() && PLAYER_STATE::JUMP != m_eCurStateLower)
	//{
	//	m_eCurStateUpper = PLAYER_STATE::IDLE;
	//	m_eCurStateLower = PLAYER_STATE::IDLE;
	//}

	//if (KEY_HOLD(KEY::S))
	//{
	//	// 점프중일때 아래를 본다
	//	if (PLAYER_STATE::JUMP == m_eCurStateLower)
	//	{
	//		m_eMoveState = PLAYER_STATE::LOOK_DOWN;
	//		m_eCurStateUpper = PLAYER_STATE::LOOK_DOWN;
	//	}
	//	// 점프중이 아닐땐 플레이어 캐릭터가 앉는다
	//	else
	//	{
	//		GetAnimator()->StopAnimationU(true);
	//		m_eMoveState = PLAYER_STATE::SIT_DOWN;
	//		m_eCurStateLower = PLAYER_STATE::SIT_DOWN;
	//	}
	//}

	//if (KEY_HOLD(KEY::A))
	//{
	//	m_iDir = -1;

	//	if (PLAYER_STATE::SIT_DOWN == m_eMoveState)
	//	{
	//		m_eMoveState = PLAYER_STATE::SIT_DOWN_WALK;
	//		m_eCurStateLower = PLAYER_STATE::SIT_DOWN_WALK;
	//		GetAnimator()->StopAnimationU(true);

	//	}
	//	else if (PLAYER_STATE::JUMP != m_eCurStateLower)
	//	{
	//		m_eMoveState = PLAYER_STATE::WALK;
	//		m_eCurStateUpper = PLAYER_STATE::WALK;
	//		m_eCurStateLower = PLAYER_STATE::WALK;
	//	}
	//}

	//if (KEY_HOLD(KEY::D))
	//{
	//	m_iDir = 1;

	//	if (PLAYER_STATE::SIT_DOWN == m_eMoveState)
	//	{
	//		m_eMoveState = PLAYER_STATE::SIT_DOWN_WALK;
	//		m_eCurStateLower = PLAYER_STATE::SIT_DOWN_WALK;
	//		GetAnimator()->StopAnimationU(true);
	//	}

	//	else if (PLAYER_STATE::JUMP != m_eCurStateLower)
	//	{
	//		m_eMoveState = PLAYER_STATE::WALK;
	//		m_eCurStateUpper = PLAYER_STATE::WALK;
	//		m_eCurStateLower = PLAYER_STATE::WALK;
	//	}
	//}

	//if (KEY_HOLD(KEY::W))
	//{
	//	m_eMoveState = PLAYER_STATE::LOOK_UP;
	//	m_eCurStateUpper = PLAYER_STATE::LOOK_UP;
	//}

	//if (KEY_TAP(KEY::J))
	//{		
	//	if (PLAYER_STATE::LOOK_UP == m_eCurStateUpper)
	//	{
	//		m_eCurStateUpper = PLAYER_STATE::LOOK_UP;
	//		m_eCurAttackState = ATTACK_KIND::SHOOT_UP;
	//		if (-1 == m_iDir)
	//			GetAnimator()->FindAnimation(L"PLAYER_SHOOT_UP_UPPER_PART_LEFT")->SetFrame(0);
	//		else
	//			GetAnimator()->FindAnimation(L"PLAYER_SHOOT_UP_UPPER_PART_RIGHT")->SetFrame(0);
	//	}
	//	else if (PLAYER_STATE::SIT_DOWN == m_eCurStateLower || PLAYER_STATE::SIT_DOWN_WALK == m_eCurStateLower)
	//	{
	//		GetAnimator()->StopAnimationU(true);
	//		m_eCurAttackState = ATTACK_KIND::SIT_DOWN_SHOOT;
	//		m_eCurStateLower = PLAYER_STATE::SIT_DOWN;
	//		if (-1 == m_iDir)
	//			GetAnimator()->FindAnimation(L"PLAYER_IDLE_SIT_DOWN_SHOOT_LEFT")->SetFrame(0);
	//		else
	//			GetAnimator()->FindAnimation(L"PLAYER_IDLE_SIT_DOWN_SHOOT_RIGHT")->SetFrame(0);

	//	}
	//	else
	//	{
	//		m_eCurStateUpper = PLAYER_STATE::ATTACK;
	//		m_eCurAttackState = ATTACK_KIND::SHOOT;
	//		// 공격 모션 진행중에 또다시 공격 키를 눌렀을 때. 공격 모션을 처음부터 초기화한다.
	//		if (-1 == m_iDir)
	//			GetAnimator()->FindAnimation(L"PLAYER_SHOOT_UPPER_PART_LEFT")->SetFrame(0);
	//		else
	//			GetAnimator()->FindAnimation(L"PLAYER_SHOOT_UPPER_PART_RIGHT")->SetFrame(0);
	//	}

	//	SetIsAttack(true);
	//	m_eAttackState = PLAYER_STATE::ATTACK;
	//}

	//if (KEY_TAP(KEY::L))
	//{
	//	m_eAttackState = PLAYER_STATE::ATTACK;
	//	m_eCurStateUpper = PLAYER_STATE::ATTACK;
	//	m_eCurAttackState = ATTACK_KIND::GRENADE_THROW;
	//	SetIsAttack(true);
	//	// 공격 모션 진행중에 또다시 공격 키를 눌렀을 때. 공격 모션을 처음부터 초기화한다.
	//	if (-1 == m_iDir)
	//		GetAnimator()->FindAnimation(L"PLAYER_GRENADE_THROW_UPPER_PART_LEFT")->SetFrame(0);
	//	else
	//		GetAnimator()->FindAnimation(L"PLAYER_GRENADE_THROW_UPPER_PART_RIGHT")->SetFrame(0);
	//}

	//if (IsAttack())
	//{
	//	m_eCurStateUpper = m_eAttackState;
	//	if (GetAnimator()->GetCurAnimU()->IsFinish())
	//	{
	//		SetIsAttack(false);
	//		m_eCurStateUpper = m_eMoveState;
	//	}
	//}


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
		if (!GetGravity()->GetGround()) // 만약 점프중이라면 가속도 붙음
		{
			pRigid->SetVelocity(Vec2(-100.f, pRigid->GetVelocity().y));
			pRigid->AddForce(Vec2(-300.f, 0.f)); 
		}
		else // 점프중이 아니라면 가속도 안붙음
			pRigid->SetVelocity(Vec2(-100.f, pRigid->GetVelocity().y));
	}

	if (KEY_HOLD(KEY::D))
	{
		if (!GetGravity()->GetGround()) // 만약 점프중이라면 가속도 붙음
		{
			pRigid->SetVelocity(Vec2(100.f, pRigid->GetVelocity().y));
			pRigid->AddForce(Vec2(300.f, 0.f));
		}
		else // 점프중이 아니라면 가속도 안붙음
			pRigid->SetVelocity(Vec2(100.f, pRigid->GetVelocity().y));
	}
	
	if (KEY_AWAY(KEY::A) && GetGravity()->GetGround())
	{
		// 만약 점프중이 아니라면 키를 뗐을때 플레이어 멈춤
		pRigid->SetVelocity(Vec2(0.f, pRigid->GetVelocity().y));
	}

	if (KEY_AWAY(KEY::D) && GetGravity()->GetGround())
	{
		// 만약 점프중이 아니라면 키를 뗐을때 플레이어 멈춤
		pRigid->SetVelocity(Vec2(0.f, pRigid->GetVelocity().y));
	}

	//if (KEY_TAP(KEY::A))
	//{		
	//	pRigid->SetVelocity(Vec2(-300.f, pRigid->GetVelocity().y));
	//}

	//if (KEY_TAP(KEY::D))
	//{
	//	pRigid->SetVelocity(Vec2(300.f, pRigid->GetVelocity().y));
	//}
}

void CPlayer::update_animation()
{	

	switch (m_stkStateLower.top())
	{
		if (m_ePrevStateLower == m_stkStateLower.top() && m_iPrevDir == m_iDir)
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
		
	case PLAYER_STATE::WALK_JUMP:
		if (m_iDir == -1)
			GetAnimator()->PlayL(L"PLAYER_WALK_JUMP_LOWER_PART_LEFT", true);
		else
			GetAnimator()->PlayL(L"PLAYER_WALK_JUMP_LOWER_PART_RIGHT", true);

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
		
	case PLAYER_STATE::HAND_GUN_SIT_DOWN:
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
	

	switch (m_stkStateUpper.top())
	{
		if (m_ePrevStateUpper == m_stkStateUpper.top() && m_iPrevDir == m_iDir)
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
		
	case PLAYER_STATE::WALK_JUMP:
		if (m_iDir == -1)
			GetAnimator()->PlayU(L"PLAYER_WALK_JUMP_UPPER_PART_LEFT", true);
		else
			GetAnimator()->PlayU(L"PLAYER_WALK_JUMP_UPPER_PART_RIGHT", true);
	
		break;

	case PLAYER_STATE::JUMP:
		if (m_iDir == -1)
			GetAnimator()->PlayU(L"PLAYER_IDLE_JUMP_UPPER_PART_LEFT", true);
		else
			GetAnimator()->PlayU(L"PLAYER_IDLE_JUMP_UPPER_PART_RIGHT", true);
	
		break;
		
	case PLAYER_STATE::HAND_GUN_SHOOT:
		if (m_iDir == -1)
			GetAnimator()->PlayU(L"PLAYER_SHOOT_UPPER_PART_LEFT", false);
		else
			GetAnimator()->PlayU(L"PLAYER_SHOOT_UPPER_PART_RIGHT", false);
	
		break;

	case PLAYER_STATE::LOOK_UP:
		if (m_iDir == -1)
			GetAnimator()->PlayU(L"PLAYER_LOOK_UP_UPPER_PART_LEFT", true);
		else
			GetAnimator()->PlayU(L"PLAYER_LOOK_UP_UPPER_PART_RIGHT", true);

		break;
		
	case PLAYER_STATE::HAND_GUN_LOOK_UP:
		if (m_iDir == -1)
			GetAnimator()->PlayU(L"PLAYER_SHOOT_UP_UPPER_PART_LEFT", false);
		else
			GetAnimator()->PlayU(L"PLAYER_SHOOT_UP_UPPER_PART_RIGHT", false);

		break;

	case PLAYER_STATE::LOOK_DOWN:
		if (m_iDir == -1)
			GetAnimator()->PlayU(L"PLAYER_LOOK_DOWN_UPPER_PART_LEFT", true);
		else
			GetAnimator()->PlayU(L"PLAYER_LOOK_DOWN_UPPER_PART_RIGHT", true);

		break;
		
	case PLAYER_STATE::HAND_GUN_LOOK_DOWN:
		if (m_iDir == -1)
			GetAnimator()->PlayU(L"PLAYER_SHOOT_UPPER_PART_LEFT", false);
		else
			GetAnimator()->PlayU(L"PLAYER_SHOOT_UPPER_PART_RIGHT", false);

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
