#include "stdafx.h"
#include "S2_LineMgr.h"
#include "S2_Player.h"
#include "ScrollMgr.h"

CS2_LineMgr*		CS2_LineMgr::m_pInstance = nullptr;
CS2_LineMgr::CS2_LineMgr()
{

}

CS2_LineMgr::~CS2_LineMgr()
{
	Release();
}
void CS2_LineMgr::Initialize(void)
{
	m_hPen[LINE_DOWN] = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	m_hPen[LINE_UP] = CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
	m_hPen[LINE_LEFT] = CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
	m_hPen[LINE_RIGHT] = CreatePen(PS_SOLID, 3, RGB(255, 255, 255));
	ZeroMemory(m_Set, sizeof(m_Set));
}

void CS2_LineMgr::Render(HDC hDC)
{
	HGDIOBJ hpenOld;
	TCHAR str[32];
	RECT Re;

	//int sx = CS2_LineMgr::Get_Instance()->Get_ScrollX();
	//int sy = CS2_LineMgr::Get_Instance()->Get_ScrollY();
	for (size_t i = 0; i < LINE_RIGHT + 1; ++i)
	{
		int count = 0;
		hpenOld = SelectObject(hDC, m_hPen[i]);
		for (auto& iter : m_LineList[i])
		{
			iter->Render(hDC);
			wsprintf(str, TEXT("%d"), count);
			Re = RECT{ LONG(iter->Get_Line()->tLPoint.fX) ,LONG(iter->Get_Line()->tLPoint.fY - 30 ) ,LONG(iter->Get_Line()->tRPoint.fX + 30 ), LONG(iter->Get_Line()->tRPoint.fY ) };




			count++;

		}
		wsprintf(str, TEXT("%d : %d"), i, count);
		Re = RECT{ 0 ,LONG(300 + (100 * i)) ,200, LONG(400 + (100 * i)) };




		m_hPen[i] = (HPEN)SelectObject(hDC, hpenOld);

	}

}

void CS2_LineMgr::Release(void)
{
	for (size_t i = 0; i < LINE_END; ++i)
	{
		for (auto& iter : m_LineList[i])
		{
			delete iter;
			iter = nullptr;
		}
		m_LineList[i].clear();
	}
	for (int i = 0; i < LINE_RIGHT + 1; ++i)
	{
		DeleteObject(m_hPen[i]);
	}
}

void CS2_LineMgr::DeleteAll(void)
{
	for (size_t i = 0; i < LINE_END; ++i)
	{
		for (auto& iter : m_LineList[i])
		{
			delete iter;
			iter = nullptr;
		}
		m_LineList[i].clear();
	}
	for (int i = 0; i < LINE_RIGHT + 1; ++i)
	{
		DeleteObject(m_hPen[i]);
	}
}

LINEID CS2_LineMgr::Collision_Line(float* fX, float* fY, float* pY, float* pX)
{
	/*if (Collision_Down(fX, fY, pY, pX))
	{
	return LINE_DOWN;
	}
	if (Collision_Up(fX, fY, pY, pX))
	{
	return LINE_UP;
	}
	if (Collision_Left(fX, fY, pY, pX))
	{
	return LINE_LEFT;
	}
	if (Collision_Right(fX, fY, pY, pX))
	{
	return LINE_RIGHT;
	}
	return LINE_END;*/
	return LINE_END;
}





