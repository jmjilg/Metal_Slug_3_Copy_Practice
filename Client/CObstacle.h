#pragma once
#include "CObject.h"
class CObstacle :
    public CObject
{
private:
    virtual void start();
    virtual void update();
    virtual void render(HDC _dc);

public:
    virtual void OnCollisionEnter(CCollider* _pOther);
    virtual void OnCollision(CCollider* _pOther);
    virtual void OnCollisionExit(CCollider* _pOther);

    CLONE(CObstacle);

public:
    CObstacle();
    ~CObstacle();

    friend class CObject;
};

