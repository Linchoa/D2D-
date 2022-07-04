#include "stdafx.h"
#include "C2_Goal.h"
#include "ScrollMgr.h"

C2_Goal::C2_Goal()
{
}


C2_Goal::~C2_Goal()
{
}

void C2_Goal::Initialize(void)
{
	m_tInfo.vPos = { 1000.f, -1000.f, 0.f };
	m_tInfo.vLook = { -1.f, 0.f, 0.f };

	m_vPoint[0] = { m_tInfo.vPos.x - 50, m_tInfo.vPos.y - 50, 0.f };
	m_vPoint[1] = { m_tInfo.vPos.x + 50, m_tInfo.vPos.y - 50, 0.f };
	m_vPoint[2] = { m_tInfo.vPos.x + 50, m_tInfo.vPos.y + 50, 0.f };
	m_vPoint[3] = { m_tInfo.vPos.x - 50, m_tInfo.vPos.y + 50, 0.f };

	for (int i = 0; i < 4; ++i)
		m_vOriginPoint[i] = m_vPoint[i];

	m_fSpeed = 0.5f;
}

int C2_Goal::Update(void)
{
	return 0;
}

void C2_Goal::Late_Update(void)
{
}

void C2_Goal::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	MoveToEx(hDC, m_vPoint[0].x + iScrollX, m_vPoint[0].y + iScrollY, nullptr);

	for (int i = 0; i < 4; ++i)
	{
		LineTo(hDC, m_vPoint[i].x + iScrollX, m_vPoint[i].y + iScrollY);
	}
	LineTo(hDC, m_vPoint[0].x + iScrollX, m_vPoint[0].y + iScrollY);
}

void C2_Goal::Release(void)
{
}
