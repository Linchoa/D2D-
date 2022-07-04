#include "stdafx.h"
#include "MainGame.h"
#include "Monster.h"
#include "BmpMgr.h"
#include "SceneMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"


CMainGame::CMainGame()
	: m_pPlayer(nullptr), m_pMonster(nullptr)
{
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{
	m_hDC = GetDC(g_hWnd);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Back.bmp", L"Back");

	CSceneMgr::Get_Instance()->Scene_Change(SC_LOGO);

	srand(unsigned(time(nullptr)));
}

void CMainGame::Update(void)
{
	CSceneMgr::Get_Instance()->Update();
}

void CMainGame::Late_Update(void)
{
	CSceneMgr::Get_Instance()->Late_Update();
}

void CMainGame::Render(void)
{
	HDC	hBackDC = CBmpMgr::Get_Instance()->Find_Image(L"Back");

	CSceneMgr::Get_Instance()->Render(hBackDC);

	BitBlt(m_hDC, 0, 0, WINCX, WINCY, hBackDC, 0, 0, SRCCOPY);
}

void CMainGame::Release(void)
{
	CSceneMgr::Get_Instance()->Destroy_Instance();
	CBmpMgr::Get_Instance()->Destroy_Instance();
	CScrollMgr::Get_Instance()->Destroy_Instance();
	CObjMgr::Get_Instance()->Destroy_Instance();
	ReleaseDC(g_hWnd, m_hDC);
}
