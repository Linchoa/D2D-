#include "stdafx.h"
#include "Obj.h"

CObj::CObj() : m_fSpeed(0.f), m_bDead(false)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	D3DXMatrixIdentity(&m_tInfo.matWorld);
}

CObj::~CObj()
{
}

