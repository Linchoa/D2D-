#include "stdafx.h"
#include "Stage2.h"
#include "S2_CObjMgr.h"
#include "S2_Player.h"
#include "S2_Obstacle.h"
#include "S2_LineMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "ScrollMgr.h"
#include "C2_Goal.h"
CStage2::CStage2()
{
}


CStage2::~CStage2()
{
	Release();
}

void CStage2::Initialize(void)
{
	/*CS2_CObjMgr::Get_Instance();*/

	CS2_CObjMgr::Get_Instance()->Add_Object(CSC_Obj::OBJ_ITEM, CFac<C2_Goal>::Create());
	CS2_CObjMgr::Get_Instance()->Add_Object(CSC_Obj::OBJ_PLAYER, CFac<CS2_Player>::Create());
	m_pLineList = CS2_LineMgr::Get_Instance()->Get_Line_List();
	m_iClickNumber = 0;
	m_Line[0].fX = 195.f;
	m_Line[0].fY = 752.f;
	m_Line[1].fX = 303.f;
	m_Line[1].fY = 752.f;
	m_lineID = LINE_DOWN;
	m_pLineList[m_lineID].push_back(new CS2_Line(m_Line[LINE_LR_LEFT], m_Line[LINE_LR_RIGHT], m_lineID));
	m_lineID = LINE_UP;
	m_Line[0].fX = 195.f;
	m_Line[0].fY = 352.f;
	m_Line[1].fX = 303.f;
	m_Line[1].fY = 352.f;
	m_pLineList[m_lineID].push_back(new CS2_Line(m_Line[LINE_LR_LEFT], m_Line[LINE_LR_RIGHT], m_lineID));
	CScrollMgr::Get_Instance()->Reset();
	m_iPage = 0;
	m_ftime = GetTickCount();
	m_iScore = 1000;
}

void CStage2::Update(void)
{
	Key_Input();
	if (m_iScore&&m_iPage==0)
	{
		CS2_CObjMgr::Get_Instance()->Update();
		if (CS2_CObjMgr::Get_Instance()->Get_List(CSC_Obj::OBJ_PLAYER)->empty() == 0)
		{
 			if (dynamic_cast<CS2_Player*>(CS2_CObjMgr::Get_Instance()->Get_List(CSC_Obj::OBJ_PLAYER)->back())->Get_Score())
			{
				m_iScore -= 10;
				dynamic_cast<CS2_Player*>(CS2_CObjMgr::Get_Instance()->Get_List(CSC_Obj::OBJ_PLAYER)->back())->Zero_Score();
			}
			m_iScore = m_iScore > 0 ? m_iScore - ((GetTickCount() - m_ftime))*0.0000004f : 0;
		}
	}
}

