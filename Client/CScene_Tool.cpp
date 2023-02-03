#include "pch.h"
#include "CScene_Tool.h"

#include "CKeyMgr.h"
#include "CTile.h"

#include "CCore.h"
#include "CResMgr.h"
#include "CSceneMgr.h"
#include "CPathMgr.h"

#include "resource.h"

#include "CUIMgr.h"
#include "CPanelUI.h"
#include "CBtnUI.h"
#include "CObject.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CTestAnim.h"
#include "string"

using namespace std;

extern HWND hMDlg;
extern HWND hList_AnimFile_Name1, hList_AnimFile_Name2, hList_Frame_Info1, hList_Frame_Info2, hList_PlayList;
extern HWND hEdit_StartX, hEdit_StartY, hEdit_EndX, hEdit_EndY, hEdit_OffsetX, hEdit_OffsetY, hEdit_Duration, hEdit_PlayTime, hEdit_PlayScale, hEdit_Frame_Count;

void ChangeScene(DWORD_PTR, DWORD_PTR);

CScene_Tool::CScene_Tool()
	: m_pUI(nullptr)
	, m_pTestAnim(nullptr)
	, iFocusAnimFile(0)
{
}

CScene_Tool::~CScene_Tool()
{
}

void CScene_Tool::Enter()
{	
	// 툴 Scene 에서 사용할 메뉴를 붙인다.
	CCore::GetInst()->DockMenu();

	// 타일 생성
	// CreateTile(5, 5);

	// UI 하나 만들어보기
	Vec2 vResolution = CCore::GetInst()->GetResolution();

	CUI* pPanelUI = new CPanelUI;
	pPanelUI->SetName(L"ParentUI");
	pPanelUI->SetScale(Vec2(300.f, 150.f));
	pPanelUI->SetPos(Vec2(vResolution.x - pPanelUI->GetScale().x, 0.f));

	CBtnUI* pBtnUI = new CBtnUI;
	pBtnUI->SetName(L"ChildUI");
	pBtnUI->SetScale(Vec2(100.f, 40.f));
	pBtnUI->SetPos(Vec2(0.f, 0.f));
	((CBtnUI*)pBtnUI)->SetClickedCallBack(this, (SCENE_MEMFUNC)&CScene_Tool::SaveTileData);
	pPanelUI->AddChild(pBtnUI);
	AddObject(pPanelUI, GROUP_TYPE::UI);


	// Object 추가
	CTestAnim* pObj = new CTestAnim;
	pObj->SetName(L"Player");
	pObj->SetPos(Vec2(640.f, 384.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);
	m_pTestAnim = pObj;
	

	RegisterPlayer(pObj);

	

	/*CTestAnim* pTestAnim = new CTestAnim;
	pTestAnim->SetName(L"TestAnim");
	AddObject(pTestAnim, GROUP_TYPE::TEST_ANIM);*/


	// 복사분 UI
	//CUI* pClonePanel = pPanelUI->Clone();
	//pClonePanel->SetPos(pClonePanel->GetPos() + Vec2(-300.f, 0.f));
	//((CBtnUI*)pClonePanel->GetChildUI()[0])->SetClickedCallBack(&ChangeScene, 0, 0);
	//AddObject(pClonePanel, GROUP_TYPE::UI);

	//m_pUI = pClonePanel;

	// Camera Look 지정
	CCamera::GetInst()->SetLookAt(vResolution / 2.f);

	start();
}

void CScene_Tool::Exit()
{
	CCore::GetInst()->DivideMenu();

	DeleteAll();
}

void CScene_Tool::update()
{
	CScene::update();

	SetTileIdx();

	//if (KEY_TAP(KEY::LSHIFT))
	//{
	//	//CUIMgr::GetInst()->SetFocusedUI(m_pUI);

	//	SaveTileData();
	//}

	/*if (KEY_TAP(KEY::CTRL))
	{
		LoadTileData();
	}*/
	
	if (KEY_TAP(KEY::S))
	{
		m_pTestAnim->GetAnimator()->StopAnimationL(true);
		m_pTestAnim->GetAnimator()->StopAnimationU(true);
	}

	
}


void CScene_Tool::SetTileIdx()
{
	if (KEY_TAP(KEY::LBTN))
	{
		Vec2 vMousePos = MOUSE_POS;
		vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);

		int iTileX = (int)GetTileX();
		int iTileY = (int)GetTileY();

		int iCol = (int)vMousePos.x / TILE_SIZE;
		int iRow = (int)vMousePos.y / TILE_SIZE;

		if (vMousePos.x < 0.f || iTileX <= iCol
			|| vMousePos.y < 0.f || iTileY <= iRow)
		{
			return;
		}

		UINT iIdx = iRow * iTileX + iCol;

		const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);
		((CTile*)vecTile[iIdx])->AddImgIdx();
	}


}

