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
#include "CDestroyedBrokenShip.h"
#include "CBeach.h"
#include "CBeachBackGround1.h"
#include "CBeachBackGround2.h"
#include "CSwampBackGround.h"
#include "CSwampBackGround2.h"
#include "CSwampBackGround3.h"
#include "CBossStageBackGround.h"
#include "CBeachFront.h"
#include "CCongaHouse.h"
#include "CShip.h"
#include "CR724.h"
#include "CShipDoor.h"
#include "CSlugTransport.h"
#include "CSlugTransportWave.h"
#include "CSlugTransportWave2.h"
#include "CSwamp.h"
#include "CSwampUnder.h"
#include "CObstacle.h"
#include "CEventObject.h"
#include "CEventObject2.h"
#include "CEventObject3.h"
#include "CCaptive.h"
#include "CCameraBox.h"

CScene_Start::CScene_Start()
	: m_bUseForce(false)
	, m_fForceRadius(500.f)
	, m_fCurRadius(0.f)
	, m_fForce(500.f)
{
	m_pRayGround = new CRayGround;
	m_pRayGround->SetName(L"Ground");
	m_pRayGround->SetPos(Vec2(100.f, 400.f));
	m_pRayGround->SetScale(Vec2(100.f, 10.f));

	m_pRayGround->GetCollider()->GetVecRay().push_back(Vec2(0, 180));
	m_pRayGround->GetCollider()->GetVecRay().push_back(Vec2(230, 180));
	//m_pRayGround->GetCollider()->GetVecRay().push_back(Vec2(0, 150));
	//m_pRayGround->GetCollider()->GetVecRay().push_back(Vec2(230, 150)); // 높이 테스트용
	m_pRayGround->GetCollider()->GetVecRay().push_back(Vec2(1000, 1000));
	m_pRayGround->GetCollider()->GetVecRay().push_back(Vec2(1001, 1000)); // 그냥 인덱스만 맞추기 위해 넣은거
	m_pRayGround->GetCollider()->GetVecRay().push_back(Vec2(230, 180));
	m_pRayGround->GetCollider()->GetVecRay().push_back(Vec2(433, 171));
	m_pRayGround->GetCollider()->GetVecRay().push_back(Vec2(433, 171));
	m_pRayGround->GetCollider()->GetVecRay().push_back(Vec2(560, 171));
	m_pRayGround->GetCollider()->GetVecRay().push_back(Vec2(560, 171));
	m_pRayGround->GetCollider()->GetVecRay().push_back(Vec2(635, 154));
	m_pRayGround->GetCollider()->GetVecRay().push_back(Vec2(635, 154));
	m_pRayGround->GetCollider()->GetVecRay().push_back(Vec2(720, 154));
	m_pRayGround->GetCollider()->GetVecRay().push_back(Vec2(720, 154)); // 밍콩게 집
	m_pRayGround->GetCollider()->GetVecRay().push_back(Vec2(814, 122)); // 밍콩게 집 
	m_pRayGround->GetCollider()->GetVecRay().push_back(Vec2(770, 154));
	m_pRayGround->GetCollider()->GetVecRay().push_back(Vec2(991, 191)); // 부서진 배 파괴되면 여기에서 15
	m_pRayGround->GetCollider()->GetVecRay().push_back(Vec2(979, 153));
	m_pRayGround->GetCollider()->GetVecRay().push_back(Vec2(1067, 153));
	m_pRayGround->GetCollider()->GetVecRay().push_back(Vec2(1067, 153));
	m_pRayGround->GetCollider()->GetVecRay().push_back(Vec2(1102, 173)); 
	m_pRayGround->GetCollider()->GetVecRay().push_back(Vec2(1102, 173)); // 여기로. 그 사이는 Delete 20
	m_pRayGround->GetCollider()->GetVecRay().push_back(Vec2(1186, 193));
	m_pRayGround->GetCollider()->GetVecRay().push_back(Vec2(1186, 193));
	m_pRayGround->GetCollider()->GetVecRay().push_back(Vec2(1478, 183));
	m_pRayGround->GetCollider()->GetVecRay().push_back(Vec2(1478, 183)); //!!
	m_pRayGround->GetCollider()->GetVecRay().push_back(Vec2(1585, 183)); // CShip 바로 다음	!!
	m_pRayGround->GetCollider()->GetVecRay().push_back(Vec2(1569, 136));
	m_pRayGround->GetCollider()->GetVecRay().push_back(Vec2(1629, 136));
	m_pRayGround->GetCollider()->GetVecRay().push_back(Vec2(1597, 108));
	m_pRayGround->GetCollider()->GetVecRay().push_back(Vec2(1663, 95));
	m_pRayGround->GetCollider()->GetVecRay().push_back(Vec2(1657, 75));
	m_pRayGround->GetCollider()->GetVecRay().push_back(Vec2(2362, 160));
	m_pRayGround->GetCollider()->GetVecRay().push_back(Vec2(2362, 160));
	m_pRayGround->GetCollider()->GetVecRay().push_back(Vec2(2727, 160));
	m_pRayGround->GetCollider()->GetVecRay().push_back(Vec2(2727, 160));
	m_pRayGround->GetCollider()->GetVecRay().push_back(Vec2(2820, 130));
	m_pRayGround->GetCollider()->GetVecRay().push_back(Vec2(1883, 59));
	m_pRayGround->GetCollider()->GetVecRay().push_back(Vec2(1981, 59));
	m_pRayGround->GetCollider()->GetVecRay().push_back(Vec2(2138, 93));
	m_pRayGround->GetCollider()->GetVecRay().push_back(Vec2(2240, 93));

	// 보여주기용
	m_pRayGround->GetCollider()->GetVecRay().push_back(Vec2(500, 500));
	m_pRayGround->GetCollider()->GetVecRay().push_back(Vec2(800, 500));

	AddObject(m_pRayGround, GROUP_TYPE::GROUND);
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
				if (!m_CongaHouse)
				{
					m_pRayGround->GetCollider()->GetVecRay()[12] = Vec2(720, 154); // 밍콩게 집 파괴됐을 때
					m_pRayGround->GetCollider()->GetVecRay()[13] = Vec2(770, 154); // 밍콩게 집 파괴시
					m_CongaHouse = true;
				}
				if (!m_BrokenShip)
				{

					m_pRayGround->GetCollider()->GetVecRay()[16] =Vec2(991, 191); 
					m_pRayGround->GetCollider()->GetVecRay()[17] =Vec2(1102, 173); 
					m_pRayGround->GetCollider()->GetVecRay()[18]=Vec2(991, 191);
					m_pRayGround->GetCollider()->GetVecRay()[19]=Vec2(1102, 173); 
					m_BrokenShip = true;
				}
				if (!m_Ship)
				{
					m_pRayGround->GetCollider()->GetVecRay().push_back(Vec2(1478, 183));
					m_pRayGround->GetCollider()->GetVecRay().push_back(Vec2(1585, 183)); // CShip 바로 다음
					m_Ship = true;
				}
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
	pObj->SetPos(Vec2(40.f, 145.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);

	RegisterPlayer(pObj);


	CObject* pCameraBox = new CCameraBox;
	pCameraBox->SetName(L"Ground"); // 직선 충돌체를 사용하므로 일단은 땅으로 간주함
	pCameraBox->SetPos(Vec2(40.f, 165.f));
	pCameraBox->SetScale(Vec2(200.f, 200.f));
	AddObject(pCameraBox, GROUP_TYPE::GROUND);

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

	CObject* pBrokenShipObstacle = new CObstacle;
	pBrokenShipObstacle->SetName(L"Ground"); // 편의상 Ground라고 하겠음
	pBrokenShipObstacle->SetPos(Vec2(1005.f, 180.f));
	pBrokenShipObstacle->SetScale(Vec2(60.f, 40.f));
	AddObject(pBrokenShipObstacle, GROUP_TYPE::GROUND);


	CObject* pBrokenShip = new CBrokenShip;
	pBrokenShip->SetName(L"BrokenShip");
	pBrokenShip->SetPos(Vec2(1060.f, 171.f));
	pBrokenShip->SetScale(Vec2(270.f, 102.f));
	pBrokenShip->SetObstacle(pBrokenShipObstacle);
	AddObject(pBrokenShip, GROUP_TYPE::BROKENSHIP);
	
	CObject* pDestroyedBrokenShip = new CDestroyedBrokenShip;
	pDestroyedBrokenShip->SetName(L"DestroyedBrokenShip");
	pDestroyedBrokenShip->SetPos(Vec2(1060.f, 171.f));
	pDestroyedBrokenShip->SetScale(Vec2(270.f, 102.f));
	AddObject(pDestroyedBrokenShip, GROUP_TYPE::DESTROYEDBROKENSHIP);

	//CObject* pBeach = new CBeach;
	//pBeach->SetName(L"Beach");
	//pBeach->SetPos(Vec2(667.f, 274.f));
	//pBeach->SetScale(Vec2(705.f, 48.f));
	////pObj->SetScale(Vec2(2889.f, 274.f));
	//AddObject(pBeach, GROUP_TYPE::BEACH);
	

	CObject* pBeachFront = new CBeachFront;
	pBeachFront->SetName(L"BeachFront");
	pBeachFront->SetPos(Vec2(688.f, 111.f));
	pBeachFront->SetScale(Vec2(1376.f, 221.f));
	//pObj->SetScale(Vec2(2889.f, 274.f));
	AddObject(pBeachFront, GROUP_TYPE::BEACHFRONT);
	
	CObject* pBeachBackGround = new CBeachBackGround1;
	pBeachBackGround->SetName(L"BeachBackGround1");
	pBeachBackGround->SetPos(Vec2(402.f, 70.f));
	pBeachBackGround->SetScale(Vec2(0.f, 0.f));
	//pObj->SetScale(Vec2(2889.f, 274.f));
	AddObject(pBeachBackGround, GROUP_TYPE::BEACHBACKGROUND1);
	
	CObject* pBeachBackGround2 = new CBeachBackGround2;  // 사실 그냥 짜깁기 한거임 사용하는 스프라이트는 같음
	pBeachBackGround2->SetName(L"BeachBackGround2");
	pBeachBackGround2->SetPos(Vec2(1804.f - 315.f, 70.f));
	pBeachBackGround2->SetScale(Vec2(0.f, 0.f));
	//pObj->SetScale(Vec2(2889.f, 274.f));
	AddObject(pBeachBackGround2, GROUP_TYPE::BEACHBACKGROUND2);
	

	CObject* pSwampBackGround = new CSwampBackGround;
	pSwampBackGround->SetName(L"SwampBackGround");
	pSwampBackGround->SetPos(Vec2(2530.f, 84.f));
	pSwampBackGround->SetScale(Vec2(0.f, 0.f));
	AddObject(pSwampBackGround, GROUP_TYPE::SWAMPBACKGROUND);
	
	CObject* pSwampBackGround2 = new CSwampBackGround2;
	pSwampBackGround2->SetName(L"SwampBackGround2");
	pSwampBackGround2->SetPos(Vec2(3058.f, 133.f));
	pSwampBackGround2->SetScale(Vec2(0.f, 0.f));
	AddObject(pSwampBackGround2, GROUP_TYPE::SWAMPBACKGROUND2);
	
	CObject* pSwampBackGround2_2 = new CSwampBackGround2;
	pSwampBackGround2_2->SetName(L"SwampBackGround2_2");
	pSwampBackGround2_2->SetPos(Vec2(3399.f, 133.f));
	pSwampBackGround2_2->SetScale(Vec2(0.f, 0.f));
	AddObject(pSwampBackGround2_2, GROUP_TYPE::SWAMPBACKGROUND2);
	
	CObject* pSwampBackGround2_3 = new CSwampBackGround2;
	pSwampBackGround2_3->SetName(L"SwampBackGround2_3");
	pSwampBackGround2_3->SetPos(Vec2(3740.f, 133.f));
	pSwampBackGround2_3->SetScale(Vec2(0.f, 0.f));
	AddObject(pSwampBackGround2_3, GROUP_TYPE::SWAMPBACKGROUND2);
	
	CObject* pSwampBackGround2_4 = new CSwampBackGround2;
	pSwampBackGround2_4->SetName(L"SwampBackGround2_4");
	pSwampBackGround2_4->SetPos(Vec2(4081.f, 133.f));
	pSwampBackGround2_4->SetScale(Vec2(0.f, 0.f));
	AddObject(pSwampBackGround2_4, GROUP_TYPE::SWAMPBACKGROUND2);
	
	CObject* pSwampBackGround3 = new CSwampBackGround3;
	pSwampBackGround3->SetName(L"SwampBackGround3");
	pSwampBackGround3->SetPos(Vec2(4422.f, 133.f));
	pSwampBackGround3->SetScale(Vec2(0.f, 0.f));
	AddObject(pSwampBackGround3, GROUP_TYPE::SWAMPBACKGROUND3);
	
	CObject* pBossStageBackGround = new CBossStageBackGround;
	pBossStageBackGround->SetName(L"BossStageBackGround");
	pBossStageBackGround->SetPos(Vec2(4711.f, 141.f));
	pBossStageBackGround->SetScale(Vec2(0.f, 0.f));
	AddObject(pBossStageBackGround, GROUP_TYPE::BOSSSTAGEBACKGROUND);
	
	CObject* pSlugTransport = new CSlugTransport;
	pSlugTransport->SetName(L"SlugTransport");
	pSlugTransport->SetPos(Vec2(2923.f, 189.f));
	pSlugTransport->SetScale(Vec2(0.f, 0.f));
	pSlugTransport->GetRayGround()->GetCollider()->GetVecRay().push_back(Vec2(2855.f, 215.f));
	pSlugTransport->GetRayGround()->GetCollider()->GetVecRay().push_back(Vec2(2966.f, 215.f));

	pSlugTransport->GetRayGround()->GetCollider()->GetVecRay().push_back(Vec2(2966.f, 215.f));
	pSlugTransport->GetRayGround()->GetCollider()->GetVecRay().push_back(Vec2(2984.f, 202.f));

	pSlugTransport->GetRayGround()->GetCollider()->GetVecRay().push_back(Vec2(2984.f, 202.f));
	pSlugTransport->GetRayGround()->GetCollider()->GetVecRay().push_back(Vec2(3018.f, 202.f));

	pSlugTransport->GetRayGround()->GetCollider()->GetVecRay().push_back(Vec2(2886.f, 174.f));
	pSlugTransport->GetRayGround()->GetCollider()->GetVecRay().push_back(Vec2(2957.f, 174.f));
	AddObject(pSlugTransport->GetRayGround(), GROUP_TYPE::GROUND);
	AddObject(pSlugTransport, GROUP_TYPE::SLUGTRANSPORT);

	//CObject* pBossStageBackGround = new CBossStageBackGround;
	//pBossStageBackGround->SetName(L"BossStageBackGround");
	//pBossStageBackGround->SetPos(Vec2(402.f, 70.f));
	//pBossStageBackGround->SetScale(Vec2(0.f, 0.f));
	////pObj->SetScale(Vec2(2889.f, 274.f));
	//AddObject(pBossStageBackGround, GROUP_TYPE::BOSSSTAGEBACKGROUND);


	CObject* pBrokenCongaHouse = new CBrokenCongaHouse;
	pBrokenCongaHouse->SetName(L"BrokenCongaHouse");
	pBrokenCongaHouse->SetPos(Vec2(777.f, 138.f));
	pBrokenCongaHouse->SetScale(Vec2(304.f, 166.f));
	AddObject(pBrokenCongaHouse, GROUP_TYPE::BROKENCONGAHOUSE);


	// 장애물 배치
	CObject* pCongaHouseObstacle = new CObstacle;
	pCongaHouseObstacle->SetName(L"Ground"); // 편의상 Ground라고 하겠음
	pCongaHouseObstacle->SetPos(Vec2(875.f, 75.f));
	pCongaHouseObstacle->SetScale(Vec2(120.f, 170.f));
	AddObject(pCongaHouseObstacle, GROUP_TYPE::GROUND);


	CObject* pCongaHouse = new CCongaHouse;
	pCongaHouse->SetName(L"CongaHouse");
	pCongaHouse->SetPos(Vec2(799.f, 116.f));
	pCongaHouse->SetScale(Vec2(264.f, 210.f));
	pCongaHouse->SetObstacle(pCongaHouseObstacle);
	AddObject(pCongaHouse, GROUP_TYPE::CONGAHOUSE);
	

	CObject* pShip = new CShip;
	pShip->SetName(L"Ship");
	pShip->SetPos(Vec2(1510.f, 93.f));
	pShip->SetScale(Vec2(203.f, 192.f));
	AddObject(pShip, GROUP_TYPE::SHIP);
	
	CObject* pR724 = new CR724;
	pR724->SetName(L"R724");
	pR724->SetPos(Vec2(1462.f, 129.f));
	pR724->SetScale(Vec2(279.f, 182.f));
	AddObject(pR724, GROUP_TYPE::R724);
	
	// 장애물 배치
	CObject* pShipEvent = new CEventObject;
	pShipEvent->SetName(L"Ground"); // 편의상 Ground라고 하겠음
	pShipEvent->SetPos(Vec2(1425.f, 118.f));
	pShipEvent->SetScale(Vec2(50.f, 200.f));	
	pShipEvent->SetCameraBox((CCameraBox*)pCameraBox);
	AddObject(pShipEvent, GROUP_TYPE::EVENT_OBJECT);
	CEventObject* pTemp = (CEventObject*)pShipEvent;
	pTemp->SetR724(pShip);
	pTemp->SetShip(pR724);
	
	CObject* pSwampEvent = new CEventObject2;
	pSwampEvent->SetName(L"Ground"); // 편의상 Ground라고 하겠음
	pSwampEvent->SetPos(Vec2(1715.f, 50.f));
	pSwampEvent->SetScale(Vec2(60.f, 40.f));
	pSwampEvent->SetCameraBox((CCameraBox*)pCameraBox);
	AddObject(pSwampEvent, GROUP_TYPE::EVENT_OBJECT);
	
	CObject* pSwampEvent2 = new CEventObject3;
	pSwampEvent2->SetName(L"Ground"); // 편의상 Ground라고 하겠음
	pSwampEvent2->SetPos(Vec2(2567.f, 110.f));
	pSwampEvent2->SetScale(Vec2(100.f, 100.f));
	pSwampEvent2->SetCameraBox((CCameraBox*)pCameraBox);
	AddObject(pSwampEvent2, GROUP_TYPE::EVENT_OBJECT);

	

	// 장애물 배치
	CObject* pStairObstacle1 = new CObstacle;
	pStairObstacle1->SetName(L"Ground"); // 편의상 Ground라고 하겠음
	pStairObstacle1->SetPos(Vec2(1600.f, 160.f));
	pStairObstacle1->SetScale(Vec2(50.f, 40.f));
	AddObject(pStairObstacle1, GROUP_TYPE::GROUND);

	 
	CObject* pStairObstacle2 = new CObstacle;
	pStairObstacle2->SetName(L"Ground"); // 편의상 Ground라고 하겠음
	pStairObstacle2->SetPos(Vec2(1636.f, 117.f));
	pStairObstacle2->SetScale(Vec2(30.f, 20.f));
	AddObject(pStairObstacle2, GROUP_TYPE::GROUND);
	 
	CObject* pStairObstacle3 = new CObstacle;
	pStairObstacle3->SetName(L"Ground"); // 편의상 Ground라고 하겠음
	pStairObstacle3->SetPos(Vec2(1675.f, 88.f));
	pStairObstacle3->SetScale(Vec2(20.f, 15.f));
	AddObject(pStairObstacle3, GROUP_TYPE::GROUND);


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
	pSwamp->SetPos(Vec2(pBeachFront->GetScale().x + 1473.f + 233.f, 127.f));
	pSwamp->SetScale(Vec2(3411.f, 221.f));
	//pObj->SetScale(Vec2(2889.f, 274.f));
	AddObject(pSwamp, GROUP_TYPE::SWAMP);
	
	CObject* pSwampUnder = new CSwampUnder;
	pSwampUnder->SetName(L"SwampUnder");
	pSwampUnder->SetPos(Vec2(pSwamp->GetPos().x -1062 , pSwamp->GetPos().y + 77));
	pSwampUnder->SetScale(Vec2(1289.f, 131.f));
	AddObject(pSwampUnder, GROUP_TYPE::SWAMPUNDER);
	
	CObject* pCaptive = new CCaptive;
	pCaptive->SetName(L"Captive");
	pCaptive->SetPos(Vec2(1015.f, 120.f));
	pCaptive->SetOrigPos(Vec2(1015.f, 120.f));
	pCaptive->SetScale(Vec2(100.f, 100.f));
	AddObject(pCaptive, GROUP_TYPE::CAPTIVE);
	
	pCaptive = new CCaptive;
	pCaptive->SetName(L"Captive");
	pCaptive->SetPos(Vec2(1905.f, 30.f));
	pCaptive->SetOrigPos(Vec2(1905.f, 30.f));
	pCaptive->SetScale(Vec2(100.f, 100.f));
	AddObject(pCaptive, GROUP_TYPE::CAPTIVE);

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


	//CMonster* pMon = CMonFactory::CreateMonster(MON_TYPE::CHOWMEIN_CONGA, Vec2(454, 149));
	////CreateObject(pMon, GROUP_TYPE::MONSTER);
	//AddObject(pMon, GROUP_TYPE::MONSTER);
	//pMon = CMonFactory::CreateMonster(MON_TYPE::CHOWMEIN_CONGA, Vec2(510, 140));
	//AddObject(pMon, GROUP_TYPE::MONSTER);
	//
	//pMon = CMonFactory::CreateMonster(MON_TYPE::CHOWMEIN_CONGA, Vec2(566, 149));
	//AddObject(pMon, GROUP_TYPE::MONSTER);
	//
	//pMon = CMonFactory::CreateMonster(MON_TYPE::CHOWMEIN_CONGA, Vec2(690, 129));
	//AddObject(pMon, GROUP_TYPE::MONSTER);
	//
	//pMon = CMonFactory::CreateMonster(MON_TYPE::CHOWMEIN_CONGA, Vec2(800, 100));
	//AddObject(pMon, GROUP_TYPE::MONSTER);
	//
	//pMon = CMonFactory::CreateMonster(MON_TYPE::CHOWMEIN_CONGA, Vec2(1040, 125));
	//AddObject(pMon, GROUP_TYPE::MONSTER);

	//pMon = CMonFactory::CreateMonster(MON_TYPE::CHOWMEIN_CONGA, Vec2(1067, 131));
	//AddObject(pMon, GROUP_TYPE::MONSTER);

	//pMon = CMonFactory::CreateMonster(MON_TYPE::CHOWMEIN_CONGA, Vec2(1345, 161));
	//AddObject(pMon, GROUP_TYPE::MONSTER);

	//pMon = CMonFactory::CreateMonster(MON_TYPE::CHOWMEIN_CONGA, Vec2(1384, 162));
	//AddObject(pMon, GROUP_TYPE::MONSTER);

	//pMon = CMonFactory::CreateMonster(MON_TYPE::CHOWMEIN_CONGA, Vec2(1400, 162));
	//AddObject(pMon, GROUP_TYPE::MONSTER);

	//pMon = CMonFactory::CreateMonster(MON_TYPE::CHOWMEIN_CONGA, Vec2(1687, 52));
	//AddObject(pMon, GROUP_TYPE::MONSTER);

	//pMon = CMonFactory::CreateMonster(MON_TYPE::CHOWMEIN_CONGA, Vec2(1719, 49));
	//AddObject(pMon, GROUP_TYPE::MONSTER);
	//
	//pMon = CMonFactory::CreateMonster(MON_TYPE::CHOWMEIN_CONGA, Vec2(2005, 93));
	//AddObject(pMon, GROUP_TYPE::MONSTER);
	//
	//pMon = CMonFactory::CreateMonster(MON_TYPE::CHOWMEIN_CONGA, Vec2(2057, 92));
	//AddObject(pMon, GROUP_TYPE::MONSTER);
	//
	//pMon = CMonFactory::CreateMonster(MON_TYPE::CHOWMEIN_CONGA, Vec2(2141, 107));
	//AddObject(pMon, GROUP_TYPE::MONSTER);
	//
	//pMon = CMonFactory::CreateMonster(MON_TYPE::CHOWMEIN_CONGA, Vec2(2180, 107));
	//AddObject(pMon, GROUP_TYPE::MONSTER);
	//
	//pMon = CMonFactory::CreateMonster(MON_TYPE::CHOWMEIN_CONGA, Vec2(2215, 60));
	//AddObject(pMon, GROUP_TYPE::MONSTER);
	//
	//pMon = CMonFactory::CreateMonster(MON_TYPE::CHOWMEIN_CONGA, Vec2(2256, 124));
	//AddObject(pMon, GROUP_TYPE::MONSTER);
	//
	//pMon = CMonFactory::CreateMonster(MON_TYPE::CHOWMEIN_CONGA, Vec2(2294, 124));
	//AddObject(pMon, GROUP_TYPE::MONSTER);
	//
	//pMon = CMonFactory::CreateMonster(MON_TYPE::CHOWMEIN_CONGA, Vec2(2330, 124));
	//AddObject(pMon, GROUP_TYPE::MONSTER);
	//
	//pMon = CMonFactory::CreateMonster(MON_TYPE::CHOWMEIN_CONGA, Vec2(2370, 124));
	//AddObject(pMon, GROUP_TYPE::MONSTER);	
	







	//pMon = CMonFactory::CreateMonster(MON_TYPE::LOCUST, Vec2(2450, 40));
	//AddObject(pMon, GROUP_TYPE::MONSTER);
	//
	//pMon = CMonFactory::CreateMonster(MON_TYPE::LOCUST, Vec2(2550, 40));
	//AddObject(pMon, GROUP_TYPE::MONSTER);
	//
	//pMon = CMonFactory::CreateMonster(MON_TYPE::LOCUST, Vec2(2600, 50));
	//AddObject(pMon, GROUP_TYPE::MONSTER);


	// 땅 물체 배치
	CObject* pGround = new CGround;
	pGround->SetName(L"Ground");
	pGround->SetPos(Vec2(100.f, 400.f));
	pGround->SetScale(Vec2(100.f, 10.f));
	AddObject(pGround, GROUP_TYPE::GROUND);
	
	


	// 타일 로딩
	//LoadTile(L"Tile\\Start.tile");				

	// 충돌 지정
	// Player 그룹과 Monster 그룹 간의 충돌체크
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::CONGAHOUSE);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PLAYER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::GROUND);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::GROUND);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::EVENT_OBJECT);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::CONGAHOUSE, GROUP_TYPE::PROJ_PLAYER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::BROKENSHIP, GROUP_TYPE::PROJ_PLAYER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::CAPTIVE, GROUP_TYPE::PROJ_PLAYER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::CAPTIVE, GROUP_TYPE::PLAYER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::CAPTIVE, GROUP_TYPE::GROUND);

	// Camera Look 지정
	// CCamera::GetInst()->SetLookAt(vResolution / 2.f);
	CCamera::GetInst()->SetLookAt(Vec2(3014.f, 242.f));

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
