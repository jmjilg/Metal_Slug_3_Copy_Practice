#pragma once
#include "CObject.h"


class CTexture;

class CMissile :
    public CObject
{
protected:
    CTexture*   pHandGunTex;
    CTexture*   pWeaponTex;

    float       m_fTheta; // 이동 방향
    float       m_fSpeed; // 총알 이동 속도

    Vec2        m_vDir;
    CTexture*   m_pTex;
    bool        IsCollision; // 이미 한번 충돌했으므로 또 충돌했을때 Delete이벤트의 중복 실행 방지 
    bool        m_bHMG;


public:
    void SetDir(float _fTheta) { m_fTheta = _fTheta; }
    void SetDir(Vec2 _vDir)
    {
        if (0 != _vDir.y) // 핸드건을 착용하고 위를 보거나 아래를 볼 경우 미사일의 방향을 대각선이 아닌 일직선으로 해야하므로. 이게 맞는지는 모르겠음
            _vDir.x = 0;
        m_vDir = _vDir;
        m_vDir.Normalize();
    }
    void SetSpeed(float _f) { m_fSpeed = _f; }
    void SetHMG(bool _b) { m_bHMG = _b; }
public:
    virtual void update();
    virtual void render(HDC _dc);

public:
    virtual void OnCollisionEnter(CCollider* _pOther);

    CLONE(CMissile);
public:
    CMissile();
    ~CMissile();
};

