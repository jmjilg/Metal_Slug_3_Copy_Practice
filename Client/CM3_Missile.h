#pragma once
#include "CMonster.h"
class CM3_Missile :
    public CMonster
{
private:
    virtual void update();
    virtual void update_animation();

public:
    virtual void OnCollisionEnter(CCollider* _pOther);

};

