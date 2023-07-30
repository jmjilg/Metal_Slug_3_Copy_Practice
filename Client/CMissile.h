#pragma once
#include "CObject.h"


class CTexture;

class CMissile :
    public CObject
{
protected:
    float       m_fTheta; // �̵� ����

    Vec2        m_vDir;
    CTexture*   m_pTex;
    bool        IsCollision; // �̹� �ѹ� �浹�����Ƿ� �� �浹������ Delete�̺�Ʈ�� �ߺ� ���� ���� 


public:
    void SetDir(float _fTheta) { m_fTheta = _fTheta; }
    void SetDir(Vec2 _vDir)
    {
        if (0 != _vDir.y) // �ڵ���� �����ϰ� ���� ���ų� �Ʒ��� �� ��� �̻����� ������ �밢���� �ƴ� ���������� �ؾ��ϹǷ�. �̰� �´����� �𸣰���
            _vDir.x = 0;
        m_vDir = _vDir;
        m_vDir.Normalize();
    }

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

