#pragma once
#include "CObject.h"


enum class CAPTIVE_STATE {
    IDLE,
    RELEASE,
    LOOKING_FOR,
    SUPPLY,
    SALUTE,
    RUN,
};

class CCaptive :
    public CObject
{
private:
    CAPTIVE_STATE   m_eCurState;
    CAPTIVE_STATE   m_ePrevState;
    float           m_fSpeed;
    int             m_iDir;
    int             m_iPrevDir;

public:
    float GetSpeed() { return m_fSpeed; }
    void SetSpeed(float _f) { m_fSpeed = _f; }

public:
    void update_state();
    void update_animation();

public:
    virtual void OnCollisionEnter(CCollider* _pOther);
    virtual void OnCollision(CCollider* _pOther);

public:
    virtual void update();
    virtual void render(HDC _dc);


    CLONE(CCaptive);

private:
    void update_IDLE(CAPTIVE_STATE _eState);
    void update_RELEASE(CAPTIVE_STATE _eState);
    void update_LOOKING_FOR(CAPTIVE_STATE _eState);
    void update_SUPPLY(CAPTIVE_STATE _eState);
    void update_SALUTE(CAPTIVE_STATE _eState);
    void update_RUN(CAPTIVE_STATE _eState);
public:
    CCaptive();
    ~CCaptive();

    friend class CMonFactory;
};