float CS2_LineMgr::Collision_Down(CSC_Obj* _Player)
{
	if (m_LineList[LINE_DOWN].empty())
	{
		return false;
	}

	SetColisionPos(_Player);

	CS2_Line*		pTarget = nullptr;
	int iScrollY =  (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	iScrollY *= -1;
	float iTemp = 0.f;
	float ichai = 400.f;

	

	for (auto& iter : m_LineList[LINE_DOWN])
	{
		int y = (*iter->Get_Line()).tLPoint.fY;
		if (iScrollY - WINCY < y && y < iScrollY + WINCY)
		{
			float tLPointY = (*iter->Get_Line()).tLPoint.fY;
			
			if (tLPointY >m_Set[LINE_DOWN]/* bottom*/ - 10)
			{
				if (m_Set[LINE_RIGHT] >(*iter->Get_Line()).tLPoint.fX &&
					m_Set[LINE_LEFT] < (*iter->Get_Line()).tRPoint.fX)
				{
					
					iTemp = (*iter->Get_Line()).tLPoint.fY - m_Set[LINE_DOWN];
					iTemp = abs(iTemp);
					pTarget = ichai > iTemp ? iter : pTarget;
					ichai = ichai > iTemp ? iTemp : ichai;

				}
			}

		}
	}


	if (!pTarget)
		return 0.f;

	float	x1 = (*pTarget->Get_Line()).tLPoint.fX;
	float	x2 = (*pTarget->Get_Line()).tRPoint.fX;

	float	y1 = (*pTarget->Get_Line()).tLPoint.fY;
	float	y2 = (*pTarget->Get_Line()).tRPoint.fY;
	int R = ((y2 - y1) / (x2 - x1)) * (m_Set[LINE_DOWN] - x1) + y1;
	return ((y2 - y1) / (x2 - x1)) * (m_Set[LINE_DOWN] - x1) + y1;
}
float CS2_LineMgr::Collision_Up(CSC_Obj* _Player)
{
	if (m_LineList[LINE_UP].empty())
	{
		return false;
	}

	SetColisionPos(_Player);
	CS2_Line*		pTarget = nullptr;
	int ichai = 500;
	int iTemp = 0;
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	iScrollY *= -1;
	for (auto& iter : m_LineList[LINE_UP])
	{
		int y = (*iter->Get_Line()).tLPoint.fY;
		if (iScrollY - WINCY < y && y < iScrollY + WINCY)
		{
			float tLPointfY = (*iter->Get_Line()).tLPoint.fY;
			
			//if (tLPointfY > top - 10)
			if (tLPointfY < m_Set[LINE_UP] + 10)
			{

				if(m_Set[LINE_RIGHT] >(*iter->Get_Line()).tLPoint.fX &&
					m_Set[LINE_LEFT] < (*iter->Get_Line()).tRPoint.fX)
				{
					iTemp = (*iter->Get_Line()).tLPoint.fY - m_Set[LINE_UP];
					iTemp = abs(iTemp);
					pTarget = ichai > iTemp ? iter : pTarget;
					ichai = ichai > iTemp ? iTemp : ichai;
					if (pTarget != nullptr)
					{
						int l = 0;
					}
				}
			}
		}
	}
	

	if (!pTarget)
	{
		return 0.f;
	}

	float	x1 = (*pTarget->Get_Line()).tLPoint.fX;
	float	x2 = (*pTarget->Get_Line()).tRPoint.fX;

	float	y1 = (*pTarget->Get_Line()).tLPoint.fY;
	float	y2 = (*pTarget->Get_Line()).tRPoint.fY;
	int R = ((y2 - y1) / (x2 - x1)) * (m_Set[LINE_UP] - x1) + y1;
	return ((y2 - y1) / (x2 - x1)) * (m_Set[LINE_UP] - x1) + y1;

}
float CS2_LineMgr::Collision_Left(CSC_Obj* _Player)
{

	SetColisionPos(_Player);
	if (m_LineList[LINE_LEFT].empty())
	{
		return false;
	}
	int ichai = 500;
	int iTemp = 0;
	CS2_Line*		pTarget = nullptr;
	int iScrollX =  (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	iScrollX *= -1;
	
	for (auto& iter : m_LineList[LINE_LEFT])
	{
		int x = (*iter->Get_Line()).tLPoint.fX;
		if (iScrollX - WINCX <x && x < iScrollX + WINCX)
		{
			/*if (*iter->Get_Line()).tLPoint.fX < _Player->Get_Rect().right)*/
			//if	(x < right && x > left)
			//if (tLPointfY < m_Set[LINE_UP] + 10)
			//if (tLPointY >m_Set[LINE_DOWN]/* bottom*/ - 10)
			if(x < m_Set[LINE_LEFT]+10)
			{
				float lineLY1 = (*iter->Get_Line()).tLPoint.fY;
				float lineLY2= (*iter->Get_Line()).tRPoint.fY;

				if (m_Set[LINE_DOWN] >= (*iter->Get_Line()).tLPoint.fY &&
					m_Set[LINE_UP]< (*iter->Get_Line()).tRPoint.fY)
				{
					iTemp = x - m_Set[LINE_LEFT];
					iTemp = abs(iTemp);
					pTarget = ichai > iTemp ? iter : pTarget;
					ichai = ichai > iTemp ? iTemp : ichai;
				}
			}
		}
	}


	if (!pTarget)
	{
		return 0.0f;
	}

	float	x1 = (*pTarget->Get_Line()).tLPoint.fX;
	float	x2 = (*pTarget->Get_Line()).tRPoint.fX;

	float	y1 = (*pTarget->Get_Line()).tLPoint.fY;
	float	y2 = (*pTarget->Get_Line()).tRPoint.fY;
	float fresult = ((x2 - x1)) / (y2 - y1) * (m_Set[LINE_LEFT] - y1) + x1;
	return ((x2 - x1)) / (y2 - y1) * (m_Set[LINE_LEFT] - y1) + x1;
}
float CS2_LineMgr::Collision_Right(CSC_Obj* _Player)
{
	if (m_LineList[LINE_RIGHT].empty())
	{
		return false;
	}
	SetColisionPos(_Player);
	CS2_Line*		pTarget = nullptr;
	int ichai = 500;
	int iTemp = 0;
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	iScrollX *= -1;
	for (auto& iter : m_LineList[LINE_RIGHT])
	{
		int x = (*iter->Get_Line()).tLPoint.fX;
		if (iScrollX - WINCX <x && x < iScrollX + WINCX)
		{
			//if (/*(*iter->Get_Line()).tLPoint.fX < _Player->Get_Rect().right &&*/
			//if (tLPointfY < m_Set[LINE_UP] + 10)
			//if (tLPointY >m_Set[LINE_DOWN]/* bottom*/ - 10)
			if(x > m_Set[LINE_RIGHT]-10)
			{
				if (m_Set[LINE_DOWN] >= (*iter->Get_Line()).tLPoint.fY &&
					m_Set[LINE_UP] < (*iter->Get_Line()).tRPoint.fY)
				{
					iTemp = (*iter->Get_Line()).tLPoint.fX - m_Set[LINE_RIGHT];
					iTemp = abs(iTemp);
					pTarget = ichai > iTemp ? iter : pTarget;
					ichai = ichai > iTemp ? iTemp : ichai;
				}
			}
		}
	}


	if (!pTarget)
	{
		return 0.f;
	}

	float	x1 = (*pTarget->Get_Line()).tLPoint.fX;
	float	x2 = (*pTarget->Get_Line()).tRPoint.fX;

	float	y1 = (*pTarget->Get_Line()).tLPoint.fY;
	float	y2 = (*pTarget->Get_Line()).tRPoint.fY;

	//*pY = ((y2 - y1) / (x2 - x1)) * (*fX - x1) + y1;
	return ((x2 - x1)) / (y2 - y1) * (m_Set[LINE_RIGHT] - y1) + x1;
}

void CS2_LineMgr::SetColisionPos(CSC_Obj * _Player)
{
	if (_Player != nullptr)
	{
		switch ((int)dynamic_cast<CS2_Player*>(_Player)->Get_Degree())
		{
		case 0:
		case 4:

			/*LINE_DOWN, LINE_UP, LINE_LEFT, LINE_RIGHT*/

			m_Set[LINE_LEFT] = _Player->Get_Info().vPos.x - 20;//left
			m_Set[LINE_UP] = _Player->Get_Info().vPos.y - 50;//top
			m_Set[LINE_RIGHT] = _Player->Get_Info().vPos.x + 20;//right
			m_Set[LINE_DOWN] = _Player->Get_Info().vPos.y + 50;//bottom;
			break;
		case 2:
			m_Set[LINE_LEFT] = _Player->Get_Info().vPos.x - 20;//left
			m_Set[LINE_UP] = _Player->Get_Info().vPos.y - 50;//top
			m_Set[LINE_RIGHT] = _Player->Get_Info().vPos.x + 20;//right
			m_Set[LINE_DOWN] = _Player->Get_Info().vPos.y + 50;//bottom;
			break;
		case 3:
		case 1:
			m_Set[LINE_LEFT] = _Player->Get_Info().vPos.x - 50;//left
			m_Set[LINE_UP] = _Player->Get_Info().vPos.y - 20;//top
			m_Set[LINE_RIGHT] = _Player->Get_Info().vPos.x + 50;//right
			m_Set[LINE_DOWN] = _Player->Get_Info().vPos.y + 20;//.bottom;
			break;
		}
	}
}






//void CS2_LineMgr::Load_File(void)
//{
//	HANDLE	hFile = CreateFile(L"../Data/Line.dat",	// 파일 경로와 이름을 명시하는 매개변수
//		GENERIC_READ,		// 모드 지정, GENERIC_WRITE(쓰기), GENERIC_READ(읽기)
//		NULL,				// 공유 방식, 파일이 열려 있는 상태에서 다른 프로세스가 오픈할 때 허용을 할 것인가, NULL로 지정 시 공유하지 않음
//		NULL,				// 보안 속성, NULL인 경우 기본 값으로 설정
//		OPEN_EXISTING,		// 파일 생성 방식, 해당 파일을 열어서 작업할 것인지 아니면 새로 만들 것인지 설정 CREATE_ALWAYS(쓰기 전용) : 파일이 없다면 생성, 있으면 덮어쓰기,  OPEN_EXISTING(읽기 전용) : 파일이 있을 경우에만 연다
//		FILE_ATTRIBUTE_NORMAL, // 파일 속성 지정, FILE_ATTRIBUTE_NORMAL : 아무런 속성이 없는 일반적인 파일 생성
//		NULL);					// 생성될 파일의 속성을 제공할 템플릿 파일, 우린 안 쓰니 NULL
//
//	if (INVALID_HANDLE_VALUE == hFile)
//	{
//		MessageBox(g_hWnd, L"Load File", L"Error", MB_OK);
//		return;
//	}
//	// 0. 메모리 제거
//	for (size_t i = 0; i < LINE_END; ++i)
//	{
//		for (auto& iter : m_LineList[i])
//		{
//			delete iter;
//			iter = nullptr;
//		}
//		m_LineList[i].clear();
//	}
//
//	// 2. 파일 쓰기
//
//	DWORD	dwByte = 0;
//
//	LINEINFO		tInfo{};
//
//	while (true)
//	{
//		ReadFile(hFile, &tInfo, sizeof(LINEINFO), &dwByte, nullptr);
//
//		if (0 == dwByte)
//		{
//			break;
//		}
//		LINEID lineID = tInfo.line_id;
//		m_LineList[lineID].push_back(new CLine(tInfo.tLPoint, tInfo.tRPoint, lineID));
//	}
//
//
//	// 3. 개방한 파일 소멸하기
//	CloseHandle(hFile);
//
//
//#ifdef _DEBUG
//	MessageBox(g_hWnd, L"Load Line 성공", L"성공", MB_OK);
//#endif // _DEBUG
//
//
//}