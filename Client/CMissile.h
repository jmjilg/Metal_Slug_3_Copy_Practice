#pragma once
#include "CObject.h"


enum class PLAYER_STATE
{
    NONE,
    IDLE,
    WALK,
    WALK_JUMP,
    JUMP,
    SHOOT,
    SIT_DOWN,
    SIT_DOWN_WALK,
    LOOK_UP,
    LOOK_DOWN,
    DEAD,

    ///

    HAND_GUN_IDLE,
    HAND_GUN_WALK,
    HAND_GUN_WALK_JUMP,
    HAND_GUN_JUMP,
    HAND_GUN_SHOOT,
    HAND_GUN_SIT_DOWN,
    HAND_GUN_SIT_DOWN_WALK,
    HAND_GUN_LOOK_UP,
    HAND_GUN_LOOK_DOWN,

    //

    HEAVY_MACHINE_GUN_IDLE,
    HEAVY_MACHINE_GUN_WALK,
    HEAVY_MACHINE_GUN_WALK_JUMP,
    HEAVY_MACHINE_GUN_JUMP,
    HEAVY_MACHINE_GUN_SHOOT,
    HEAVY_MACHINE_GUN_SIT_DOWN,
    HEAVY_MACHINE_GUN_SIT_DOWN_WALK,
    HEAVY_MACHINE_GUN_LOOK_UP,
    HEAVY_MACHINE_GUN_LOOK_DOWN,

    //

    GRENADE_IDLE,
    GRENADE_WALK,
    GRENADE_WALK_JUMP,
    GRENADE_JUMP,
    GRENADE_SHOOT,
    GRENADE_SIT_DOWN,
    GRENADE_SIT_DOWN_WALK,
    GRENADE_LOOK_UP,
    GRENADE_LOOK_DOWN,

    //

    KNIFE_IDLE,
    KNIFE_WALK,
    KNIFE_WALK_JUMP,
    KNIFE_JUMP,
    KNIFE_SHOOT,
    KNIFE_SIT_DOWN,
    KNIFE_SIT_DOWN_WALK,
    KNIFE_LOOK_UP,
    KNIFE_LOOK_DOWN,
};

enum class WEAPON
{
    HAND_GUN,
    HEAVY_MACHIN_GUN,
    GRENADE,
};


class CMissile :
    public CObject
{
private:
    float       m_fTheta; // 이동 방향

    Vec2        m_vDir;


public:
    void SetDir(float _fTheta) { m_fTheta = _fTheta; }
    void SetDir(Vec2 _vDir)
    {
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

