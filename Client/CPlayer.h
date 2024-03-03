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
    PLAYER_STATE        m_ePrevStateUpper;  // ���� �������� ���¸� ��Ÿ��
    PLAYER_STATE        m_ePrevStateLower;

    stack<PLAYER_STATE> m_stkStateUpper;
    stack<PLAYER_STATE> m_stkStateLower;

    PLAYER_STATE        m_eBefore_The_Change_Upper; // ������ � ���¿��� �ٲ���°��� ��Ÿ��.
    PLAYER_STATE        m_eBefore_The_Change_Lower; // ���°� ������ ��, ���ϱ� ���� ���¸� �����
    WEAPON              m_eCurWeapon;
    WEAPON              m_ePrevWeapon;
    Vec2                m_iDir;
    int                 m_iPrevDir;
    int                 m_iGrenade;
    int                 m_iGrenadeCount;
    int                 m_iLife;
    int                 m_iHeavyMachineGunCount;
    int                 m_iTempFrameUpper;             // m_bFrameLock �� ��������
    int                 m_iTempFrameLower;             // m_bFrameLock �� ��������
    bool                m_bJump;
    bool                m_bAttacked;                // �÷��̾ ���Ϳ��� ������ �޾Ҵ��� ����
    bool                m_bSetCamera;                // ī�޶� ��� �÷��̾ Ÿ������ ���� ����
    bool                m_bFrameLockUpper;               // �� �����Ӵ� �ѹ߾��� �̻����� �߻��ϵ��� �ϴ� ���� (�⺻���� ù �����Ӹ� �̻��� �߻�)
    bool                m_bFrameLockLower;               // �ɾƼ� �� �� ����
    bool                m_bMeleeAtt;                    // ����Ű�� �������� ���������� �Ұ����� ����
    Vec2                m_vMissilePrevDir;
    

  //  bool m_btemp = false; // ������ �ӽ� ����

private:
    LARGE_INTEGER	m_llCurCount;
    LARGE_INTEGER	m_llPrevCount;
    LARGE_INTEGER	m_llFrequency; // 1�ʴ� �����ִ� ī��Ʈ��

    double			m_dDT; // ������ ������ �ð���, �����Ӱ� ������ ������ �ɸ� �ð�
    double			m_dAcc;	// 1�� üũ�� ���� ���� �ð�
    UINT			m_iCallCount; // �Լ� ȣ�� Ƚ�� üũ
    UINT			m_iFPS; // �ʴ� ȣ�� Ƚ��
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

    void update_HEAVYMACHINE_GUN_SCATTERING_UP(stack<PLAYER_STATE>& _stkState);  // �Լ��� �����丵�� �ʿ��غ���
    void update_HEAVYMACHINE_GUN_SCATTERING_DOWN(stack<PLAYER_STATE>& _stkState);
    
    void update_DEAD(stack<PLAYER_STATE>& _stkState);
    void update_RESPAWN(stack<PLAYER_STATE>& _stkState);

    void update_KNIFE_ATTACK(stack<PLAYER_STATE>& _stkState);

    void OneFrameOneShot(int _iMissileDir = 0); // �� �����Ӵ� �ѹ߾��� �̻����� �߻��ϵ��� �ϴ� ���� (�⺻���� ù �����Ӹ� �̻��� �߻�)
private:
    //virtual void OnCollision(CCollider* _pOther);         // �浹 ���� ��� ȣ��Ǵ� �Լ�
    //virtual void OnCollisionEnter(CCollider* _pOther);     // �浹 ���� ��
    virtual void OnCollisionExit(CCollider* _pOther);     // �浹 ���� ��

public:
    CPlayer();
    //CPlayer(const CPlayer& _origin)
    //    : CObject(_origin)
    //    , m_pTex(_origin.m_pTex)
    //{} �����Ϸ��� �ڵ����� �̷��� ����

    ~CPlayer();
};

