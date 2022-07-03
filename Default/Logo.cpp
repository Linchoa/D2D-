#include "stdafx.h"
#include "Logo.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"


CLogo::CLogo()
{
}


CLogo::~CLogo()
{
	Release();
}

void CLogo::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Background/Logo.bmp", L"Logo");
}

void CLogo::Update(void)
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON) || CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON)) {
		CSceneMgr::Get_Instance()->Scene_Change(SC_MENU);
	}
}

void CLogo::Late_Update(void)
{
}

void CLogo::Render(HDC hDC)
{
	HDC	hMenuDC;

	hMenuDC = CBmpMgr::Get_Instance()->Find_Image(L"Logo");

	BitBlt(hDC, 0, 0, WINCX, WINCY, hMenuDC, 0, 0, SRCCOPY);
}

void CLogo::Release(void)
{
}
