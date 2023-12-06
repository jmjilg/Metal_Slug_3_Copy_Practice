#include "pch.h"
#include "CPlayer.h"

#include "CSceneMgr.h"
#include "CScene.h"

#include "CKeyMgr.h"

#include "CMissile.h"
#include "CHeavyMachineGun.h"

#include "CResMgr.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "CRigidBody.h"
#include "CGravity.h"
#include "CCore.h"
#include "CKeyMgr.h"
#include "CCamera.h"

CPlayer::CPlayer()
	: m_eCurStateUpper(PLAYER_STATE::IDLE)
	, m_eCurStateLower(PLAYER_STATE::IDLE)
	, m_ePrevStateUpper(PLAYER_STATE::IDLE)
	, m_ePrevStateLower(PLAYER_STATE::IDLE)
	, m_eBefore_The_Change_Upper(PLAYER_STATE::IDLE)
	, m_eBefore_The_Change_Lower(PLAYER_STATE::IDLE)
	, m_eCurWeapon(WEAPON::HEAVY_MACHIN_GUN)
	, m_ePrevWeapon(WEAPON::HAND_GUN)
	, m_iDir(1.f, 0.f)
	, m_iPrevDir(1)
	, m_iGrenade(10)
	, m_iGrenadeCount(0)
	, m_bJump(false)
	, m_vMissilePrevDir(1.f, 0.f)
	, m_llCurCount{}
	, m_llPrevCount{}
	, m_llFrequency{}
	, m_dDT(0.)
	, m_dAcc(0.)
	, m_iCallCount(0)
	, m_iLife(3)
	, m_bAttacked(false)
	, m_bSetCamera(false)
	, m_iBulletCount(0)
	, m_bMainHMGflag(false)
	, m_bSubHMGflag(false)
{
	// Texture 로딩하기
	//m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\Player.bmp");


	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 30.f));
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
	GetAnimator()->LoadAnimation(L"animation\\PLAYER_DEAD_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\PLAYER_DEAD_RIGHT.anim");
	GetAnimator()->LoadAnimation(L"animation\\PLAYER_RESPAWN_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\PLAYER_RESPAWN_RIGHT.anim");

	GetAnimator()->LoadAnimation(L"animation\\HEAVY_MACHINE_GUN_PLAYER_GRENADE_THROW_UPPER_PART_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\HEAVY_MACHINE_GUN_PLAYER_GRENADE_THROW_UPPER_PART_RIGHT.anim");
	GetAnimator()->LoadAnimation(L"animation\\HEAVY_MACHINE_GUN_PLAYER_HAND_GUN_LOOK_DOWN_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\HEAVY_MACHINE_GUN_PLAYER_HAND_GUN_LOOK_DOWN_RIGHT.anim");
	GetAnimator()->LoadAnimation(L"animation\\HEAVY_MACHINE_GUN_PLAYER_IDLE_JUMP_UPPER_PART_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\HEAVY_MACHINE_GUN_PLAYER_IDLE_JUMP_UPPER_PART_RIGHT.anim");
	GetAnimator()->LoadAnimation(L"animation\\HEAVY_MACHINE_GUN_PLAYER_IDLE_SIT_DOWN_GRENADE_THROW_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\HEAVY_MACHINE_GUN_PLAYER_IDLE_SIT_DOWN_GRENADE_THROW_RIGHT.anim");
	GetAnimator()->LoadAnimation(L"animation\\HEAVY_MACHINE_GUN_PLAYER_IDLE_SIT_DOWN_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\HEAVY_MACHINE_GUN_PLAYER_IDLE_SIT_DOWN_RIGHT.anim");
	GetAnimator()->LoadAnimation(L"animation\\HEAVY_MACHINE_GUN_PLAYER_IDLE_SIT_DOWN_SHOOT_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\HEAVY_MACHINE_GUN_PLAYER_IDLE_SIT_DOWN_SHOOT_RIGHT.anim");
	GetAnimator()->LoadAnimation(L"animation\\HEAVY_MACHINE_GUN_PLAYER_IDLE_SIT_DOWN_WALK_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\HEAVY_MACHINE_GUN_PLAYER_IDLE_SIT_DOWN_WALK_RIGHT.anim");
	GetAnimator()->LoadAnimation(L"animation\\HEAVY_MACHINE_GUN_PLAYER_IDLE_UPPER_PART_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\HEAVY_MACHINE_GUN_PLAYER_IDLE_UPPER_PART_RIGHT.anim");
	GetAnimator()->LoadAnimation(L"animation\\HEAVY_MACHINE_GUN_PLAYER_LOOK_DOWN_UPPER_PART_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\HEAVY_MACHINE_GUN_PLAYER_LOOK_DOWN_UPPER_PART_RIGHT.anim");
	GetAnimator()->LoadAnimation(L"animation\\HEAVY_MACHINE_GUN_PLAYER_LOOK_UP_UPPER_PART_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\HEAVY_MACHINE_GUN_PLAYER_LOOK_UP_UPPER_PART_RIGHT.anim");
	GetAnimator()->LoadAnimation(L"animation\\HEAVY_MACHINE_GUN_PLAYER_MELEE_ATTACK_UPPER_PART_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\HEAVY_MACHINE_GUN_PLAYER_MELEE_ATTACK_UPPER_PART_RIGHT.anim");
	GetAnimator()->LoadAnimation(L"animation\\HEAVY_MACHINE_GUN_PLAYER_SHOOT_UP_UPPER_PART_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\HEAVY_MACHINE_GUN_PLAYER_SHOOT_UP_UPPER_PART_RIGHT.anim");
	GetAnimator()->LoadAnimation(L"animation\\HEAVY_MACHINE_GUN_PLAYER_SHOOT_UPPER_PART_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\HEAVY_MACHINE_GUN_PLAYER_SHOOT_UPPER_PART_RIGHT.anim");
	GetAnimator()->LoadAnimation(L"animation\\HEAVY_MACHINE_GUN_PLAYER_WALK_JUMP_UPPER_PART_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\HEAVY_MACHINE_GUN_PLAYER_WALK_JUMP_UPPER_PART_RIGHT.anim");
	GetAnimator()->LoadAnimation(L"animation\\HEAVY_MACHINE_GUN_PLAYER_WALK_UPPER_PART_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\HEAVY_MACHINE_GUN_PLAYER_WALK_UPPER_PART_RIGHT.anim");

	m_stkStateLower.push(PLAYER_STATE::IDLE);
	m_stkStateUpper.push(PLAYER_STATE::IDLE);




	//GetAnimator()->CreateAnimation(L"PLAYER_SHOOT_UPPER_PART_LEFT", pLeftTex, Vec2(1758.f, 1047.f), Vec2(52.f, 25.f), Vec2(-34.f, 0.f), Vec2(3.f, -5.f), 0.1f, 10);
	//GetAnimator()->CreateAnimation(L"PLAYER_SHOOT_UPPER_PART_RIGHT", pRightTex, Vec2(9.f, 1047.f), Vec2(52.f, 25.f), Vec2(34.f, 0.f), Vec2(-7.f, -5.f), 0.1f, 10);


	// Animation 저장해보기
	//GetAnimator()->FindAnimation(L"PLAYER_SHOOT_UPPER_PART_LEFT")->Save(L"animation\\PLAYER_SHOOT_UPPER_PART_LEFT.anim");
	//GetAnimator()->FindAnimation(L"PLAYER_SHOOT_UPPER_PART_RIGHT")->Save(L"animation\\PLAYER_SHOOT_UPPER_PART_RIGHT.anim"); 


	CreateGravity();

	// 현재 카운트 
	QueryPerformanceCounter(&m_llPrevCount);

	// 초당 카운트 횟수
	QueryPerformanceFrequency(&m_llFrequency);
}