void CScene_Tool::SaveTileData()
{
	wchar_t szName[256] = {};

	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CCore::GetInst()->GetMainHwnd(); // 열릴 창, 부모 윈도우
	ofn.lpstrFile = szName;		// 완성된 경로가 채워질 곳
	ofn.nMaxFile = sizeof(szName);		// 방금 지정한 배열의 최대 길이(배열의 크기)
	ofn.lpstrFilter = L"ALL\0*.*\0Tile\0*.tile";		// 특정 확장자명 파일만 보여주기 ALL은 필터에서 노출되는 녀석이지 모든 파일이 다 보이는 건 아님 다 보이려면 \0*.* 이걸 붙여야 됨
	ofn.nFilterIndex = 0;		// 내가 골라놓은 것 중에 초기 필터를 뭘로 세팅해놓을까를 말하는 것
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;
	
	wstring strTileFolder = CPathMgr::GetInst()->GetContentPath();
	strTileFolder += L"tile";

	ofn.lpstrInitialDir = strTileFolder.c_str();		// 초기 경로
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;		// 경로가 반드시 존재해야 함
	
	// Modal 방식임
	if (GetSaveFileName(&ofn)) // 인자 정보를 토대로 창을 엶
	{
		CPathMgr::GetInst()->GetRelativePath(szName);
		SaveTile(szName);
	}

}


void CScene_Tool::LoadTileData()
{
	wchar_t szName[256] = {};

	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CCore::GetInst()->GetMainHwnd(); // 열릴 창, 부모 윈도우
	ofn.lpstrFile = szName;		// 완성된 경로가 채워질 곳
	ofn.nMaxFile = sizeof(szName);		// 방금 지정한 배열의 최대 길이(배열의 크기)
	ofn.lpstrFilter = L"ALL\0*.*\0Tile\0*.tile";		// 특정 확장자명 파일만 보여주기 ALL은 필터에서 노출되는 녀석이지 모든 파일이 다 보이는 건 아님 다 보이려면 \0*.* 이걸 붙여야 됨
	ofn.nFilterIndex = 0;		// 내가 골라놓은 것 중에 초기 필터를 뭘로 세팅해놓을까를 말하는 것
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;

	wstring strTileFolder = CPathMgr::GetInst()->GetContentPath();
	strTileFolder += L"tile";

	ofn.lpstrInitialDir = strTileFolder.c_str();		// 초기 경로
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;		// 경로가 반드시 존재해야 함

	// Modal 방식임
	if (GetOpenFileName(&ofn)) // 인자 정보를 토대로 창을 엶
	{
		// 어차피 이 안에서 절대경로를 다시 붙여주니까 상대경로만 주면 됨
		wstring strRelativePath = CPathMgr::GetInst()->GetRelativePath(szName);
		LoadTile(strRelativePath);
	}
}

