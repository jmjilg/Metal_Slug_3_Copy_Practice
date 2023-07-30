#pragma once
#include "CObject.h"
class CBrokenShip :
    public CObject
{

private:
    CTexture* m_pTexture;
    Vec2 m_vFinalPos;
    int m_iHP;


private:
    virtual void start();
    virtual void update();
    virtual void render(HDC _dc);

public:
    CLONE(CBrokenShip);

public:
    virtual void OnCollisionEnter(CCollider* _pOther);

public:
    CBrokenShip();
    ~CBrokenShip();
};

