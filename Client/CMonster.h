#pragma once
#include "CObject.h"

struct tMonInfo
{
    MON_TYPE eMonType;        // 몬스터 종류
    float    fHP;              // 체력
    float    fSpeed;           // 속도
    float    fRecogRange;      // 인지 범위
    Vec2     fAttRange;        // 공격 범위
    float    fAtt;             // 공격력
    int      iDir;             // 방향
    clock_t  lAttStart;       // 공격을 시작한 시간
    clock_t  lAttAcc;         // 공격을 시작하고 지난 시간
    Vec2     vOrigPos;
    Vec2     vNextPos;       // 거대 메뚜기에게만 해당, 패트롤할 목적지
    Vec2     vKidnappingPos;  // 거대 메뚜기에게만 해당, 공격할 위치 저장
};

class AI;

class CMonster :
    public CObject
{
protected:
    tMonInfo    m_tInfo;
    AI*         m_pAI;

public:
    float GetSpeed() { return m_tInfo.fSpeed; }
    void SetSpeed(float _f) { m_tInfo.fSpeed = _f; }
    void SetAI(AI* _AI);
    void SetDir(int _i) { m_tInfo.iDir = _i; }
    void SetNextPos(Vec2 _v) { m_tInfo.vNextPos = _v; }
    void SetOrigPos(Vec2 _v) { m_tInfo.vOrigPos = _v; }
    void SetKidnappingPos(Vec2 _v) { m_tInfo.vKidnappingPos = _v; }
    const tMonInfo& GetInfo() { return m_tInfo; }
    AI* GetAI() { return m_pAI; }

private:
	void SetMonInfo(const tMonInfo& _info) { m_tInfo = _info; }

public:
    virtual void update_animation();
    void SetAttStart(long _l) { m_tInfo.lAttStart = _l; }
    void SetAttAcc(long _l) { m_tInfo.lAttAcc = _l; }

public:
    virtual void OnCollisionEnter(CCollider* _pOther);

public:
    virtual void update();
    virtual void render(HDC _dc);


    CLONE(CMonster);
public:
    CMonster();
    ~CMonster();
    
    friend class CMonFactory;
};

