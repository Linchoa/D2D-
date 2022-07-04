#include "stdafx.h"
#include "Stage1.h"
#include "Player.h"
#include "Monster.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "BmpMgr.h"
#include "SceneMgr.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"


CStage1::CStage1() : m_dwMonsterTime(GetTickCount()), m_iMonsterTimer(500)
{
}


CStage1::~CStage1()
{
	Release();
}

void CStage1::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map.bmp", L"Map");	
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Background/GameOver.bmp", L"GameOver");

	CObjMgr::Get_Instance()->Get_List(OBJ_PLAYER)->front()->Set_Pos(26.f, 774.f);
	static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_List(OBJ_PLAYER)->front())->Set_OriginPos();

	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster>::Create(250.f, -100.f));
}

void CStage1::Update(void)
{
	if (CObjMgr::Get_Instance()->Get_List(OBJ_PLAYER)->front()->Get_Dead()) {
		if (CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON) || CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON)) {
			CSceneMgr::Get_Instance()->Scene_Change(SC_MENU);
			static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_List(OBJ_PLAYER)->front())->Set_Reset(0);
		}
	}
	else {
		CObjMgr::Get_Instance()->Update();

		if (m_dwMonsterTime + m_iMonsterTimer < GetTickCount()) {
			m_dwMonsterTime = GetTickCount();
			m_iMonsterTimer = ((rand() % 5) + 1) * 100 + 500;
			CObj* pObj = CAbstractFactory<CMonster>::Create(rand() % 440 + 30, -100.f);
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pObj);
		}
	}
}

void CStage1::Late_Update(void)
{
	if (CObjMgr::Get_Instance()->Get_List(OBJ_PLAYER)->front()->Get_Dead()) {
	}
	else {
		CObjMgr::Get_Instance()->Late_Update();
	}
}

void CStage1::Render(HDC hDC)
{
	HDC	hGroundDC;
	HFONT Font, oldFont;
	TCHAR		szBuff[32] = L"";

	if (CObjMgr::Get_Instance()->Get_List(OBJ_PLAYER)->front()->Get_Dead()) {
		hGroundDC = CBmpMgr::Get_Instance()->Find_Image(L"GameOver");
		BitBlt(hDC, 0, 0, WINCX, WINCY, hGroundDC, 0, 0, SRCCOPY);

		Font = CreateFont(100, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, _T("µ¸¿òÃ¼"));
		oldFont = (HFONT)SelectObject(hDC, Font);

		swprintf_s(szBuff, L"%d", static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_List(OBJ_PLAYER)->front())->Get_Score(0));
		SetTextColor(hDC, RGB(255, 130, 0));
		TextOut(hDC, 150, 620, szBuff, lstrlen(szBuff));

		DeleteObject(oldFont);
	}
	else {
		hGroundDC = CBmpMgr::Get_Instance()->Find_Image(L"Map");
		int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

		BitBlt(hDC, iScrollX, 0, WINCX, WINCY, hGroundDC, 0, 0, SRCCOPY);

		CObjMgr::Get_Instance()->Render(hDC);

		Font = CreateFont(25, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, _T("µ¸¿òÃ¼"));
		oldFont = (HFONT)SelectObject(hDC, Font);

		swprintf_s(szBuff, L"Score : %d", static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_List(OBJ_PLAYER)->front())->Get_Score(0));
		SetTextColor(hDC, RGB(0, 200, 255));
		TextOut(hDC, 30, 40, szBuff, lstrlen(szBuff));

		DeleteObject(oldFont);
	}
}

void CStage1::Release(void)
{
	CObjMgr::Get_Instance()->Delete_ID(OBJ_MONSTER);
}
