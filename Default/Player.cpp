#include "stdafx.h"
#include "Player.h"
#include "SceneMgr.h"

CPlayer::CPlayer()
{
}


CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize(void)
{
	m_tInfo.vPos = { 400.f, 300.f, 0.f };

	m_fSpeed = 10.f;
}

int CPlayer::Update(void)
{
	switch (CSceneMgr::Get_Instance()->Get_Scene()) {
	case SC_STAGE1:
		break;
	case SC_STAGE2:
		break;
	case SC_STAGE3:
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
		break;
	}
}

void CPlayer::Render(HDC hDC)
{
	switch (CSceneMgr::Get_Instance()->Get_Scene()) {
	case SC_STAGE1:
		break;
	case SC_STAGE2:
		break;
	case SC_STAGE3:
		break;
	}
	
}

void CPlayer::Release(void)
{	
}

void CPlayer::Key_Input(void)
{
	switch (CSceneMgr::Get_Instance()->Get_Scene()) {
	case SC_STAGE1:
		break;
	case SC_STAGE2:
		break;
	case SC_STAGE3:
		break;
	}
	//if (GetAsyncKeyState(VK_RIGHT))
	//	m_fAngle += D3DXToRadian(3.f);

	//if (GetAsyncKeyState(VK_LEFT))
	//	m_fAngle -= D3DXToRadian(3.f);

}