#include "stdafx.h"
#include "MainGame.h"
#include "Monster.h"


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

}

void CMainGame::Update(void)
{
}

void CMainGame::Render(void)
{
}

void CMainGame::Release(void)
{
	ReleaseDC(g_hWnd, m_hDC);
}