CPlayer::~CPlayer()
{

}

void CPlayer::update()
{
	update_move();

	update_state();

	update_animation();

	update_jumptime();


	GetAnimator()->SetTransParentColor(153, 217, 234); // 무시할 RGB값 설정 (한번만 하면 됨)


	if (KEY_TAP(KEY::LBTN) && !m_bAttacked)
	{
		Vec2 vMousePos = CCamera::GetInst()->GetRealPos(CKeyMgr::GetInst()->GetMousePos());
		SetPos(vMousePos);
	}

	if (KEY_TAP(KEY::ENTER))
	{
		if (m_bSetCamera)
			m_bSetCamera = false;
		else
			m_bSetCamera = true;
	}


	if (m_bSetCamera)
	{
		Vec2 vPos = GetPos();
		vPos.x += 292; // 535; 해상도가 1980 768 일때
		vPos.y += 58; // 252; 해상도가 1980 768 일때
		CCamera::GetInst()->SetLookAt(vPos);
	}

	if (KEY_TAP(KEY::J) && !m_bAttacked && m_eCurWeapon == WEAPON::HAND_GUN)
	{
		CreateMissile();
	}
	
	else if (KEY_TAP(KEY::J) && !m_bAttacked && m_eCurWeapon == WEAPON::HEAVY_MACHIN_GUN)
	{
		m_bMainHMGflag = true;
		m_iBulletCount = 0;
	}

	//if (!m_bMainHMGflag)
	//{
	//	if (m_bSubHMGflag)
	//	{
	//		m_bMainHMGflag = true;
	//		m_bSubHMGflag = false;
	//	}
	//}

	if (m_bMainHMGflag && !m_bAttacked)  // 헤비머신건일때 공격키를 눌렀을때, 일정간격으로 총알 4발을 발사함
	{
		m_lBulletAcc = clock();

		if (m_lBulletAcc - m_lBulletStart > 100.f) // 0.1초
		{
			if (m_iBulletCount < 4)
			{
				CreateMissile();
				m_iBulletCount++;
			}
			else
			{
				m_iBulletCount = 0;
				m_bMainHMGflag = false;
			}

			m_lBulletStart = m_lBulletAcc;
		}


	}

	GetAnimator()->update();

	if (m_ePrevStateLower != m_stkStateLower.top())
		m_eBefore_The_Change_Lower = m_ePrevStateLower;

	if (m_ePrevStateUpper != m_stkStateUpper.top())
		m_eBefore_The_Change_Upper = m_ePrevStateUpper;

	m_ePrevStateLower = m_stkStateLower.top();
	m_ePrevStateUpper = m_stkStateUpper.top();
	m_iPrevDir = m_iDir.x;

	CCore::GetInst()->SetPlayerPos(GetPos()); // 화면에 출력할 플레이어 좌표 정보 기록
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

	//SetColliderRender(false);   Collider 렌더링 안하도록 설정
	

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
	// Missile Object
	CMissile* pMissile = new CMissile;
	pMissile->SetName(L"Missile_Player");

	Vec2 vMissilePos = GetPos();	
	float fSpeed = 600.f;
	//vMissilePos.y -= GetScale().y / 2.f; 메탈슬러그는 탑뷰가 아니기 때문에 이 코드가 없어도 됨
	
	if (m_eCurWeapon == WEAPON::HAND_GUN)
	{
		vMissilePos.x += 10;
		vMissilePos.y += 10;
		if (m_iDir.y != 0)  // 위나 밑을 볼때 총알 오프셋 조정, x가 1 일때 오른쪽, -1 일때 왼쪽, y가 -1일때 위쪽, 1일때 아래쪽임. 0일때는 위나 아래 둘다 아닐때
			vMissilePos.x -= 10;
		if (m_stkStateUpper.top() == PLAYER_STATE::NONE)
			vMissilePos.y += 10;
		
	}

	if (m_eCurWeapon == WEAPON::HEAVY_MACHIN_GUN)
	{ // 위로 쏠때랑 아래로 쏠때, 대각선으로 쏠때는 아직 구현 안했음 
		pMissile->SetHMG(true);
		fSpeed = 450.f;
	}

	// 미사일 나가는 방향 설정
	pMissile->SetScale(Vec2(25.f, 25.f));
	if (m_iDir.x == 1)
		pMissile->SetDir(MISSILE_DIR::RIGHT);
	else
		pMissile->SetDir(MISSILE_DIR::LEFT);
	if (m_iDir.y >= 1)
		pMissile->SetDir(MISSILE_DIR::DOWN);
	else if (m_iDir.y < 0)
		pMissile->SetDir(MISSILE_DIR::UP);

	switch (pMissile->GetDir())
	{
	case MISSILE_DIR::RIGHT:
		vMissilePos.x += 10;
		vMissilePos.y += 20;
		break;
	case MISSILE_DIR::LEFT:
		vMissilePos.x -= 30;
		vMissilePos.y += 20;
		break;
	case MISSILE_DIR::DOWN:
		vMissilePos.x += 10;
		vMissilePos.y += 20;
		break;
	case MISSILE_DIR::UP:
		vMissilePos.x += 8;
		vMissilePos.y -= 40;
		break;
	}

	pMissile->SetPos(vMissilePos);
	pMissile->SetSpeed(fSpeed);
	
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
		update_HAND_GUN_SHOOT_SIT_DOWN(m_stkStateLower);
		break;

	case PLAYER_STATE::SIT_DOWN_WALK:
		update_SIT_DOWN_WALK(m_stkStateLower);
		break;

	case PLAYER_STATE::DEAD:
		update_DEAD(m_stkStateLower);
		break;
		
	case PLAYER_STATE::RESPAWN:
		update_RESPAWN(m_stkStateLower);
		break;


	}
}

