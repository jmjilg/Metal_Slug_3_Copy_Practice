#pragma once
#include "CObject.h"
class CShipDoor :
    public CObject
{

private:
    CTexture* m_pTexture;
    Vec2 m_vFinalPos;
    bool m_IsFinish;


private:
    virtual void start();
    virtual void update();
    virtual void render(HDC _dc);

public:
    CLONE(CShipDoor);

public:
    CShipDoor();
    ~CShipDoor();
};

