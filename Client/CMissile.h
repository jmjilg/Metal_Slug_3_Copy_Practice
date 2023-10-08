#pragma once
#include "CObject.h"


class CTexture;

class CMissile :
    public CObject
{
protected:
    CTexture*   pHandGunTex;
    CTexture*   pWeaponTex;

    float       m_fTheta; // �̵� ����
    float       m_fSpeed; // �Ѿ� �̵� �ӵ�

    Vec2        m_vDir;
    CTexture*   m_pTex;
    bool        IsCollision; // �̹� �ѹ� �浹�����Ƿ� �� �浹������ Delete�̺�Ʈ�� �ߺ� ���� ���� 
    bool        m_bHMG;


public:
    void SetDir(float _fTheta) { m_fTheta = _fTheta; }
    void SetDir(Vec2 _vDir)
    {
        if (0 != _vDir.y) // �ڵ���� �����ϰ� ���� ���ų� �Ʒ��� �� ��� �̻����� ������ �밢���� �ƴ� ���������� �ؾ��ϹǷ�. �̰� �´����� �𸣰���
            _vDir.x = 0;
        m_vDir = _vDir;
        m_vDir.Normalize();
    }
    void SetSpeed(float _f) { m_fSpeed = _f; }
    void SetHMG(bool _b) { m_bHMG = _b; }
public:
    virtual void update();
    virtual void render(HDC _dc);

public:
    virtual void OnCollisionEnter(CCollider* _pOther);

    CLONE(CMissile);
public:
    CMissile();
    ~CMissile();
};

