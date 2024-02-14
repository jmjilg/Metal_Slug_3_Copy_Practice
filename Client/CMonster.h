#pragma once
#include "CObject.h"

struct tMonInfo
{
    MON_TYPE eMonType;        // ���� ����
    float    fHP;              // ü��
    float    fSpeed;           // �ӵ�
    float    fRecogRange;      // ���� ����
    Vec2     vAttRange;        // ���� ����
    float    fAtt;             // ���ݷ�
    int      iDir;             // ����
    clock_t  lAttStart;       // ������ ������ �ð�
    clock_t  lAttAcc;         // ������ �����ϰ� ���� �ð�
    Vec2     vOrigPos;
    Vec2     vNextPos;       // �Ŵ� �޶ѱ⿡�Ը� �ش�, ��Ʈ���� ������
    Vec2     vKidnappingPos;  // �Ŵ� �޶ѱ⿡�Ը� �ش�, ������ ��ġ ����
    bool     bContact;        // M3_Rocket_Launch_Support_Van �� SlugTransport�� �ε������� ���θ� �˷��ִ� ����
};

class AI;

class CMonster :
    public CObject
{
protected:
    tMonInfo    m_tInfo;
    AI*         m_pAI;
    CObject*    m_pRelatedObj;  // ���Ϳ� �������ִ� ������Ʈ, CM3�� ��쿡�� WoodenStool�� ����������
    bool        m_bMeleeAttacked; 

public:
    float GetSpeed() { return m_tInfo.fSpeed; }
    void SetSpeed(float _f) { m_tInfo.fSpeed = _f; }
    void SetAI(AI* _AI);
    void SetDir(int _i) { m_tInfo.iDir = _i; }
    void SetNextPos(Vec2 _v) { m_tInfo.vNextPos = _v; }
    void SetOrigPos(Vec2 _v) { m_tInfo.vOrigPos = _v; }
    void SetKidnappingPos(Vec2 _v) { m_tInfo.vKidnappingPos = _v; }
    void SetContact(bool _b) { m_tInfo.bContact = _b; }
    void SetRelatedObj(CObject* pObj) { m_pRelatedObj = pObj; }
    const tMonInfo& GetInfo() { return m_tInfo; }
    AI* GetAI() { return m_pAI; }
    bool GetAttacked() { return m_bMeleeAttacked; }
    void SetMeleeAttacked(bool _b) { m_bMeleeAttacked = _b; }
    
private:
	void SetMonInfo(const tMonInfo& _info) { m_tInfo = _info; }

public:
    virtual void update_animation();
    void SetAttStart(long _l) { m_tInfo.lAttStart = _l; }
    void SetAttAcc(long _l) { m_tInfo.lAttAcc = _l; }

public:
    virtual void OnCollisionEnter(CCollider* _pOther);
    virtual void OnCollision(CCollider* _pOther);

public:
    virtual void update();
    virtual void render(HDC _dc);


    CLONE(CMonster);
public:
    CMonster();
    ~CMonster();
    
    friend class CMonFactory;
};

