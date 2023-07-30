#pragma once
#include "CMonster.h"

class CLocust :
    public CMonster
{
private:
    Vec2 m_vNextPos;    // �Ŵ� �޶ѱⰡ ������ �ϴ� ��ġ

private:
    virtual void update_animation();

public:
    Vec2 GetNextPos() { return m_vNextPos; }
    void SetNextPos(Vec2 _v) { m_vNextPos = _v; }

    CLocust();
    ~CLocust();
};

