#pragma once
#include "CState.h"

class CKidnapping :
    public CState
{

public:
    virtual void update();
    virtual void Enter();
    virtual void Exit();

public:
    CKidnapping();
    ~CKidnapping();
};

