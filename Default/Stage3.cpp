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
#include "Player.h"

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
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Background/GameOver.bmp", L"GameOver");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Background/Win.bmp", L"Win");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/ui/Score.bmp", L"Score");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/ui/Line_Cloud.bmp", L"Line_Cloud");

	CScrollMgr::Get_Instance()->Reset();

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
	static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_List(OBJ_PLAYER)->front())->Set_OriginPos();
}

void CStage3::Update(void)
{
	if (CObjMgr::Get_Instance()->Get_List(OBJ_PLAYER)->front()->Get_Dead()) {
		if (CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON) || CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON)) {
			CSceneMgr::Get_Instance()->Scene_Change(SC_MENU);
			static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_List(OBJ_PLAYER)->front())->Set_Reset(2);
		}
	}
	else if (static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_List(OBJ_PLAYER)->front())->Get_Win()) {
		if (CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON) || CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON)) {
			CSceneMgr::Get_Instance()->Scene_Change(SC_MENU);
			static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_List(OBJ_PLAYER)->front())->Set_Reset(2);
		}
	}
	else {
		int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		CObjMgr::Get_Instance()->Update();

		if (m_dwItemTime + m_iItemTimer < GetTickCount()) {
			m_dwItemTime = GetTickCount();
			m_iItemTimer = ((rand() % 5) + 1) * 100 + 1000;
			CObj* pObj = CAbstractFactory<CItemScore>::Create(rand() % 400 + 50, -100.f - iScrollY);
			CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, pObj);
		}
	}
}

void CStage3::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CStage3::Render(HDC hDC)
{
	HDC	hMenuDC;

	HFONT Font, oldFont;
	TCHAR		szBuff[32] = L"";
	if (CObjMgr::Get_Instance()->Get_List(OBJ_PLAYER)->front()->Get_Dead()) {
		hMenuDC = CBmpMgr::Get_Instance()->Find_Image(L"GameOver");
		BitBlt(hDC, 0, 0, WINCX, WINCY, hMenuDC, 0, 0, SRCCOPY);
	}
	else if (static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_List(OBJ_PLAYER)->front())->Get_Win()) {
		hMenuDC = CBmpMgr::Get_Instance()->Find_Image(L"Win");
		BitBlt(hDC, 0, 0, WINCX, WINCY, hMenuDC, 0, 0, SRCCOPY);

		Font = CreateFont(100, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, _T("µ¸¿òÃ¼"));
		oldFont = (HFONT)SelectObject(hDC, Font);

		swprintf_s(szBuff, L"%d", static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_List(OBJ_PLAYER)->front())->Get_Score(2));
		SetTextColor(hDC, RGB(255, 130, 0));
		TextOut(hDC, 180, 620, szBuff, lstrlen(szBuff));

		DeleteObject(oldFont);
	}
	else {
		int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		hMenuDC = CBmpMgr::Get_Instance()->Find_Image(L"Stage3_BG");

		BitBlt(hDC, 0, 0, WINCX, WINCY, hMenuDC, 0, 2200 - iScrollY, SRCCOPY);

		hMenuDC = CBmpMgr::Get_Instance()->Find_Image(L"Score");

		GdiTransparentBlt(hDC, 0, 0, int(200), int(100), hMenuDC, 0, 0, 200, 100, RGB(166, 202, 240));

		hMenuDC = CBmpMgr::Get_Instance()->Find_Image(L"Line_Cloud");

		GdiTransparentBlt(hDC, 0, -1400 + iScrollY, int(500), int(100), hMenuDC, 0, 0, 500, 100, RGB(0, 0, 0));

		Font = CreateFont(25, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, _T("µ¸¿òÃ¼"));
		oldFont = (HFONT)SelectObject(hDC, Font);

		swprintf_s(szBuff, L"Score : %d", static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_List(OBJ_PLAYER)->front())->Get_Score(2));
		SetTextColor(hDC, RGB(0, 200, 255));
		TextOut(hDC, 30, 40, szBuff, lstrlen(szBuff));

		DeleteObject(oldFont);

		CObjMgr::Get_Instance()->Render(hDC);
	}
}

void CStage3::Release(void)
{
	CObjMgr::Get_Instance()->Delete_ID(OBJ_BLOCK);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_ITEM);
}
