#pragma once

class CObject;

class CCollider
{
protected:
	static UINT g_iNextID;

	CObject*	 m_pOwner;		// collider �� �����ϰ� �ִ� ������Ʈ
	Vec2		 m_vOffsetPos;	// ������Ʈ�� ���� ������� ��ġ
	Vec2		 m_vFinalPos;	// finalupdate ���� �� �����Ӹ��� ���
	Vec2		 m_vScale;		// �浹ü�� ũ��

	UINT		 m_iID;			// �浹ü ������ ID ��
	int			 m_iCol;

	bool		 m_bActive;		// �浹ü Ȱ��ȭ ����
	bool		 m_bIsRay;		// ���� �浹ü���� ����
	
	vector<Vec2> m_vecRay;		// �� ���� ���������ϴ� �������� ������
	Vec2		 m_H;			// ���� �浹ü���� �÷��̾�� ���� ����� ��
	 
public:
	void SetOffsetPos(Vec2 _vPos) { m_vOffsetPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }
	void SetIsRay(bool _b) { m_bIsRay = _b; }
	void SetH(Vec2 _v) { m_H = _v; }

	Vec2 GetOffsetPos() { return m_vOffsetPos; }
	Vec2 GetScale() { return m_vScale; }
	bool GetIsRay() { return m_bIsRay; }
	Vec2 GetH() { return m_H; }

	Vec2 GetFinalPos() { return m_vFinalPos; }
	CObject* GetObj() { return m_pOwner; }
	vector<Vec2>& GetVecRay() { return m_vecRay; }


	UINT GetID() { return m_iID; }

public:
	void finalupdate();
	void render(HDC _dc);

public:
	void OnCollision(CCollider* _pOther); // �浹 ���� ��� ȣ��Ǵ� �Լ�
	void OnCollisionEnter(CCollider* _pOther); // �浹 ���� ��
	void OnCollisionExit(CCollider* _pOther); // �浹 ���� ��


	CCollider& operator = (CCollider& _origin) = delete;

public:
	CCollider();
	CCollider(const CCollider& _origin);
	~CCollider();


	friend class CObject;	
};

