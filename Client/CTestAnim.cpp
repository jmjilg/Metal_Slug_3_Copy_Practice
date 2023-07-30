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

	CTexture* pLeftTex = CResMgr::GetInst()->LoadTexture(L"Captive_Left", L"texture\\Helpful_NPCs.Left.bmp");
	CTexture* pRightTex = CResMgr::GetInst()->LoadTexture(L"Captive_Right", L"texture\\Helpful_NPCs.Right.bmp");

	strAnimFile.clear();
	strAnimFile2.clear();
	CreateAnimator();
	

	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2(20.f, 20.f));
	//GetCollider()->SetScale(Vec2(30.f, 30.f));  // 중밍콩게 충돌체 크기
	//GetCollider()->SetScale(Vec2(55.f, 30.f));  // 거대 메뚜기 충돌체 크기

	//GetAnimator()->LoadAnimation(L"animation\\PLAYER_IDLE_LOWER_PART_LEFT.anim");
	//GetAnimator()->LoadAnimation(L"animation\\PLAYER_IDLE_UPPER_PART_LEFT.anim");

	
	

	//GetAnimator()->CreateAnimation(L"CAPTIVE_RELEASE_LEFT", pLeftTex, Vec2(5.f, 25.f), Vec2(32.f, 29.f), Vec2(33.f, 0.f), Vec2(0.f, -0.f), 0.1f, 4);
	//GetAnimator()->CreateAnimation(L"CAPTIVE_RELEASE_RIGHT", pRightTex, Vec2(541.f, 25.f), Vec2(32.f, 29.f), Vec2(-33.f, 0.f), Vec2(0.f, -0.f), 0.1f, 4);
	//GetAnimator()->CreateAnimation(L"CAPTIVE_LOOKING_FOR_LEFT", pLeftTex, Vec2(5.f, 25.f), Vec2(32.f, 29.f), Vec2(33.f, 0.f), Vec2(0.f, -0.f), 0.1f, 12);
	//GetAnimator()->CreateAnimation(L"CAPTIVE_LOOKING_FOR_RIGHT", pRightTex, Vec2(541.f, 25.f), Vec2(32.f, 29.f), Vec2(-33.f, 0.f), Vec2(0.f, -0.f), 0.1f, 12);
	//GetAnimator()->CreateAnimation(L"CAPTIVE_SUPPLY_LEFT", pLeftTex, Vec2(5.f, 25.f), Vec2(32.f, 29.f), Vec2(33.f, 0.f), Vec2(0.f, -0.f), 0.1f, 11);
	//GetAnimator()->CreateAnimation(L"CAPTIVE_SUPPLY_RIGHT", pRightTex, Vec2(541.f, 25.f), Vec2(32.f, 29.f), Vec2(-33.f, 0.f), Vec2(0.f, -0.f), 0.1f, 11);
	//GetAnimator()->CreateAnimation(L"CAPTIVE_RUN_LEFT", pLeftTex, Vec2(5.f, 25.f), Vec2(32.f, 29.f), Vec2(33.f, 0.f), Vec2(0.f, -0.f), 0.1f, 8);
	//GetAnimator()->CreateAnimation(L"CAPTIVE_RUN_RIGHT", pRightTex, Vec2(541.f, 25.f), Vec2(32.f, 29.f), Vec2(-33.f, 0.f), Vec2(0.f, -0.f), 0.1f, 8);
	//GetAnimator()->CreateAnimation(L"CAPTIVE_SALUTE_LEFT", pLeftTex, Vec2(5.f, 25.f), Vec2(32.f, 29.f), Vec2(33.f, 0.f), Vec2(0.f, -0.f), 0.1f, 14);
	//GetAnimator()->CreateAnimation(L"CAPTIVE_SALUTE_RIGHT", pRightTex, Vec2(541.f, 25.f), Vec2(32.f, 29.f), Vec2(-33.f, 0.f), Vec2(0.f, -0.f), 0.1f, 14);
	//GetAnimator()->CreateAnimation(L"PLAYER_RESPAWN_LEFT", pLeftTex, Vec2(709.f, 291.f), Vec2(210.f, 98.f), Vec2(211.f, 0.f), Vec2(0.f, -0.f), 0.1f, 7);
	//GetAnimator()->CreateAnimation(L"PLAYER_RESPAWN_RIGHT", pRightTex, Vec2(709.f, 291.f), Vec2(210.f, 98.f), Vec2(211.f, 0.f), Vec2(0.f, -0.f), 0.1f, 7);
	//GetAnimator()->CreateAnimation(L"LOCUST_ATTACK_LEFT", pLeftTex, Vec2(709.f, 291.f), Vec2(210.f, 98.f), Vec2(211.f, 0.f), Vec2(0.f, -0.f), 0.1f, 20);
	//GetAnimator()->CreateAnimation(L"LOCUST_ATTACK_RIGHT", pRightTex, Vec2(709.f, 291.f), Vec2(210.f, 98.f), Vec2(211.f, 0.f), Vec2(0.f, -0.f), 0.1f, 20);
	//GetAnimator()->CreateAnimation(L"LOCUST_DIE_LEFT", pLeftTex, Vec2(709.f, 291.f), Vec2(210.f, 98.f), Vec2(211.f, 0.f), Vec2(0.f, -0.f), 0.1f, 30);
	//GetAnimator()->CreateAnimation(L"LOCUST_DIE_RIGHT", pRightTex, Vec2(709.f, 291.f), Vec2(210.f, 98.f), Vec2(211.f, 0.f), Vec2(0.f, -0.f), 0.1f, 30);
	//GetAnimator()->CreateAnimation(L"CHOWMEIN_CONGA_SPIT_LEFT", pLeftTex, Vec2(709.f, 291.f), Vec2(210.f, 98.f), Vec2(211.f, 0.f), Vec2(0.f, -0.f), 0.1f, 13);
	//GetAnimator()->CreateAnimation(L"CHOWMEIN_CONGA_SPIT_RIGHT", pRightTex, Vec2(709.f, 291.f), Vec2(210.f, 98.f), Vec2(211.f, 0.f), Vec2(0.f, -0.f), 0.1f, 13);
	//GetAnimator()->CreateAnimation(L"CHOWMEIN_CONGA_DEATH_LEFT", pLeftTex, Vec2(709.f, 291.f), Vec2(210.f, 98.f), Vec2(211.f, 0.f), Vec2(0.f, -0.f), 0.1f, 27);
	//GetAnimator()->CreateAnimation(L"CHOWMEIN_CONGA_DEATH_RIGHT", pRightTex, Vec2(709.f, 291.f), Vec2(210.f, 98.f), Vec2(211.f, 0.f), Vec2(0.f, -0.f), 0.1f, 27);
	//GetAnimator()->CreateAnimation(L"PLAYER_HAND_GUN_LOOK_DOWN_RIGHT", pRightTex, Vec2(9.f, 2226.f), Vec2(22.f, 54.f), Vec2(25.f, 0.f), Vec2(0.f, -0.f), 0.1f, 6);


	//GetAnimator()->FindAnimation(L"CAPTIVE_RELEASE_LEFT")->Save(L"animation\\CAPTIVE_RELEASE_LEFT.anim");
	//GetAnimator()->FindAnimation(L"CAPTIVE_RELEASE_RIGHT")->Save(L"animation\\CAPTIVE_RELEASE_RIGHT.anim");
	//GetAnimator()->FindAnimation(L"CAPTIVE_LOOKING_FOR_LEFT")->Save(L"animation\\CAPTIVE_LOOKING_FOR_LEFT.anim");
	//GetAnimator()->FindAnimation(L"CAPTIVE_LOOKING_FOR_RIGHT")->Save(L"animation\\CAPTIVE_LOOKING_FOR_RIGHT.anim");
	//GetAnimator()->FindAnimation(L"CAPTIVE_SUPPLY_LEFT")->Save(L"animation\\CAPTIVE_SUPPLY_LEFT.anim");
	//GetAnimator()->FindAnimation(L"CAPTIVE_SUPPLY_RIGHT")->Save(L"animation\\CAPTIVE_SUPPLY_RIGHT.anim");
	//GetAnimator()->FindAnimation(L"CAPTIVE_RUN_LEFT")->Save(L"animation\\CAPTIVE_RUN_LEFT.anim");
	//GetAnimator()->FindAnimation(L"CAPTIVE_RUN_RIGHT")->Save(L"animation\\CAPTIVE_RELEASE_RIGHT.anim");
	//GetAnimator()->FindAnimation(L"CAPTIVE_SALUTE_LEFT")->Save(L"animation\\CAPTIVE_SALUTE_LEFT.anim");
	//GetAnimator()->FindAnimation(L"CAPTIVE_SALUTE_RIGHT")->Save(L"animation\\CAPTIVE_SALUTE_RIGHT.anim");
	//GetAnimator()->FindAnimation(L"PLAYER_RESPAWN_LEFT")->Save(L"animation\\PLAYER_RESPAWN_LEFT.anim");
	//GetAnimator()->FindAnimation(L"PLAYER_RESPAWN_RIGHT")->Save(L"animation\\PLAYER_RESPAWN_RIGHT.anim");
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
	GetAnimator()->SetTransParentColor(255, 255, 255);
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
