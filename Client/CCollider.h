#pragma once

class CObject;

class CCollider
{
protected:
	static UINT g_iNextID;

	CObject*	 m_pOwner;		// collider 를 소유하고 있는 오브젝트
	Vec2		 m_vOffsetPos;	// 오브젝트로 부터 상대적인 위치
	Vec2		 m_vFinalPos;	// finalupdate 에서 매 프레임마다 계산
	Vec2		 m_vScale;		// 충돌체의 크기

	UINT		 m_iID;			// 충돌체 고유한 ID 값
	int			 m_iCol;

	bool		 m_bActive;		// 충돌체 활성화 여부
	bool		 m_bIsRay;		// 직선 충돌체인지 여부
	bool		 m_bDead;		// 충돌체 판정을 할 것인가 여부. 몬스터가 죽었을때, 죽는 애니메이션이 재생될때는 충돌판정 안하는 용도로 사용
	
	vector<Vec2> m_vecRay;		// 두 점을 기준으로하는 여러가지 직선들
	Vec2		 m_H;			// 직선 충돌체에서 플레이어와 가장 가까운 점
	bool		 m_bObstacle;   // 장애물에 대한 충돌체인지 여부

	bool		 m_bRender;		// 렌더링 할것인가 여부
	
	 
public:
	void SetOffsetPos(Vec2 _vPos) { m_vOffsetPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }
	void SetIsRay(bool _b) { m_bIsRay = _b; }
	void SetH(Vec2 _v) { m_H = _v; }
	void SetDead(bool _b) { m_bDead = _b; }
	void SetObstacle(bool _b) { m_bObstacle = _b; }
	void SetRender(bool _b) { m_bRender = _b; }

	Vec2 GetOffsetPos() { return m_vOffsetPos; }
	Vec2 GetScale() { return m_vScale; }
	bool GetIsRay() { return m_bIsRay; }
	Vec2 GetH() { return m_H; }
	bool GetDead() { return m_bDead; }
	bool GetRender() { return m_bRender; }

	Vec2 GetFinalPos() { return m_vFinalPos; };
	CObject* GetObj() { return m_pOwner; }
	vector<Vec2>& GetVecRay() { return m_vecRay; }

	UINT GetID() { return m_iID; }

public:
	void finalupdate();
	void render(HDC _dc);

public:
	void OnCollision(CCollider* _pOther); // 충돌 중인 경우 호출되는 함수
	void OnCollisionEnter(CCollider* _pOther); // 충돌 진입 시
	void OnCollisionExit(CCollider* _pOther); // 충돌 해제 시


	CCollider& operator = (CCollider& _origin) = delete;

public:
	CCollider();
	CCollider(const CCollider& _origin);
	~CCollider();


	friend class CObject;	
};

