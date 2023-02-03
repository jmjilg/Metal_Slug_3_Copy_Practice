#pragma once
#include "CObject.h"



enum class PLAYER_STATE
{
    IDLE,
    WALK,
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
    HAND_GUN_JUMP,
    HAND_GUN_SHOOT,
    HAND_GUN_SIT_DOWN,
    HAND_GUN_SIT_DOWN_WALK,
    HAND_GUN_LOOK_UP,
    HAND_GUN_LOOK_DOWN,

    //

    HEAVY_MACHINE_GUN_IDLE,
    HEAVY_MACHINE_GUN_WALK,
    HEAVY_MACHINE_GUN_JUMP,
    HEAVY_MACHINE_GUN_SHOOT,
    HEAVY_MACHINE_GUN_SIT_DOWN,
    HEAVY_MACHINE_GUN_SIT_DOWN_WALK,
    HEAVY_MACHINE_GUN_LOOK_UP,
    HEAVY_MACHINE_GUN_LOOK_DOWN,

    //

    GRENADE_IDLE,
    GRENADE_WALK,
    GRENADE_JUMP,
    GRENADE_SHOOT,
    GRENADE_SIT_DOWN,
    GRENADE_SIT_DOWN_WALK,
    GRENADE_LOOK_UP,
    GRENADE_LOOK_DOWN,

    //

    KNIFE_IDLE,
    KNIFE_WALK,
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

class CTexture;

class CPlayer :
    public CObject
{
private:
    vector<CObject*>    m_vecColObj;

    PLAYER_STATE        m_eCurStateUpper;
    PLAYER_STATE        m_eCurStateLower;
    PLAYER_STATE        m_ePrevStateUpper;
    PLAYER_STATE        m_ePrevStateLower;
    WEAPON              m_eCurWeapon;
    WEAPON              m_ePrevWeapon;
    int                 m_iDir;
    int                 m_iPrevDir;
    int                 m_iGrenade;
    int                 m_iGrenadeCount;
    bool                m_bAttack;

public:
    virtual void update();
    virtual void render(HDC _dc);

private:
    void CreateMissile();
    void update_state();
    void update_move();
    void update_animation();
    void update_gravity();
    bool IsAttack() { return m_bAttack; }
    void SetIsAttack(bool _bAnimLock) { m_bAttack = _bAnimLock; }

    virtual void OnCollisionEnter(CCollider* _pOther);

    CLONE(CPlayer);

private:
    void UpdateIdle();
    void UpdateMoving();
    void UpdateDie();


public:
    CPlayer();
    //CPlayer(const CPlayer& _origin)
    //    : CObject(_origin)
    //    , m_pTex(_origin.m_pTex)
    //{} 컴파일러가 자동으로 이렇게 해줌

    ~CPlayer();
};

