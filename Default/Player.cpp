#include "stdafx.h"
#include "Player.h"
#include "SceneMgr.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"

CPlayer::CPlayer() : m_bJump(false), m_fSize(0.f), m_fJumpPower(0.f), m_fTime(0.f), m_bCollision(true), m_bWin(false)
{
	ZeroMemory(&m_iScore, sizeof(int) * 3);
}


CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize(void) 
{
	m_tInfo.vPos = { 26.f, 774.f, 0.f };
	m_tInfo.vLook = { 1.f, 0.f, 0.f };


	m_vOriginPos = m_tInfo.vPos;

	m_fSpeed = 10.f;

	m_fJumpPower = 15.f;
}

int CPlayer::Update(void)
{
	D3DXMATRIX	matScale, matRotZ, matTrans;

	switch (CSceneMgr::Get_Instance()->Get_Scene()) {
	case SC_STAGE1:
		if (m_bDead)
			m_bDead = true;
		Key_Input();
		break;
	case SC_STAGE2:
		break;
	case SC_STAGE3:
		Key_Input();
		Offset();
		Jumping();

		D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
		D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

		m_tInfo.matWorld = matScale * matTrans;

		m_tInfo.vPos = m_vOriginPos;
		m_tInfo.vPos -= m_vOriginPos;

		D3DXVec3TransformCoord(&m_tInfo.vPos, &m_tInfo.vPos, &m_tInfo.matWorld);

		if (m_tInfo.vPos.y < -1300)
			m_bWin = true;

		int iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

		if (m_tInfo.vPos.y + iScrollY > 800)
			m_bDead = true;
		break;
	}

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(void)
{
	switch (CSceneMgr::Get_Instance()->Get_Scene()) {
	case SC_STAGE1:
		if (25.f >= m_tInfo.vPos.x)
			m_tInfo.vPos.x = 25.f;
		if (WINCX - 25.f <= m_tInfo.vPos.x)
			m_tInfo.vPos.x = WINCX - 25.f;
		break;
	case SC_STAGE2:
		break;
	case SC_STAGE3:
		m_fSize = 25.f;
		if (m_tInfo.vPos.x < m_fSize)
			m_tInfo.vPos.x = m_fSize;
		if (m_tInfo.vPos.x > WINCX - m_fSize)
			m_tInfo.vPos.x = WINCX - m_fSize;
		break;
	}
}

void CPlayer::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	switch (CSceneMgr::Get_Instance()->Get_Scene()) {
	case SC_STAGE1:
		Rectangle(hDC,
			int(m_tInfo.vPos.x - 25.f),
			int(m_tInfo.vPos.y - 25.f),
			int(m_tInfo.vPos.x + 25.f),
			int(m_tInfo.vPos.y + 25.f));
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
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT) || CKeyMgr::Get_Instance()->Key_Pressing('D'))
			m_tInfo.vPos.x += m_fSpeed;

		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT) || CKeyMgr::Get_Instance()->Key_Pressing('A'))
			m_tInfo.vPos.x -= m_fSpeed;
		break;
	case SC_STAGE2:
		break;
	case SC_STAGE3:
		if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE) && !m_bJump) {
			m_bJump = true;
			m_bCollision = false;
		}
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT) || CKeyMgr::Get_Instance()->Key_Pressing('D')) {
			m_tInfo.vLook = { 1.f, 0.f, 0.f };
			D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
			m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
		}
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT) || CKeyMgr::Get_Instance()->Key_Pressing('A')) {
			m_tInfo.vLook = { 1.f, 0.f, 0.f };
			D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
			m_tInfo.vPos -= m_tInfo.vDir * m_fSpeed;
		}
		if (CKeyMgr::Get_Instance()->Key_Down(VK_DOWN) || CKeyMgr::Get_Instance()->Key_Down('S')) {

		}
		break;
	}
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
			//m_tInfo.vPos.y -= check;

			m_tInfo.vLook = { 0.f, 1.f, 0.f };
			D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
			m_tInfo.vPos -= m_tInfo.vDir * check;

			m_fTime += 0.17f;
			if (check < 0)
				m_bCollision = true;
		}
		else {
			m_tInfo.vLook = { 0.f, 1.f, 0.f };
			D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
			m_tInfo.vPos += m_tInfo.vDir * 13.f;
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
		CScrollMgr::Get_Instance()->Set_ScrollY(2.f);
		break;
	}
}

void CPlayer::Release(void)
{
}
