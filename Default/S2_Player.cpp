#include "stdafx.h"
#include "S2_Player.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include <iostream>
#include "S2_CObjMgr.h"

CS2_Player::CS2_Player()
{
}


CS2_Player::~CS2_Player()
{
}

void CS2_Player::Initialize(void)
{


	m_tInfo.vPos = { 250.f, 700.f, 0.f };
	m_tInfo.vLook = { -1.f, 0.f, 0.f };
	m_fDegree = 0.f;

	m_vPoint[0] = { m_tInfo.vPos.x - PLAYER_X, m_tInfo.vPos.y - PLAYER_Y, 0.f };
	m_vPoint[1] = { m_tInfo.vPos.x + PLAYER_X, m_tInfo.vPos.y - PLAYER_Y, 0.f };
	m_vPoint[2] = { m_tInfo.vPos.x + PLAYER_X, m_tInfo.vPos.y + PLAYER_Y, 0.f };
	m_vPoint[3] = { m_tInfo.vPos.x - PLAYER_X, m_tInfo.vPos.y + PLAYER_Y, 0.f };

	for (int i = 0; i < 4; ++i)
		m_vOriginPoint[i] = m_vPoint[i];

	m_vTarget.vPos = { 100.f, 100.f, 0.f };


	//m_vGunPoint = { m_tInfo.vPos.x, m_tInfo.vPos.y - 100.f, 0.f };
	//m_vOriginGunPoint = m_vGunPoint;


	m_fSpeed = 0.5f;

	m_fTime=0.f;
	m_fPast_move = m_tInfo.vLook.x;
	m_fPostX = m_tInfo.vPos.x;
	m_fPostY = m_tInfo.vPos.y;
	m_iScore = 0;

}

int CS2_Player::Update(void)
{
	CScrollMgr::Get_Instance()->Set_ScrollY(1.f);
	CScrollMgr::Get_Instance()->Set_ScrollX(-0.7f);

	/*if (fabsf(m_fPostX - m_tInfo.vPos.x) <=FLT_EPSILON)
	{

	}
	else
	{
		CScrollMgr::Get_Instance()->Set_ScrollX(m_fPostX - m_tInfo.vPos.x);
		m_fPostX = m_tInfo.vPos.x;
	}
	if (fabsf(m_fPostY - m_tInfo.vPos.y) <= FLT_EPSILON)
	{

	}
	else
	{
		CScrollMgr::Get_Instance()->Set_ScrollY(m_fPostY - m_tInfo.vPos.y);
		m_fPostY = m_tInfo.vPos.y;
	}*/



	//m_vTarget.vPos = m_tInfo.vPos;
	//m_vTarget.vDir = CS2_CObjMgr::Get_Instance()->Get_List(CSC_Obj::OBJ_ITEM)->back()->Get_Info().vPos - m_vTarget.vPos;
	//cout << "m_vTarget.vDir.x" << m_vTarget.vDir.x << endl;
	//cout << "m_vTarget.vDir.y" << m_vTarget.vDir.y << endl;
	//float		fLength = sqrtf(m_vTarget.vDir.x * m_vTarget.vDir.x + m_vTarget.vDir.y * m_vTarget.vDir.y);
	//
	//m_vTarget.vDir.x;// /= fLength;
	//m_vTarget.vDir.y;// /= fLength;
	//m_vTarget.vDir.z = 0.f;


	//m_vTarget.vPos += m_vTarget.vDir * m_fSpeed;

	/*D3DXVECTOR3 r = CS2_CObjMgr::Get_Instance()->Get_List(CSC_Obj::OBJ_ITEM)->back()->Get_Info().vPos;
	float xxx = r.x;
	float yyy = r.y;
	cout << "m_tInfo.vPos.x " << m_tInfo.vPos.x << endl;
	cout << "m_tInfo.vPos.y " << m_tInfo.vPos.y << endl;
	m_vTarget.vPos = m_tInfo.vPos;
	m_vTarget.vDir = CS2_CObjMgr::Get_Instance()->Get_List(CSC_Obj::OBJ_ITEM)->back()->Get_Info().vPos - m_vTarget.vPos;
	D3DXVec3Normalize(&m_vTarget.vDir, &m_vTarget.vDir);
	D3DXVec3Normalize(&m_vTarget.vLook, &m_vTarget.vLook);
	float fDot = D3DXVec3Dot(&m_vTarget.vDir, &m_vTarget.vLook);
	float	fAngle = acosf(fDot);
	if (m_vTarget.vPos.y < ::Get_Mouse().y)
		fAngle = 2.f * D3DX_PI - fAngle;

	m_vTarget.vPos.x = cosf(fAngle) * 50.f;
	m_vTarget.vPos.y = sinf(fAngle) * 50.f;*/

	//cout << "scroll X:" << iScrollX << endl;
	//cout << "scroll Y:" << iScrollY << endl;
	//D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
	//D3DXVec3Normalize(&m_tInfo.vLook, &m_tInfo.vLook);
	//float fDot = D3DXVec3Dot(&m_tInfo.vDir, &m_tInfo.vLook);

	m_tInfo.vLook.x = m_fTime > 0.16f ? 0 : m_fPast_move;

	Key_Input();
	Gravity();

	D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);

	m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
	m_tInfo.vLook.x;
	//CScrollMgr::Get_Instance()->Set_ScrollX(posX- m_tInfo.vPos.x);
	//CScrollMgr::Get_Instance()->Set_ScrollY(posY - m_tInfo.vPos.y);
	//CScrollMgr::Get_Instance()->Set_ScrollY(m_tInfo.vLook.y*m_fSpeed);

	D3DXMATRIX	matScale, matRotZ, matTrans;


	if (m_fDegree)
	{

		D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
		D3DXMatrixRotationZ(&matRotZ, m_fAngle);
		D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

		D3DXMATRIX m_rot;
		D3DXMatrixRotationZ(&m_rot, 90.f* m_fDegree*D3DX_PI / 180.f);
		m_tInfo.matWorld = matScale * matRotZ  *m_rot * matTrans;
	}
	else {
		D3DXMatrixScaling(&matScale, -1.f, 1.f, 1.f);
		D3DXMatrixRotationZ(&matRotZ, m_fAngle);
		D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

		D3DXMATRIX m_rot;
		D3DXMatrixRotationZ(&m_rot, m_fDegree*90.f*PI / 180.f);
		m_tInfo.matWorld = matScale * matRotZ * matTrans;
	}
	for (int i = 0; i < 4; ++i)
	{
		m_vPoint[i] = m_vOriginPoint[i];
		m_vPoint[i] -= {250.f, 700.f, 0.f };

		D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_tInfo.matWorld);
	}



	//D3DXVec3TransformCoord(&m_vGunPoint, &m_vGunPoint, &m_tInfo.matWorld);

	//m_tInfo.vDir = ::Get_Mouse() - m_tInfo.vPos;
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	if (m_tInfo.vPos.y + iScrollY > WINCY)
	{
		m_iScore = 1;
	}
	else if (m_tInfo.vPos.x + iScrollX > WINCX)
	{
		m_iScore = 1;
	}
	else if (m_tInfo.vPos.x < 50)
	{
		m_iScore = 1;
	}
	else if (m_tInfo.vPos.x > WINCX - 50)
	{
		
	}

	return 0;
	

}

