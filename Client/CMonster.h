#pragma once
#include "CObject.h"

struct tMonInfo
{
    MON_TYPE eMonType;        // ���� ����
    float    fHP;              // ü��
    float    fSpeed;           // �ӵ�
    float    fRecogRange;      // ���� ����
    Vec2     fAttRange;        // ���� ����
    float    fAtt;             // ���ݷ�
    int      iDir;             // ����
    clock_t  lAttStart;       // ������ ������ �ð�
    clock_t  lAttAcc;         // ������ �����ϰ� ���� �ð�
    Vec2     vOrigPos;
    Vec2     vNextPos;       // �Ŵ� �޶ѱ⿡�Ը� �ش�, ��Ʈ���� ������
    Vec2     vKidnappingPos;  // �Ŵ� �޶ѱ⿡�Ը� �ش�, ������ ��ġ ����
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

