#pragma once

#include "global.h"

#include "CMonFactory.h"

// 전방선언
class CObject;

class CScene
{
private:
	vector<CObject*> m_arrObj[(UINT)GROUP_TYPE::END]; // 오브젝트를 저장 및 관리할 벡터를 그룹 개수만큼 선언
	wstring			 m_strName; // Scene 이름

	UINT			 m_iTileX;	// 타일 가로 개수
	UINT			 m_iTileY;	// 타일 세로 개수

	CObject*		 m_pPlayer; // Player
	CObject*		 m_pMonster;

protected:
	CObject*		 m_pRayGround; // 직선 충돌체
	bool			 m_CongaHouse;
	bool			 m_BrokenShip;	
	bool			 m_Ship;
	bool			 m_bColliderRender;      // 충돌체 렌더링 할건지 여부

public:
	void SetName(const wstring& _strName){m_strName = _strName;}
	const wstring& GetName() { return m_strName; }

	UINT GetTileX() { return m_iTileX; }
	UINT GetTileY() { return m_iTileY; }
	CObject* GetRayGround() { return m_pRayGround; }
	void SetCongaHouse(bool _b) { m_CongaHouse = _b; }
	void SetBrokenShip(bool _b) { m_BrokenShip = _b; }
	void SetShip(bool _b) { m_Ship = _b; }

	CObject* GetPlayer() { return m_pPlayer; }

	virtual void start();
	virtual void update();
	virtual void finalupdate();
	virtual void render(HDC _dc);

	void render_tile(HDC _dc);

	virtual void Enter() = 0; // 해당 Scene 에 진입 시 호출
	virtual void Exit() = 0; // 해당 Scene 을 탈출 시 호출


public:

	void AddObject(CObject* _pObj, GROUP_TYPE _eType)
	{
		m_arrObj[(UINT)_eType].push_back(_pObj);
	}
	void RegisterPlayer(CObject* _pPlayer) { m_pPlayer = _pPlayer; }

	const vector<CObject*>& GetGroupObject(GROUP_TYPE _eType)	{ return m_arrObj[(UINT)_eType];}
	void DeleteGroup(GROUP_TYPE _eTarget);
	void DeleteAll();
	void CreateTile(UINT _iXCount, UINT _iYCount);
	void LoadTile(const wstring& _strRelativePath);

	vector<CObject*>& GetUIGroup() { return m_arrObj[(UINT)GROUP_TYPE::UI]; }

public:
	CScene();
	virtual ~CScene();
};