void CS2_Player::Late_Update(void)
{
	

}

void CS2_Player::Render(HDC hDC)
{
	
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	MoveToEx(hDC, m_vPoint[0].x+ iScrollX, m_vPoint[0].y+ iScrollY, nullptr);
	
	for (int i = 0; i < 4; ++i)
	{
		LineTo(hDC, m_vPoint[i].x+ iScrollX, m_vPoint[i].y+ iScrollY);
	}
	LineTo(hDC, m_vPoint[0].x+ iScrollX, m_vPoint[0].y+ iScrollY);

	MoveToEx(hDC, m_tInfo.vPos.x+ iScrollX, m_tInfo.vPos.y+ iScrollY, nullptr);
	float target_x = CS2_CObjMgr::Get_Instance()->Get_List(CSC_Obj::OBJ_ITEM)->back()->Get_Info().vPos.x;
	float target_y = CS2_CObjMgr::Get_Instance()->Get_List(CSC_Obj::OBJ_ITEM)->back()->Get_Info().vPos.y;

	LineTo(hDC, target_x + iScrollX, target_y + iScrollY);
	TCHAR		szBuff[32] = L"";
	swprintf_s(szBuff, L"x : %.2f", (target_x-m_tInfo.vPos.x));
	SetTextColor(hDC, RGB(255, 100, 100));
	TextOut(hDC, 30, 90, szBuff, lstrlen(szBuff));
	swprintf_s(szBuff, L"y : %.2f", (target_y - m_tInfo.vPos.y));
	SetTextColor(hDC, RGB(100, 100, 255));
	TextOut(hDC, 30, 110, szBuff, lstrlen(szBuff));
}

void CS2_Player::Release(void)
{
}

