#include "CTestAnim.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CCollider.h"

CTestAnim::CTestAnim()
{
	//CTexture* pLeftTex = CResMgr::GetInst()->LoadTexture(L"PlayerLeft", L"texture\\Marco_Rossi_Left.bmp");
	//CTexture* pRightTex = CResMgr::GetInst()->LoadTexture(L"PlayerRight", L"texture\\Marco_Rossi_Right.bmp");
	//CTexture* pLeftTex = CResMgr::GetInst()->LoadTexture(L"Chowmein_Conga_Left", L"texture\\Chowmein_Conga_Left.bmp");
	//CTexture* pRightTex = CResMgr::GetInst()->LoadTexture(L"Chowmein_Conga_Right", L"texture\\Chowmein_Conga_Right.bmp");
	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"Mission1", L"texture\\Mission1.bmp");

	CTexture* pLeftTex = CResMgr::GetInst()->LoadTexture(L"Locust_Left", L"texture\\Locust_Left.bmp");
	CTexture* pRightTex = CResMgr::GetInst()->LoadTexture(L"Locust_Right", L"texture\\Locust_Right.bmp");

	strAnimFile.clear();
	strAnimFile2.clear();
	CreateAnimator();
	

	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 30.f));
	//GetCollider()->SetScale(Vec2(30.f, 30.f));  // 중밍콩게 충돌체 크기
	GetCollider()->SetScale(Vec2(55.f, 30.f));  // 거대 메뚜기 충돌체 크기

	//GetAnimator()->LoadAnimation(L"animation\\PLAYER_IDLE_LOWER_PART_LEFT.anim");
	//GetAnimator()->LoadAnimation(L"animation\\PLAYER_IDLE_UPPER_PART_LEFT.anim");


	

	//GetAnimator()->CreateAnimation(L"LOCUST_FLYING_LEFT", pLeftTex, Vec2(709.f, 291.f), Vec2(210.f, 98.f), Vec2(211.f, 0.f), Vec2(0.f, -0.f), 0.1f, 40);
	//GetAnimator()->CreateAnimation(L"LOCUST_FLYING_RIGHT", pRightTex, Vec2(709.f, 291.f), Vec2(210.f, 98.f), Vec2(211.f, 0.f), Vec2(0.f, -0.f), 0.1f, 40);
	//GetAnimator()->CreateAnimation(L"LOCUST_ATTACK_LEFT", pLeftTex, Vec2(709.f, 291.f), Vec2(210.f, 98.f), Vec2(211.f, 0.f), Vec2(0.f, -0.f), 0.1f, 20);
	//GetAnimator()->CreateAnimation(L"LOCUST_ATTACK_RIGHT", pRightTex, Vec2(709.f, 291.f), Vec2(210.f, 98.f), Vec2(211.f, 0.f), Vec2(0.f, -0.f), 0.1f, 20);
	//GetAnimator()->CreateAnimation(L"LOCUST_DIE_LEFT", pLeftTex, Vec2(709.f, 291.f), Vec2(210.f, 98.f), Vec2(211.f, 0.f), Vec2(0.f, -0.f), 0.1f, 30);
	//GetAnimator()->CreateAnimation(L"LOCUST_DIE_RIGHT", pRightTex, Vec2(709.f, 291.f), Vec2(210.f, 98.f), Vec2(211.f, 0.f), Vec2(0.f, -0.f), 0.1f, 30);
	//GetAnimator()->CreateAnimation(L"CHOWMEIN_CONGA_SPIT_LEFT", pLeftTex, Vec2(709.f, 291.f), Vec2(210.f, 98.f), Vec2(211.f, 0.f), Vec2(0.f, -0.f), 0.1f, 13);
	//GetAnimator()->CreateAnimation(L"CHOWMEIN_CONGA_SPIT_RIGHT", pRightTex, Vec2(709.f, 291.f), Vec2(210.f, 98.f), Vec2(211.f, 0.f), Vec2(0.f, -0.f), 0.1f, 13);
	//GetAnimator()->CreateAnimation(L"CHOWMEIN_CONGA_DEATH_LEFT", pLeftTex, Vec2(709.f, 291.f), Vec2(210.f, 98.f), Vec2(211.f, 0.f), Vec2(0.f, -0.f), 0.1f, 27);
	//GetAnimator()->CreateAnimation(L"CHOWMEIN_CONGA_DEATH_RIGHT", pRightTex, Vec2(709.f, 291.f), Vec2(210.f, 98.f), Vec2(211.f, 0.f), Vec2(0.f, -0.f), 0.1f, 27);
	//GetAnimator()->CreateAnimation(L"PLAYER_HAND_GUN_LOOK_DOWN_RIGHT", pRightTex, Vec2(9.f, 2226.f), Vec2(22.f, 54.f), Vec2(25.f, 0.f), Vec2(0.f, -0.f), 0.1f, 6);


	//GetAnimator()->FindAnimation(L"LOCUST_FLYING_LEFT")->Save(L"animation\\LOCUST_FLYING_LEFT.anim");
	//GetAnimator()->FindAnimation(L"LOCUST_FLYING_RIGHT")->Save(L"animation\\LOCUST_FLYING_RIGHT.anim");
	//GetAnimator()->FindAnimation(L"LOCUST_ATTACK_LEFT")->Save(L"animation\\LOCUST_ATTACK_LEFT.anim");
	//GetAnimator()->FindAnimation(L"LOCUST_ATTACK_RIGHT")->Save(L"animation\\LOCUST_ATTACK_RIGHT.anim");
	//GetAnimator()->FindAnimation(L"LOCUST_DIE_LEFT")->Save(L"animation\\LOCUST_DIE_LEFT.anim");
	//GetAnimator()->FindAnimation(L"LOCUST_DIE_RIGHT")->Save(L"animation\\LOCUST_DIE_RIGHT.anim");
	//GetAnimator()->FindAnimation(L"CHOWMEIN_CONGA_SPIT_LEFT")->Save(L"animation\\CHOWMEIN_CONGA_SPIT_LEFT.anim");
	//GetAnimator()->FindAnimation(L"CHOWMEIN_CONGA_SPIT_RIGHT")->Save(L"animation\\CHOWMEIN_CONGA_SPIT_RIGHT.anim");
	//GetAnimator()->FindAnimation(L"CHOWMEIN_CONGA_DEATH_LEFT")->Save(L"animation\\CHOWMEIN_CONGA_DEATH_LEFT.anim");
	//GetAnimator()->FindAnimation(L"CHOWMEIN_CONGA_DEATH_RIGHT")->Save(L"animation\\CHOWMEIN_CONGA_DEATH_RIGHT.anim");
	//GetAnimator()->FindAnimation(L"PLAYER_HAND_GUN_LOOK_DOWN_RIGHT")->Save(L"animation\\PLAYER_HAND_GUN_LOOK_DOWN_RIGHT.anim"); 
}

CTestAnim::~CTestAnim()
{
}

void CTestAnim::update()
{
	GetAnimator()->SetTransParentColor(248, 0, 248);
	GetAnimator()->update();	

	if(strAnimFile2.empty())
		GetAnimator()->PlayL(strAnimFile, true);
	else
		GetAnimator()->Play(strAnimFile, strAnimFile2, true);
}

void CTestAnim::render(HDC _dc)
{
	component_render(_dc);
}
