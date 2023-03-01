#pragma once
#include "CObject.h"


class CTexture;

class CMissile :
    public CObject
{
private:
    float       m_fTheta; // 이동 방향

    Vec2        m_vDir;
    CTexture*   m_pTex;


public:
    void SetDir(float _fTheta) { m_fTheta = _fTheta; }
    void SetDir(Vec2 _vDir)
    {
        if (0 != _vDir.y) // 핸드건을 착용하고 위를 보거나 아래를 볼 경우 미사일의 방향을 대각선이 아닌 일직선으로 해야하므로. 이게 맞는지는 모르겠음
            _vDir.x = 0;
        m_vDir = _vDir;
        m_vDir.Normalize();
    }

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

