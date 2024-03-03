#pragma once
#include "CObject.h"

class CTexture;
class CPlayer;

class CGrenade :
    public CObject
{
protected:
    CTexture*   m_pTex;

    int         m_iDir; // 이동 방향
    float       m_fSpeed; // 총알 이동 속도
    bool        IsCollision; // 충돌했는지 여부
    bool        m_bHMG;
    int         m_iBounceCount; // 슈류탄이 바닥에 튕긴 횟수

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

