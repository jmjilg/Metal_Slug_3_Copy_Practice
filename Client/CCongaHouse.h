#pragma once
#include "CObject.h"


class CCongaHouse :
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
    CLONE(CCongaHouse);

public:
    virtual void OnCollisionEnter(CCollider* _pOther);
    //virtual void OnCollision(CCollider* _pOther);
    //virtual void OnCollisionExit(CCollider* _pOther);


public:
    CCongaHouse();
    ~CCongaHouse();
};

