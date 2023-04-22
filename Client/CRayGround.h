#pragma once
#include "CObject.h"
class CRayGround :
    public CObject
{
private:
    virtual void start();
    virtual void update();

public:
    virtual void OnCollisionEnter(CCollider* _pOther);
    virtual void OnCollision(CCollider* _pOther);
    virtual void OnCollisionExit(CCollider* _pOther);

    CLONE(CRayGround);

public:
    CRayGround();
    ~CRayGround();


    bool IsOnRay();
};

