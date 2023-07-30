#pragma once
#include "CObject.h"

class CCameraBox :
    public CObject
{
private:
    float m_fCorrection_Value_X; // Ȯ�� �������� ���� ���� ������ x�� ������
    float m_fCorrection_Value_Y; // Ȯ�� �������� ���� ���� ������ y�� ������
    bool  m_bTracePlayer;        // �÷��̾ �Ѿư��� �������ϴ� ī�޶�ڽ��� ����� ���� �� �� �ֵ��� �ϴ� ����

public:
    float GetCorrectionValueX() { return m_fCorrection_Value_X; }
    float GetCorrectionValueY() { return m_fCorrection_Value_Y; }
    bool  GetTracePlayer() { return m_bTracePlayer;}
    void SetCorrectionValueX(float _f) { m_fCorrection_Value_X = _f; }
    void SetCorrectionValueY(float _f) { m_fCorrection_Value_Y = _f; }
    void SetTracePlayer(bool _b) { m_bTracePlayer = _b; }

private:
    virtual void start();
    virtual void update();
    virtual void render(HDC _dc);

public:
    virtual void OnCollisionEnter(CCollider* _pOther);
    virtual void OnCollision(CCollider* _pOther);
    virtual void OnCollisionExit(CCollider* _pOther);

    CLONE(CCameraBox);



public:
    CCameraBox();
    ~CCameraBox();
};

