#pragma once
#include "CScene.h"

class CUI;
class CTestAnim;

class CScene_Tool :
    public CScene
{
private:
    CUI* m_pUI;
    CTestAnim* m_pTestAnim;
    vector<wstring> m_vecAnimFile1;
    vector<wstring> m_vecAnimFile2;

public:
    virtual void update();
    virtual void Enter();
    virtual void Exit();
    int iFocusAnimFile;


public:
    void SetTileIdx();
    CTestAnim* GetTestAnim() { return m_pTestAnim; }
    const vector<wstring>& GetAnimFile1() { return m_vecAnimFile1; }
    const vector<wstring>& GetAnimFile2() { return m_vecAnimFile2; }

    void SaveTileData();
    void SaveTile(const wstring& _strFilePath);

    void LoadTileData();
    void LoadAnimationData();
    void LoadAnimationData2();


public:
    CScene_Tool();
    ~CScene_Tool();
};

