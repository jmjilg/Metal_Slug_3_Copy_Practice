#pragma once
#include "CObject.h"



enum class PLAYER_STATE
{
    IDLE,
    WALK,
    ATTACK,
    JUMP,
    SHOOT,
    SIT_DOWN,
    STAND_UP,
    DEAD,
};



enum class PLAYER_ATTACK
{
    NORMAL_SHOOT_LEFT,
    NORMAL_SHOOT_RIGHT,
    NORMAL_SHOOT_UP,
    MELEE_ATTACK_LEFT,
    MELEE_ATTACK_RIGHT,
    GRENADE_THROW_LEFT,
    GRENADE_THROW_RIGHT,
    SIT_DOWN_NORMAL_SHOOT_LEFT,
    SIT_DOWN_NORMAL_SHOOT_RIGHT,
    SIT_DOWN_NORMAL_SHOOT_UP,
    SIT_DOWN_MELEE_ATTACK_LEFT,
    SIT_DOWN_MELEE_ATTACK_RIGHT,
    SIT_DOWN_GRENADE_THROW_LEFT,
    SIT_DOWN_GRENADE_THROW_RIGHT,
    SKILL_ATT_1,
    // ....
};

class CTexture;

class CPlayer :
    public CObject
{
private:
    vector<CObject*>    m_vecColObj;

    PLAYER_STATE        m_eCurStateUpper;
    PLAYER_STATE        m_eMoveState;
    PLAYER_STATE        m_eAttackState;
    PLAYER_STATE        m_eCurStateLower;
    PLAYER_STATE        m_ePrevStateUpper;
    PLAYER_STATE        m_ePrevStateLower;
    int                 m_iDir;
    int                 m_iPrevDir;
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

public:
    CPlayer();
    //CPlayer(const CPlayer& _origin)
    //    : CObject(_origin)
    //    , m_pTex(_origin.m_pTex)
    //{} 컴파일러가 자동으로 이렇게 해줌

    ~CPlayer();
};

