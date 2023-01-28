#pragma once
#include "CObject.h"

class CAnimator;

class CTestAnim :
    public CObject
{
private:
    CLONE(CTestAnim);
    wstring strAnimFile;
    wstring strAnimFile2;

public:
    virtual void update();
    virtual void render(HDC _dc);

public:
    void SetCurAnimFile1(wstring _strAnimFile) { strAnimFile = _strAnimFile; }
    void SetCurAnimFile2(wstring _strAnimFile) { strAnimFile2 = _strAnimFile; }

    wstring GetCurAnimFile1() { return strAnimFile; }
    wstring GetCurAnimFile2() { return strAnimFile2; }


public:
    CTestAnim();
    ~CTestAnim();
};

