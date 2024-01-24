#include "CBulletUI.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CRes.h"
#include "CResMgr.h"
#include "CPlayer.h"
#include "CCamera.h"

CBulletUI::CBulletUI(Digit _eDigit, CPlayer* _pPlayer)
	: m_pPlayer(nullptr)
	, m_pSystemSetupTex(nullptr)
	, m_pTime_NumbersTex(nullptr)
	, m_eFont(FONT::NONE)
{
	
	SetPlayer(_pPlayer);
	SetDigit(_eDigit);

	// Texture 로딩하기
	m_pSystemSetupTex = CResMgr::GetInst()->LoadTexture(L"System_Setup", L"texture\\System_Setup.bmp");
	m_pTime_NumbersTex = CResMgr::GetInst()->LoadTexture(L"Time_Numbers", L"texture\\Time_Numbers.bmp");

	CreateAnimator();


	GetAnimator()->LoadAnimation(L"animation\\BackGround\\Font_A.anim");
	GetAnimator()->LoadAnimation(L"animation\\BackGround\\Font_B.anim");
	GetAnimator()->LoadAnimation(L"animation\\BackGround\\Font_M.anim");
	GetAnimator()->LoadAnimation(L"animation\\BackGround\\Font_O.anim");
	GetAnimator()->LoadAnimation(L"animation\\BackGround\\Font_R.anim");
	GetAnimator()->LoadAnimation(L"animation\\BackGround\\Font_S.anim");
	GetAnimator()->LoadAnimation(L"animation\\BackGround\\Time_Number0.anim");
	GetAnimator()->LoadAnimation(L"animation\\BackGround\\Time_Number1.anim");
	GetAnimator()->LoadAnimation(L"animation\\BackGround\\Time_Number2.anim");
	GetAnimator()->LoadAnimation(L"animation\\BackGround\\Time_Number3.anim");
	GetAnimator()->LoadAnimation(L"animation\\BackGround\\Time_Number4.anim");
	GetAnimator()->LoadAnimation(L"animation\\BackGround\\Time_Number5.anim");
	GetAnimator()->LoadAnimation(L"animation\\BackGround\\Time_Number6.anim");
	GetAnimator()->LoadAnimation(L"animation\\BackGround\\Time_Number7.anim");
	GetAnimator()->LoadAnimation(L"animation\\BackGround\\Time_Number8.anim");
	GetAnimator()->LoadAnimation(L"animation\\BackGround\\Time_Number9.anim");

}

CBulletUI::CBulletUI(FONT _eFont, CPlayer* _pPlayer)
	: m_pPlayer(nullptr)
	, m_pSystemSetupTex(nullptr)
	, m_pTime_NumbersTex(nullptr)
	, m_eDigit(Digit::NONE)
{
	
	SetPlayer(_pPlayer);
	SetFont(_eFont);

	// Texture 로딩하기
	m_pSystemSetupTex = CResMgr::GetInst()->LoadTexture(L"System_Setup", L"texture\\System_Setup.bmp");
	m_pTime_NumbersTex = CResMgr::GetInst()->LoadTexture(L"Time_Numbers", L"texture\\Time_Numbers.bmp");

	CreateAnimator();


	GetAnimator()->LoadAnimation(L"animation\\BackGround\\Font_A.anim");
	GetAnimator()->LoadAnimation(L"animation\\BackGround\\Font_B.anim");
	GetAnimator()->LoadAnimation(L"animation\\BackGround\\Font_M.anim");
	GetAnimator()->LoadAnimation(L"animation\\BackGround\\Font_O.anim");
	GetAnimator()->LoadAnimation(L"animation\\BackGround\\Font_R.anim");
	GetAnimator()->LoadAnimation(L"animation\\BackGround\\Font_S.anim");
	GetAnimator()->LoadAnimation(L"animation\\BackGround\\Time_Number0.anim");
	GetAnimator()->LoadAnimation(L"animation\\BackGround\\Time_Number1.anim");
	GetAnimator()->LoadAnimation(L"animation\\BackGround\\Time_Number2.anim");
	GetAnimator()->LoadAnimation(L"animation\\BackGround\\Time_Number3.anim");
	GetAnimator()->LoadAnimation(L"animation\\BackGround\\Time_Number4.anim");
	GetAnimator()->LoadAnimation(L"animation\\BackGround\\Time_Number5.anim");
	GetAnimator()->LoadAnimation(L"animation\\BackGround\\Time_Number6.anim");
	GetAnimator()->LoadAnimation(L"animation\\BackGround\\Time_Number7.anim");
	GetAnimator()->LoadAnimation(L"animation\\BackGround\\Time_Number8.anim");
	GetAnimator()->LoadAnimation(L"animation\\BackGround\\Time_Number9.anim");

}

