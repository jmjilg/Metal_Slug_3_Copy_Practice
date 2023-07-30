#pragma once
#include "CMissile.h"
class CHeavyMachineGun :
    public CMissile
{
private:
    int ixOriginSrc;
    int iyOriginSrc;
    int iwSrc;
    int ihSrc;

public:
    CHeavyMachineGun();
    ~CHeavyMachineGun();

    virtual void render(HDC _dc);
};

