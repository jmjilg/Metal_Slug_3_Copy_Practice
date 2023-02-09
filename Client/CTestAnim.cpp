#include "CTestAnim.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CCollider.h"

CTestAnim::CTestAnim()
{
	CTexture* pLeftTex = CResMgr::GetInst()->LoadTexture(L"PlayerLeft", L"texture\\Marco_Rossi_Left.bmp");
	CTexture* pRightTex = CResMgr::GetInst()->LoadTexture(L"PlayerRight", L"texture\\Marco_Rossi_Right.bmp");

	strAnimFile.clear();
	strAnimFile2.clear();
	CreateAnimator();
	

	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 15.f));
	GetCollider()->SetScale(Vec2(50.f, 50.f));

	//GetAnimator()->LoadAnimation(L"animation\\PLAYER_IDLE_LOWER_PART_LEFT.anim");
	//GetAnimator()->LoadAnimation(L"animation\\PLAYER_IDLE_UPPER_PART_LEFT.anim");




	/*GetAnimator()->CreateAnimation(L"PLAYER_HAND_GUN_LOOK_DOWN_LEFT", pLeftTex, Vec2(1787.f, 2226.f), Vec2(22.f, 54.f), Vec2(-25.f, 0.f), Vec2(0.f, -0.f), 0.1f, 6);
	GetAnimator()->CreateAnimation(L"PLAYER_HAND_GUN_LOOK_DOWN_RIGHT", pRightTex, Vec2(9.f, 2226.f), Vec2(22.f, 54.f), Vec2(25.f, 0.f), Vec2(0.f, -0.f), 0.1f, 6);


	GetAnimator()->FindAnimation(L"PLAYER_HAND_GUN_LOOK_DOWN_LEFT")->Save(L"animation\\PLAYER_HAND_GUN_LOOK_DOWN_LEFT.anim");
	GetAnimator()->FindAnimation(L"PLAYER_HAND_GUN_LOOK_DOWN_RIGHT")->Save(L"animation\\PLAYER_HAND_GUN_LOOK_DOWN_RIGHT.anim"); */
}

CTestAnim::~CTestAnim()
{
}

void CTestAnim::update()
{
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
