#pragma once
#include "CState.h"

class CFlying :
    public CState
{

public:
    virtual void update();
    virtual void Enter();
    virtual void Exit();

public:
    CFlying();
    ~CFlying();
};

