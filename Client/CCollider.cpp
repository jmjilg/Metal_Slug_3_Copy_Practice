#include "pch.h"
#include "CCollider.h"

#include "CObject.h"
#include "CCore.h"
#include "CCamera.h"

#include "SelectGDI.h"

UINT CCollider::g_iNextID = 0;

CCollider::CCollider()
	: m_pOwner(nullptr)
	, m_iID(g_iNextID++)
	, m_iCol(0)
	, m_bActive(true)
	, m_bIsRay(false)
	, m_bDead(false)
	, m_bObstacle(false)
	, m_bRender(true)
{
}

CCollider::CCollider(const CCollider& _origin)
	: m_pOwner(nullptr)
    , m_vOffsetPos(_origin.m_vOffsetPos)
    , m_vScale(_origin.m_vScale)
    , m_iID(g_iNextID++)
	, m_bActive(_origin.m_bActive)
{
}

CCollider::~CCollider()
{
}

void CCollider::finalupdate()
{
	// Object 의 위치를 따라간다.
	Vec2 vObjectPos = m_pOwner->GetPos();
	m_vFinalPos = vObjectPos + m_vOffsetPos;

	assert(0 <= m_iCol);
}

void CCollider::render(HDC _dc)
{
	if (!m_bRender)
		return;

	PEN_TYPE ePen = PEN_TYPE::GREEN;

	if (m_bObstacle)
		ePen = PEN_TYPE::BLUE;

	if (m_iCol)
		ePen = PEN_TYPE::RED;



	SelectGDI p(_dc, ePen);
	SelectGDI b(_dc, BRUSH_TYPE::HOLLOW);

	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(m_vFinalPos);

	if (m_bIsRay) // 직선 충돌체인 경우
	{
		for (size_t i = 0; i < m_vecRay.size()-1; i=i+2)
		{
			Vec2 vRenderPos1 = CCamera::GetInst()->GetRenderPos(m_vecRay[i]);
			Vec2 vRenderPos2 = CCamera::GetInst()->GetRenderPos(m_vecRay[i+1]);
			MoveToEx(_dc, vRenderPos1.x, vRenderPos1.y, NULL);
			LineTo(_dc, vRenderPos2.x, vRenderPos2.y);
		}
	}
	else // 박스형 충돌체인 경우
	{
		Rectangle(_dc
			, (int)(vRenderPos.x - m_vScale.x / 2.f)
			, (int)(vRenderPos.y - m_vScale.y / 2.f)
			, (int)(vRenderPos.x + m_vScale.x / 2.f)
			, (int)(vRenderPos.y + m_vScale.y / 2.f));
	}
	

}



void CCollider::OnCollision(CCollider* _pOther)
{
	m_pOwner->OnCollision(_pOther);
}

void CCollider::OnCollisionEnter(CCollider* _pOther)
{
	++m_iCol;
	m_pOwner->OnCollisionEnter(_pOther);
}

void CCollider::OnCollisionExit(CCollider* _pOther)
{
	--m_iCol;
	m_pOwner->OnCollisionExit(_pOther);
}


