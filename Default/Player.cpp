#include "stdafx.h"
#include "Player.h"
#include "SceneMgr.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"

CPlayer::CPlayer() : m_bJump(false), m_fSize(0.f), m_fJumpPower(0.f), m_fTime(0.f), m_bCollision(true)
{
	ZeroMemory(&m_iScore, sizeof(int) * 3);
}


CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize(void) 
{
	m_tInfo.vPos = { 250.f, 700.f, 0.f };

	m_fSpeed = 10.f;

	m_fJumpPower = 15.f;
}

int CPlayer::Update(void)
{
	switch (CSceneMgr::Get_Instance()->Get_Scene()) {
	case SC_STAGE1:

		break;
	case SC_STAGE2:
		break;
	case SC_STAGE3:
		Key_Input();
		Offset();
		Jumping();
		if (m_tInfo.vPos.y < -1300)
			CSceneMgr::Get_Instance()->Scene_Change(SC_MENU);
		break;
	}

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(void)
{
	switch (CSceneMgr::Get_Instance()->Get_Scene()) {
	case SC_STAGE1:
		break;
	case SC_STAGE2:
		break;
	case SC_STAGE3:
		m_fSize = 25.f;
		if (m_tInfo.vPos.x < 25)
			m_tInfo.vPos.x = 25;
		if (m_tInfo.vPos.x > 475)
			m_tInfo.vPos.x = 475;
		break;
	}
}

void CPlayer::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	switch (CSceneMgr::Get_Instance()->Get_Scene()) {
	case SC_STAGE1:
		break;
	case SC_STAGE2:
		break;
	case SC_STAGE3:
		Ellipse(hDC, m_tInfo.vPos.x - 25, m_tInfo.vPos.y - 25 + iScrollY, m_tInfo.vPos.x + 25, m_tInfo.vPos.y + 25 + iScrollY);
		break;
	}
}

void CPlayer::Key_Input(void)
{
	switch (CSceneMgr::Get_Instance()->Get_Scene()) {
	case SC_STAGE1:
		break;
	case SC_STAGE2:
		break;
	case SC_STAGE3:
		if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE) && !m_bJump) {
			m_bJump = true;
			m_bCollision = false;
		}
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT) || CKeyMgr::Get_Instance()->Key_Pressing('D')) {
			m_tInfo.vPos.x += m_fSpeed;
		}
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT) || CKeyMgr::Get_Instance()->Key_Pressing('A')) {
			m_tInfo.vPos.x -= m_fSpeed;
		}
		if (CKeyMgr::Get_Instance()->Key_Down(VK_DOWN) || CKeyMgr::Get_Instance()->Key_Down('S')) {

		}
		break;
	}
	//if (GetAsyncKeyState(VK_RIGHT))
	//	m_fAngle += D3DXToRadian(3.f);

	//if (GetAsyncKeyState(VK_LEFT))
	//	m_fAngle -= D3DXToRadian(3.f);
}

void CPlayer::Jumping(void)
{
	switch (CSceneMgr::Get_Instance()->Get_Scene()) {
	case SC_STAGE1:

		break;
	case SC_STAGE2:
		break;
	case SC_STAGE3:
		if (m_bJump) {
			float check = m_fJumpPower * m_fTime - (9.8f * m_fTime * m_fTime * 0.5f);
			m_tInfo.vPos.y -= check;
			m_fTime += 0.17f;
			if (check < 0)
				m_bCollision = true;
		}
		else {
			m_tInfo.vPos.y += 13;
		}
		break;
	}
}

void CPlayer::Offset(void)
{
	switch (CSceneMgr::Get_Instance()->Get_Scene()) {
	case SC_STAGE1:

		break;
	case SC_STAGE2:
		break;
	case SC_STAGE3:
		int iOffsetMinY = 600.f;
		int iOffsetMaxY = 700.f;

		int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		if (iOffsetMinY > m_tInfo.vPos.y + iScrollY)
			CScrollMgr::Get_Instance()->Set_ScrollY(m_fSpeed);

		if (iOffsetMaxY < m_tInfo.vPos.y + iScrollY)
			CScrollMgr::Get_Instance()->Set_ScrollY(-m_fSpeed);
		break;
	}
}

void CPlayer::Release(void)
{
}
