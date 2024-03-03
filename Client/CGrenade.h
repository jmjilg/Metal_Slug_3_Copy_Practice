#pragma once
#include "CObject.h"

class CTexture;
class CPlayer;

class CGrenade :
    public CObject
{
protected:
    CTexture*   m_pTex;

    int         m_iDir; // �̵� ����
    float       m_fSpeed; // �Ѿ� �̵� �ӵ�
    bool        IsCollision; // �浹�ߴ��� ����
    bool        m_bHMG;
    int         m_iBounceCount; // ����ź�� �ٴڿ� ƨ�� Ƚ��

public:
    void SetSpeed(float _f) { m_fSpeed = _f; }
    void SetDir(int _i) { m_iDir = _i; }

public:
    virtual void update();
    virtual void render(HDC _dc);
    virtual void OnCollisionEnter(CCollider* _pOther);
    virtual void OnCollision(CCollider* _pOther);
    virtual void OnCollisionExit(CCollider* _pOther);

private:
    void update_animation();

public:
    CGrenade();
    ~CGrenade();

    CLONE(CGrenade);

    friend CPlayer;
};

