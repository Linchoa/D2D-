#include "stdafx.h"
#include "Stage3.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "AbstractFactory.h"
#include "BlockStage3.h"
#include "ScrollMgr.h"
#include "ItemScore.h"


CStage3::CStage3() : m_iYScroll(1200), m_dwItemTime(GetTickCount()), m_iItemTimer(1000)
{
}


CStage3::~CStage3()
{
	Release();
}

void CStage3::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Background/Stage3.bmp", L"Stage3_BG");

	CObj*	pObj = CAbstractFactory<CBlockStage3>::Create( 250.f, 735.f );
	static_cast<CBlockStage3*>(pObj)->Set_SizeX(500.f);
	CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, pObj);

	pObj = CAbstractFactory<CItemScore>::Create(250.f, -100.f);
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, pObj);

	int iY = 635;
	while (iY > -1200) {
		CObj*	pBlock = CAbstractFactory<CBlockStage3>::Create(rand() % 500, iY);
		CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, pBlock);

		iY -= 100;
	}

	CObjMgr::Get_Instance()->Get_List(OBJ_PLAYER)->front()->Set_Pos(250.f, 700.f);
}

void CStage3::Update(void)
{
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	CObjMgr::Get_Instance()->Update();

	if (m_dwItemTime + m_iItemTimer < GetTickCount()) {
		m_dwItemTime = GetTickCount();
		m_iItemTimer = ((rand() % 5) + 1) * 100 + 1000;
		CObj* pObj = CAbstractFactory<CItemScore>::Create(rand() % 400 + 50, -100.f - iScrollY);
		CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, pObj);
	}
}

void CStage3::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CStage3::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMenuDC;

	hMenuDC = CBmpMgr::Get_Instance()->Find_Image(L"Stage3_BG");

	BitBlt(hDC, 0, 0, WINCX, WINCY, hMenuDC, 0, 2200 - iScrollY, SRCCOPY);

	CObjMgr::Get_Instance()->Render(hDC);
}

void CStage3::Release(void)
{
	CObjMgr::Get_Instance()->Delete_ID(OBJ_BLOCK);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_ITEM);
}
