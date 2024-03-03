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
#include "CEventObject4.h"
#include "CCaptive.h"
#include "CCameraBox.h"
#include "CM3_Rocket_Launch_Support_Van.h"
#include "CWoodenStool.h"
#include "CBossStageTile.h"
#include "CBossStageTileCopy.h"
#include "CSupplies.h"
#include "CBulletUI.h"

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
	if (KEY_TAP(KEY::C))
	{
		m_bColliderRender = !m_bColliderRender;
	}

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
	CCore::GetInst()->SetStretchRender(true);

	// Object 추가
	CObject* pObj = new CPlayer;
	pObj->SetName(L"Player");
	pObj->SetPos(Vec2(40.f, 145.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);

	RegisterPlayer(pObj);


	CObject* pCameraBox = new CCameraBox;
	pCameraBox->SetName(L"CameraBox"); // 직선 충돌체를 사용하므로 일단은 땅으로 간주함
	pCameraBox->SetPos(Vec2(40.f, 165.f));
	pCameraBox->SetScale(Vec2(200.f, 200.f));
	AddObject(pCameraBox, GROUP_TYPE::CAMERABOX);

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

	CObject* pBeach = new CBeach;  // 사실상 BEACHBACKGROUND3 임
	pBeach->SetName(L"Beach");
	pBeach->SetPos(Vec2(667.f, 170.f));
	pBeach->SetScale(Vec2(705.f, 48.f));
	//pObj->SetScale(Vec2(2889.f, 274.f));
	AddObject(pBeach, GROUP_TYPE::BEACHBACKGROUND3);
	

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
	
	CObject* pBossStageBackGroundCopy = new CBossStageBackGround;
	pBossStageBackGroundCopy->SetName(L"BossStageBackGroundCopy");
	pBossStageBackGroundCopy->SetPos(Vec2(5223.f, 141.f));
	pBossStageBackGroundCopy->SetScale(Vec2(0.f, 0.f));
	AddObject(pBossStageBackGroundCopy, GROUP_TYPE::BOSSSTAGEBACKGROUND);

	pBossStageBackGroundCopy = new CBossStageBackGround;
	pBossStageBackGroundCopy->SetName(L"BossStageBackGroundCopy");
	pBossStageBackGroundCopy->SetPos(Vec2(5735.f, 141.f));
	pBossStageBackGroundCopy->SetScale(Vec2(0.f, 0.f));
	AddObject(pBossStageBackGroundCopy, GROUP_TYPE::BOSSSTAGEBACKGROUND);
	
	pBossStageBackGroundCopy = new CBossStageBackGround;
	pBossStageBackGroundCopy->SetName(L"BossStageBackGroundCopy");
	pBossStageBackGroundCopy->SetPos(Vec2(6247.f, 141.f));
	pBossStageBackGroundCopy->SetScale(Vec2(0.f, 0.f));
	AddObject(pBossStageBackGroundCopy, GROUP_TYPE::BOSSSTAGEBACKGROUND);
	
	pBossStageBackGroundCopy = new CBossStageBackGround;
	pBossStageBackGroundCopy->SetName(L"BossStageBackGroundCopy");
	pBossStageBackGroundCopy->SetPos(Vec2(6759.f, 141.f));
	pBossStageBackGroundCopy->SetScale(Vec2(0.f, 0.f));
	AddObject(pBossStageBackGroundCopy, GROUP_TYPE::BOSSSTAGEBACKGROUND);
	
	CObject* pSlugTransport = new CSlugTransport;
	pSlugTransport->SetName(L"SlugTransport");
	pSlugTransport->SetPos(Vec2(2923.f, 189.f)); // Vec2(4600.f, 189.f)
	pSlugTransport->SetScale(Vec2(0.f, 0.f));

	pSlugTransport->SetCameraBox((CCameraBox*)pCameraBox);

	
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
	
	CObject* pSwampEvent2 = new CEventObject3;  // 거대메뚜기 이벤트
	pSwampEvent2->SetName(L"Ground"); // 편의상 Ground라고 하겠음
	pSwampEvent2->SetPos(Vec2(2567.f, 110.f));
	pSwampEvent2->SetScale(Vec2(100.f, 100.f));
	pSwampEvent2->SetCameraBox((CCameraBox*)pCameraBox);
	AddObject(pSwampEvent2, GROUP_TYPE::EVENT_OBJECT);
	
	CObject* pSwampEvent3 = new CEventObject4;
	pSwampEvent3->SetName(L"EventObject4"); 
	pSwampEvent3->SetPos(Vec2(4800.f, 210.f));
	pSwampEvent3->SetScale(Vec2(50.f, 50.f));
	pSwampEvent3->SetCameraBox((CCameraBox*)pCameraBox);
	AddObject(pSwampEvent3, GROUP_TYPE::EVENT_OBJECT);

	

	// 장애물 배치
	CObject* pStairObstacle1 = new CObstacle;
	pStairObstacle1->SetName(L"Ground"); // 편의상 Ground라고 하겠음
	pStairObstacle1->SetPos(Vec2(1600.f, 160.f));
	pStairObstacle1->SetScale(Vec2(50.f, 40.f));
	AddObject(pStairObstacle1, GROUP_TYPE::GROUND);

	 
	CObject* pStairObstacle2 = new CObstacle;
	pStairObstacle2->SetName(L"Ground"); 
	pStairObstacle2->SetPos(Vec2(1636.f, 117.f));
	pStairObstacle2->SetScale(Vec2(30.f, 20.f));
	AddObject(pStairObstacle2, GROUP_TYPE::GROUND);
	 
	CObject* pStairObstacle3 = new CObstacle;
	pStairObstacle3->SetName(L"Ground"); 
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
	
	CObject* pBossStageTile = new CBossStageTile;
	pBossStageTile->SetName(L"BossStageTile");
	pBossStageTile->SetPos(Vec2(4802.f, 219.f));
	pBossStageTile->SetScale(Vec2(50.f, 50.f));
	AddObject(pBossStageTile, GROUP_TYPE::BOSSSTAGETILE);

	CObject* pBossStageTileCopy;
	for (int i = 0; i < 10; ++i)
	{
		pBossStageTileCopy = new CBossStageTileCopy;
		pBossStageTileCopy->SetName(L"BossStageTileCopy");
		pBossStageTileCopy->SetPos(Vec2(4843.f + 32.f * i, 219.f));
		pBossStageTileCopy->SetScale(Vec2(50.f, 50.f));
		AddObject(pBossStageTileCopy, GROUP_TYPE::BOSSSTAGETILECOPY);

		//pBossStageTileCopy->GetRayGround()->GetCollider()->GetVecRay().push_back(Vec2(4843.f + 32.f * i - 16.f, 207.f));
		//pBossStageTileCopy->GetRayGround()->GetCollider()->GetVecRay().push_back(Vec2(4843.f + 32.f * i + 16.f, 207.f));
		//AddObject(pBossStageTileCopy->GetRayGround(), GROUP_TYPE::GROUND);
	}

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


	CObject* pSupplies = new CSupplies;
	pSupplies->SetName(L"Supplies");
	pSupplies->SetPos(Vec2(200.f, 139.f));
	pSupplies->SetScale(Vec2(100.f, 100.f));
	AddObject(pSupplies, GROUP_TYPE::SUPPLIES);


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
	

	CMonster* pMon = CMonFactory::CreateMonster(MON_TYPE::CHOWMEIN_CONGA, Vec2(454, 149));
	//CreateObject(pMon, GROUP_TYPE::MONSTER);
	AddObject(pMon, GROUP_TYPE::MONSTER);
	 
	 
	pMon = CMonFactory::CreateMonster(MON_TYPE::CHOWMEIN_CONGA, Vec2(510, 140));
	AddObject(pMon, GROUP_TYPE::MONSTER);
	
	pMon = CMonFactory::CreateMonster(MON_TYPE::CHOWMEIN_CONGA, Vec2(566, 149));
	AddObject(pMon, GROUP_TYPE::MONSTER);
	
	pMon = CMonFactory::CreateMonster(MON_TYPE::CHOWMEIN_CONGA, Vec2(690, 129));
	AddObject(pMon, GROUP_TYPE::MONSTER);
	
	pMon = CMonFactory::CreateMonster(MON_TYPE::CHOWMEIN_CONGA, Vec2(800, 100));
	AddObject(pMon, GROUP_TYPE::MONSTER);
	
	pMon = CMonFactory::CreateMonster(MON_TYPE::CHOWMEIN_CONGA, Vec2(1040, 125));
	AddObject(pMon, GROUP_TYPE::MONSTER);

	pMon = CMonFactory::CreateMonster(MON_TYPE::CHOWMEIN_CONGA, Vec2(1067, 131));
	AddObject(pMon, GROUP_TYPE::MONSTER);

	pMon = CMonFactory::CreateMonster(MON_TYPE::CHOWMEIN_CONGA, Vec2(1345, 161));
	AddObject(pMon, GROUP_TYPE::MONSTER);

	pMon = CMonFactory::CreateMonster(MON_TYPE::CHOWMEIN_CONGA, Vec2(1384, 162));
	AddObject(pMon, GROUP_TYPE::MONSTER);

	pMon = CMonFactory::CreateMonster(MON_TYPE::CHOWMEIN_CONGA, Vec2(1400, 162));
	AddObject(pMon, GROUP_TYPE::MONSTER);

	pMon = CMonFactory::CreateMonster(MON_TYPE::CHOWMEIN_CONGA, Vec2(1687, 52));
	AddObject(pMon, GROUP_TYPE::MONSTER);

	pMon = CMonFactory::CreateMonster(MON_TYPE::CHOWMEIN_CONGA, Vec2(1719, 49));
	AddObject(pMon, GROUP_TYPE::MONSTER);
	
	pMon = CMonFactory::CreateMonster(MON_TYPE::CHOWMEIN_CONGA, Vec2(2005, 93));
	AddObject(pMon, GROUP_TYPE::MONSTER);
	
	pMon = CMonFactory::CreateMonster(MON_TYPE::CHOWMEIN_CONGA, Vec2(2057, 92));
	AddObject(pMon, GROUP_TYPE::MONSTER);
	
	pMon = CMonFactory::CreateMonster(MON_TYPE::CHOWMEIN_CONGA, Vec2(2141, 107));
	AddObject(pMon, GROUP_TYPE::MONSTER);
	
	pMon = CMonFactory::CreateMonster(MON_TYPE::CHOWMEIN_CONGA, Vec2(2180, 107));
	AddObject(pMon, GROUP_TYPE::MONSTER);
	
	pMon = CMonFactory::CreateMonster(MON_TYPE::CHOWMEIN_CONGA, Vec2(2215, 60));
	AddObject(pMon, GROUP_TYPE::MONSTER);
	
	pMon = CMonFactory::CreateMonster(MON_TYPE::CHOWMEIN_CONGA, Vec2(2256, 124));
	AddObject(pMon, GROUP_TYPE::MONSTER);
	
	pMon = CMonFactory::CreateMonster(MON_TYPE::CHOWMEIN_CONGA, Vec2(2294, 124));
	AddObject(pMon, GROUP_TYPE::MONSTER);
	
	pMon = CMonFactory::CreateMonster(MON_TYPE::CHOWMEIN_CONGA, Vec2(2330, 124));
	AddObject(pMon, GROUP_TYPE::MONSTER);
	
	pMon = CMonFactory::CreateMonster(MON_TYPE::M3_ROCKET_LAUNCH_SUPPORT_VAN, Vec2(3300.f, 180.f));
	AddObject(pMon, GROUP_TYPE::MONSTER);

	CObject* pSwampObstacle = new CObstacle;
	pSwampObstacle->SetName(L"Ground");
	pSwampObstacle->SetPos(Vec2(3300.f, 180.f));
	pSwampObstacle->SetScale(Vec2(100.f, 100.f));
	pMon->SetObstacle(pSwampObstacle);
	AddObject(pSwampObstacle, GROUP_TYPE::GROUND);


	CObject* pWoodenStool = new CWoodenStool;
	pWoodenStool->SetName(L"WoodenStool");
	pWoodenStool->SetPos(Vec2(3315.f, 230.f));
	pWoodenStool->SetScale(Vec2(0.f, 0.f));
	AddObject(pWoodenStool, GROUP_TYPE::WOODENSTOOL);

	pMon->SetRelatedObj(pWoodenStool);
	
	pMon = CMonFactory::CreateMonster(MON_TYPE::M3_ROCKET_LAUNCH_SUPPORT_VAN, Vec2(4200.f, 180.f));
	AddObject(pMon, GROUP_TYPE::MONSTER);

	CObject* pSwampObstacle2 = new CObstacle;
	pSwampObstacle2->SetName(L"Ground");
	pSwampObstacle2->SetPos(Vec2(4200.f, 180.f));
	pSwampObstacle2->SetScale(Vec2(100.f, 100.f));
	pMon->SetObstacle(pSwampObstacle2);
	AddObject(pSwampObstacle2, GROUP_TYPE::GROUND);


	CObject* pWoodenStool2 = new CWoodenStool;
	pWoodenStool2->SetName(L"WoodenStool2");
	pWoodenStool2->SetPos(Vec2(4215.f, 230.f));
	pWoodenStool2->SetScale(Vec2(0.f, 0.f));
	AddObject(pWoodenStool2, GROUP_TYPE::WOODENSTOOL);

	pMon->SetRelatedObj(pWoodenStool2);


	//pMon = CMonFactory::CreateMonster(MON_TYPE::HUGE_HERMIT, Vec2(4700.f, 134.f));
	//AddObject(pMon, GROUP_TYPE::MONSTER);


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

	// 총알수 UI 배치

	CPlayer* pPlayer = (CPlayer*)pObj;
	Vec2 vCameraPos = CCamera::GetInst()->GetLookAt();

	CObject* pBulletUIDigit100 = new CBulletUI(Digit::Bullet100, pPlayer);
	pBulletUIDigit100->SetName(L"BulletUI");
	pBulletUIDigit100->SetDiff(Vec2(20.f -500.f, 0.f - 350.f));
	pBulletUIDigit100->SetScale(Vec2(100.f, 10.f));
	AddObject(pBulletUIDigit100, GROUP_TYPE::BULLETUI);
	

	CObject* pBulletUIDigit10 = new CBulletUI(Digit::Bullet10, pPlayer);
	pBulletUIDigit10->SetName(L"BulletUI");
	pBulletUIDigit10->SetDiff(Vec2(36.f - 500.f, 0.f - 350.f));
	pBulletUIDigit10->SetScale(Vec2(100.f, 10.f));
	AddObject(pBulletUIDigit10, GROUP_TYPE::BULLETUI);

	CObject* pBulletUIDigit1 = new CBulletUI(Digit::Bullet1, pPlayer);
	pBulletUIDigit1->SetName(L"BulletUI");
	pBulletUIDigit1->SetDiff(Vec2(52.f - 500.f , 0.f - 350.f));
	pBulletUIDigit1->SetScale(Vec2(100.f, 10.f));
	AddObject(pBulletUIDigit1, GROUP_TYPE::BULLETUI);

	CObject* pGrenadeUIDigit10 = new CBulletUI(Digit::Grenade10, pPlayer);
	pGrenadeUIDigit10->SetName(L"BulletUI");
	pGrenadeUIDigit10->SetDiff(Vec2(82.f - 500.f, 0.f - 350.f));
	pGrenadeUIDigit10->SetScale(Vec2(100.f, 10.f));
	AddObject(pGrenadeUIDigit10, GROUP_TYPE::BULLETUI);

	CObject* pGrenadeUIDigit1 = new CBulletUI(Digit::Grenade1, pPlayer);
	pGrenadeUIDigit1->SetName(L"BulletUI");
	pGrenadeUIDigit1->SetDiff(Vec2(98.f - 500.f, 0.f - 350.f));
	pGrenadeUIDigit1->SetScale(Vec2(100.f, 10.f));
	AddObject(pGrenadeUIDigit1, GROUP_TYPE::BULLETUI);

	CObject* pBulletUI_B = new CBulletUI(FONT::B, pPlayer);
	pBulletUI_B->SetName(L"BulletUI");
	pBulletUI_B->SetDiff(Vec2(98.f - 520.f, 0.f - 365.f));
	pBulletUI_B->SetScale(Vec2(100.f, 10.f));
	AddObject(pBulletUI_B, GROUP_TYPE::BULLETUI);
	
	CObject* pBulletUI_O = new CBulletUI(FONT::O, pPlayer);
	pBulletUI_O->SetName(L"BulletUI");
	pBulletUI_O->SetDiff(Vec2(98.f - 510.f, 0.f - 365.f));
	pBulletUI_O->SetScale(Vec2(100.f, 10.f));
	AddObject(pBulletUI_O, GROUP_TYPE::BULLETUI);

	CObject* pBulletUI_M = new CBulletUI(FONT::M, pPlayer);
	pBulletUI_M->SetName(L"BulletUI");
	pBulletUI_M->SetDiff(Vec2(98.f - 500.f, 0.f - 365.f));
	pBulletUI_M->SetScale(Vec2(100.f, 10.f));
	AddObject(pBulletUI_M, GROUP_TYPE::BULLETUI);

	CObject* pBulletUI_B2 = new CBulletUI(FONT::B, pPlayer);
	pBulletUI_B2->SetName(L"BulletUI");
	pBulletUI_B2->SetDiff(Vec2(98.f - 490.f, 0.f - 365.f));
	pBulletUI_B2->SetScale(Vec2(100.f, 10.f));
	AddObject(pBulletUI_B2, GROUP_TYPE::BULLETUI);

	
	CObject* pBulletUI_A = new CBulletUI(FONT::A, pPlayer);
	pBulletUI_A->SetName(L"BulletUI");
	pBulletUI_A->SetDiff(Vec2(98.f - 575.f, 0.f - 365.f));
	pBulletUI_A->SetScale(Vec2(100.f, 10.f));
	AddObject(pBulletUI_A, GROUP_TYPE::BULLETUI);
	
	CObject* pBulletUI_R = new CBulletUI(FONT::R, pPlayer);
	pBulletUI_R->SetName(L"BulletUI");
	pBulletUI_R->SetDiff(Vec2(98.f - 565.f, 0.f - 365.f));
	pBulletUI_R->SetScale(Vec2(100.f, 10.f));
	AddObject(pBulletUI_R, GROUP_TYPE::BULLETUI);

	CObject* pBulletUI_M2 = new CBulletUI(FONT::M, pPlayer);
	pBulletUI_M2->SetName(L"BulletUI");
	pBulletUI_M2->SetDiff(Vec2(98.f - 555.f, 0.f - 365.f));
	pBulletUI_M2->SetScale(Vec2(100.f, 10.f));
	AddObject(pBulletUI_M2, GROUP_TYPE::BULLETUI);

	CObject* pBulletUI_S = new CBulletUI(FONT::S, pPlayer);
	pBulletUI_S->SetName(L"BulletUI");
	pBulletUI_S->SetDiff(Vec2(98.f - 545.f, 0.f - 365.f));
	pBulletUI_S->SetScale(Vec2(100.f, 10.f));
	AddObject(pBulletUI_S, GROUP_TYPE::BULLETUI);
	
	//CObject* pBulletUI_ZERO = new CBulletUI(FONT::ZERO, pPlayer);
	//pBulletUI_ZERO->SetName(L"BulletUI");
	//pBulletUI_ZERO->SetPos(Vec2(660.f, 400.f));
	//pBulletUI_ZERO->SetScale(Vec2(100.f, 10.f));
	//AddObject(pBulletUI_ZERO, GROUP_TYPE::BULLETUI);
	//
	//CObject* pBulletUI_ONE = new CBulletUI(FONT::ONE, pPlayer);
	//pBulletUI_ONE->SetName(L"BulletUI");
	//pBulletUI_ONE->SetPos(Vec2(670.f, 400.f));
	//pBulletUI_ONE->SetScale(Vec2(100.f, 10.f));
	//AddObject(pBulletUI_ONE, GROUP_TYPE::BULLETUI);
	//
	//CObject* pBulletUI_TWO = new CBulletUI(FONT::TWO, pPlayer);
	//pBulletUI_TWO->SetName(L"BulletUI");
	//pBulletUI_TWO->SetPos(Vec2(680.f, 400.f));
	//pBulletUI_TWO->SetScale(Vec2(100.f, 10.f));
	//AddObject(pBulletUI_TWO, GROUP_TYPE::BULLETUI);
	//
	//CObject* pBulletUI_THREE = new CBulletUI(FONT::THREE, pPlayer);
	//pBulletUI_THREE->SetName(L"BulletUI");
	//pBulletUI_THREE->SetPos(Vec2(690.f, 400.f));
	//pBulletUI_THREE->SetScale(Vec2(100.f, 10.f));
	//AddObject(pBulletUI_THREE, GROUP_TYPE::BULLETUI);
	//
	//CObject* pBulletUI_FOUR = new CBulletUI(FONT::FOUR, pPlayer);
	//pBulletUI_FOUR->SetName(L"BulletUI");
	//pBulletUI_FOUR->SetPos(Vec2(700.f, 400.f));
	//pBulletUI_FOUR->SetScale(Vec2(100.f, 10.f));
	//AddObject(pBulletUI_FOUR, GROUP_TYPE::BULLETUI);
	//
	//CObject* pBulletUI_FIVE = new CBulletUI(FONT::FIVE, pPlayer);
	//pBulletUI_FIVE->SetName(L"BulletUI");
	//pBulletUI_FIVE->SetPos(Vec2(7100.f, 400.f));
	//pBulletUI_FIVE->SetScale(Vec2(100.f, 10.f));
	//AddObject(pBulletUI_FIVE, GROUP_TYPE::BULLETUI);
	//
	//CObject* pBulletUI_SIX = new CBulletUI(FONT::SIX, pPlayer);
	//pBulletUI_SIX->SetName(L"BulletUI");
	//pBulletUI_SIX->SetPos(Vec2(720.f, 400.f));
	//pBulletUI_SIX->SetScale(Vec2(100.f, 10.f));
	//AddObject(pBulletUI_SIX, GROUP_TYPE::BULLETUI);
	//
	//CObject* pBulletUI_SEVEN = new CBulletUI(FONT::SEVEN, pPlayer);
	//pBulletUI_SEVEN->SetName(L"BulletUI");
	//pBulletUI_SEVEN->SetPos(Vec2(730.f, 400.f));
	//pBulletUI_SEVEN->SetScale(Vec2(100.f, 10.f));
	//AddObject(pBulletUI_SEVEN, GROUP_TYPE::BULLETUI);
	//
	//CObject* pBulletUI_EIGHT = new CBulletUI(FONT::EIGHT, pPlayer);
	//pBulletUI_EIGHT->SetName(L"BulletUI");
	//pBulletUI_EIGHT->SetPos(Vec2(740.f, 400.f));
	//pBulletUI_EIGHT->SetScale(Vec2(100.f, 10.f));
	//AddObject(pBulletUI_EIGHT, GROUP_TYPE::BULLETUI);
	//
	//CObject* pBulletUI_NINE = new CBulletUI(FONT::NINE, pPlayer);
	//pBulletUI_NINE->SetName(L"BulletUI");
	//pBulletUI_NINE->SetPos(Vec2(750.f, 400.f));
	//pBulletUI_NINE->SetScale(Vec2(100.f, 10.f));
	//AddObject(pBulletUI_NINE, GROUP_TYPE::BULLETUI);
	
	
	


	// 타일 로딩
	//LoadTile(L"Tile\\Start.tile");				

	// 충돌 지정
	// Player 그룹과 Monster 그룹 간의 충돌체크
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::CONGAHOUSE);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::SUPPLIES);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::CAMERABOX);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PLAYER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::GROUND, GROUP_TYPE::PROJ_PLAYER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::GROUND);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::GROUND);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::SUPPLIES, GROUP_TYPE::GROUND);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::EVENT_OBJECT);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::CONGAHOUSE, GROUP_TYPE::PROJ_PLAYER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::BROKENSHIP, GROUP_TYPE::PROJ_PLAYER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::CAPTIVE, GROUP_TYPE::PROJ_PLAYER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::CAPTIVE, GROUP_TYPE::PLAYER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::CAPTIVE, GROUP_TYPE::GROUND);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::SLUGTRANSPORT);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::SLUGTRANSPORT, GROUP_TYPE::GROUND);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::SLUGTRANSPORT, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::SLUGTRANSPORT, GROUP_TYPE::BOSSSTAGETILECOPY);

	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::BOSSSTAGETILECOPY); // 보스 몬스터와 타일맵
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::BOSSSTAGETILE);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::SLUGTRANSPORT, GROUP_TYPE::EVENT_OBJECT);

	// Camera Look 지정
	CCamera::GetInst()->SetLookAt(vResolution / 2.f);
	// CCamera::GetInst()->SetLookAt(Vec2(3014.f, 242.f)); //늪지대 비추기
	//CCamera::GetInst()->SetLookAt(Vec2(5010.f, 292.f)); // 보스 스테이지 비추기

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
