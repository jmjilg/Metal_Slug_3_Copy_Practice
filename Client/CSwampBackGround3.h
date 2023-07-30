#pragma once
#include "CObject.h"
class CSwampBackGround3 :
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
    CLONE(CSwampBackGround3);

public:
    CSwampBackGround3();
    ~CSwampBackGround3();
};

