#pragma once
#include "CObject.h"

class CRayGround;

class CSlugTransport :
    public CObject
{

private:
    CTexture*   m_pTexture;
    Vec2        m_vFinalPos;
    float       m_fVelocity;           // SlugTransport �� ���� ������Ʈ ��ġ�� ���� ��ġ���� ����
    bool        m_bContact;
    bool        m_bRespawn;              // ���������� ����
    int         m_iRespawnCount;          // �ö��� ų�� �������� Ƚ��
    clock_t     m_lRespawnStart;       // �ö��� ų���� ������ �ð�
    clock_t     m_lRespawnAcc;         // �ö��� ų���� �����ϰ� ���� �ð�
    bool        m_bRespawnEvent;       // �ö��� ų���� �������� �ð�
    clock_t     m_IBossEventStart;     // ���� ���� �̺�Ʈ�� ������ �ð�
    clock_t     m_IBossEventAcc;       // ���� ���� �̺�Ʈ�� �����ϰ� ���� �ð�
    bool        m_bStop;               // �踦 ���߰� �ϴ� ����
    bool        m_bBossEvent;          // ���� �̺�Ʈ�� ���������� ����

private:
    CRayGround* m_pRayGround;

private:
    virtual void start();
    virtual void update();
    virtual void render(HDC _dc);

public:
    CLONE(CSlugTransport);

public:
    CSlugTransport();
    ~CSlugTransport();

    virtual void OnCollisionEnter(CCollider* _pOther);
    virtual void OnCollision(CCollider* _pOther);
    virtual void OnCollisionExit(CCollider* _pOther);
};

