#pragma once
#include "CObject.h"

class CMonster;

class CEventObject4 :
    public CObject
{
private:
    bool        m_bIsEnterEvent;     // 이벤트가 한번만 작동하도록 하는 변수
    bool        m_bIsHugeHermitRespawn;     // 이벤트가 한번만 작동하도록 하는 변수
    clock_t     m_lEventStart;       // 공격을 시작한 시간
    clock_t     m_lEventAcc;         // 공격을 시작하고 지난 시간

private:
    virtual void start();
    virtual void render(HDC _dc);
    virtual void update();


public:
    virtual void OnCollisionEnter(CCollider* _pOther);

public:
    CEventObject4();
    ~CEventObject4();

    CLONE(CEventObject4);


};

