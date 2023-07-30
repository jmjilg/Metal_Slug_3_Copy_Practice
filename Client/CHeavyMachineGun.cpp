#include "CHeavyMachineGun.h"
#include "CRes.h"
#include "CResMgr.h"
#include "CTexture.h"


CHeavyMachineGun::CHeavyMachineGun()
	: ixOriginSrc(0)
	, iyOriginSrc(0)
	, iwSrc(0)
	, ihSrc(0)
{
	CTexture* pWeaponTex = CResMgr::GetInst()->LoadTexture(L"WeaponSFX", L"texture\\WeaponSFX.bmp");

	m_pTex = pWeaponTex;
}

CHeavyMachineGun::~CHeavyMachineGun()
{
}

void CHeavyMachineGun::render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();


	//Ellipse(_dc, (int)(vPos.x - vScale.x / 2.f), (int)(vPos.y - vScale.y / 2.f)
	//	, (int)(vPos.x + vScale.x / 2.f), (int)(vPos.y + vScale.y / 2.f));

	vPos = CCamera::GetInst()->GetRenderPos(vPos);  // 필요함. 이게 아니면 실제 좌표가 아닌 렌더링 좌표에서만 출력이 됨

	//vPos = GetCollider()->GetFinalPos();



	TransparentBlt(_dc
		, (int)(vPos.x - 15 / 2.f)
		, (int)(vPos.y - 10 / 2.f)
		, 30
		, 5
		, m_pTex->GetDC()
		, 4
		, 20
		, 30
		, 5
		, RGB(0, 248, 0)
	);


	component_render(_dc);
}
