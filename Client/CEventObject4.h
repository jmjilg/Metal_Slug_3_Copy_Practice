#pragma once
#include "CObject.h"

class CMonster;

class CEventObject4 :
    public CObject
{
private:
    bool        m_bIsEnterEvent;     // �̺�Ʈ�� �ѹ��� �۵��ϵ��� �ϴ� ����
    bool        m_bIsHugeHermitRespawn;     // �̺�Ʈ�� �ѹ��� �۵��ϵ��� �ϴ� ����
    clock_t     m_lEventStart;       // ������ ������ �ð�
    clock_t     m_lEventAcc;         // ������ �����ϰ� ���� �ð�

private:
    virtual void start();
    virtual void render(HDC _dc);
    virtual void update();


public:
    virtual void OnCollisionEnter(CCollider* _pOther);

public:
    CEventObject4();
    ~CEventObject4();

    CLONE(CEventObject4);


};

