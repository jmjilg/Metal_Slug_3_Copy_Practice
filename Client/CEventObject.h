#pragma once
#include "CObject.h"

// �� Ŭ���� (�̺�Ʈ ������Ʈ 1)�� CShip������ �̺�Ʈ, �� CShip���� ���� ������ ����(�߹����)���� ���� ��� �����߷����� 
// ������ �� �ִ� �̺�Ʈ��.


class CRayGround;
class CMonster;
class CShip;
class CR724;
class CShipDoor;

class CEventObject :
    public CObject
{
private:
    bool        bIsEnterEvent;     // �̺�Ʈ�� �ѹ��� �۵��ϵ��� �ϴ� ����
    int         m_iMonsterRespawnCount;   // �迡�� ���͸� �������� Ƚ��(4������)
    bool        IsMonsterClear;        // �迡�� ������ ���Ͱ� �� �׾�����
    CRayGround* m_pRayGround; // �迡�� �����ϴ� ���� �浹ü
    CMonster* m_arrMonster1;
    CMonster* m_arrMonster2;
    CMonster* m_arrMonster3;
    CMonster* m_arrMonster4;
    CShipDoor* m_pShipDoor;
    CObject* m_pShip;         // �̺�Ʈ������Ʈ�� ��������Ʈ�� ������ ����
    CObject* m_pR724;
    bool m_bannihilation[8];  // ���Ͱ� �����ߴ��� ����

private:
    virtual void start();
    virtual void render(HDC _dc);
    virtual void update();


public:
    virtual void OnCollisionEnter(CCollider* _pOther);
    void RespawnMonster(CMonster* _arrMonster, Vec2 _v, int i);
    void SetR724(CObject* _p) { m_pR724 = _p; }
    void SetShip(CObject* _p) { m_pShip = _p; }

public:
    CEventObject();
    ~CEventObject();

    CLONE(CEventObject);


};