void CScene_Tool::LoadAnimationData()
{
	wchar_t szName[256] = {};

	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CCore::GetInst()->GetMainHwnd(); // 열릴 창, 부모 윈도우
	ofn.lpstrFile = szName;		// 완성된 경로가 채워질 곳
	ofn.nMaxFile = sizeof(szName);		// 방금 지정한 배열의 최대 길이(배열의 크기)
	ofn.lpstrFilter = L"ALL\0*.*\0animation\0*.txt";		// 특정 확장자명 파일만 보여주기 ALL은 필터에서 노출되는 녀석이지 모든 파일이 다 보이는 건 아님 다 보이려면 \0*.* 이걸 붙여야 됨
	ofn.nFilterIndex = 0;		// 내가 골라놓은 것 중에 초기 필터를 뭘로 세팅해놓을까를 말하는 것
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;

	wstring strTileFolder = CPathMgr::GetInst()->GetContentPath();
	strTileFolder += L"anim";

	ofn.lpstrInitialDir = strTileFolder.c_str();		// 초기 경로
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;		// 경로가 반드시 존재해야 함

	// Modal 방식임
	if (GetOpenFileName(&ofn)) // 인자 정보를 토대로 창을 엶
	{
		// 어차피 이 안에서 절대경로를 다시 붙여주니까 상대경로만 주면 됨
		wstring strRelativePath = CPathMgr::GetInst()->GetRelativePath(szName);
		m_pTestAnim->GetAnimator()->LoadAnimation(strRelativePath);

		strRelativePath.erase(0, 10);

		std::wstring::size_type strTemp;
		strTemp = strRelativePath.find(L".anim", 0);
		strRelativePath.erase(strTemp, 5);

		wstring strAnimFile = strRelativePath;
		m_pTestAnim->SetCurAnimFile1(strAnimFile);
		m_vecAnimFile1.push_back(strAnimFile);
		SendMessage(hList_AnimFile_Name1, LB_ADDSTRING, 0, (LPARAM)strAnimFile.c_str());
	}
}

void CScene_Tool::LoadAnimationData2()
{
	wchar_t szName[256] = {};

	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CCore::GetInst()->GetMainHwnd(); // 열릴 창, 부모 윈도우
	ofn.lpstrFile = szName;		// 완성된 경로가 채워질 곳
	ofn.nMaxFile = sizeof(szName);		// 방금 지정한 배열의 최대 길이(배열의 크기)
	ofn.lpstrFilter = L"ALL\0*.*\0animation\0*.txt";		// 특정 확장자명 파일만 보여주기 ALL은 필터에서 노출되는 녀석이지 모든 파일이 다 보이는 건 아님 다 보이려면 \0*.* 이걸 붙여야 됨
	ofn.nFilterIndex = 0;		// 내가 골라놓은 것 중에 초기 필터를 뭘로 세팅해놓을까를 말하는 것
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;

	wstring strTileFolder = CPathMgr::GetInst()->GetContentPath();
	strTileFolder += L"anim";

	ofn.lpstrInitialDir = strTileFolder.c_str();		// 초기 경로
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;		// 경로가 반드시 존재해야 함

	// Modal 방식임
	if (GetOpenFileName(&ofn)) // 인자 정보를 토대로 창을 엶
	{
		// 어차피 이 안에서 절대경로를 다시 붙여주니까 상대경로만 주면 됨
		wstring strRelativePath = CPathMgr::GetInst()->GetRelativePath(szName);
		m_pTestAnim->GetAnimator()->LoadAnimation(strRelativePath);

		strRelativePath.erase(0, 10);

		std::wstring::size_type strTemp;
		strTemp = strRelativePath.find(L".anim", 0);
		strRelativePath.erase(strTemp, 5);

		wstring strAnimFile = strRelativePath;
		m_pTestAnim->SetCurAnimFile2(strAnimFile);
		m_vecAnimFile2.push_back(strAnimFile);
		SendMessage(hList_AnimFile_Name2, LB_ADDSTRING, 0, (LPARAM)strAnimFile.c_str());
	}
}

void CScene_Tool::SaveTile(const wstring& _strFilePath)
{
	// 커널 오브젝트
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, _strFilePath.c_str(), L"wb");

	assert(pFile);

	// 타일 가로세로 개수 저장
	UINT xCount = GetTileX();
	UINT yCount = GetTileY();

	fwrite(&xCount, sizeof(UINT), 1, pFile);
	fwrite(&yCount, sizeof(UINT), 1, pFile);

	// 모든 타일들을 개별적으로 저장할 데이터를 저장하게 함
	const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		((CTile*)vecTile[i])->Save(pFile);
	}

	fclose(pFile);
}


void ChangeScene(DWORD_PTR, DWORD_PTR)
{
	ChangeScene(SCENE_TYPE::START);
}






