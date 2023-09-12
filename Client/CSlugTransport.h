#pragma once
#include "CObject.h"

class CRayGround;

class CSlugTransport :
    public CObject
{

private:
    CTexture*   m_pTexture;
    Vec2        m_vFinalPos;
    float       m_fVelocity;           // SlugTransport 의 이전 업데이트 위치와 현재 위치와의 차이
    bool        m_bContact;
    bool        m_bRespawn;              // 리스폰할지 여부
    int         m_iRespawnCount;          // 플라잉 킬러 리스폰한 횟수
    clock_t     m_lRespawnStart;       // 플라잉 킬러를 스폰한 시간
    clock_t     m_lRespawnAcc;         // 플라잉 킬러를 스폰하고 지난 시간
    bool        m_bRespawnEvent;       // 플라잉 킬러를 리스폰할 시간
    clock_t     m_IBossEventStart;     // 보스 몬스터 이벤트를 시작한 시간
    clock_t     m_IBossEventAcc;       // 보스 몬스터 이벤트를 시작하고 지난 시간
    bool        m_bStop;               // 배를 멈추게 하는 변수
    bool        m_bBossEvent;          // 보스 이벤트가 진행중인지 여부

private:
    CRayGround* m_pRayGround;

private:
    virtual void start();
    virtual void update();
    virtual void render(HDC _dc);

public:
    CLONE(CSlugTransport);

public:
    CSlugTransport();
    ~CSlugTransport();

    virtual void OnCollisionEnter(CCollider* _pOther);
    virtual void OnCollision(CCollider* _pOther);
    virtual void OnCollisionExit(CCollider* _pOther);
};

