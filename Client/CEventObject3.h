#pragma once
#include "CObject.h"

class CMonster;

class CEventObject3 :
    public CObject
{
private:
    bool        bIsEnterEvent;     // 이벤트가 한번만 작동하도록 하는 변수
    int         m_iMonsterRespawnCount;   // 배에서 몬스터를 리스폰할 횟수(4마리씩)
    bool        IsMonsterClear;        // 배에서 생성된 몬스터가 다 죽었는지
    CMonster* m_arrMonster[4] = {};
    bool m_bannihilation[4];  // 몬스터가 전멸했는지 여부
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

