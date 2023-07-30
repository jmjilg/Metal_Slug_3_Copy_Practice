#pragma once
#include "CObject.h"
class CBeachBackGround1 :
    public CObject
{
private:
    CTexture* m_pTexture;
    Vec2 m_vFinalPos;

private:
    virtual void start();
    virtual void update();
    virtual void render(HDC _dc);

public:
    CLONE(CBeachBackGround1);

public:
    CBeachBackGround1();
    ~CBeachBackGround1();
};

