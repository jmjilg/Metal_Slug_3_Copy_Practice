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
    RESPAWN,

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
    HEAVY_MACHINE_GUN_SCATTERING_UP,
    HEAVY_MACHINE_GUN_SCATTERING_DOWN,

    //

    GRENADE_THROW,

    //

    KNIFE_ATTACK,
    KNIFE_IDLE,
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
    Vec2                m_iDir;
    int                 m_iPrevDir;
    int                 m_iGrenade;
    int                 m_iGrenadeCount;
    int                 m_iLife;
    int                 m_iHeavyMachineGunCount;
    int                 m_iTempFrameUpper;             // m_bFrameLock 과 관련있음
    int                 m_iTempFrameLower;             // m_bFrameLock 과 관련있음
    bool                m_bJump;
    bool                m_bAttacked;                // 플레이어가 몬스터에게 공격을 받았는지 여부
    bool                m_bSetCamera;                // 카메라가 계속 플레이어를 타겟으로 할지 여부
    bool                m_bFrameLockUpper;               // 한 프레임당 한발씩만 미사일을 발사하도록 하는 변수 (기본총은 첫 프레임만 미사일 발사)
    bool                m_bFrameLockLower;               // 앉아서 쏠때 쓸 변수
    bool                m_bMeleeAtt;                    // 공격키를 눌렀을때 근접공격을 할건지의 여부
    Vec2                m_vMissilePrevDir;
    

  //  bool m_btemp = false; // 디버깅용 임시 변수

private:
    LARGE_INTEGER	m_llCurCount;
    LARGE_INTEGER	m_llPrevCount;
    LARGE_INTEGER	m_llFrequency; // 1초당 셀수있는 카운트값

    double			m_dDT; // 프레임 사이의 시간값, 프레임과 프레임 사이의 걸린 시간
    double			m_dAcc;	// 1초 체크를 위한 누적 시간
    UINT			m_iCallCount; // 함수 호출 횟수 체크
    UINT			m_iFPS; // 초당 호출 횟수
    Vec2            m_vMeleeAttRange;

public:
    virtual void update();
    virtual void render(HDC _dc);

public:
    double GetDT() { return m_dDT; }
    float GetfDT() { return (float)m_dDT; }
    bool GetbStandLine() { return m_bStandLine; }
    bool GetbAttacked() { return m_bAttacked; }
    void SetAttacked(bool _b) { m_bAttacked = _b; }
	int GetHeavyMachinGunCount() { return m_iHeavyMachineGunCount; }
	int GetGrenadeCount() { return m_iGrenadeCount; }

private:
    void CreateMissile(int _iMissileDir = 0);
    void CreateGrenade();
    void update_state();
    void update_move();
    void update_animation();
    void update_gravity();
    void update_jumptime();
    void update_UI();
    void SetIsJump(bool _bJump) { m_bJump = _bJump; }
    void SetFrame0(const wstring& _strName1, const wstring& _strName2);
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

    void update_HAND_GUN_SHOOT_UP(stack<PLAYER_STATE>& _stkState);
    void update_HAND_GUN_SHOOT_DOWN(stack<PLAYER_STATE>& _stkState);
    void update_HAND_GUN_SHOOT_SIT_DOWN(stack<PLAYER_STATE>& _stkState);
    void update_HAND_GUN_SHOOT(stack<PLAYER_STATE>& _stkState);

    void update_GRENADE_THROW(stack<PLAYER_STATE>& _stkState);

    void update_HEAVYMACHINE_GUN_SCATTERING_UP(stack<PLAYER_STATE>& _stkState);  // 함수명 리펙토링이 필요해보임
    void update_HEAVYMACHINE_GUN_SCATTERING_DOWN(stack<PLAYER_STATE>& _stkState);
    
    void update_DEAD(stack<PLAYER_STATE>& _stkState);
    void update_RESPAWN(stack<PLAYER_STATE>& _stkState);

    void update_KNIFE_ATTACK(stack<PLAYER_STATE>& _stkState);

    void OneFrameOneShot(int _iMissileDir = 0); // 한 프레임당 한발씩만 미사일을 발사하도록 하는 변수 (기본총은 첫 프레임만 미사일 발사)
private:
    //virtual void OnCollision(CCollider* _pOther);         // 충돌 중인 경우 호출되는 함수
    //virtual void OnCollisionEnter(CCollider* _pOther);     // 충돌 진입 시
    virtual void OnCollisionExit(CCollider* _pOther);     // 충돌 해제 시

public:
    CPlayer();
    //CPlayer(const CPlayer& _origin)
    //    : CObject(_origin)
    //    , m_pTex(_origin.m_pTex)
    //{} 컴파일러가 자동으로 이렇게 해줌

    ~CPlayer();
};

