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

class CTexture;

class CPlayer :
    public CObject
{
private:
    vector<CObject*>    m_vecColObj;

    PLAYER_STATE        m_eCurStateUpper;
    PLAYER_STATE        m_eCurStateLower;
    PLAYER_STATE        m_ePrevStateUpper;  // 이전 프레임의 상태를 나타냄
    PLAYER_STATE        m_ePrevStateLower;

    stack<PLAYER_STATE> m_stkStateUpper;
    stack<PLAYER_STATE> m_stkStateLower;

    PLAYER_STATE        m_eBefore_The_Change_Upper; // 이전에 어떤 상태에서 바뀌었는가를 나타냄.
    PLAYER_STATE        m_eBefore_The_Change_Lower; // 상태가 변했을 때, 변하기 전의 상태를 기록함
    WEAPON              m_eCurWeapon;
    WEAPON              m_ePrevWeapon;
    int                 m_iDir;
    int                 m_iPrevDir;
    int                 m_iGrenade;
    int                 m_iGrenadeCount;
    bool                m_bJump;

public:
    virtual void update();
    virtual void render(HDC _dc);

private:
    void CreateMissile();
    void update_state();
    void update_move();
    void update_animation();
    void update_gravity();
    void SetIsJump(bool _bJump) { m_bJump = _bJump; }
    bool IsJump() { return m_bJump; }

    virtual void OnCollisionEnter(CCollider* _pOther);

    CLONE(CPlayer);

private:
	void LOWERPART_update();
	void UPPERPART_update();

private:
    void update_NONE(stack<PLAYER_STATE>& _stkState);
    void update_IDLE(stack<PLAYER_STATE>& _stkState);
    void update_JUMP(stack<PLAYER_STATE>& _stkState);
    void update_WALK(stack<PLAYER_STATE>& _stkState);
    void update_WALK_JUMP(stack<PLAYER_STATE>& _stkState);
    void update_SIT_DOWN(stack<PLAYER_STATE>& _stkState);
    void update_SIT_DOWN_WALK(stack<PLAYER_STATE>& _stkState);
    void update_LOOK_DOWN(stack<PLAYER_STATE>& _stkState);
    void update_LOOK_UP(stack<PLAYER_STATE>& _stkState);

    void update_HAND_GUN_SHOOT(stack<PLAYER_STATE>& _stkState);
    void update_HAND_GUN_LOOK_UP(stack<PLAYER_STATE>& _stkState);
    void update_HAND_GUN_LOOK_DOWN(stack<PLAYER_STATE>& _stkState);
    void update_HAND_GUN_SIT_DOWN(stack<PLAYER_STATE>& _stkState);
    
private:
    //virtual void OnCollision(CCollider* _pOther);         // 충돌 중인 경우 호출되는 함수
    //virtual void OnCollisionEnter(CCollider* _pOther);     // 충돌 진입 시
    //virtual void OnCollisionExit(CCollider* _pOther);     // 충돌 해제 시

public:
    CPlayer();
    //CPlayer(const CPlayer& _origin)
    //    : CObject(_origin)
    //    , m_pTex(_origin.m_pTex)
    //{} 컴파일러가 자동으로 이렇게 해줌

    ~CPlayer();
};

