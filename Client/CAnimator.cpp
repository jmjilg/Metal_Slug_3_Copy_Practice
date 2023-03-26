#include "pch.h"
#include "CAnimator.h"

#include "CAnimation.h"

CAnimator::CAnimator()
	: m_pCurAnimL(nullptr)
	, m_pCurAnimU(nullptr)
	, m_pOwner(nullptr)
	, m_bRepeatL(false)
	, m_bRepeatU(false)
	, m_bStop(false)
{
}

CAnimator::~CAnimator()
{
	Safe_Delete_Map(m_mapAnim);
}

void CAnimator::update()
{

}

void CAnimator::finalupdate()
{
	if (nullptr != m_pCurAnimL)
	{
		m_pCurAnimL->update();

		if (m_bRepeatL && m_pCurAnimL->IsFinish())
		{
			m_pCurAnimL->SetFrame(0);
		}

	}
	if (nullptr != m_pCurAnimU)
	{
		m_pCurAnimU->update();

		if (m_bRepeatU && m_pCurAnimU->IsFinish())
		{
			m_pCurAnimU->SetFrame(0);
		}
	}
}

void CAnimator::render(HDC _dc)
{
	if (nullptr != m_pCurAnimL)
	{
		m_pCurAnimL->render(_dc);
	}
	if (nullptr != m_pCurAnimU)
	{
		m_pCurAnimU->render(_dc);
	}
}

void CAnimator::StopAnimationL(bool _bStop)
{
	if(m_pCurAnimL != nullptr)
		m_pCurAnimL->SetStop(_bStop);
}

void CAnimator::StopAnimationU(bool _bStop)
{
	if(m_pCurAnimU != nullptr)
		m_pCurAnimU->SetStop(_bStop);
}

void CAnimator::SetTransParentColor(COLORREF _r, COLORREF _g, COLORREF _b)
{
	if (nullptr != m_pCurAnimL)
		m_pCurAnimL->SetTransParentColor(_r, _g, _b);
	if (nullptr != m_pCurAnimU)
		m_pCurAnimU->SetTransParentColor(_r, _g, _b);
}

void CAnimator::CreateAnimation(const wstring& _strName, CTexture* _pTex, Vec2 _vLT
								, Vec2 _vSliceSize, Vec2 _vStep, Vec2 _vOffset, float _fDuration, UINT _iFreamCount)
{
	CAnimation* pAnim = FindAnimation(_strName);
	assert(nullptr == pAnim);

	pAnim = new CAnimation;

	pAnim->SetName(_strName);
	pAnim->m_pAnimator = this;
	pAnim->Create(_pTex, _vLT, _vSliceSize, _vStep, _vOffset, _fDuration, _iFreamCount);

	
	m_mapAnim.insert(make_pair(_strName, pAnim));
	
}

void CAnimator::LoadAnimation(const wstring& _strRelativePath)
{
	CAnimation* pAnim = new CAnimation;
	pAnim->Load(_strRelativePath);

	pAnim->m_pAnimator = this;
	m_mapAnim.insert(make_pair(pAnim->GetName(), pAnim));
}

CAnimation* CAnimator::FindAnimation(const wstring& _strName)
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.find(_strName);

	if (iter == m_mapAnim.end())
		return nullptr;

	return iter->second;
}

void CAnimator::PlayL(const wstring& _strName, bool _bRepeat)
{
	m_pCurAnimL = FindAnimation(_strName);
	m_bRepeatL = _bRepeat;
}

void CAnimator::PlayU(const wstring& _strName, bool _bRepeat)
{
	m_pCurAnimU = FindAnimation(_strName);
	m_bRepeatU = _bRepeat;
}

void CAnimator::Play(const wstring& _strName, const wstring& _strName2, bool _bRepeat)
{
	m_pCurAnimL = FindAnimation(_strName);
	m_pCurAnimU = FindAnimation(_strName2);
	m_bRepeatL = _bRepeat;
	m_bRepeatU = _bRepeat;
}
