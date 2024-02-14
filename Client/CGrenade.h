#pragma once
#include "CObject.h"

class CTexture;
class CPlayer;

class CGrenade :
    public CObject
{
protected:
    CTexture*   m_pTex;

    float       m_fTheta; // 이동 방향
    float       m_fSpeed; // 총알 이동 속도
    bool        IsCollision; // 이미 한번 충돌했으므로 또 충돌했을때 Delete이벤트의 중복 실행 방지 
    bool        m_bHMG;
    int         m_iBounceCount; // 슈류탄이 바닥에 튕긴 횟수

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

