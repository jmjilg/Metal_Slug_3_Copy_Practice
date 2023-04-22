#include "pch.h"
#include "CScene_Start.h"

#include "CObject.h"

#include "CPlayer.h"
#include "CMonster.h"

#include "CCore.h"

#include "CPathMgr.h"
#include "CTexture.h"

#include "CCollisionMgr.h"
#include "CCollider.h"

#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CCamera.h"

#include "AI.h"
#include "CIdleState.h"
#include "CTraceState.h"

#include "CRigidBody.h"
#include "SelectGDI.h"
#include "CTimeMgr.h"

#include "CGround.h"
#include "CRayGround.h"
#include "CBackGround.h"
#include "CBackGroundAnim.h"
#include "CBrokenCongaHouse.h"
#include "CBrokenShip.h"
#include "CBeach.h"
#include "CBeachFront.h"
#include "CCongaHouse.h"
#include "CShip.h"
#include "CShipDoor.h"
#include "CSlugTransport.h"
#include "CSlugTransportWave.h"
#include "CSlugTransportWave2.h"
#include "CSwamp.h"
#include "CSwampUnder.h"

CScene_Start::CScene_Start()
	: m_bUseForce(false)
	, m_fForceRadius(500.f)
	, m_fCurRadius(0.f)
	, m_fForce(500.f)
{

}

CScene_Start::~CScene_Start()
{
}

void CScene_Start::update()
{
	if (KEY_HOLD(KEY::LBTN))
	{
		//m_bUseForce = true;
		//CreateForce();
	}
	//else
	//{
	//	m_bUseForce = false;
	//}

	if (KEY_TAP(KEY::SPACE))
	{
		if (CCore::GetInst()->GetStretchRender())
			CCore::GetInst()->SetStretchRender(false);
		else
			CCore::GetInst()->SetStretchRender(true);
	}

	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		const vector<CObject*>& vecObj = GetGroupObject((GROUP_TYPE)i);

		for (size_t j = 0; j < vecObj.size(); ++j)
		{
			if (!vecObj[j]->IsDead())
			{
				if (m_bUseForce && vecObj[j]->GetRigidBody())
				{
					Vec2 vDiff =  vecObj[j]->GetPos() - m_vForcePos;
					float fLen = vDiff.Length();
					if (fLen < m_fForceRadius)
					{
						float fRatio =  1.f - (fLen / m_fForceRadius);
						float fForce = m_fForce * fRatio;

						vecObj[j]->GetRigidBody()->AddForce(vDiff.Normalize() * fForce);					
					}
				}

				vecObj[j]->update();
			}
		}
	}




	/*if (KEY_TAP(KEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::TOOL);
	}*/

	// 클릭시 카메라 움직임
	//if (KEY_TAP(KEY::LBTN))
	//{
	//	Vec2 vLookAt = CCamera::GetInst()->GetRealPos(MOUSE_POS);
	//	CCamera::GetInst()->SetLookAt(vLookAt);
	//}
}

void CScene_Start::render(HDC _dc)
{
	CScene::render(_dc);

	if (!m_bUseForce)
		return;

	SelectGDI gdi1(_dc, BRUSH_TYPE::HOLLOW);
	SelectGDI gdi2(_dc, PEN_TYPE::GREEN);

	m_fCurRadius += m_fForceRadius * 3.f * fDT;
	if (m_fCurRadius > m_fForceRadius)
	{
		m_fCurRadius = 0.f;
	}

	Vec2 vRenderPos =  CCamera::GetInst()->GetRenderPos(m_vForcePos);
	

	Ellipse(_dc
		, (int)(vRenderPos.x - m_fCurRadius)
		, (int)(vRenderPos.y - m_fCurRadius)
		, (int)(vRenderPos.x + m_fCurRadius)
		, (int)(vRenderPos.y + m_fCurRadius));

	
}

