#include "CSlugTransport.h"
#include "CRes.h"
#include "CResMgr.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CCollider.h"
#include "CRayGround.h"

CSlugTransport::CSlugTransport()
	: m_pTexture(nullptr)
{
	// Texture 로딩하기
	m_pTexture = CResMgr::GetInst()->LoadTexture(L"Mission1", L"texture\\Mission1.bmp");

	CreateAnimator();

	SetRayGround(new CRayGround);
	GetRayGround()->SetName(L"SlugTransPortGround");

	GetAnimator()->LoadAnimation(L"animation\\BackGround\\SlugTransport.anim");
}

CSlugTransport::~CSlugTransport()
{
}

void CSlugTransport::start()
{
}

void CSlugTransport::update()
{
	GetAnimator()->PlayL(L"SlugTransport", true);
	CRayGround* p = GetRayGround();
	
	int size = p->GetCollider()->GetVecRay().size();

	for (int i = 0; i < size; ++i)
	{
		p->GetCollider()->GetVecRay()[i] += Vec2(1.f, 0.f);
	}
}

void CSlugTransport::render(HDC _dc)
{
	component_render(_dc);
}
