#include "stdafx.h"
#include "ScrollMgr.h"

CScrollMgr*		CScrollMgr::m_pInstance = nullptr;

CScrollMgr::CScrollMgr()
	: m_fScrollX(0.f), m_fScrollY(0.f), m_fMaxX(900.f), m_fMaxY(2000.f)
{
}


CScrollMgr::~CScrollMgr()
{
}

void CScrollMgr::Scroll_Lock(void)
{
	if (0.f < m_fScrollX)
		m_fScrollX = 0.f;

	if (WINCX - m_fMaxX > m_fScrollX)
		m_fScrollX = WINCX - m_fMaxX;


	if (0.f < m_fScrollY)
		m_fScrollY = 0.f;

	if (WINCY - m_fMaxY > m_fScrollY)
		m_fScrollY = WINCY - m_fMaxY;

}