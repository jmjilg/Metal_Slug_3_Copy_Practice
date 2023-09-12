#pragma once
#include "CState.h"
class CBounce :
    public CState
{
public:
    virtual void update();
    virtual void Enter();
    virtual void Exit();

public:
    CBounce();
    ~CBounce();
};

