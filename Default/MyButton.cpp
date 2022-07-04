#include "stdafx.h"
#include "MyButton.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"


CMyButton::CMyButton()
{
}


CMyButton::~CMyButton()
{

}

void CMyButton::Initialize(void)
{
}

int CMyButton::Update(void)
{
	return OBJ_NOEVENT;
}

void CMyButton::Late_Update(void)
{
	POINT		Pt;
	GetCursorPos(&Pt);
	ScreenToClient(g_hWnd, &Pt);

	RECT rect = { m_tInfo.vPos.x - 150, m_tInfo.vPos.y - 50, m_tInfo.vPos.x + 150, m_tInfo.vPos.y + 50 };

	if (PtInRect(&rect, Pt))
	{
		if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		{
			if (!lstrcmp(L"Stage1", m_pFrameKey))
				CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE1);

			else if (!lstrcmp(L"Stage2", m_pFrameKey))
				CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE2);

			else if(!lstrcmp(L"Stage3", m_pFrameKey))
				CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE3);

			return;
		}

		m_iDrawID = 1;
	}
	else
		m_iDrawID = 0;
}

void CMyButton::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tInfo.vPos.x - 150),			// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tInfo.vPos.y - 50),
		int(300),				// 4,5 인자 : 복사받을 가로, 세로 길이
		int(100),
		hMemDC,							// 비트맵을 가지고 있는 DC
		m_iDrawID * 300,								// 비트맵 출력 시작 좌표, X,Y
		0,
		300,				// 복사할 비트맵의 가로, 세로 길이
		100,
		RGB(255, 255, 255));			// 제거하고자 하는 색상
}

void CMyButton::Release(void)
{
}
