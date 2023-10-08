#pragma once
#include "CObject.h"
class CSupplies :
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
    CLONE(CSupplies);

public:
    CSupplies();
    ~CSupplies();

public:
    void OnCollisionEnter(CCollider* _pOther);
};

