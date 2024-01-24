#pragma once

class CObject;
class CAnimation;
class CTexture;

class CAnimator
{
private:
	map<wstring, CAnimation*>	m_mapAnim;		// ��� Animation
	CAnimation*					m_pCurAnimL;		// ���� ������� Animation (���� ��Ʈ)
	CAnimation*					m_pCurAnimU;		// ���� ������� Animation (�Ʒ��� ��Ʈ)
	CObject*					m_pOwner;		// Animator ���� ������Ʈ
	bool						m_bRepeatL;		// �ݺ���� ����
	bool						m_bRepeatU;		// �ݺ���� ����

public:
	CObject* GetObj() { return m_pOwner; }
	void StopAnimationL(bool _bStop);
	void StopAnimationU(bool _bStop);
	CAnimation* GetCurAnimL() { return m_pCurAnimL; }
	CAnimation* GetCurAnimU() { return m_pCurAnimU; }
	void SetTransParentColor(COLORREF _r, COLORREF _g, COLORREF _b);


public:
	void CreateAnimation(const wstring& _strName, CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, Vec2 _vOffset, float _fDuration, UINT _iFreamCount);
	void LoadAnimation(const wstring& _strRelativePath);
	CAnimation* FindAnimation(const wstring& _strName);
	void PlayL(const wstring& _strName, bool _bRepeat);
	void PlayU(const wstring& _strName, bool _bRepeat);
	void Play(const wstring& _strName, const wstring& _strName2, bool _bRepeat);

	void update();
	void finalupdate();
	void render(HDC _dc);

public:
	CAnimator();
	~CAnimator();

	friend class CObject;
};