void CPlayer::UPPERPART_update()
{
	// m_btemp = CKeyMgr::GetInst()->GetKeyState(KEY::J) == KEY_STATE::TAP;

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
		update_HAND_GUN_SHOOT_DOWN(m_stkStateUpper);
		break;
		
	case PLAYER_STATE::LOOK_UP: 
		update_LOOK_UP(m_stkStateUpper);
		break;
		
	case PLAYER_STATE::HAND_GUN_LOOK_UP: 
		update_HAND_GUN_SHOOT_UP(m_stkStateUpper);
		break;		
		
	}
}

void CPlayer::update_NONE(stack<PLAYER_STATE>& _stkState)
{
	//if (GetCollider() != nullptr)
	//{
	//	GetCollider()->SetOffsetPos(Vec2(0.f, 15.f));
	//	GetCollider()->SetScale(Vec2(10.f, 10.f));
	//}

	if (m_bAttacked)
	{
		_stkState.pop();
		_stkState.push(PLAYER_STATE::NONE);
		GetAnimator()->StopAnimationU(true);
		return;
	}


	if (KEY_AWAY(KEY::S))
	{

		//if (GetCollider() != nullptr)
		//{
		//	GetCollider()->SetOffsetPos(Vec2(0.f, 15.f));
		//	GetCollider()->SetScale(Vec2(20.f, 20.f));
		//}

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
	if (m_bAttacked)
	{
		if ((&_stkState == &m_stkStateUpper))
		{
			_stkState.pop();
			_stkState.push(PLAYER_STATE::NONE);  // Upper Part 라면 NONE 상태로, LOWER 파트라면 DEAD 상태로
		}
		else
		{
			_stkState.pop();
			_stkState.push(PLAYER_STATE::DEAD);
		}
		return;
	}

	if(&_stkState == &m_stkStateUpper)
		m_iDir.y = 0;

	if (KEY_TAP(KEY::K))
	{
		if (GetRigidBody())
		{
			GetRigidBody()->SetVelocity(Vec2(GetRigidBody()->GetVelocity().x, -350.f));
		}
		m_dAcc = 0.f;
		m_bStandLine = false;
		_stkState.pop();
		_stkState.push(PLAYER_STATE::JUMP);
	} 
	else if (KEY_HOLD(KEY::A))
	{
		m_iDir.x = -1;
		_stkState.pop();
		_stkState.push(PLAYER_STATE::WALK);
	}
	else if (KEY_HOLD(KEY::D))
	{
		m_iDir.x = 1;
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
	if (m_bAttacked)
	{
		if ((&_stkState == &m_stkStateUpper))
		{
			_stkState.pop();
			_stkState.push(PLAYER_STATE::NONE);  // Upper Part 라면 NONE 상태로, LOWER 파트라면 DEAD 상태로
		}
		else
		{
			_stkState.pop();
			_stkState.push(PLAYER_STATE::DEAD);
		}
		return;
	}

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
	
	else if (KEY_HOLD(KEY::W) && (&_stkState == &m_stkStateUpper))
	{
		_stkState.pop();
		_stkState.push(PLAYER_STATE::LOOK_UP);
	}

	else if (KEY_TAP(KEY::J) && (&_stkState == &m_stkStateUpper))
	{		
		if (KEY_HOLD(KEY::A))
			m_iDir.x = -1;
		else if (KEY_HOLD(KEY::D))
			m_iDir.x = -1;

		_stkState.push(PLAYER_STATE::HAND_GUN_SHOOT);
	}

	
}

void CPlayer::update_WALK(stack<PLAYER_STATE>& _stkState)
{
	if (m_bAttacked)
	{
		if ((&_stkState == &m_stkStateUpper))
		{
			_stkState.pop();
			_stkState.push(PLAYER_STATE::NONE);  // Upper Part 라면 NONE 상태로, LOWER 파트라면 DEAD 상태로
		}
		else
		{
			_stkState.pop();
			_stkState.push(PLAYER_STATE::DEAD);
		}
		return;
	}

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
		m_dAcc = 0.f;
		m_bStandLine = false;
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
	if (m_bAttacked)
	{
		if ((&_stkState == &m_stkStateUpper))
		{
			_stkState.pop();
			_stkState.push(PLAYER_STATE::NONE);  // Upper Part 라면 NONE 상태로, LOWER 파트라면 DEAD 상태로
		}
		else
		{
			_stkState.pop();
			_stkState.push(PLAYER_STATE::DEAD);
		}
		return;
	}

	if (GetGravity()->GetGround())
	{
		_stkState.pop();
		_stkState.push(PLAYER_STATE::WALK);
	}
	else if (KEY_HOLD(KEY::S) && (&_stkState == &m_stkStateUpper))
	{
		_stkState.pop();
		_stkState.push(PLAYER_STATE::LOOK_DOWN);
	}
	else if (KEY_TAP(KEY::J) && (&_stkState == &m_stkStateUpper))
	{
		if (KEY_HOLD(KEY::A))
			m_iDir.x = -1;
		else if (KEY_HOLD(KEY::D))
			m_iDir.x = 1;

		_stkState.push(PLAYER_STATE::HAND_GUN_SHOOT);
	}

}

void CPlayer::update_SIT_DOWN(stack<PLAYER_STATE>& _stkState)
{
	if (m_bAttacked)
	{
		if ((&_stkState == &m_stkStateUpper))
		{
			_stkState.pop();
			_stkState.push(PLAYER_STATE::NONE);  // Upper Part 라면 NONE 상태로, LOWER 파트라면 DEAD 상태로
		}
		else
		{
			_stkState.pop();
			_stkState.push(PLAYER_STATE::DEAD);
		}
		return;
	}

	if (KEY_AWAY(KEY::S))
	{
		_stkState.pop();
		_stkState.push(PLAYER_STATE::IDLE);
	}

	else if (KEY_HOLD(KEY::A))
	{
		m_iDir.x = -1;
		_stkState.pop();
		_stkState.push(PLAYER_STATE::SIT_DOWN_WALK);
	}

	else if (KEY_HOLD(KEY::D))
	{
		m_iDir.x = 1;
		_stkState.pop();
		_stkState.push(PLAYER_STATE::SIT_DOWN_WALK);
	}

	else if (KEY_TAP(KEY::J) && (&_stkState == &m_stkStateLower))
	{
		_stkState.push(PLAYER_STATE::HAND_GUN_SIT_DOWN);
	}
}

void CPlayer::update_SIT_DOWN_WALK(stack<PLAYER_STATE>& _stkState)
{
	if (m_bAttacked)
	{
		if ((&_stkState == &m_stkStateUpper))
		{
			_stkState.pop();
			_stkState.push(PLAYER_STATE::NONE);  // Upper Part 라면 NONE 상태로, LOWER 파트라면 DEAD 상태로
		}
		else
		{
			_stkState.pop();
			_stkState.push(PLAYER_STATE::DEAD);
		}
		return;
	}

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
	else if (KEY_TAP(KEY::J) && (&_stkState == &m_stkStateLower))
	{
		_stkState.push(PLAYER_STATE::HAND_GUN_SIT_DOWN);
	}

}

void CPlayer::update_LOOK_DOWN(stack<PLAYER_STATE>& _stkState)
{
	if (m_bAttacked)
	{
		if ((&_stkState == &m_stkStateUpper))
		{
			_stkState.pop();
			_stkState.push(PLAYER_STATE::NONE);  // Upper Part 라면 NONE 상태로, LOWER 파트라면 DEAD 상태로
		}
		else
		{
			_stkState.pop();
			_stkState.push(PLAYER_STATE::DEAD);
		}
		return;
	}

	if (&_stkState == &m_stkStateUpper)
		m_iDir.y = 1;

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
	else if (KEY_TAP(KEY::J) && (&_stkState == &m_stkStateUpper))
	{
		_stkState.push(PLAYER_STATE::HAND_GUN_LOOK_DOWN);
	}
	
}

void CPlayer::update_LOOK_UP(stack<PLAYER_STATE>& _stkState)
{
	if (m_bAttacked)
	{
		if ((&_stkState == &m_stkStateUpper))
		{
			_stkState.pop();
			_stkState.push(PLAYER_STATE::NONE);  // Upper Part 라면 NONE 상태로, LOWER 파트라면 DEAD 상태로
		}
		else
		{
			_stkState.pop();
			_stkState.push(PLAYER_STATE::DEAD);
		}
		return;
	}

	if (&_stkState == &m_stkStateUpper)
		m_iDir.y = -1;

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
	if (m_bAttacked)
	{
		if ((&_stkState == &m_stkStateUpper))
		{
			_stkState.pop();
			_stkState.push(PLAYER_STATE::NONE);  // Upper Part 라면 NONE 상태로, LOWER 파트라면 DEAD 상태로
		}
		else
		{
			_stkState.pop();
			_stkState.push(PLAYER_STATE::DEAD);
		}
		return;
	}

	if ((m_iPrevDir != m_iDir.x) || KEY_HOLD(KEY::S))
	{
		_stkState.pop();
		SetFrame0(L"PLAYER_SHOOT_UPPER_PART", L"HEAVY_MACHINE_GUN_PLAYER_SHOOT_UPPER_PART");
		return;
	}

	if (KEY_HOLD(KEY::W) && KEY_TAP(KEY::J))
	{
		_stkState.pop();
		_stkState.push(PLAYER_STATE::HAND_GUN_LOOK_UP);
		SetFrame0(L"PLAYER_SHOOT_UPPER_PART", L"HEAVY_MACHINE_GUN_PLAYER_SHOOT_UPPER_PART");
		return;
	}


	if (GetAnimator()->GetCurAnimU()->IsFinish()) // 애니메이션이 끝났을 때
	{
		SetFrame0(L"PLAYER_SHOOT_UPPER_PART", L"HEAVY_MACHINE_GUN_PLAYER_SHOOT_UPPER_PART");
		_stkState.pop(); // 원래 상태로 돌아간다
	}
	else // 애니메이션이 안끝났을 때
	{
		if (KEY_HOLD(KEY::A))
			m_iDir.x = -1;
		else if (KEY_HOLD(KEY::D))
			m_iDir.x = 1;

		if (KEY_TAP(KEY::J)) // 공격 모션 진행중에 또다시 공격 키를 눌렀을 때. 공격 모션을 처음부터 초기화한다.
		{
			SetFrame0(L"PLAYER_SHOOT_UPPER_PART", L"HEAVY_MACHINE_GUN_PLAYER_SHOOT_UPPER_PART");
		}
	}

}

void CPlayer::update_HAND_GUN_SHOOT_UP(stack<PLAYER_STATE>& _stkState)
{
	if (m_bAttacked)
	{
		if ((&_stkState == &m_stkStateUpper))
		{
			_stkState.pop();
			_stkState.push(PLAYER_STATE::NONE);  // Upper Part 라면 NONE 상태로, LOWER 파트라면 DEAD 상태로
		}
		else
		{
			_stkState.pop();
			_stkState.push(PLAYER_STATE::DEAD);
		}
		return;
	}

	if (&_stkState == &m_stkStateUpper)
		m_iDir.y = -1;

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


	if ((m_iPrevDir != m_iDir.x) || KEY_HOLD(KEY::S))
	{
		_stkState.pop();
		SetFrame0(L"PLAYER_SHOOT_UP_UPPER_PART", L"HEAVY_MACHINE_GUN_PLAYER_SHOOT_UP_UPPER_PART");
		return;
	}

	if (GetAnimator()->GetCurAnimU()->IsFinish()) // 애니메이션이 끝났을 때
	{
		SetFrame0(L"PLAYER_SHOOT_UP_UPPER_PART", L"HEAVY_MACHINE_GUN_PLAYER_SHOOT_UP_UPPER_PART");
		_stkState.pop(); // 원래 상태로 돌아간다
	}
	else // 애니메이션이 안끝났을 때
	{
		if (KEY_TAP(KEY::J) && KEY_HOLD(KEY::W)) // 공격 모션 진행중에 또다시 공격 키를 눌렀을 때. 공격 모션을 처음부터 초기화한다.
		{
			SetFrame0(L"PLAYER_SHOOT_UP_UPPER_PART", L"HEAVY_MACHINE_GUN_PLAYER_SHOOT_UP_UPPER_PART");
		}
	}

}

void CPlayer::update_HAND_GUN_SHOOT_DOWN(stack<PLAYER_STATE>& _stkState)
{
	if (m_bAttacked)
	{
		if ((&_stkState == &m_stkStateUpper))
		{
			_stkState.pop();
			_stkState.push(PLAYER_STATE::NONE);  // Upper Part 라면 NONE 상태로, LOWER 파트라면 DEAD 상태로
		}
		else
		{
			_stkState.pop();
			_stkState.push(PLAYER_STATE::DEAD);
		}
		return;
	}

	if (&_stkState == &m_stkStateUpper)
		m_iDir.y = 1;

	if (GetGravity()->GetGround())
	{
		_stkState.pop();
		_stkState.pop();
		_stkState.push(PLAYER_STATE::IDLE);	
		SetFrame0(L"PLAYER_HAND_GUN_LOOK_DOWN", L"HEAVY_MACHINE_GUN_PLAYER_HAND_GUN_LOOK_DOWN");
		return;
	}

	if (GetAnimator()->GetCurAnimU()->IsFinish()) // 애니메이션이 끝났을 때
	{
		SetFrame0(L"PLAYER_HAND_GUN_LOOK_DOWN", L"HEAVY_MACHINE_GUN_PLAYER_HAND_GUN_LOOK_DOWN");
		_stkState.pop(); // 원래 상태로 돌아간다
	}
	else // 애니메이션이 안끝났을 때
	{
		if (KEY_TAP(KEY::J)) // 공격 모션 진행중에 또다시 공격 키를 눌렀을 때. 공격 모션을 처음부터 초기화한다.
		{
			SetFrame0(L"PLAYER_HAND_GUN_LOOK_DOWN", L"HEAVY_MACHINE_GUN_PLAYER_HAND_GUN_LOOK_DOWN");
		}
	}
}

void CPlayer::update_HAND_GUN_SHOOT_SIT_DOWN(stack<PLAYER_STATE>& _stkState)
{

	if (m_bAttacked)
	{
		if ((&_stkState == &m_stkStateUpper))
		{
			_stkState.pop();
			_stkState.push(PLAYER_STATE::NONE);  // Upper Part 라면 NONE 상태로, LOWER 파트라면 DEAD 상태로
		}
		else
		{
			_stkState.pop();
			_stkState.push(PLAYER_STATE::DEAD);
		}
		return;
	}

	if ((m_iPrevDir != m_iDir.x) || KEY_AWAY(KEY::S))
	{
		_stkState.pop();
		_stkState.pop();
		_stkState.push(PLAYER_STATE::IDLE);

		SetFrame0(L"PLAYER_IDLE_SIT_DOWN_SHOOT", L"HEAVY_MACHINE_GUN_PLAYER_IDLE_SIT_DOWN_SHOOT");
		return;
	}

	if (GetAnimator()->GetCurAnimL()->IsFinish()) // 애니메이션이 끝났을 때
	{
		SetFrame0(L"PLAYER_IDLE_SIT_DOWN_SHOOT", L"HEAVY_MACHINE_GUN_PLAYER_IDLE_SIT_DOWN_SHOOT");
		_stkState.pop(); // 원래 상태로 돌아간다
	}
	else // 애니메이션이 안끝났을 때
	{
		if (KEY_TAP(KEY::J)) // 공격 모션 진행중에 또다시 공격 키를 눌렀을 때. 공격 모션을 처음부터 초기화한다.
		{
			SetFrame0(L"PLAYER_IDLE_SIT_DOWN_SHOOT", L"HEAVY_MACHINE_GUN_PLAYER_IDLE_SIT_DOWN_SHOOT");
		}
	}
	GetRigidBody()->SetVelocity(Vec2(0.f, 0.f));
}

void CPlayer::update_DEAD(stack<PLAYER_STATE>& _stkState)
{
	GetAnimator()->StopAnimationU(true);
	//m_iLife--;
	if (GetAnimator()->GetCurAnimL()->IsFinish()) //  GetAnimator()->GetCurAnimL()->GetCurFrame() == 18
	{
		_stkState.pop();
		_stkState.push(PLAYER_STATE::RESPAWN);

		if (-1 == m_iDir.x)
			GetAnimator()->FindAnimation(L"PLAYER_DEAD_LEFT")->SetFrame(0);
		else
			GetAnimator()->FindAnimation(L"PLAYER_DEAD_RIGHT")->SetFrame(0);
	}

	
}

void CPlayer::update_RESPAWN(stack<PLAYER_STATE>& _stkState)
{
	if (GetAnimator()->GetCurAnimL()->IsFinish()) // GetAnimator()->GetCurAnimL()->GetCurFrame() == 16
	{
		m_bAttacked = false;
		GetAnimator()->StopAnimationU(false);


		_stkState.pop();
		_stkState.push(PLAYER_STATE::IDLE); //LOWER PART


		m_stkStateUpper.pop();
		m_stkStateUpper.push(PLAYER_STATE::IDLE);

		if (-1 == m_iDir.x)
			GetAnimator()->FindAnimation(L"PLAYER_RESPAWN_LEFT")->SetFrame(0);
		else
			GetAnimator()->FindAnimation(L"PLAYER_RESPAWN_RIGHT")->SetFrame(0);

		
	}
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

	if (m_bAttacked)
		return;

	CRigidBody* pRigid = GetRigidBody();

	if (KEY_HOLD(KEY::D) && KEY_HOLD(KEY::A) && GetGravity()->GetGround())
	{
		// 만약 둘 다 누른 상태면 플레이어 멈춤
		pRigid->SetVelocity(Vec2(0.f, 0.f));
	}

	else if (KEY_HOLD(KEY::A))
	{
		if (!GetGravity()->GetGround()) // 만약 점프중이라면 가속도 붙음
		{
			Vec2 temp = Vec2(0.f, pRigid->GetVelocity().y);
			pRigid->SetVelocity(Vec2(-100.f, temp.y));
			//pRigid->AddVelocity(Vec2(-100.f, 0.f));
			//pRigid->AddForce(Vec2(-300.f, 0.f)); 

		}
		else // 점프중이 아니라면 가속도 안붙음
			pRigid->SetVelocity(Vec2(-100.f, pRigid->GetVelocity().y));
	}

	else if (KEY_HOLD(KEY::D))
	{
		if (!GetGravity()->GetGround()) // 만약 점프중이라면 가속도 붙음
		{
			pRigid->SetVelocity(Vec2(100.f, pRigid->GetVelocity().y));
			//pRigid->AddVelocity(Vec2(100.f, 0.f));
			//pRigid->AddForce(Vec2(300.f, 0.f));

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
		if (m_ePrevStateLower == m_stkStateLower.top() && m_iPrevDir == m_iDir.x)
			break;

	case PLAYER_STATE::IDLE:
		if (m_iDir.x == -1)
			GetAnimator()->PlayL(L"PLAYER_IDLE_LOWER_PART_LEFT", true);
		else
			GetAnimator()->PlayL(L"PLAYER_IDLE_LOWER_PART_RIGHT", true);

		break;
	case PLAYER_STATE::WALK:
		if (m_iDir.x == -1)
			GetAnimator()->PlayL(L"PLAYER_WALK_LOWER_PART_LEFT", true);
		else
			GetAnimator()->PlayL(L"PLAYER_WALK_LOWER_PART_RIGHT", true);

		break;
		
	case PLAYER_STATE::WALK_JUMP:
		if (m_iDir.x == -1)
			GetAnimator()->PlayL(L"PLAYER_WALK_JUMP_LOWER_PART_LEFT", true);
		else
			GetAnimator()->PlayL(L"PLAYER_WALK_JUMP_LOWER_PART_RIGHT", true);

		break;

	case PLAYER_STATE::JUMP:
		if (m_iDir.x == -1)
			GetAnimator()->PlayL(L"PLAYER_IDLE_JUMP_LOWER_PART_LEFT", true);
		else
			GetAnimator()->PlayL(L"PLAYER_IDLE_JUMP_LOWER_PART_RIGHT", true);

		break;

	case PLAYER_STATE::SIT_DOWN:
		if (m_eCurWeapon == WEAPON::HAND_GUN)
		{
			if (m_iDir.x == -1)
				GetAnimator()->PlayL(L"PLAYER_IDLE_SIT_DOWN_LEFT", true);
			else
				GetAnimator()->PlayL(L"PLAYER_IDLE_SIT_DOWN_RIGHT", true);
		}

		else if (m_eCurWeapon == WEAPON::HEAVY_MACHIN_GUN)
		{
			if (m_iDir.x == -1)
				GetAnimator()->PlayL(L"HEAVY_MACHINE_GUN_PLAYER_IDLE_SIT_DOWN_LEFT", true);
			else
				GetAnimator()->PlayL(L"HEAVY_MACHINE_GUN_PLAYER_IDLE_SIT_DOWN_RIGHT", true);
		}
		break;
		
	case PLAYER_STATE::HAND_GUN_SIT_DOWN:
		if (m_eCurWeapon == WEAPON::HAND_GUN)
		{
			if (m_iDir.x == -1)
				GetAnimator()->PlayL(L"PLAYER_IDLE_SIT_DOWN_SHOOT_LEFT", false);
			else
				GetAnimator()->PlayL(L"PLAYER_IDLE_SIT_DOWN_SHOOT_RIGHT", false);
		}

		else if (m_eCurWeapon == WEAPON::HEAVY_MACHIN_GUN)
		{
			if (m_iDir.x == -1)
				GetAnimator()->PlayL(L"HEAVY_MACHINE_GUN_PLAYER_IDLE_SIT_DOWN_SHOOT_LEFT", false);
			else
				GetAnimator()->PlayL(L"HEAVY_MACHINE_GUN_PLAYER_IDLE_SIT_DOWN_SHOOT_RIGHT", false);
		}
		break;
		
	case PLAYER_STATE::SIT_DOWN_WALK:
		if (m_eCurWeapon == WEAPON::HAND_GUN)
		{
			if (m_iDir.x == -1)
				GetAnimator()->PlayL(L"PLAYER_IDLE_SIT_DOWN_WALK_LEFT", true);
			else
				GetAnimator()->PlayL(L"PLAYER_IDLE_SIT_DOWN_WALK_RIGHT", true);
		}

		else if (m_eCurWeapon == WEAPON::HEAVY_MACHIN_GUN)
		{
			if (m_iDir.x == -1)
				GetAnimator()->PlayL(L"HEAVY_MACHINE_GUN_PLAYER_IDLE_SIT_DOWN_WALK_LEFT", true);
			else
				GetAnimator()->PlayL(L"HEAVY_MACHINE_GUN_PLAYER_IDLE_SIT_DOWN_WALK_RIGHT", true);
		}
		break;

	//case PLAYER_STATE::STAND_UP:
	//	if (m_iDir == -1)
	//		GetAnimator()->PlayL(L"PLAYER_IDLE_LOWER_PART_LEFT", true);
	//	else
	//		GetAnimator()->PlayL(L"PLAYER_IDLE_LOWER_PART_RIGHT", true);

	//	break;

	case PLAYER_STATE::DEAD:
		if (m_iDir.x == -1)
			GetAnimator()->PlayL(L"PLAYER_DEAD_LEFT", false);
		else
			GetAnimator()->PlayL(L"PLAYER_DEAD_RIGHT", false);

		break;

	case PLAYER_STATE::RESPAWN:
		if (m_iDir.x == -1)
			GetAnimator()->PlayL(L"PLAYER_RESPAWN_LEFT", false);
		else
			GetAnimator()->PlayL(L"PLAYER_RESPAWN_RIGHT", false);

		break;
	}
	

	switch (m_stkStateUpper.top())
	{
		if (m_ePrevStateUpper == m_stkStateUpper.top() && m_iPrevDir == m_iDir.x)
			break;

	case PLAYER_STATE::IDLE:
		if (m_eCurWeapon == WEAPON::HAND_GUN)
		{
			if (m_iDir.x == -1)
				GetAnimator()->PlayU(L"PLAYER_IDLE_UPPER_PART_LEFT", true);
			else
				GetAnimator()->PlayU(L"PLAYER_IDLE_UPPER_PART_RIGHT", true);
		}

		else if (m_eCurWeapon == WEAPON::HEAVY_MACHIN_GUN)
		{
			if (m_iDir.x == -1)
				GetAnimator()->PlayU(L"HEAVY_MACHINE_GUN_PLAYER_IDLE_UPPER_PART_LEFT", true);
			else
				GetAnimator()->PlayU(L"HEAVY_MACHINE_GUN_PLAYER_IDLE_UPPER_PART_RIGHT", true);
		}
		break;
	case PLAYER_STATE::WALK:
		if (m_eCurWeapon == WEAPON::HAND_GUN)
		{
			if (m_iDir.x == -1)
				GetAnimator()->PlayU(L"PLAYER_WALK_UPPER_PART_LEFT", true);
			else
				GetAnimator()->PlayU(L"PLAYER_WALK_UPPER_PART_RIGHT", true);
		}

		else if (m_eCurWeapon == WEAPON::HEAVY_MACHIN_GUN)
		{
			if (m_iDir.x == -1)
				GetAnimator()->PlayU(L"HEAVY_MACHINE_GUN_PLAYER_WALK_UPPER_PART_LEFT", true);
			else
				GetAnimator()->PlayU(L"HEAVY_MACHINE_GUN_PLAYER_WALK_UPPER_PART_RIGHT", true);
		}
		break;
		
	case PLAYER_STATE::WALK_JUMP:
		if (m_eCurWeapon == WEAPON::HAND_GUN)
		{
			if (m_iDir.x == -1)
				GetAnimator()->PlayU(L"PLAYER_WALK_JUMP_UPPER_PART_LEFT", true);
			else
				GetAnimator()->PlayU(L"PLAYER_WALK_JUMP_UPPER_PART_RIGHT", true);
		}

		else if (m_eCurWeapon == WEAPON::HEAVY_MACHIN_GUN)
		{
			if (m_iDir.x == -1)
				GetAnimator()->PlayU(L"HEAVY_MACHINE_GUN_PLAYER_WALK_JUMP_UPPER_PART_LEFT", true);
			else
				GetAnimator()->PlayU(L"HEAVY_MACHINE_GUN_PLAYER_WALK_JUMP_UPPER_PART_RIGHT", true);
		}
		break;

	case PLAYER_STATE::JUMP:
		if (m_eCurWeapon == WEAPON::HAND_GUN)
		{
			if (m_iDir.x == -1)
				GetAnimator()->PlayU(L"PLAYER_IDLE_JUMP_UPPER_PART_LEFT", true);
			else
				GetAnimator()->PlayU(L"PLAYER_IDLE_JUMP_UPPER_PART_RIGHT", true);
		}

		else if (m_eCurWeapon == WEAPON::HEAVY_MACHIN_GUN)
		{
			if (m_iDir.x == -1)
				GetAnimator()->PlayU(L"HEAVY_MACHINE_GUN_PLAYER_IDLE_JUMP_UPPER_PART_LEFT", true);
			else
				GetAnimator()->PlayU(L"HEAVY_MACHINE_GUN_PLAYER_IDLE_JUMP_UPPER_PART_RIGHT", true);
		}
		break;
		
	case PLAYER_STATE::HAND_GUN_SHOOT:
		if (m_eCurWeapon == WEAPON::HAND_GUN)
		{
			if (m_iDir.x == -1)
				GetAnimator()->PlayU(L"PLAYER_SHOOT_UPPER_PART_LEFT", false);
			else
				GetAnimator()->PlayU(L"PLAYER_SHOOT_UPPER_PART_RIGHT", false);
		}

		else if (m_eCurWeapon == WEAPON::HEAVY_MACHIN_GUN)
		{
			if (m_iDir.x == -1)
				GetAnimator()->PlayU(L"HEAVY_MACHINE_GUN_PLAYER_SHOOT_UPPER_PART_LEFT", false);
			else
				GetAnimator()->PlayU(L"HEAVY_MACHINE_GUN_PLAYER_SHOOT_UPPER_PART_RIGHT", false);
		}
		break;

	case PLAYER_STATE::LOOK_UP:
		if (m_eCurWeapon == WEAPON::HAND_GUN)
		{
			if (m_iDir.x == -1)
				GetAnimator()->PlayU(L"PLAYER_LOOK_UP_UPPER_PART_LEFT", true);
			else
				GetAnimator()->PlayU(L"PLAYER_LOOK_UP_UPPER_PART_RIGHT", true);
		}

		else if (m_eCurWeapon == WEAPON::HEAVY_MACHIN_GUN)
		{
			if (m_iDir.x == -1)
				GetAnimator()->PlayU(L"HEAVY_MACHINE_GUN_PLAYER_LOOK_UP_UPPER_PART_LEFT", true);
			else
				GetAnimator()->PlayU(L"HEAVY_MACHINE_GUN_PLAYER_LOOK_UP_UPPER_PART_RIGHT", true);
		}
		break;
		
	case PLAYER_STATE::HAND_GUN_LOOK_UP:
		if (m_eCurWeapon == WEAPON::HAND_GUN)
		{
			if (m_iDir.x == -1)
				GetAnimator()->PlayU(L"PLAYER_SHOOT_UP_UPPER_PART_LEFT", false);
			else
				GetAnimator()->PlayU(L"PLAYER_SHOOT_UP_UPPER_PART_RIGHT", false);
		}

		else if (m_eCurWeapon == WEAPON::HEAVY_MACHIN_GUN)
		{
			if (m_iDir.x == -1)
				GetAnimator()->PlayU(L"HEAVY_MACHINE_GUN_PLAYER_SHOOT_UP_UPPER_PART_LEFT", false);
			else
				GetAnimator()->PlayU(L"HEAVY_MACHINE_GUN_PLAYER_SHOOT_UP_UPPER_PART_RIGHT", false);
		}
		break;

	case PLAYER_STATE::LOOK_DOWN:
		if (m_eCurWeapon == WEAPON::HAND_GUN)
		{
			if (m_iDir.x == -1)
				GetAnimator()->PlayU(L"PLAYER_LOOK_DOWN_UPPER_PART_LEFT", true);
			else
				GetAnimator()->PlayU(L"PLAYER_LOOK_DOWN_UPPER_PART_RIGHT", true);
		}

		else if (m_eCurWeapon == WEAPON::HEAVY_MACHIN_GUN)
		{
			if (m_iDir.x == -1)
				GetAnimator()->PlayU(L"HEAVY_MACHINE_GUN_PLAYER_LOOK_DOWN_UPPER_PART_LEFT", true);
			else
				GetAnimator()->PlayU(L"HEAVY_MACHINE_GUN_PLAYER_LOOK_DOWN_UPPER_PART_RIGHT", true);
		}
		break;
		
	case PLAYER_STATE::HAND_GUN_LOOK_DOWN:
		if (m_eCurWeapon == WEAPON::HAND_GUN)
		{
			if (m_iDir.x == -1)
				GetAnimator()->PlayU(L"PLAYER_HAND_GUN_LOOK_DOWN_LEFT", false);
			else
				GetAnimator()->PlayU(L"PLAYER_HAND_GUN_LOOK_DOWN_RIGHT", false);
		}

		else if (m_eCurWeapon == WEAPON::HEAVY_MACHIN_GUN)
		{
			if (m_iDir.x == -1)
				GetAnimator()->PlayU(L"HEAVY_MACHINE_GUN_PLAYER_HAND_GUN_LOOK_DOWN_LEFT", false);
			else
				GetAnimator()->PlayU(L"HEAVY_MACHINE_GUN_PLAYER_HAND_GUN_LOOK_DOWN_RIGHT", false);
		}
		break;

	}


}

void CPlayer::update_gravity()
{
	GetRigidBody()->AddForce(Vec2(0.f, 500.f));
}

void CPlayer::update_jumptime()
{

	QueryPerformanceCounter(&m_llCurCount);

	// 이전 프레임의 카운팅과, 현재 프레임 카운팅 값의 차이를 구한다.
	m_dDT = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)m_llFrequency.QuadPart;



	m_dAcc += m_dDT; // DT 누적, 흘러간 시간을 의미

	if (m_dAcc >= 0.5f) // 0.5초에 한 번
	{
		m_bStandLine = true;
		m_dAcc = 0.;
	}


	// 이전 카운트 값을 현재값으로 갱신(다음번에 계산을 위해서)
	m_llPrevCount = m_llCurCount;


#ifdef _DEBUG
	if (m_dDT > (1. / 60.))
		m_dDT = (1. / 60.);

#endif
}

void CPlayer::SetFrame0(const wstring& _strName1, const wstring& _strName2)
{
	if (m_eCurWeapon == WEAPON::HAND_GUN)
	{
		if (-1 == m_iDir.x)
			GetAnimator()->FindAnimation(_strName1 + L"_LEFT")->SetFrame(0);
		else
			GetAnimator()->FindAnimation(_strName1 + L"_RIGHT")->SetFrame(0);
	}
	else if (m_eCurWeapon == WEAPON::HEAVY_MACHIN_GUN)
	{
		if (-1 == m_iDir.x)
			GetAnimator()->FindAnimation(_strName2 + L"_LEFT")->SetFrame(0);
		else
			GetAnimator()->FindAnimation(_strName2 + L"_RIGHT")->SetFrame(0);
	}

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