CBulletUI::~CBulletUI()
{
}

void CBulletUI::start()
{
}

void CBulletUI::update()
{
	Vec2 vCameraPos = CCamera::GetInst()->GetLookAt();
	SetPos(vCameraPos + m_vDiff);

	int iNumberOfBullet = m_pPlayer->GetHeavyMachinGunCount();
	int iNumberOfGrenade = m_pPlayer->GetGrenadeCount();
	
	int iBulletDigit1 = iNumberOfBullet % 10;
	int iTemp = iNumberOfBullet / 10;

	int iBulletDigit10 = iTemp % 10;
	int iBulletDigit100 = iTemp / 10;

	int iGrenadeDigit1 = iNumberOfGrenade % 10;
	int iGrenadeDigit10 = iNumberOfGrenade / 10;

	switch (m_eDigit)
	{
	case Digit::Bullet1:
		m_eFont = (FONT)iBulletDigit1;
		break;
	case Digit::Bullet10:
		m_eFont = (FONT)iBulletDigit10;
		break;
	case Digit::Bullet100:
		m_eFont = (FONT)iBulletDigit100;
		break;
	case Digit::Grenade1:
		m_eFont = (FONT)iGrenadeDigit1;
		break;
	case Digit::Grenade10:
		m_eFont = (FONT)iGrenadeDigit10;
		break;
	default:
		break;
	}
	
	switch (m_eFont)
	{
	case FONT::ZERO:
		GetAnimator()->PlayL(L"Time_Number0", true);
		break;
	case FONT::ONE:
		GetAnimator()->PlayL(L"Time_Number1", true);
		break;
	case FONT::TWO:
		GetAnimator()->PlayL(L"Time_Number2", true);
		break;
	case FONT::THREE:
		GetAnimator()->PlayL(L"Time_Number3", true);
		break;
	case FONT::FOUR:
		GetAnimator()->PlayL(L"Time_Number4", true);
		break;
	case FONT::FIVE:
		GetAnimator()->PlayL(L"Time_Number5", true);
		break;
	case FONT::SIX:
		GetAnimator()->PlayL(L"Time_Number6", true);
		break;
	case FONT::SEVEN:
		GetAnimator()->PlayL(L"Time_Number7", true);
		break;
	case FONT::EIGHT:
		GetAnimator()->PlayL(L"Time_Number8", true);
		break;
	case FONT::NINE:
		GetAnimator()->PlayL(L"Time_Number9", true);
		break;
	case FONT::A:
		GetAnimator()->PlayL(L"Font_A", true);
		break;
	case FONT::B:
		GetAnimator()->PlayL(L"Font_B", true);
		break;
	case FONT::M:
		GetAnimator()->PlayL(L"Font_M", true);
		break;
	case FONT::O:
		GetAnimator()->PlayL(L"Font_O", true);
		break;
	case FONT::R:
		GetAnimator()->PlayL(L"Font_R", true);
		break;
	case FONT::S:
		GetAnimator()->PlayL(L"Font_S", true);
		break;
	default:
		break;
	}
}

void CBulletUI::render(HDC _dc)
{

	if ((int)m_eFont < 10)
		GetAnimator()->SetTransParentColor(163.f, 73.f, 164.f);
	else
		GetAnimator()->SetTransParentColor(0.f, 255.f, 0.f);

	component_render(_dc);
}
