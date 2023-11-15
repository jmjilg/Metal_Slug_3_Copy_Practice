#pragma once
#include "CObject.h"

class CMonster;

class CEventObject3 :
    public CObject
{
private:
    bool        bIsEnterEvent;     // �̺�Ʈ�� �ѹ��� �۵��ϵ��� �ϴ� ����
    int         m_iMonsterRespawnCount;   // �迡�� ���͸� �������� Ƚ��(4������)
    bool        IsMonsterClear;        // �迡�� ������ ���Ͱ� �� �׾�����
    CMonster* m_arrMonster[4] = {};
    bool m_bannihilation[4];  // ���Ͱ� �����ߴ��� ����
    CMonster* m_arrMonster1;
    CMonster* m_arrMonster2;
    CMonster* m_arrMonster3;
    CMonster* m_arrMonster4;

private:
    virtual void start();
    virtual void render(HDC _dc);
    virtual void update();


public:
    virtual void OnCollisionEnter(CCollider* _pOther);

public:
    CEventObject3();
    ~CEventObject3();

    CLONE(CEventObject3);


};

