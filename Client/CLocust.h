#pragma once
#include "CMonster.h"

class CLocust :
    public CMonster
{
private:
    Vec2 m_vNextPos;    // 거대 메뚜기가 가려고 하는 위치

private:
    virtual void update_animation();

public:
    Vec2 GetNextPos() { return m_vNextPos; }
    void SetNextPos(Vec2 _v) { m_vNextPos = _v; }

    CLocust();
    ~CLocust();
};

