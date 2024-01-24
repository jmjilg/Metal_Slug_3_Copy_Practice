#pragma once
#include "CObject.h"


class CTexture;
class CPlayer;

enum MISSILE_DIR
{
    NONE = 0,
    RIGHT,           // 1 도
    DEGREES_22,     // 22.5
    DEGREES_55,     // 55
    DEGREES_77,     // 77.5
    DOWN,           // 90도
    DEGREES_112,    // 112.5
    DEGREES_135, 
    DEGREES_157,    // 157.5
    LEFT,          // 180 도
    DEGREES_202,    // 202.5
    DEGREES_225, 
    DEGREES_247,    // 247.5
    UP,             // 270도
    DEGREES_292,    // 292.5
    DEGREES_315,    // 314
    DEGREES_337,    // 337.5
};

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

    MISSILE_DIR m_eDir; // 미사일 방향을 enum화 한거

    int         m_xoriginDest;
    int         m_yoriginDest;
    int         m_wDest;
    int         m_hDest;
    int         m_xoriginSrc;
    int         m_yoriginSrc;
    int         m_wSrc;
    int         m_hSrc;


public:
    void SetDir(MISSILE_DIR _eDir);
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
    void SetRenderInfo(int ixoriginDest, int iyoriginDest, int iwDest, int ihDest, int ixoriginSrc, int iyoriginSrc, int iwSrc, int ihSrc)
	{
        m_xoriginDest = ixoriginDest;
        m_yoriginDest = iyoriginDest;
		m_wDest = iwDest;
		m_hDest = ihDest;
		m_xoriginSrc = ixoriginSrc;
		m_yoriginSrc = iyoriginSrc;
		m_wSrc = iwSrc;
		m_hSrc = ihSrc;
    }
    MISSILE_DIR GetDir() { return m_eDir; }
public:
    virtual void update();
    virtual void render(HDC _dc);

public:
    virtual void OnCollisionEnter(CCollider* _pOther);

    CLONE(CMissile);
public:
    CMissile();
    ~CMissile();

    friend CPlayer;
};

