#pragma once

class CCollider;
class CRayCollider;




union COLLIDER_ID
{
	struct {
		UINT Left_id;
		UINT Right_id;
	};
	ULONGLONG ID;
};

class CCollisionMgr
{
	SINGLE(CCollisionMgr)
private:
	map<ULONGLONG, bool> m_mapColInfo;						// 충돌체 간의 이전 프레임 충돌 정보
	UINT				m_arrCheck[(UINT)GROUP_TYPE::END];	// 그룹간의 충돌 체크 매트릭스


	bool IsUnderRay;	// 플레이어 y위치가 선 위쪽에 있엇냐 아래쪽에 있었냐 판정

public:
	void update();
	void CheckGroup(GROUP_TYPE eLeft, GROUP_TYPE _eRight);
	void Reset(){ memset(m_arrCheck, 0, sizeof(UINT) * (UINT)GROUP_TYPE::END); }

private:
	void CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	bool IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol);
	bool IsRayCollision(CCollider* _pLeftCol, CCollider* _pRightCol);


};

