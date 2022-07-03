#include "stdafx.h"
#include "BlockStage3.h"
#include "ScrollMgr.h"


CBlockStage3::CBlockStage3() : m_fSizeX(0.f), m_fSizeY(0.f)
{
}


CBlockStage3::~CBlockStage3()
{
}

void CBlockStage3::Initialize(void)
{
	m_fSizeX = float((rand() % 4 + 1) * 100);
	m_fSizeY = 20.f;
}

int CBlockStage3::Update(void)
{
	return OBJ_NOEVENT;
}

void CBlockStage3::Late_Update(void)
{
}

void CBlockStage3::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	Rectangle(hDC, m_tInfo.vPos.x - m_fSizeX * 0.5f, m_tInfo.vPos.y - m_fSizeY * 0.5f + iScrollY, m_tInfo.vPos.x + m_fSizeX * 0.5f, m_tInfo.vPos.y + m_fSizeY * 0.5f + iScrollY);
}

void CBlockStage3::Release(void)
{
}