void CStage2::Late_Update(void)
{
	float r = 0;
	float fwhat = CS2_LineMgr::Get_Instance()->Collision_Down(CS2_CObjMgr::Get_Instance()->Get_List(CSC_Obj::OBJ_PLAYER)->back());
	if (fwhat)
	{
		float fd = dynamic_cast<CS2_Player*>(CS2_CObjMgr::Get_Instance()->Get_List(CSC_Obj::OBJ_PLAYER)->back())->Get_Degree();
		float add = (fd == 3 || fd == 1) ? 20 : 50;
		float y = CS2_CObjMgr::Get_Instance()->Get_List(CSC_Obj::OBJ_PLAYER)->back()->Get_Info().vPos.y + add;


		r = (float)fwhat - y;
		r = r > -100 ? r : 0;
		if (r < 0/*&&( fd==4|| fd == 0)*/)
		{
			CS2_CObjMgr::Get_Instance()->Get_List(CSC_Obj::OBJ_PLAYER)->back()->Add_PosY(r);
			CS2_CObjMgr::Get_Instance()->Get_List(CSC_Obj::OBJ_PLAYER)->back()->Update();
			
			dynamic_cast<CS2_Player*>(CS2_CObjMgr::Get_Instance()->Get_List(CSC_Obj::OBJ_PLAYER)->back())->SetZeroTime();
		}
		m_iScore += 1;
	}

	fwhat = CS2_LineMgr::Get_Instance()->Collision_Up(CS2_CObjMgr::Get_Instance()->Get_List(CSC_Obj::OBJ_PLAYER)->back());
	if (fwhat)
	{
		float fd = dynamic_cast<CS2_Player*>(CS2_CObjMgr::Get_Instance()->Get_List(CSC_Obj::OBJ_PLAYER)->back())->Get_Degree();
		float add = (fd == 3 || fd == 1) ? 20 : 51;
		float y = CS2_CObjMgr::Get_Instance()->Get_List(CSC_Obj::OBJ_PLAYER)->back()->Get_Info().vPos.y - add;
		r = (float)fwhat - y;
		if (fwhat&&fwhat>y/*-54*//*&&fd==2*/)
		{
			CS2_CObjMgr::Get_Instance()->Get_List(CSC_Obj::OBJ_PLAYER)->back()->Add_PosY(+r);
			CS2_CObjMgr::Get_Instance()->Get_List(CSC_Obj::OBJ_PLAYER)->back()->Update();
			dynamic_cast<CS2_Player*>(CS2_CObjMgr::Get_Instance()->Get_List(CSC_Obj::OBJ_PLAYER)->back())->SetZeroTime();
		}
		m_iScore += 1;
	}

	fwhat = CS2_LineMgr::Get_Instance()->Collision_Left(CS2_CObjMgr::Get_Instance()->Get_List(CSC_Obj::OBJ_PLAYER)->back());
	if (fwhat)
	{
		/*float x = CS2_CObjMgr::Get_Instance()->Get_List(CSC_Obj::OBJ_PLAYER)->back()->Get_Info().vPos.x - 50;
		float fd = dynamic_cast<CS2_Player*>(CS2_CObjMgr::Get_Instance()->Get_List(CSC_Obj::OBJ_PLAYER)->back())->Get_Degree();*/
		float fd = dynamic_cast<CS2_Player*>(CS2_CObjMgr::Get_Instance()->Get_List(CSC_Obj::OBJ_PLAYER)->back())->Get_Degree();
		float add = (fd == 3 || fd == 1) ? 51 : 20;
		float x = CS2_CObjMgr::Get_Instance()->Get_List(CSC_Obj::OBJ_PLAYER)->back()->Get_Info().vPos.x - add;
		r = (float)fwhat - x;
		r = r < 100 ? r : 0;

		if (fwhat&&fwhat > x /*&& fd==3*/)
		{
			CS2_CObjMgr::Get_Instance()->Get_List(CSC_Obj::OBJ_PLAYER)->back()->Add_posX(r);
			CS2_CObjMgr::Get_Instance()->Get_List(CSC_Obj::OBJ_PLAYER)->back()->Update();
			dynamic_cast<CS2_Player*>(CS2_CObjMgr::Get_Instance()->Get_List(CSC_Obj::OBJ_PLAYER)->back())->SetZeroTime();
		}
		m_iScore += 1;
	}

	fwhat = CS2_LineMgr::Get_Instance()->Collision_Right(CS2_CObjMgr::Get_Instance()->Get_List(CSC_Obj::OBJ_PLAYER)->back());
	if (fwhat)
	{
		/*float x = CS2_CObjMgr::Get_Instance()->Get_List(CSC_Obj::OBJ_PLAYER)->back()->Get_Info().vPos.x - 50;
		float fd = dynamic_cast<CS2_Player*>(CS2_CObjMgr::Get_Instance()->Get_List(CSC_Obj::OBJ_PLAYER)->back())->Get_Degree();*/
		float fd = dynamic_cast<CS2_Player*>(CS2_CObjMgr::Get_Instance()->Get_List(CSC_Obj::OBJ_PLAYER)->back())->Get_Degree();
		float add = (fd == 3 || fd == 1) ? 50 : 20;
		float x = CS2_CObjMgr::Get_Instance()->Get_List(CSC_Obj::OBJ_PLAYER)->back()->Get_Info().vPos.x + add;
		r = (float)fwhat - x;
		r = r < 100 ? r : 0;

		if (fwhat&&fwhat < x /*&& fd == 3*/)
		{
			CS2_CObjMgr::Get_Instance()->Get_List(CSC_Obj::OBJ_PLAYER)->back()->Add_posX(r);
			CS2_CObjMgr::Get_Instance()->Get_List(CSC_Obj::OBJ_PLAYER)->back()->Update();
			dynamic_cast<CS2_Player*>(CS2_CObjMgr::Get_Instance()->Get_List(CSC_Obj::OBJ_PLAYER)->back())->SetZeroTime();
		}
		m_iScore += 1;
	}


	m_iPage = CS2_CObjMgr::Get_Instance()->Late_Update();
	if (m_iPage == 1)
	{
		//CS2_CObjMgr::Get_Instance()->Destroy_Instance();
		//	CS2_CObjMgr::Get_Instance()->Delete_ID(CSC_Obj::OBJ_ITEM);
		CS2_LineMgr::Get_Instance()->DeleteAll();
	}
}

