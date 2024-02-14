#pragma once
#include "CObject.h"

class CTexture;
class CPlayer;

class CGrenade :
    public CObject
{
protected:
    CTexture*   m_pTex;

    float       m_fTheta; // �̵� ����
    float       m_fSpeed; // �Ѿ� �̵� �ӵ�
    bool        IsCollision; // �̹� �ѹ� �浹�����Ƿ� �� �浹������ Delete�̺�Ʈ�� �ߺ� ���� ���� 
    bool        m_bHMG;
    int         m_iBounceCount; // ����ź�� �ٴڿ� ƨ�� Ƚ��

public:
    void SetSpeed(float _f) { m_fSpeed = _f; }

public:
    virtual void update();
    virtual void render(HDC _dc);
    virtual void OnCollisionEnter(CCollider* _pOther);

private:
    void update_animation();

public:
    CGrenade();
    ~CGrenade();

    CLONE(CGrenade);

    friend CPlayer;
};

