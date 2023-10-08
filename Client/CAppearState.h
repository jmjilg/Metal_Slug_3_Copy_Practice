#pragma once
#include "CState.h"
class CAppearState :
    public CState
{
public:
    virtual void update();
    virtual void Enter();
    virtual void Exit();

public:
    CAppearState();
    ~CAppearState();
};