void CStage2::Render(HDC hDC)
{
	if (m_iPage == 1)
	{
		HFONT Font, oldFont;
		TCHAR		szBuff[124] = L"";
		Font = CreateFont(100, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, _T("µ¸¿òÃ¼"));
		oldFont = (HFONT)SelectObject(hDC, Font);

		swprintf_s(szBuff, L"Score %d", m_iScore);
		SetTextColor(hDC, RGB(0, 0, 0));
		TextOut(hDC, 50, WINCY / 2, szBuff, lstrlen(szBuff));
		Font = (HFONT)SelectObject(hDC, oldFont);

		Font = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, _T("µ¸¿òÃ¼"));
		oldFont = (HFONT)SelectObject(hDC, Font);

		swprintf_s(szBuff, L"Click the mouse to play a new game");
		SetTextColor(hDC, RGB(0, 0, 0));
		TextOut(hDC, 70, 500, szBuff, lstrlen(szBuff));
		oldFont = (HFONT)SelectObject(hDC, Font);
		Font = (HFONT)SelectObject(hDC, oldFont);
	}
	else if (m_iScore)
	{
		Rectangle(hDC, 0, 0, WINCX, WINCY);
		CS2_CObjMgr::Get_Instance()->Render(hDC);
		CS2_LineMgr::Get_Instance()->Render(hDC);

		TCHAR		szBuff[32] = L"";
		swprintf_s(szBuff, L"Score : %d", m_iScore);
		SetTextColor(hDC, RGB(0, 0, 0));
		TextOut(hDC, 30, 50, szBuff, lstrlen(szBuff));

		swprintf_s(szBuff, L"Time : %.2f", ((GetTickCount() - m_ftime) / 1000));
		SetTextColor(hDC, RGB(0, 0, 0));
		TextOut(hDC, 30, 70, szBuff, lstrlen(szBuff));
	}
	else
	{
		HFONT Font, oldFont;
		TCHAR		szBuff[124] = L"";
		Font = CreateFont(100, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, _T("µ¸¿òÃ¼"));
		oldFont = (HFONT)SelectObject(hDC, Font);

		swprintf_s(szBuff, L"GameOver");
		SetTextColor(hDC, RGB(0, 0, 0));
		TextOut(hDC, 50, WINCY / 2, szBuff, lstrlen(szBuff));
		Font = (HFONT)SelectObject(hDC, oldFont);

		Font = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, _T("µ¸¿òÃ¼"));
		oldFont = (HFONT)SelectObject(hDC, Font);

		swprintf_s(szBuff, L"Click the mouse to play a new game");
		SetTextColor(hDC, RGB(0, 0, 0));
		TextOut(hDC, 70, 500, szBuff, lstrlen(szBuff));
		oldFont = (HFONT)SelectObject(hDC, Font);
		Font = (HFONT)SelectObject(hDC, oldFont);
	}

}

void CStage2::Release(void)
{
	CS2_CObjMgr::Get_Instance()->Destroy_Instance();
	CS2_LineMgr::Get_Instance()->Destroy_Instance();
}

void CStage2::Key_Input(void)
{
	if (m_iScore && m_iPage==0)
	{
		if (CKeyMgr::Get_Instance()->Key_Down('S'))
		{
			m_lineID = LINE_DOWN;
			m_iClickNumber = 0;
		}
		else if (CKeyMgr::Get_Instance()->Key_Down('W'))
		{
			m_lineID = LINE_UP;
			m_iClickNumber = 0;
		}
		else if (CKeyMgr::Get_Instance()->Key_Down('A'))
		{
			m_lineID = LINE_LEFT;
			m_iClickNumber = 0;
		}
		else if (CKeyMgr::Get_Instance()->Key_Down('D'))
		{
			m_lineID = LINE_RIGHT;
			m_iClickNumber = 0;
		}
		if (CKeyMgr::Get_Instance()->Key_Down('Z'))
		{
			if (!m_pLineList[m_lineID].empty())
			{
				m_pLineList[m_lineID].pop_back();
			}
		}
		if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		{
			POINT	pt;
			GetCursorPos(&pt);
			ScreenToClient(g_hWnd, &pt);
			pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
			pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();
			switch (m_lineID)
			{
			case LINE_DOWN:
			case LINE_UP:
				m_Line[m_iClickNumber].fX = pt.x;
				m_Line[m_iClickNumber++].fY = m_iClickNumber >= 1 ? m_Line[m_iClickNumber - 1].fY : pt.y;
				break;
			case LINE_LEFT:
			case LINE_RIGHT:
				m_Line[m_iClickNumber].fX = m_iClickNumber >= 1 ? m_Line[m_iClickNumber - 1].fX : pt.x;
				m_Line[m_iClickNumber++].fY = pt.y;
				break;
			}




		}
		if (m_iClickNumber == 2)
		{
			m_pLineList[m_lineID].push_back(new CS2_Line(m_Line[LINE_LR_LEFT], m_Line[LINE_LR_RIGHT], m_lineID));
		}

		m_iClickNumber = m_iClickNumber >= 2 ? 0 : m_iClickNumber;
		

	}
	else
	{
		if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		{
			CSceneMgr::Get_Instance()->Scene_Change(SC_MENU);
		}
	}
}
