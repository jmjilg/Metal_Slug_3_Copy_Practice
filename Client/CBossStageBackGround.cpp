#include "CBossStageBackGround.h"
#include "CRes.h"
#include "CResMgr.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CCore.h"

CBossStageBackGround::CBossStageBackGround()
	: m_pTexture(nullptr)
{
	// Texture 로딩하기
	m_pTexture = CResMgr::GetInst()->LoadTexture(L"Mission1", L"texture\\Mission1.bmp");

	CreateAnimator();

	//GetAnimator()->CreateAnimation(L"Ship", m_pTexture, Vec2(569.f, 884.f), Vec2(194.f, 192.f), Vec2(198.f, 0.f), Vec2(-0.f, -0.f), 0.1f, 5);


	// Animation 저장해보기
	//GetAnimator()->FindAnimation(L"Ship")->Save(L"animation\\BackGround\\Ship.anim");

	GetAnimator()->LoadAnimation(L"animation\\BackGround\\BossStageBackGround.anim");
}

CBossStageBackGround::~CBossStageBackGround()
{
}

void CBossStageBackGround::start()
{
}

void CBossStageBackGround::update()
{
	GetAnimator()->PlayL(L"BossStageBackGround", true);
}

void CBossStageBackGround::render(HDC _dc)
{
	component_render(_dc);
}