void CScene_Start::Enter()
{
	// Object 추가
	CObject* pObj = new CPlayer;
	pObj->SetName(L"Player");
	pObj->SetPos(Vec2(0.f, 0.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);

	RegisterPlayer(pObj);


	// 배경 추가
	//CObject* pBackGround = new CBackGround;
	//pBackGround->SetName(L"BackGround");
	//pBackGround->SetPos(Vec2(640.f, 384.f));
	//pBackGround->SetScale(Vec2(1280.f, 274.f));
	////pObj->SetScale(Vec2(2889.f, 274.f));
	//AddObject(pBackGround, GROUP_TYPE::BACKGROUND);

	//CObject* pBackGroundAnim = new CBackGroundAnim;
	//pBackGroundAnim->SetName(L"BackGroundAnim");
	//pBackGroundAnim->SetPos(Vec2(667.f, 274.f));
	//pBackGroundAnim->SetScale(Vec2(705.f, 48.f));
	////pObj->SetScale(Vec2(2889.f, 274.f));
	//AddObject(pBackGroundAnim, GROUP_TYPE::BACKGROUNDANIM);
	

	//CObject* pBrokenCongaHouse = new CBrokenCongaHouse;
	//pBrokenCongaHouse->SetName(L"BrokenCongaHouse");
	//pBrokenCongaHouse->SetPos(Vec2(152.f, 83.f));
	//pBrokenCongaHouse->SetScale(Vec2(304.f, 166.f));
	////pObj->SetScale(Vec2(2889.f, 274.f));
	//AddObject(pBrokenCongaHouse, GROUP_TYPE::BROKENCONGAHOUSE);

	//CObject* pBrokenShip = new CBrokenShip;
	//pBrokenShip->SetName(L"BrokenShip");
	//pBrokenShip->SetPos(Vec2(135.f, 51.f));
	//pBrokenShip->SetScale(Vec2(270.f, 102.f));
	////pObj->SetScale(Vec2(2889.f, 274.f));
	//AddObject(pBrokenShip, GROUP_TYPE::BROKENSHIP);

	//CObject* pBeach = new CBeach;
	//pBeach->SetName(L"Beach");
	//pBeach->SetPos(Vec2(667.f, 274.f));
	//pBeach->SetScale(Vec2(705.f, 48.f));
	////pObj->SetScale(Vec2(2889.f, 274.f));
	//AddObject(pBeach, GROUP_TYPE::BEACH);
	

	CObject* pBeachFront = new CBeachFront;
	pBeachFront->SetName(L"BeachFront");
	pBeachFront->SetPos(Vec2(805.f, 111.f));
	pBeachFront->SetScale(Vec2(1609.f, 221.f));
	//pObj->SetScale(Vec2(2889.f, 274.f));
	AddObject(pBeachFront, GROUP_TYPE::BEACHFRONT);
	

	//CObject* pCongaHouse = new CCongaHouse;
	//pCongaHouse->SetName(L"CongaHouse");
	//pCongaHouse->SetPos(Vec2(132.f, 105.f));
	//pCongaHouse->SetScale(Vec2(264.f, 210.f));
	////pObj->SetScale(Vec2(2889.f, 274.f));
	//AddObject(pCongaHouse, GROUP_TYPE::CONGAHOUSE);
	

	CObject* pShip = new CShip;
	pShip->SetName(L"Ship");
	pShip->SetPos(Vec2(1510.f, 93.f));
	pShip->SetScale(Vec2(203.f, 192.f));
	AddObject(pShip, GROUP_TYPE::SHIP);
	

	//CObject* pShipDoor = new CShipDoor;
	//pShipDoor->SetName(L"ShipDoor");
	//pShipDoor->SetPos(Vec2(1550.f, 130.f));
	//pShipDoor->SetScale(Vec2(705.f, 48.f));
	//AddObject(pShipDoor, GROUP_TYPE::SHIPDOOR);
	//

	//CObject* pSlugTransport = new CSlugTransport;
	//pSlugTransport->SetName(L"SlugTransport");
	//pSlugTransport->SetPos(Vec2(667.f, 274.f));
	//pSlugTransport->SetScale(Vec2(705.f, 48.f));
	////pObj->SetScale(Vec2(2889.f, 274.f));
	//AddObject(pSlugTransport, GROUP_TYPE::SLUGTRANSPORT);
	

	//CObject* pSlugTransportWave = new CSlugTransportWave;
	//pSlugTransportWave->SetName(L"SlugTransportWave");
	//pSlugTransportWave->SetPos(Vec2(667.f, 274.f));
	//pSlugTransportWave->SetScale(Vec2(705.f, 48.f));
	//AddObject(pSlugTransportWave, GROUP_TYPE::SLUGTRANSPORTWAVE);
	/*
	CObject* pSlugTransportWave2 = new CSlugTransportWave2;
	pSlugTransportWave2->SetName(L"SlugTransportWave2");
	pSlugTransportWave2->SetPos(Vec2(667.f, 274.f));
	pSlugTransportWave2->SetScale(Vec2(705.f, 48.f));
	AddObject(pSlugTransportWave2, GROUP_TYPE::SLUGTRANSPORTWAVE2);
	*/

	CObject* pSwamp = new CSwamp;
	pSwamp->SetName(L"Swamp");
	pSwamp->SetPos(Vec2(pBeachFront->GetScale().x + 1473.f, 127.f));
	pSwamp->SetScale(Vec2(3411.f, 221.f));
	//pObj->SetScale(Vec2(2889.f, 274.f));
	AddObject(pSwamp, GROUP_TYPE::SWAMP);
	
	CObject* pSwampUnder = new CSwampUnder;
	pSwampUnder->SetName(L"SwampUnder");
	pSwampUnder->SetPos(Vec2(pSwamp->GetPos().x -1062 , pSwamp->GetPos().y + 77));
	pSwampUnder->SetScale(Vec2(1289.f, 131.f));
	AddObject(pSwampUnder, GROUP_TYPE::SWAMPUNDER);
	
	/*CObject* pOtherPlayer = new CPlayer(*(CPlayer*)pObj);
	pOtherPlayer->SetPos(Vec2(740.f, 384.f)); 아래로 바뀜 */

	//CObject* pOtherPlayer = pObj->Clone();
	//pOtherPlayer->SetPos(Vec2(740.f, 384.f));
	//AddObject(pOtherPlayer, GROUP_TYPE::PLAYER);

	//CCamera::GetInst()->SetTarget(pObj);
	// 몬스터 배치
	int iMonCount = 1;
	float fObjScale = 50.f;

	Vec2 vResolution = CCore::GetInst()->GetResolution();
	CMonster* pMon = CMonFactory::CreateMonster(MON_TYPE::NORMAL, vResolution / 2.f - Vec2(0.f, 300.f));
	CreateObject(pMon, GROUP_TYPE::MONSTER);

	// 땅 물체 배치
	CObject* pGround = new CGround;
	pGround->SetName(L"Ground");
	pGround->SetPos(Vec2(100.f, 400.f));
	pGround->SetScale(Vec2(100.f, 10.f));
	AddObject(pGround, GROUP_TYPE::GROUND);
	
	CObject* pRayGround = new CRayGround;
	pRayGround->SetName(L"Ground");
	pRayGround->SetPos(Vec2(100.f, 400.f));
	pRayGround->SetScale(Vec2(100.f, 10.f));
	pRayGround->GetCollider()->GetVecRay().push_back(Vec2(0, 180));
	pRayGround->GetCollider()->GetVecRay().push_back(Vec2(230, 180));
	//pRayGround->GetCollider()->GetVecRay().push_back(Vec2(0, 150));
	//pRayGround->GetCollider()->GetVecRay().push_back(Vec2(230, 150));


	pRayGround->GetCollider()->GetVecRay().push_back(Vec2(231, 180));
	pRayGround->GetCollider()->GetVecRay().push_back(Vec2(432, 171));
	pRayGround->GetCollider()->GetVecRay().push_back(Vec2(433, 171));
	pRayGround->GetCollider()->GetVecRay().push_back(Vec2(560, 171));
	pRayGround->GetCollider()->GetVecRay().push_back(Vec2(561, 171));
	pRayGround->GetCollider()->GetVecRay().push_back(Vec2(634, 154));
	pRayGround->GetCollider()->GetVecRay().push_back(Vec2(635, 154));
	pRayGround->GetCollider()->GetVecRay().push_back(Vec2(700, 154));
	AddObject(pRayGround, GROUP_TYPE::GROUND);

	// 타일 로딩
	//LoadTile(L"Tile\\Start.tile");				

	// 충돌 지정
	// Player 그룹과 Monster 그룹 간의 충돌체크
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PLAYER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::GROUND);

	// Camera Look 지정
	CCamera::GetInst()->SetLookAt(vResolution / 2.f);

	// Camera 효과 지정
	CCamera::GetInst()->FadeOut(1.f);
	CCamera::GetInst()->FadeIn(1.f);

	start();
}

void CScene_Start::Exit()
{
	DeleteAll();

	CCollisionMgr::GetInst()->Reset();
}

void CScene_Start::CreateForce()
{
	m_vForcePos = CCamera::GetInst()->GetRealPos(MOUSE_POS);
}
