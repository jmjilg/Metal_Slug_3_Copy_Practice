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
	: m_eCurState(PLAYER_STATE::IDLE)
	, m_ePrevState(PLAYER_STATE::WALK)
	, m_iDir(1)
	, m_iPrevDir(1)
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

	GetAnimator()->LoadAnimation(L"animation\\PLAYER_LOWER_PART_IDLE_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\PLAYER_UPPER_PART_IDLE_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\PLAYER_LOWER_PART_IDLE_RIGHT.anim");
	GetAnimator()->LoadAnimation(L"animation\\PLAYER_UPPER_PART_IDLE_RIGHT.anim");
	GetAnimator()->LoadAnimation(L"animation\\PLAYER_LOWER_PART_WALK_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\PLAYER_UPPER_PART_WALK_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\PLAYER_LOWER_PART_WALK_RIGHT.anim");
	GetAnimator()->LoadAnimation(L"animation\\PLAYER_UPPER_PART_WALK_RIGHT.anim");

	//GetAnimator()->LoadAnimation(L"animation\\player_walk_right.anim");
	//GetAnimator()->LoadAnimation(L"animation\\player_jump_left.anim");
	//GetAnimator()->LoadAnimation(L"animation\\player_jump_right.anim");

	//GetAnimator()->CreateAnimation(L"PLAYER_LOWER_PART_IDLE_LEFT", pLeftTex, Vec2(1647.f, 275.f), Vec2(23.f, 18.f), Vec2(0.f, 0.f), Vec2(5.f, 15.f), 0.1f, 1);
	//GetAnimator()->CreateAnimation(L"PLAYER_LOWER_PART_IDLE_RIGHT", pRightTex, Vec2(148.f, 275.f), Vec2(23.f, 18.f), Vec2(0.f, 0.f), Vec2(-5.f, 15.f), 0.1f, 1);


	// Animation 저장해보기
	//GetAnimator()->FindAnimation(L"PLAYER_LOWER_PART_IDLE_LEFT")->Save(L"animation\\PLAYER_LOWER_PART_IDLE_LEFT.anim");
	//GetAnimator()->FindAnimation(L"PLAYER_LOWER_PART_IDLE_RIGHT")->Save(L"animation\\PLAYER_LOWER_PART_IDLE_RIGHT.anim"); 


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

	m_ePrevState = m_eCurState;
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
	if (KEY_HOLD(KEY::A))
	{
		m_iDir = -1;
		if (PLAYER_STATE::JUMP != m_eCurState)
			m_eCurState = PLAYER_STATE::WALK;		
	}

	if (KEY_HOLD(KEY::D))
	{
		m_iDir = 1;
		if (PLAYER_STATE::JUMP != m_eCurState)
			m_eCurState = PLAYER_STATE::WALK;
	}

	if (0.f == GetRigidBody()->GetSpeed() && PLAYER_STATE::JUMP != m_eCurState)
	{
		m_eCurState = PLAYER_STATE::IDLE;
	}

	if (KEY_TAP(KEY::SPACE))
	{
		//CreateMissile();
		m_eCurState = PLAYER_STATE::JUMP;

		if (GetRigidBody())
		{			
			GetRigidBody()->SetVelocity(Vec2(GetRigidBody()->GetVelocity().x, -300.f));
		}
	}
}

void CPlayer::update_move()
{
	CRigidBody* pRigid = GetRigidBody();

	if (KEY_HOLD(KEY::A))
	{
		pRigid->AddForce(Vec2(-200.f, 0.f));
	}

	if (KEY_HOLD(KEY::D))
	{
		pRigid->AddForce(Vec2(200.f, 0.f));
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
	if (m_ePrevState == m_eCurState && m_iPrevDir == m_iDir)
		return;


	switch (m_eCurState)
	{
	case PLAYER_STATE::IDLE:
	{
		if(m_iDir == -1)
			GetAnimator()->Play(L"PLAYER_LOWER_PART_IDLE_LEFT", L"PLAYER_UPPER_PART_IDLE_LEFT", true);
		else
			GetAnimator()->Play(L"PLAYER_LOWER_PART_IDLE_RIGHT", L"PLAYER_UPPER_PART_IDLE_RIGHT", true);
	}

		break;
	case PLAYER_STATE::WALK:
	{
		if (m_iDir == -1)
		{
			GetAnimator()->Play(L"PLAYER_LOWER_PART_WALK_LEFT", L"PLAYER_UPPER_PART_WALK_LEFT", true);
		}
		else
		{
			GetAnimator()->Play(L"PLAYER_LOWER_PART_WALK_RIGHT", L"PLAYER_UPPER_PART_WALK_RIGHT", true);
		}
	}
		break;

	case PLAYER_STATE::JUMP:
		if (m_iDir == -1)
			GetAnimator()->Play(L"JUMP_LEFT", true);
		else
			GetAnimator()->Play(L"JUMP_RIGHT", true);
		break;

	case PLAYER_STATE::ATTACK:

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
			m_eCurState = PLAYER_STATE::IDLE;
		}
	}
}
