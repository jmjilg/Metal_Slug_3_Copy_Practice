#pragma once
#include "CObject.h"
class CR724 :
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
    CLONE(CR724);

public:
    CR724();
    ~CR724();
};

