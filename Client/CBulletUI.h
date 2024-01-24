#pragma once
#include "CObject.h"

class CPlayer;




class CBulletUI : public CObject
{
private:
    FONT        m_eFont;
    CPlayer*    m_pPlayer; 
    CTexture*   m_pSystemSetupTex;
    CTexture*   m_pTime_NumbersTex;
    Digit       m_eDigit;


public:
    void SetPlayer(CPlayer* _pPlayer) { m_pPlayer = _pPlayer; }
    void SetFont(FONT _eFont) { m_eFont = _eFont; }
    void SetDigit(Digit _eDigit) { m_eDigit = _eDigit; }


public:
    virtual void start();
    virtual void update();
    virtual void render(HDC _dc);

public:
    CLONE(CBulletUI);

    CBulletUI(Digit _eDigit, CPlayer* _pPlayer);
    CBulletUI(FONT _eFont, CPlayer* _pPlayer);
    ~CBulletUI();
};

