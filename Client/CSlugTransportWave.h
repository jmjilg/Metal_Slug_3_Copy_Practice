#pragma once
#include "CObject.h"
class CSlugTransportWave :
    public CObject
{

private:
    CTexture* m_pTexture;
    Vec2 m_vFinalPos;


private:
    virtual void start();
    virtual void update();
    virtual void render(HDC _dc);

public:
    CLONE(CSlugTransportWave);

public:
    CSlugTransportWave();
    ~CSlugTransportWave();
};