// ======================
// Tile Count Window Proc
// ======================
INT_PTR CALLBACK TileCountProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) // CSene_tool의 멤버 함수는 아님!!
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK )
		{
			UINT iXCount = GetDlgItemInt(hDlg, IDC_EDIT1, nullptr, false);
			UINT iYCount = GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, false);

			CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

			// ToolScene 확인
			CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(pCurScene);
			assert(pToolScene);

			pToolScene->DeleteGroup(GROUP_TYPE::TILE);
			pToolScene->CreateTile(iXCount, iYCount);

			EndDialog(hDlg, LOWORD(wParam));
		 	return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK AnimationToolProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	// ToolScene 확인
	CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(pCurScene);
	assert(pToolScene);

	CAnimator* pAnimator = pToolScene->GetTestAnim()->GetAnimator();

	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_LoadFile:
			pToolScene->LoadAnimationData();
			return TRUE;
			
		case IDC_BUTTON_LoadFile2:
			pToolScene->LoadAnimationData2();
			return TRUE;

		case IDC_BUTTON_Set:
			return TRUE;

		case IDC_BUTTON_Reset:
			return TRUE;

		case IDC_BUTTON_Add_PlayList:
			return TRUE;

		case IDC_BUTTON_SaveFile:
		{
			if (pToolScene->iFocusAnimFile == 1)
			{
				int Anim_idx = SendMessage(hList_AnimFile_Name1, LB_GETCURSEL, 0, 0);
				int Frame_idx = SendMessage(hList_Frame_Info1, LB_GETCURSEL, 0, 0);
				wstring AnimFile1 = pToolScene->GetAnimFile1().at(Anim_idx);
				CAnimation* pAnimation = pAnimator->FindAnimation(AnimFile1);
				AnimFile1.insert(0, L"animation\\");
				AnimFile1.append(L".anim");
				pAnimation->Save(AnimFile1);
			}
			if (pToolScene->iFocusAnimFile == 2)
			{
				int Anim_idx = SendMessage(hList_AnimFile_Name2, LB_GETCURSEL, 0, 0);
				int Frame_idx = SendMessage(hList_Frame_Info2, LB_GETCURSEL, 0, 0);
				wstring AnimFile2 = pToolScene->GetAnimFile2().at(Anim_idx);
				CAnimation* pAnimation = pAnimator->FindAnimation(AnimFile2);
				AnimFile2.insert(0, L"animation\\");
				AnimFile2.append(L".anim");
				pAnimation->Save(AnimFile2);
			}
			//GetAnimator()->FindAnimation(L"PLAYER_SHOOT_UPPER_PART_LEFT")->Save(L"animation\\PLAYER_SHOOT_UPPER_PART_LEFT.anim");
			
			return TRUE;
		}
		case IDC_BUTTON_Play:
			pToolScene->GetTestAnim()->GetAnimator()->StopAnimationL(false);
			pToolScene->GetTestAnim()->GetAnimator()->StopAnimationU(false);
			return TRUE;

		case IDC_BUTTON_STOP:
			pToolScene->GetTestAnim()->GetAnimator()->StopAnimationL(true);
			pToolScene->GetTestAnim()->GetAnimator()->StopAnimationU(true);
			return TRUE;

		case IDC_BUTTON_Clear:
			if(pToolScene->GetTestAnim()->GetClear())
				pToolScene->GetTestAnim()->SetClear(false);
			else
				pToolScene->GetTestAnim()->SetClear(true);
			return TRUE;

		case IDC_BUTTON_Quit:
			DestroyWindow(hDlg);
			return TRUE;

		case IDC_LIST_AnimFile_Name1:
			switch (HIWORD(wParam))
			{
			case LBN_DBLCLK:
			{
				pToolScene->iFocusAnimFile = 1;
				SendMessage(hList_Frame_Info1, LB_RESETCONTENT, 0, 0);
				int index = SendMessage(hList_AnimFile_Name1, LB_GETCURSEL, 0, 0);
				wstring AnimFile1 = pToolScene->GetAnimFile1().at(index);
				pToolScene->GetTestAnim()->SetCurAnimFile1(AnimFile1);
				int iMaxFrame = pToolScene->GetTestAnim()->GetAnimator()->FindAnimation(AnimFile1)->GetMaxFrame();
				for (int i = 0; i < iMaxFrame; ++i)
				{
					wstring str = std::to_wstring(i);
					SendMessage(hList_Frame_Info1, LB_ADDSTRING, 0, (LPARAM)str.c_str());
				}
				break;
			}
			}
			break;
			
		case IDC_LIST_AnimFile_Name2:
			switch (HIWORD(wParam))
			{
			case LBN_DBLCLK:
			{
				pToolScene->iFocusAnimFile = 2;
				SendMessage(hList_Frame_Info2, LB_RESETCONTENT, 0, 0);
				int index = SendMessage(hList_AnimFile_Name2, LB_GETCURSEL, 0, 0);
				wstring AnimFile2 = pToolScene->GetAnimFile2().at(index);
				pToolScene->GetTestAnim()->SetCurAnimFile2(AnimFile2);
				int iMaxFrame = pToolScene->GetTestAnim()->GetAnimator()->FindAnimation(AnimFile2)->GetMaxFrame();
				for (int i = 0; i < iMaxFrame; ++i)
				{
					wstring str = std::to_wstring(i);
					SendMessage(hList_Frame_Info2, LB_ADDSTRING, 0, (LPARAM)str.c_str());
				}
				break;
			}
			}
			break;

		case IDC_LIST_Frame_Info1:
			switch (HIWORD(wParam))
			{
			case LBN_DBLCLK:
			{
				int Anim_idx = SendMessage(hList_AnimFile_Name1, LB_GETCURSEL, 0, 0);
				int Frame_idx = SendMessage(hList_Frame_Info1, LB_GETCURSEL, 0, 0);
				wstring AnimFile1 = pToolScene->GetAnimFile1().at(Anim_idx);
				tAnimFrm& tAnimFrm = pAnimator->FindAnimation(AnimFile1)->GetFrame(Frame_idx);
				pAnimator->FindAnimation(AnimFile1)->SetStop(true);
				pAnimator->FindAnimation(AnimFile1)->SetFrame(Frame_idx);
				
				wstring str = to_wstring((int)tAnimFrm.vLT.x);
				SendMessage(hEdit_StartX, WM_SETTEXT, (WPARAM)128, (LPARAM)str.c_str());
				str = to_wstring((int)tAnimFrm.vLT.y);
				SendMessage(hEdit_StartY, WM_SETTEXT, (WPARAM)128, (LPARAM)str.c_str());
				str = to_wstring((int)tAnimFrm.vSlice.x);
				SendMessage(hEdit_EndX, WM_SETTEXT, (WPARAM)128, (LPARAM)str.c_str());
				str = to_wstring((int)tAnimFrm.vSlice.y);
				SendMessage(hEdit_EndY, WM_SETTEXT, (WPARAM)128, (LPARAM)str.c_str());
				str = to_wstring((int)tAnimFrm.vOffset.x);
				SendMessage(hEdit_OffsetX, WM_SETTEXT, (WPARAM)128, (LPARAM)str.c_str());
				str = to_wstring((int)tAnimFrm.vOffset.y);
				SendMessage(hEdit_OffsetY, WM_SETTEXT, (WPARAM)128, (LPARAM)str.c_str());
				str = to_wstring(tAnimFrm.fDuration);
				SendMessage(hEdit_Duration, WM_SETTEXT, (WPARAM)128, (LPARAM)str.c_str());
				break;
			}
			}
			break;
			
		case IDC_LIST_Frame_Info2:
			switch (HIWORD(wParam))
			{
			case LBN_DBLCLK:
			{
				int Anim_idx = SendMessage(hList_AnimFile_Name2, LB_GETCURSEL, 0, 0);
				int Frame_idx = SendMessage(hList_Frame_Info2, LB_GETCURSEL, 0, 0);
				wstring AnimFile2 = pToolScene->GetAnimFile2().at(Anim_idx);
				tAnimFrm& tAnimFrm = pAnimator->FindAnimation(AnimFile2)->GetFrame(Frame_idx);
				pAnimator->FindAnimation(AnimFile2)->SetStop(true);
				pAnimator->FindAnimation(AnimFile2)->SetFrame(Frame_idx);
				
				wstring str = to_wstring((int)tAnimFrm.vLT.x);
				SendMessage(hEdit_StartX, WM_SETTEXT, (WPARAM)128, (LPARAM)str.c_str());
				str = to_wstring((int)tAnimFrm.vLT.y);
				SendMessage(hEdit_StartY, WM_SETTEXT, (WPARAM)128, (LPARAM)str.c_str());
				str = to_wstring((int)tAnimFrm.vSlice.x);
				SendMessage(hEdit_EndX, WM_SETTEXT, (WPARAM)128, (LPARAM)str.c_str());
				str = to_wstring((int)tAnimFrm.vSlice.y);
				SendMessage(hEdit_EndY, WM_SETTEXT, (WPARAM)128, (LPARAM)str.c_str());
				str = to_wstring((int)tAnimFrm.vOffset.x);
				SendMessage(hEdit_OffsetX, WM_SETTEXT, (WPARAM)128, (LPARAM)str.c_str());
				str = to_wstring((int)tAnimFrm.vOffset.y);
				SendMessage(hEdit_OffsetY, WM_SETTEXT, (WPARAM)128, (LPARAM)str.c_str());
				str = to_wstring(tAnimFrm.fDuration);
				SendMessage(hEdit_Duration, WM_SETTEXT, (WPARAM)128, (LPARAM)str.c_str());
				break;
			}
			}
			break;

		case IDC_EDIT_StartX:
			switch (HIWORD(wParam)) 
			{
			case EN_CHANGE:
			{
				wchar_t str[128];
				GetWindowText(hEdit_StartX, str, 128);
				int iStartX = stoi(str);
				int Anim_idx;
				int Frame_idx;
				if (pToolScene->iFocusAnimFile == 1)
				{
					Anim_idx = SendMessage(hList_AnimFile_Name1, LB_GETCURSEL, 0, 0);
					Frame_idx = SendMessage(hList_Frame_Info1, LB_GETCURSEL, 0, 0);
					wstring AnimFile1 = pToolScene->GetAnimFile1().at(Anim_idx);
					tAnimFrm& tAnimFrm = pAnimator->FindAnimation(AnimFile1)->GetFrame(Frame_idx);
					tAnimFrm.vLT.x = iStartX;
					pAnimator->FindAnimation(AnimFile1)->SetStop(true);
				}
				else
				{
					Anim_idx = SendMessage(hList_AnimFile_Name2, LB_GETCURSEL, 0, 0);
					Frame_idx = SendMessage(hList_Frame_Info2, LB_GETCURSEL, 0, 0);
					wstring AnimFile2 = pToolScene->GetAnimFile2().at(Anim_idx);
					tAnimFrm& tAnimFrm = pAnimator->FindAnimation(AnimFile2)->GetFrame(Frame_idx);
					tAnimFrm.vLT.x = iStartX;
					pAnimator->FindAnimation(AnimFile2)->SetStop(true);
				}
				

				break;
			}
			}
			break;

		case IDC_EDIT_StartY:
			switch (HIWORD(wParam))
			{
			case EN_CHANGE:
			{
				wchar_t str[128];
				GetWindowText(hEdit_StartY, str, 128);
				int iStartY = stoi(str);
				int Anim_idx;
				int Frame_idx;
				if (pToolScene->iFocusAnimFile == 1)
				{
					Anim_idx = SendMessage(hList_AnimFile_Name1, LB_GETCURSEL, 0, 0);
					Frame_idx = SendMessage(hList_Frame_Info1, LB_GETCURSEL, 0, 0);
					wstring AnimFile1 = pToolScene->GetAnimFile1().at(Anim_idx);
					tAnimFrm& tAnimFrm = pAnimator->FindAnimation(AnimFile1)->GetFrame(Frame_idx);
					tAnimFrm.vLT.y = iStartY;
					pAnimator->FindAnimation(AnimFile1)->SetStop(true);
				}
				else
				{
					Anim_idx = SendMessage(hList_AnimFile_Name2, LB_GETCURSEL, 0, 0);
					Frame_idx = SendMessage(hList_Frame_Info2, LB_GETCURSEL, 0, 0);
					wstring AnimFile2 = pToolScene->GetAnimFile2().at(Anim_idx);
					tAnimFrm& tAnimFrm = pAnimator->FindAnimation(AnimFile2)->GetFrame(Frame_idx);
					tAnimFrm.vLT.y = iStartY;
					pAnimator->FindAnimation(AnimFile2)->SetStop(true);
				}

				break;
			}
			}
			break;
		case IDC_EDIT_EndX:
			switch (HIWORD(wParam))
			{
			case EN_CHANGE:
			{
				wchar_t str[128];
				GetWindowText(hEdit_EndX, str, 128);
				int iEndX = stoi(str);
				int Anim_idx;
				int Frame_idx;
				if (pToolScene->iFocusAnimFile == 1)
				{
					Anim_idx = SendMessage(hList_AnimFile_Name1, LB_GETCURSEL, 0, 0);
					Frame_idx = SendMessage(hList_Frame_Info1, LB_GETCURSEL, 0, 0);
					wstring AnimFile1 = pToolScene->GetAnimFile1().at(Anim_idx);
					tAnimFrm& tAnimFrm = pAnimator->FindAnimation(AnimFile1)->GetFrame(Frame_idx);
					tAnimFrm.vSlice.x = iEndX;
					pAnimator->FindAnimation(AnimFile1)->SetStop(true);
				}
				else
				{
					Anim_idx = SendMessage(hList_AnimFile_Name2, LB_GETCURSEL, 0, 0);
					Frame_idx = SendMessage(hList_Frame_Info2, LB_GETCURSEL, 0, 0);
					wstring AnimFile2 = pToolScene->GetAnimFile2().at(Anim_idx);
					tAnimFrm& tAnimFrm = pAnimator->FindAnimation(AnimFile2)->GetFrame(Frame_idx);
					tAnimFrm.vSlice.x = iEndX;
					pAnimator->FindAnimation(AnimFile2)->SetStop(true);
				}


				break;
			}
			}
			break;
		case IDC_EDIT_EndY:
			switch (HIWORD(wParam))
			{
			case EN_CHANGE:
			{
				wchar_t str[128];
				GetWindowText(hEdit_EndY, str, 128);
				int iEndY = stoi(str);
				int Anim_idx;
				int Frame_idx;
				if (pToolScene->iFocusAnimFile == 1)
				{
					Anim_idx = SendMessage(hList_AnimFile_Name1, LB_GETCURSEL, 0, 0);
					Frame_idx = SendMessage(hList_Frame_Info1, LB_GETCURSEL, 0, 0);
					wstring AnimFile1 = pToolScene->GetAnimFile1().at(Anim_idx);
					tAnimFrm& tAnimFrm = pAnimator->FindAnimation(AnimFile1)->GetFrame(Frame_idx);
					tAnimFrm.vSlice.y = iEndY;
					pAnimator->FindAnimation(AnimFile1)->SetStop(true);
				}
				else
				{
					Anim_idx = SendMessage(hList_AnimFile_Name2, LB_GETCURSEL, 0, 0);
					Frame_idx = SendMessage(hList_Frame_Info2, LB_GETCURSEL, 0, 0);
					wstring AnimFile2 = pToolScene->GetAnimFile2().at(Anim_idx);
					tAnimFrm& tAnimFrm = pAnimator->FindAnimation(AnimFile2)->GetFrame(Frame_idx);
					tAnimFrm.vSlice.y = iEndY;
					pAnimator->FindAnimation(AnimFile2)->SetStop(true);
				}


				break;
			}
			}
			break;
		case IDC_EDIT_OffsetX:
			switch (HIWORD(wParam))
			{
			case EN_CHANGE:
			{
				wchar_t str[128];
				GetWindowText(hEdit_OffsetX, str, 128);
				int iOffsetX = stoi(str);
				int Anim_idx;
				int Frame_idx;
				if (pToolScene->iFocusAnimFile == 1)
				{
					Anim_idx = SendMessage(hList_AnimFile_Name1, LB_GETCURSEL, 0, 0);
					Frame_idx = SendMessage(hList_Frame_Info1, LB_GETCURSEL, 0, 0);
					wstring AnimFile1 = pToolScene->GetAnimFile1().at(Anim_idx);
					tAnimFrm& tAnimFrm = pAnimator->FindAnimation(AnimFile1)->GetFrame(Frame_idx);
					tAnimFrm.vOffset.x = iOffsetX;
					pAnimator->FindAnimation(AnimFile1)->SetStop(true);
				}
				else
				{
					Anim_idx = SendMessage(hList_AnimFile_Name2, LB_GETCURSEL, 0, 0);
					Frame_idx = SendMessage(hList_Frame_Info2, LB_GETCURSEL, 0, 0);
					wstring AnimFile2 = pToolScene->GetAnimFile2().at(Anim_idx);
					tAnimFrm& tAnimFrm = pAnimator->FindAnimation(AnimFile2)->GetFrame(Frame_idx);
					tAnimFrm.vOffset.x = iOffsetX;
					pAnimator->FindAnimation(AnimFile2)->SetStop(true);
				}


				break;
			}
			}
			break;
		case IDC_EDIT_OffsetY:
			switch (HIWORD(wParam))
			{
			case EN_CHANGE:
			{
				wchar_t str[128];
				GetWindowText(hEdit_OffsetY, str, 128);
				int iOffsetY = stoi(str);
				int Anim_idx;
				int Frame_idx;
				if (pToolScene->iFocusAnimFile == 1)
				{
					Anim_idx = SendMessage(hList_AnimFile_Name1, LB_GETCURSEL, 0, 0);
					Frame_idx = SendMessage(hList_Frame_Info1, LB_GETCURSEL, 0, 0);
					wstring AnimFile1 = pToolScene->GetAnimFile1().at(Anim_idx);
					tAnimFrm& tAnimFrm = pAnimator->FindAnimation(AnimFile1)->GetFrame(Frame_idx);
					tAnimFrm.vOffset.y = iOffsetY;
					pAnimator->FindAnimation(AnimFile1)->SetStop(true);
				}
				else
				{
					Anim_idx = SendMessage(hList_AnimFile_Name2, LB_GETCURSEL, 0, 0);
					Frame_idx = SendMessage(hList_Frame_Info2, LB_GETCURSEL, 0, 0);
					wstring AnimFile2 = pToolScene->GetAnimFile2().at(Anim_idx);
					tAnimFrm& tAnimFrm = pAnimator->FindAnimation(AnimFile2)->GetFrame(Frame_idx);
					tAnimFrm.vOffset.y = iOffsetY;
					pAnimator->FindAnimation(AnimFile2)->SetStop(true);
				}


				break;
			}
			}
			break;
		case IDC_EDIT_Duration:
			switch (HIWORD(wParam))
			{
			case EN_CHANGE:
			{
				wchar_t str[128];
				GetWindowText(hEdit_Duration, str, 128);
				float fDuration = stod(str);
				int Anim_idx;
				int Frame_idx;
				if (pToolScene->iFocusAnimFile == 1)
				{
					Anim_idx = SendMessage(hList_AnimFile_Name1, LB_GETCURSEL, 0, 0);
					Frame_idx = SendMessage(hList_Frame_Info1, LB_GETCURSEL, 0, 0);
					wstring AnimFile1 = pToolScene->GetAnimFile1().at(Anim_idx);
					tAnimFrm& tAnimFrm = pAnimator->FindAnimation(AnimFile1)->GetFrame(Frame_idx);
					tAnimFrm.fDuration = fDuration;
					pAnimator->FindAnimation(AnimFile1)->SetStop(true);
				}
				else
				{
					Anim_idx = SendMessage(hList_AnimFile_Name2, LB_GETCURSEL, 0, 0);
					Frame_idx = SendMessage(hList_Frame_Info2, LB_GETCURSEL, 0, 0);
					wstring AnimFile2 = pToolScene->GetAnimFile2().at(Anim_idx);
					tAnimFrm& tAnimFrm = pAnimator->FindAnimation(AnimFile2)->GetFrame(Frame_idx);
					tAnimFrm.fDuration = fDuration;
					pAnimator->FindAnimation(AnimFile2)->SetStop(true);
				}


				break;
			}
			}
			break;
		}
		break;
	}
	return FALSE;
}