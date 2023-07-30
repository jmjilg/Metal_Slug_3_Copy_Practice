#pragma once
#include "global.h"

#include "CCamera.h"

class CCollider;
class CAnimator;
class CRigidBody;
class CGravity;
class AI;
class CCameraBox;
class CRayGround;

class CObject
{
private:
	wstring		m_strName;

	Vec2		m_vPos;
	Vec2		m_vScale;

	// Component
	CCollider*	m_pCollider;
	CAnimator*	m_pAnimator;
	CRigidBody* m_pRigidBody;
	CGravity*	m_pGravity;


	
	bool		m_bAlive;
	bool		m_bClear;
	CObject*	m_pObstacle;
	CCameraBox* m_pCameraBox;
	CRayGround* m_pRayGround;

public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }
	void SetClear(bool _bClear) { m_bClear = _bClear; }
	void SetObstacle(CObject* _pObj) { m_pObstacle = _pObj; }
	void SetColliderRender(bool _b) { m_bColliderRender = _b; }
	void SetCameraBox(CCameraBox* _p) { m_pCameraBox = _p; }
	void SetRayGround(CRayGround* _p) { m_pRayGround = _p; }

	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }
	bool GetClear() { return m_bClear; }
	bool GetColliderRender() { return m_bColliderRender; }
	CObject* GetObstacle() { return m_pObstacle; }
	CCameraBox* GetCameraBox() { return m_pCameraBox; }
	CRayGround* GetRayGround() { return m_pRayGround; }



	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }
	CCollider* GetCollider() { return m_pCollider; }
	CAnimator* GetAnimator() { return m_pAnimator; }
	CRigidBody* GetRigidBody() { return m_pRigidBody; }
	CGravity* GetGravity() { return m_pGravity; }

	bool IsDead() { return !m_bAlive; }

	void CreateCollider();
	void CreateAnimator();
	void CreateRigidBody();
	void CreateGravity();

	virtual void OnCollision(CCollider* _pOther) {}
	virtual void OnCollisionEnter(CCollider* _pOther) {}
	virtual void OnCollisionExit(CCollider* _pOther) {}

private:
	void SetDead() { m_bAlive = false; }
	Vec2            m_vOrigPos;		// 포로 오브젝트에게 사용할 멤버 변수. 처음 씬에 배치된 위치가 어딘지 저장

public:
	void SetOrigPos(Vec2 _v) { m_vOrigPos = _v; }
	Vec2 GetOrigPos() { return m_vOrigPos; }

public:
	virtual void start() {}; // Scene 이 시작되기 직전에 호출되는 함수
	virtual void update() = 0;
	virtual void finalupdate();
	virtual void render(HDC _dc);
	void component_render(HDC _dc);


	virtual CObject* Clone() = 0;

public:
	CObject();
	CObject(const CObject& _origin);
	virtual ~CObject();
	
	friend class CEventMgr;

protected:
	bool		m_bStandLine;  // 이 변수가 true여야 직선 충돌체의 충돌판정을 할 수 있음.
	bool		m_bColliderRender;	// 충돌체 렌더링 할건지 여부

public:
	bool GetbStandLine() { return m_bStandLine; }

};

