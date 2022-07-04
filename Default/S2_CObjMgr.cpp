#include "stdafx.h"
#include "S2_CObjMgr.h"
#include "S2_Player.h"

CS2_CObjMgr*		CS2_CObjMgr::m_pInstance = nullptr;
CS2_CObjMgr::CS2_CObjMgr()
{
}


CS2_CObjMgr::~CS2_CObjMgr()
{
	Release();
}

void CS2_CObjMgr::Add_Object(CSC_Obj::OBJID eID, CSC_Obj * pObj)
{
	if (eID >= CSC_Obj::OBJ_END || nullptr == pObj)
		return;

	m_ObjList[eID].push_back(pObj);
}

void CS2_CObjMgr::Delete_ID(CSC_Obj::OBJID eID)
{
	for (auto& iter : m_ObjList[eID])
		Safe_Delete(iter);

	m_ObjList[eID].clear();
}

int CS2_CObjMgr::Update(void)
{
	int	iEvent = 0;

	for (size_t i = 0; i < CSC_Obj::OBJ_END; ++i)
	{
		for (auto& iter = m_ObjList[i].begin();
			iter != m_ObjList[i].end();)
		{
			iEvent = (*iter)->Update();

			if (OBJ_DEAD == iEvent)
			{
				Safe_Delete<CSC_Obj*>(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else
				++iter;
		}
	}

	return iEvent;
}

bool Check_Sphere(CObj * pDest, CObj * pSour)
{
	// abs : 절대값을 만들어주는 함수
	float	fWidth = fabs(pDest->Get_Info().vPos.x - pSour->Get_Info().vPos.x);
	float	fHeight = fabs(pDest->Get_Info().vPos.y - pSour->Get_Info().vPos.y);

	// sqrt : 루트를 씌워주는 함수
	float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

	float	fRadius = (100) * 0.5f;

	return fRadius >= fDiagonal;	// 충돌을 한 경우
}

int CS2_CObjMgr::Late_Update(void)
{
	if(Check_Sphere(m_ObjList[CSC_Obj::OBJ_PLAYER].back(), m_ObjList[CSC_Obj::OBJ_ITEM].back()))
	{
		return 1;
	}


	for (size_t i = 0; i < CSC_Obj::OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			iter->Late_Update();
	}
	return 0;
}

void CS2_CObjMgr::Render(HDC hDC)
{
	for (size_t i = 0; i < CSC_Obj::OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			iter->Render(hDC);
	}
}

void CS2_CObjMgr::Release(void)
{
	for (size_t i = 0; i < CSC_Obj::OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			Safe_Delete(iter);

		m_ObjList[i].clear();
	}
}
