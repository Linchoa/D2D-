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

	GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
		int(m_tInfo.vPos.x - 150),			// 2,3 ���� :  ������� ��ġ X, Y
		int(m_tInfo.vPos.y - 50),
		int(300),				// 4,5 ���� : ������� ����, ���� ����
		int(100),
		hMemDC,							// ��Ʈ���� ������ �ִ� DC
		m_iDrawID * 300,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
		0,
		300,				// ������ ��Ʈ���� ����, ���� ����
		100,
		RGB(255, 255, 255));			// �����ϰ��� �ϴ� ����
}

void CMyButton::Release(void)
{
}
