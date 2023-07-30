#pragma once
#include "CObject.h"

class CMonster;

class CEventObject5 :
    public CObject
{
private:
    bool        bIsEnterEvent;     // �̺�Ʈ�� �ѹ��� �۵��ϵ��� �ϴ� ����
    int         m_iMonsterRespawnCount;   // �迡�� ���͸� �������� Ƚ��(4������)
    bool        IsMonsterClear;        // �迡�� ������ ���Ͱ� �� �׾�����
    CMonster* m_arrMonster[4] = {};

private:
    virtual void start();
    virtual void render(HDC _dc);
    virtual void update();


public:
    virtual void OnCollisionEnter(CCollider* _pOther);

public:
    CEventObject5();
    ~CEventObject5();

    CLONE(CEventObject5);


};

