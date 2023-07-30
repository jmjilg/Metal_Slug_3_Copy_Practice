#pragma once
#include "CObject.h"
class CSwampBackGround2 :
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
    CLONE(CSwampBackGround2);

public:
    CSwampBackGround2();
    ~CSwampBackGround2();
};

