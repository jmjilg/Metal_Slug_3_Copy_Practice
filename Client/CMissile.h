#pragma once
#include "CObject.h"


class CTexture;
class CPlayer;

enum MISSILE_DIR
{
    NONE = 0,
    RIGHT,           // 1 ��
    DEGREES_22,     // 22.5
    DEGREES_55,     // 55
    DEGREES_77,     // 77.5
    DOWN,           // 90��
    DEGREES_112,    // 112.5
    DEGREES_135, 
    DEGREES_157,    // 157.5
    LEFT,          // 180 ��
    DEGREES_202,    // 202.5
    DEGREES_225, 
    DEGREES_247,    // 247.5
    UP,             // 270��
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

    float       m_fTheta; // �̵� ����
    float       m_fSpeed; // �Ѿ� �̵� �ӵ�

    Vec2        m_vDir;
    CTexture*   m_pTex;
    bool        IsCollision; // �̹� �ѹ� �浹�����Ƿ� �� �浹������ Delete�̺�Ʈ�� �ߺ� ���� ���� 
    bool        m_bHMG;

    MISSILE_DIR m_eDir; // �̻��� ������ enumȭ �Ѱ�

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
        if (0 != _vDir.y) // �ڵ���� �����ϰ� ���� ���ų� �Ʒ��� �� ��� �̻����� ������ �밢���� �ƴ� ���������� �ؾ��ϹǷ�. �̰� �´����� �𸣰���
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

