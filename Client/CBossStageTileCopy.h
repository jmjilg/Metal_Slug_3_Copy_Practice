#pragma once
#include "CObject.h"
class CBossStageTileCopy :
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
    CLONE(CBossStageTileCopy);

public:
    CBossStageTileCopy();
    ~CBossStageTileCopy();

    virtual void OnCollisionEnter(CCollider* _pOther);
    virtual void OnCollision(CCollider* _pOther);
    virtual void OnCollisionExit(CCollider* _pOther);

public:
    void CreateRayGround(); // 타일에 직선 충돌체를 생성해주는 함수
};

