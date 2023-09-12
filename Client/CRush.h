#pragma once
#include "CState.h"
class CRush :
    public CState
{
public:
    virtual void update();
    virtual void Enter();
    virtual void Exit();

public:
    CRush();
    ~CRush();
};

