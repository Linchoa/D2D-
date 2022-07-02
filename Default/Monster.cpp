#include "stdafx.h"
#include "Monster.h"


CMonster::CMonster()
{
}


CMonster::~CMonster()
{
	Release();
}

void CMonster::Initialize(void)
{
	m_tInfo.vPos = { 100.f, 100.f, 0.f };
	m_fSpeed = 5.f;
	
}

int CMonster::Update(void)
{
	return OBJ_NOEVENT;
}

void CMonster::Late_Update(void)
{
}

void CMonster::Render(HDC hDC)
{
}

void CMonster::Release(void)
{
	
}