void CS2_Player::Key_Input(void)
{

	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
	{
			m_tInfo.vLook = { 0.f, -1.f, 0.f };
			D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
			m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
		
	}
	if (CKeyMgr::Get_Instance()->Key_Down(VK_DOWN))
	{
		m_tInfo.vLook = { 0.f, +1.f, 0.f };
		D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;


	}
	if (CKeyMgr::Get_Instance()->Key_Down('Q'))
	{
		m_fDegree = m_fDegree >= 4 ?1 : ++m_fDegree;
		
		//m_tInfo.vLook.x *= -1;
		
		/*m_tInfo.vPos.x += 10;
		m_tInfo.vPos.y -= 30;*/
		switch ((int)m_fDegree)
		{
		case 1:
			m_tInfo.vLook.x = -1;
			m_fPast_move = m_tInfo.vLook.x;
			m_tInfo.vPos.x -= PLAYER_X*2*0.75;
			m_tInfo.vPos.y += PLAYER_X * 2 * 0.75;
			break;
		case 2:
			m_tInfo.vLook.x = +1;
			m_fPast_move = m_tInfo.vLook.x;
			m_tInfo.vLook.y = 0;

			m_tInfo.vPos.x += PLAYER_X * 2 * 0.75;
			m_tInfo.vPos.y += PLAYER_X * 2 * 0.75;
			break;
		case 3:
			m_tInfo.vLook.x = -1;
			m_fPast_move = m_tInfo.vLook.x;
			m_tInfo.vLook.y = 0;

			m_tInfo.vPos.x += PLAYER_X * 2 * 0.75; 30;
			m_tInfo.vPos.y -= PLAYER_X * 2 * 0.75;
			break;
		case 4:
			m_tInfo.vLook.x = +1;
			m_fPast_move = m_tInfo.vLook.x;
			m_tInfo.vLook.y = 0;

			m_tInfo.vPos.x -= PLAYER_X * 2 * 0.75;
			m_tInfo.vPos.y -= PLAYER_X * 2 * 0.75;
			break;
		default:
			break;
		}
		
	}
	if (CKeyMgr::Get_Instance()->Key_Down('E'))
	{
		m_fDegree = m_fDegree <= 1 ? 4 : --m_fDegree;

		//m_tInfo.vLook.x *= -1;

		/*m_tInfo.vPos.x += 10;
		m_tInfo.vPos.y -= 30;*/
		switch ((int)m_fDegree)
		{
		case 1:
			m_tInfo.vLook.x = -1;
			m_fPast_move = m_tInfo.vLook.x;
			m_tInfo.vPos.x -= PLAYER_X * 2 * 0.75;
			m_tInfo.vPos.y += PLAYER_X * 2 * 0.75;
			break;
		case 2:
			m_tInfo.vLook.x = +1;
			m_fPast_move = m_tInfo.vLook.x;
			m_tInfo.vLook.y = 0;

			m_tInfo.vPos.x += PLAYER_X * 2 * 0.75;
			m_tInfo.vPos.y += PLAYER_X * 2 * 0.75;
			break;
		case 3:
			m_tInfo.vLook.x = -1;
			m_fPast_move = m_tInfo.vLook.x;
			m_tInfo.vLook.y = 0;

			m_tInfo.vPos.x += PLAYER_X * 2 * 0.75; 30;
			m_tInfo.vPos.y -= PLAYER_X * 2 * 0.75;
			break;
		case 4:
			m_tInfo.vLook.x = +1;
			m_fPast_move = m_tInfo.vLook.x;
			m_tInfo.vLook.y = 0;

			m_tInfo.vPos.x -= PLAYER_X * 2 * 0.75;
			m_tInfo.vPos.y -= PLAYER_X * 2 * 0.75;
			break;
		default:
			break;
		}

	}
	
}

void CS2_Player::Gravity(void)
{
	float m_fJumpPower = 0.5f;
	float calcule = m_fJumpPower - (9.8f* m_fTime);
	calcule = (calcule <= -8.f) ? -8.f : calcule;
	float posX = m_tInfo.vPos.x;
	float posY = m_tInfo.vPos.y;

	switch ((int)m_fDegree)
	{
	case 0:
		/*CScrollMgr::Get_Instance()->Set_ScrollY(+calcule);*/
		m_tInfo.vPos.y -= calcule;
		break;
	case 1:
		//CScrollMgr::Get_Instance()->Set_ScrollX(+calcule);
		m_tInfo.vPos.x -= calcule;
		break;
	case 2:
		//CScrollMgr::Get_Instance()->Set_ScrollY(-calcule);
		m_tInfo.vPos.y += calcule;
		break;
	case 3:
		//CScrollMgr::Get_Instance()->Set_ScrollX(-calcule);
		m_tInfo.vPos.x += calcule;
		break;
	case 4:
		//CScrollMgr::Get_Instance()->Set_ScrollY(+calcule);
		m_tInfo.vPos.y -= calcule;
		break;
	}
	//CScrollMgr::Get_Instance()->Set_ScrollX(posX- m_tInfo.vPos.x);
	m_fTime += 0.15f;
	
}
