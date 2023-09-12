#pragma once
#include "CState.h"
class CFiring :
    public CState
{
public:
    virtual void update();
    virtual void Enter();
    virtual void Exit();

private:
    bool m_bRespawn;              // ���������� ����
    int m_iRespawnCount;          // �̻��� �������� Ƚ��
    clock_t  lRespawnStart;       // �̻��� �������� �ð�
    clock_t  lRespawnAcc;         // �̻��� �������ϰ� ���� �ð�

public:
    CFiring();
    ~CFiring();
};

