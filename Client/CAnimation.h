#pragma once

#include "global.h"

class CAnimator;
class CTexture;

struct tAnimFrm
{
	Vec2	vLT;
	Vec2	vSlice;
	Vec2	vOffset;
	float	fDuration;

};

class CAnimation
{
private:
	wstring				m_strName;
	CAnimator*			m_pAnimator;	
	CTexture*			m_pTex;			// Animation �� ����ϴ� �ؽ���
	vector<tAnimFrm>	m_vecFrm;		// ��� ������ ����
	int					m_iCurFrm;		// ���� ������
	float				m_fAccTime;		// �ð� ����

	bool				m_bFinish;		// ��� ���� ���޿���
	bool				m_bStop;		// �Ͻ����� ����

	COLORREF			m_red;
	COLORREF			m_green;
	COLORREF			m_blue;

public:
	const wstring& GetName() { return m_strName; }
	bool IsFinish() { return m_bFinish; }
	void SetFrame(int _iFrameIdx)
	{
		m_bFinish = false;
		m_iCurFrm = _iFrameIdx;
		m_fAccTime = 0.f;
	}
	void SetStop(bool _bStop) { m_bStop = _bStop; }

	tAnimFrm& GetFrame(int _iIdx) { return m_vecFrm[_iIdx]; }	
	UINT GetMaxFrame() { return (UINT)m_vecFrm.size(); }
	void SetTransParentColor(COLORREF _r, COLORREF _g, COLORREF _b) { m_red = _r, m_green = _g, m_blue = _b; }

private:
	void SetName(const wstring& _strName) { m_strName = _strName; }

public:
	void update();
	void render(HDC _dc);
	void Create(CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, Vec2 _vOffset, float _fDuration, UINT _iFreamCount);

public:
	void Save(const wstring& _strRelativePath);
	void Load(const wstring& _strRelativePath);


public:
	CAnimation();
	~CAnimation();

	friend class CAnimator;
};

