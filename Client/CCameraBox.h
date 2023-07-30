#pragma once
#include "CObject.h"

class CCameraBox :
    public CObject
{
private:
    float m_fCorrection_Value_X; // 확대 렌더링을 했을 때의 렌더링 x축 보정값
    float m_fCorrection_Value_Y; // 확대 렌더링을 했을 때의 렌더링 y축 보정값
    bool  m_bTracePlayer;        // 플레이어를 쫓아가서 렌더링하는 카메라박스의 기능을 끄고 켤 수 있도록 하는 변수

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

