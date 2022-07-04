#include "stdafx.h"
#include "Monster.h"
#include "ObjMgr.h"
#include "Player.h"


CMonster::CMonster()
{
}


CMonster::~CMonster()
{
	Release();
}

void CMonster::Initialize(void)
{
	m_tInfo.vPos.y = 0.f ;
	m_fSpeed = 10.f;
	
}

int CMonster::Update(void)
{
	if (m_bDead) {
		static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_List(OBJ_PLAYER)->front())->Set_Score(0, 100);
		return OBJ_DEAD;
	}

	m_tInfo.vPos.y += m_fSpeed;
	return OBJ_NOEVENT;
}

void CMonster::Late_Update(void)
{
	if (m_tInfo.vPos.y > 800)
		m_bDead = true;
}

void CMonster::Render(HDC hDC)
{
	Rectangle(hDC,
		int(m_tInfo.vPos.x - 30.f),
		int(m_tInfo.vPos.y - 30.f),
		int(m_tInfo.vPos.x + 30.f),
		int(m_tInfo.vPos.y + 30.f));
}

void CMonster::Release(void)
{
	
}
