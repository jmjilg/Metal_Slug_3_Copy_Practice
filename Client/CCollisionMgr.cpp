#include "pch.h"
#include "CCollisionMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CObject.h"
#include "CCollider.h"
#include "CRayCollider.h"
#include "CKeyMgr.h"
#include <functional>
#include <numeric>


CCollisionMgr::CCollisionMgr()
	: m_arrCheck{}
	, IsUnderRay(false)
{
}

CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::update()
{
	for (UINT iRow = 0; iRow < (UINT)GROUP_TYPE::END; ++iRow) // 행단위로
	{
		for (UINT iCol = iRow; iCol < (UINT)GROUP_TYPE::END; ++iCol) // 체크박스를 전부다 쓰는게 아니므로, 또 오른쪽에서부터 왼쪽으로 세니까
		{
			if (m_arrCheck[iRow] & (1 << iCol))
			{
				CollisionGroupUpdate((GROUP_TYPE)iRow, (GROUP_TYPE)iCol); // 두 그룹 중 작은 수가 행으로 들어감
			}
		}
	}
}



void CCollisionMgr::CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	const vector<CObject*>& vecLeft = pCurScene->GetGroupObject(_eLeft);
	const vector<CObject*>& vecRight = pCurScene->GetGroupObject(_eRight);
	map<ULONGLONG, bool>::iterator iter;

	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		// 충돌체를 보유하지 않는 경우
		if (nullptr == vecLeft[i]->GetCollider())
		{
			continue;
		}


		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			// 충돌체가 없거나, 자기 자신과의 충돌인 경우
			if (nullptr == vecRight[j]->GetCollider()
				|| vecLeft[i] == vecRight[j])
			{
				continue;
			}

			CCollider* pLeftCol = vecLeft[i]->GetCollider();
			CCollider* pRightCol = vecRight[j]->GetCollider();

			// 두 충돌체 조합 아이디 생성
			COLLIDER_ID ID;
			ID.Left_id = pLeftCol->GetID();
			ID.Right_id = pRightCol->GetID();

			iter = m_mapColInfo.find(ID.ID);

			// 충돌 정보가 미 등록 상태인 경우 등록(충돌하지 않았다 로)
			if (m_mapColInfo.end() == iter)
			{
				m_mapColInfo.insert(make_pair(ID.ID, false));
				iter = m_mapColInfo.find(ID.ID);
			}

			auto func = &CCollisionMgr::IsCollision;
			// 만약 선형 충돌체라면 IsRayCollision, 아니면 IsCollision 검사를 시행
			if (pLeftCol->GetIsRay() || pRightCol->GetIsRay())
				func = &CCollisionMgr::IsRayCollision;
			else
				func = &CCollisionMgr::IsCollision;


			if ((this->*func)(pLeftCol, pRightCol))
			{
				// 현재 충돌 중이다. 

				if (iter->second)
				{
					// 이전에도 충돌 하고 있었다.
					if (vecLeft[i]->IsDead() || vecRight[j]->IsDead())
					{
						// 근데 둘 중 하나가 삭제 예정이라면, 충돌 해제시켜준다.
						pLeftCol->OnCollisionExit(pRightCol);
						pRightCol->OnCollisionExit(pLeftCol);
						iter->second = false;
					}
					else
					{
						pLeftCol->OnCollision(pRightCol);
						pRightCol->OnCollision(pLeftCol);
					}
				}
				else
				{
					// 이전에는 충돌하지 않았다.
					// 근데 둘 중 하나가 삭제 예정이라면, 충돌하지 않은것으로 취급
					if (!vecLeft[i]->IsDead() && !vecRight[j]->IsDead())
					{
						pLeftCol->OnCollisionEnter(pRightCol);
						pRightCol->OnCollisionEnter(pLeftCol);
						iter->second = true;
					}
				}
			}
			else
			{
				// 현재 충돌하고 있지 않다.
				if (iter->second)
				{
					// 이전에는 충돌하고 있었다.
					pLeftCol->OnCollisionExit(pRightCol);
					pRightCol->OnCollisionExit(pLeftCol);
					iter->second = false;
				}

			}

		}
	}
}
	bool CCollisionMgr::IsCollision(CCollider * _pLeftCol, CCollider * _pRightCol) // 박스형 충돌체 충돌감지
	{
		if (_pLeftCol->GetDead() || _pRightCol->GetDead())
			return false;

		Vec2 vLeftPos = _pLeftCol->GetFinalPos();
		Vec2 vLeftScale = _pLeftCol->GetScale();

		Vec2 vRightPos = _pRightCol->GetFinalPos();
		Vec2 vRightScale = _pRightCol->GetScale();

		if (abs(vRightPos.x - vLeftPos.x) <= (vLeftScale.x + vRightScale.x) / 2.f
			&& abs(vRightPos.y - vLeftPos.y) <= (vLeftScale.y + vRightScale.y) / 2.f)
		{
			return true;
		}

		return false;
	}

	bool CCollisionMgr::IsRayCollision(CCollider * _pLeftCol, CCollider * _pRightCol) // 직선형 충돌체 충돌감지
	{
		// left가 땅, right가 플레이어
		// right가 땅, left가 플레이어로 바꾸자
		auto temp = _pRightCol->GetVecRay();

		if (!_pLeftCol->GetObj()->GetbStandLine())
			return false;

		if (temp.size() < 2)
			return false;

		for (size_t i = 0; i < _pRightCol->GetVecRay().size() - 1; i = i + 2)
		{
			Vec2 vLeftDot = _pRightCol->GetVecRay()[i];
			Vec2 vRightDot = _pRightCol->GetVecRay()[i + 1];

			Vec2 vRightPos = _pLeftCol->GetFinalPos();
			Vec2 vRightScale = _pLeftCol->GetScale();

			// 플레이어의 발밑 위치
			Vec2 vFootPos = vRightPos;
			vFootPos.y = vRightPos.y + vRightScale.y / 2;


			//Vec2 H = vLeftDot + std::inner_product((vRightDot - vLeftDot).Normalize(), vRightPos - vLeftDot) * (vRightDot - vLeftDot).Normalize();
			Vec2 inner_product;
			inner_product.x = (vRightDot - vLeftDot).Normalize().x * (vFootPos - vLeftDot).x;
			inner_product.y = (vRightDot - vLeftDot).Normalize().y * (vFootPos - vLeftDot).y;

			// 플레이어의 발밑에서 가장 가까운 위치에 있는 직선 충돌체위의 점 H
			Vec2 H = vLeftDot + (vRightDot - vLeftDot).Normalize() * inner_product.Length();
			_pRightCol->SetH(H);

			// 플레이어의 발밑과 점 사이의 선분 거리
			double Distance = sqrt(pow(vFootPos.x - H.x, 2) + pow(vFootPos.y - H.y, 2));

			if ((abs(Distance) < 10.f) && ((vFootPos.x >= vLeftDot.x) && (vFootPos.x <= vRightDot.x)))  
			{
				if (KEY_TAP(KEY::K))
					return false;

				return true;
			}

		}

		return false;
	}




	void CCollisionMgr::CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
	{
		// 더 작은 값의 그룹 타입을 행으로,
		// 큰 값을 열(비트) 로 사용

		UINT iRow = (UINT)_eLeft;
		UINT iCol = (UINT)_eRight;

		if (iCol < iRow)
		{
			iRow = (UINT)_eRight;
			iCol = (UINT)_eLeft;
		}

		if (m_arrCheck[iRow] & (1 << iCol))
		{
			m_arrCheck[iRow] &= ~(1 << iCol);

		}
		else
		{
			m_arrCheck[iRow] |= (1 << iCol);

		}


	}


