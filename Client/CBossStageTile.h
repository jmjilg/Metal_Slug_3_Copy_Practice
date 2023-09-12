#pragma once
#include "CObject.h"
class CBossStageTile :
    public CObject
{
private:
    CTexture* m_pTexture;
    Vec2 m_vFinalPos;


private:
    virtual void start();
    virtual void update();
    virtual void render(HDC _dc);

private:
    CRayGround* m_pRayGround; 

public:
    CLONE(CBossStageTile);

public:
    CBossStageTile();
    ~CBossStageTile();


    virtual void OnCollisionEnter(CCollider* _pOther);
    virtual void OnCollision(CCollider* _pOther);
    virtual void OnCollisionExit(CCollider* _pOther);
};

