#pragma once
#include "CAttackState.h"
class CBubblefire :
    public CState
{
private:


public:
    virtual void update();
    virtual void Enter();
    virtual void Exit();

public:
    CBubblefire();
    ~CBubblefire();
};

