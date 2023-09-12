#pragma once
#include "CMonster.h"
class CM3_Rocket_Launch_Support_Van :
    public CMonster
{
private:
    virtual void update_animation();


public:
    virtual void OnCollision(CCollider* _pOther);

    CM3_Rocket_Launch_Support_Van();
    ~CM3_Rocket_Launch_Support_Van();
};

