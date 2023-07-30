#pragma once
#include "CObject.h"

// 이 클래스 (이벤트 오브젝트 1)은 CShip에서의 이벤트, 즉 CShip에서 문이 열리고 몬스터(중밍콩게)들이 나와 모두 쓰러뜨려야지 
// 전진할 수 있는 이벤트임.


class CRayGround;
class CMonster;
class CShip;
class CR724;
class CShipDoor;

class CEventObject :
    public CObject
{
private:
    bool        bIsEnterEvent;     // 이벤트가 한번만 작동하도록 하는 변수
    int         m_iMonsterRespawnCount;   // 배에서 몬스터를 리스폰할 횟수(4마리씩)
    bool        IsMonsterClear;        // 배에서 생성된 몬스터가 다 죽었는지
    CRayGround* m_pRayGround; // 배에서 생성하는 직선 충돌체
    CMonster* m_arrMonster1;
    CMonster* m_arrMonster2;
    CMonster* m_arrMonster3;
    CMonster* m_arrMonster4;
    CShipDoor* m_pShipDoor;
    CObject* m_pShip;         // 이벤트오브젝트가 배경오브젝트를 가지고 있음
    CObject* m_pR724;
    bool m_bannihilation[8];  // 몬스터가 전멸했는지 여부

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

