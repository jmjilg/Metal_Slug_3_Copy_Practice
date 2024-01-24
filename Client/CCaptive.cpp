#include "CCaptive.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CCollider.h"
#include "CRes.h"
#include "CResMgr.h"
#include "CGravity.h"
#include "CTimeMgr.h"
#include "CCore.h"
#include "CSupplies.h"



CCaptive::CCaptive()
	: m_fSpeed(50.f)
	, m_iDir(-1)
	, m_iPrevDir(-1)
{

	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2(20.f, 20.f));

	CreateRigidBody();

	CreateGravity();

	// Texture 로딩하기
	CTexture* pLeftTex = CResMgr::GetInst()->LoadTexture(L"Captive_Left", L"texture\\Helpful_NPCs.Left.bmp");
	CTexture* pRightTex = CResMgr::GetInst()->LoadTexture(L"Captive_Right", L"texture\\Helpful_NPCs.Right.bmp");

	CreateAnimator();
		
	GetAnimator()->LoadAnimation(L"animation\\CAPTIVE_IDLE_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\CAPTIVE_LOOKING_FOR_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\CAPTIVE_LOOKING_FOR_RIGHT.anim");
	GetAnimator()->LoadAnimation(L"animation\\CAPTIVE_RELEASE_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\CAPTIVE_RUN_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\CAPTIVE_SALUTE_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\CAPTIVE_SUPPLY_LEFT.anim");

	m_eCurState = CAPTIVE_STATE::IDLE;
	m_ePrevState = CAPTIVE_STATE::IDLE;
}

CCaptive::~CCaptive()
{
}

void CCaptive::update()
{
	update_state();

	update_animation();

	GetAnimator()->SetTransParentColor(255, 255, 255); // 무시할 RGB값 설정 (한번만 하면 됨)

	GetAnimator()->update();

	
	m_ePrevState = m_eCurState;
	m_iPrevDir = m_iDir;
}

void CCaptive::render(HDC _dc)
{
	component_render(_dc);
}

void CCaptive::update_state()
{
	switch (m_eCurState)
	{
	case CAPTIVE_STATE::IDLE:
		update_IDLE(m_eCurState);
		break;
	case CAPTIVE_STATE::RELEASE:
		update_RELEASE(m_eCurState);
		break;
	case CAPTIVE_STATE::LOOKING_FOR:
		update_LOOKING_FOR(m_eCurState);
		break;
	case CAPTIVE_STATE::SUPPLY:
		update_SUPPLY(m_eCurState);
		break;
	case CAPTIVE_STATE::SALUTE:
		update_SALUTE(m_eCurState);
		break;
	case CAPTIVE_STATE::RUN:
		update_RUN(m_eCurState);
		break;
	default:
		break;
	}
}

void CCaptive::update_IDLE(CAPTIVE_STATE _eState)
{

}

void CCaptive::update_RELEASE(CAPTIVE_STATE _eState)
{
	if(GetAnimator()->GetCurAnimL()->GetCurFrame() == 3)
		m_eCurState = CAPTIVE_STATE::LOOKING_FOR;
}

void CCaptive::update_LOOKING_FOR(CAPTIVE_STATE _eState)
{

	// 플레이어와 부딫힐 때까지 왔다갔다 한다
	Vec2 vPos = GetPos();

	vPos.x = vPos.x + m_iDir * m_fSpeed * fDT;

	SetPos(vPos);


	float fLen = abs(GetOrigPos().x - vPos.x);
	//long temp = GetMonster()->GetInfo().lAttAcc;

	// 플레이어가 몬스터의 공격범위범위 안으로 진입
	if (fLen >= 50.f)
	{
		m_iDir *= -1;
	}
	
}

void CCaptive::update_SUPPLY(CAPTIVE_STATE _eState)
{
	if (GetAnimator()->GetCurAnimL()->GetCurFrame() == 10)
	{
		m_eCurState = CAPTIVE_STATE::SALUTE;
		CObject* pSupplies = new CSupplies;
		pSupplies->SetName(L"Supplies");
		pSupplies->SetPos(GetPos());
		pSupplies->SetScale(Vec2(100.f, 100.f));
		CreateObject(pSupplies, GROUP_TYPE::SUPPLIES);
	}
}

void CCaptive::update_SALUTE(CAPTIVE_STATE _eState)
{
	if (GetAnimator()->GetCurAnimL()->GetCurFrame() == 13)
		m_eCurState = CAPTIVE_STATE::RUN;
}

void CCaptive::update_RUN(CAPTIVE_STATE _eState)
{
	Vec2 vPos = GetPos();

	vPos.x -= m_fSpeed * fDT;

	SetPos(vPos);

	Vec2 vResolution = CCore::GetInst()->GetResolution();
	vPos = CCamera::GetInst()->GetRenderPos(vPos);


	if ((vPos.x < 0) || (vPos.x > vResolution.x) || (vPos.y < 0) || (vPos.y > vResolution.y))
		DeleteObject(this);

	
}

void CCaptive::update_animation()
{
	switch (m_eCurState)
	{
		if(m_ePrevState == m_eCurState && m_iPrevDir == m_iDir)
			break;

	case CAPTIVE_STATE::IDLE:
			GetAnimator()->PlayL(L"CAPTIVE_IDLE_LEFT", true);
		break;
	case CAPTIVE_STATE::RELEASE:
			GetAnimator()->PlayL(L"CAPTIVE_RELEASE_LEFT", true);
		break;
	case CAPTIVE_STATE::LOOKING_FOR:
		if (m_iDir == -1)
			GetAnimator()->PlayL(L"CAPTIVE_LOOKING_FOR_LEFT", true);
		else
			GetAnimator()->PlayL(L"CAPTIVE_LOOKING_FOR_RIGHT", true);
		break;
	case CAPTIVE_STATE::SUPPLY:
			GetAnimator()->PlayL(L"CAPTIVE_SUPPLY_LEFT", true);
		break;
	case CAPTIVE_STATE::SALUTE:
			GetAnimator()->PlayL(L"CAPTIVE_SALUTE_LEFT", true);
		break;
	case CAPTIVE_STATE::RUN:
			GetAnimator()->PlayL(L"CAPTIVE_RUN_LEFT", true);
		break;
	}
}

void CCaptive::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Missile_Player")
	{
		if (m_eCurState == CAPTIVE_STATE::IDLE)
		{
			m_eCurState = CAPTIVE_STATE::RELEASE;
		}
	}
}

void CCaptive::OnCollision(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Player")
	{
		if (m_eCurState == CAPTIVE_STATE::LOOKING_FOR)
		{
			m_eCurState = CAPTIVE_STATE::SUPPLY;
		}
	}

}

