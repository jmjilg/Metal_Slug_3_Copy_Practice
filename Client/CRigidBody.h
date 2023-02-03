#pragma once

class CObject;

class CRigidBody
{
private:
	CObject*	m_pOwner;

	Vec2		m_vForce;			// ũ��, ����
	Vec2		m_vAccel;			// ���ӵ�
	Vec2		m_vAccelA;			// �߰� ���ӵ�
	Vec2		m_vVelocity;		// �ӵ�(�ӷ�(ũ��), ���� �� �� ������ ����)
	Vec2		m_vMaxVelocity;		// �ִ� �ӵ�

	float		m_fMass;			// ����
	float		m_fFricCoeff;		// ���� ���


	// F = M * A;
	// V += A * DT

public:
	void finalupdate();

public:
	void AddForce(Vec2 _vf) { m_vForce += _vf; }
	void SetMass(float _fMass) { m_fMass = _fMass; }
	float GetMass() { return m_fMass; }
	float GetSpeed() { return m_vVelocity.Length(); }
	Vec2 GetVelocity() { return m_vVelocity; }

	void SetVelocity(Vec2 _v) { m_vVelocity = _v; }
	void AddVelocity(Vec2 _v) { m_vVelocity += _v; }
	void SetMaxVelocity(Vec2 _v) { m_vMaxVelocity = _v; }
	void SetAccelAlpha(Vec2 _vAccel) { m_vAccelA = _vAccel; }


private:
	void Move();

public:
	CRigidBody();
	~CRigidBody();

	friend class CObject;
};
