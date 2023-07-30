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
	for (UINT iRow = 0; iRow < (UINT)GROUP_TYPE::END; ++iRow) // �������
	{
		for (UINT iCol = iRow; iCol < (UINT)GROUP_TYPE::END; ++iCol) // üũ�ڽ��� ���δ� ���°� �ƴϹǷ�, �� �����ʿ������� �������� ���ϱ�
		{
			if (m_arrCheck[iRow] & (1 << iCol))
			{
				CollisionGroupUpdate((GROUP_TYPE)iRow, (GROUP_TYPE)iCol); // �� �׷� �� ���� ���� ������ ��
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
		// �浹ü�� �������� �ʴ� ���
		if (nullptr == vecLeft[i]->GetCollider())
		{
			continue;
		}


		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			// �浹ü�� ���ų�, �ڱ� �ڽŰ��� �浹�� ���
			if (nullptr == vecRight[j]->GetCollider()
				|| vecLeft[i] == vecRight[j])
			{
				continue;
			}

			CCollider* pLeftCol = vecLeft[i]->GetCollider();
			CCollider* pRightCol = vecRight[j]->GetCollider();

			// �� �浹ü ���� ���̵� ����
			COLLIDER_ID ID;
			ID.Left_id = pLeftCol->GetID();
			ID.Right_id = pRightCol->GetID();

			iter = m_mapColInfo.find(ID.ID);

			// �浹 ������ �� ��� ������ ��� ���(�浹���� �ʾҴ� ��)
			if (m_mapColInfo.end() == iter)
			{
				m_mapColInfo.insert(make_pair(ID.ID, false));
				iter = m_mapColInfo.find(ID.ID);
			}

			auto func = &CCollisionMgr::IsCollision;
			// ���� ���� �浹ü��� IsRayCollision, �ƴϸ� IsCollision �˻縦 ����
			if (pLeftCol->GetIsRay() || pRightCol->GetIsRay())
				func = &CCollisionMgr::IsRayCollision;
			else
				func = &CCollisionMgr::IsCollision;


			if ((this->*func)(pLeftCol, pRightCol))
			{
				// ���� �浹 ���̴�. 

				if (iter->second)
				{
					// �������� �浹 �ϰ� �־���.
					if (vecLeft[i]->IsDead() || vecRight[j]->IsDead())
					{
						// �ٵ� �� �� �ϳ��� ���� �����̶��, �浹 ���������ش�.
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
					// �������� �浹���� �ʾҴ�.
					// �ٵ� �� �� �ϳ��� ���� �����̶��, �浹���� ���������� ���
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
				// ���� �浹�ϰ� ���� �ʴ�.
				if (iter->second)
				{
					// �������� �浹�ϰ� �־���.
					pLeftCol->OnCollisionExit(pRightCol);
					pRightCol->OnCollisionExit(pLeftCol);
					iter->second = false;
				}

			}

		}
	}
}
	bool CCollisionMgr::IsCollision(CCollider * _pLeftCol, CCollider * _pRightCol) // �ڽ��� �浹ü �浹����
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

	bool CCollisionMgr::IsRayCollision(CCollider * _pLeftCol, CCollider * _pRightCol) // ������ �浹ü �浹����
	{
		// left�� ��, right�� �÷��̾�
		// right�� ��, left�� �÷��̾�� �ٲ���
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

			// �÷��̾��� �߹� ��ġ
			Vec2 vFootPos = vRightPos;
			vFootPos.y = vRightPos.y + vRightScale.y / 2;


			//Vec2 H = vLeftDot + std::inner_product((vRightDot - vLeftDot).Normalize(), vRightPos - vLeftDot) * (vRightDot - vLeftDot).Normalize();
			Vec2 inner_product;
			inner_product.x = (vRightDot - vLeftDot).Normalize().x * (vFootPos - vLeftDot).x;
			inner_product.y = (vRightDot - vLeftDot).Normalize().y * (vFootPos - vLeftDot).y;

			// �÷��̾��� �߹ؿ��� ���� ����� ��ġ�� �ִ� ���� �浹ü���� �� H
			Vec2 H = vLeftDot + (vRightDot - vLeftDot).Normalize() * inner_product.Length();
			_pRightCol->SetH(H);

			// �÷��̾��� �߹ذ� �� ������ ���� �Ÿ�
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
		// �� ���� ���� �׷� Ÿ���� ������,
		// ū ���� ��(��Ʈ) �� ���

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


