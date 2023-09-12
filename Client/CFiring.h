#pragma once
#include "CState.h"
class CFiring :
    public CState
{
public:
    virtual void update();
    virtual void Enter();
    virtual void Exit();

private:
    bool m_bRespawn;              // 리스폰할지 여부
    int m_iRespawnCount;          // 미사일 리스폰한 횟수
    clock_t  lRespawnStart;       // 미사일 리스폰한 시간
    clock_t  lRespawnAcc;         // 미사일 리스폰하고 지난 시간

public:
    CFiring();
    ~CFiring();
};

