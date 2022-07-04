#include "stdafx.h"
#include "S2_Line.h"
#include "ScrollMgr.h"

CS2_Line::CS2_Line(LINEPOINT & tLeft, LINEPOINT & tRight, LINEID lineID)
	: m_tLineInfo(tLeft, tRight, lineID)
{
}

CS2_Line::CS2_Line(LINEINFO & _LineInfo)
	: m_tLineInfo(_LineInfo)
{

}

CS2_Line::~CS2_Line()
{
	Release();
}

void CS2_Line::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	MoveToEx(hDC, (int)m_tLineInfo.tLPoint.fX+ iScrollX, (int)m_tLineInfo.tLPoint.fY+ iScrollY, nullptr);
	LineTo(hDC, (int)m_tLineInfo.tRPoint.fX+ iScrollX, (int)m_tLineInfo.tRPoint.fY+ iScrollY);
}

void CS2_Line::Release(void)
{
}
