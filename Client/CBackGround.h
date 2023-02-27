#pragma once
#include "CObject.h"

class CTexture;

class CBackGround :
    public CObject
{
private:
    CTexture* m_pBackground;
    Vec2 m_vFinalPos;
    

private:
    virtual void start();
    virtual void update();
    virtual void render(HDC _dc);

public:
    CLONE(CBackGround);

public:
    CBackGround();
    ~CBackGround();
};

