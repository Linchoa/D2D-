#include "stdafx.h"
#include "ItemScore.h"
#include "ScrollMgr.h"


CItemScore::CItemScore() 
{
}


CItemScore::~CItemScore()
{
}

void CItemScore::Initialize(void)
{
	m_tInfo.vPos.z = 0.f;

	m_fX = m_tInfo.vPos.x;
	m_fY = m_tInfo.vPos.y;

	m_tInfo.vLook = { 0.f, -1.f, 0.f };

	m_fSpeed = 5.f;

	m_vPoint[2] = { m_tInfo.vPos.x + 15.f, m_tInfo.vPos.y + 11.f, 0.f };
	m_vPoint[1] = { m_tInfo.vPos.x - 15.f, m_tInfo.vPos.y + 11.f, 0.f };
	m_vPoint[0] = { m_tInfo.vPos.x, m_tInfo.vPos.y - 22.f, 0.f };

	for (int i = 0; i < 3; ++i)
		m_vOriginPoint[i] = m_vPoint[i];

	m_fAngle = D3DXToRadian(rand()% 100 + 130);
}

int CItemScore::Update(void)
{
	if (m_bDead) {
		return OBJ_DEAD;
	}

	D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
	m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;

	D3DXMATRIX	matScale, matRotZ, matTrans;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&matRotZ, m_fAngle);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	m_tInfo.matWorld = matScale * matRotZ * matTrans;

	for (int i = 0; i < 3; ++i)
	{
		m_vPoint[i] = m_vOriginPoint[i];
		m_vPoint[i] -= {m_fX, m_fY, 0.f};

		D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_tInfo.matWorld);
	}

	//m_fAngle += D3DXToRadian(3.f);

	return OBJ_NOEVENT; 
}

void CItemScore::Late_Update(void)
{
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	if (m_tInfo.vPos.y - 50 + iScrollY > 800)
		m_bDead = true;

	if(m_tInfo.vPos.x < 20)
		m_fAngle = D3DXToRadian(rand() % 40 + 110);
	else if(m_tInfo.vPos.x > 480)
		m_fAngle = D3DXToRadian(rand() % 40 + 210);
}

void CItemScore::Render(HDC hDC)
{
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	MoveToEx(hDC, m_vPoint[0].x, m_vPoint[0].y + iScrollY, nullptr);

	for (int i = 0; i < 3; ++i)
	{
		LineTo(hDC, m_vPoint[i].x, m_vPoint[i].y + iScrollY);

		if (i > 0)
			continue;

		Ellipse(hDC,
			int(m_vPoint[i].x - 5.f),
			int(m_vPoint[i].y - 5.f + iScrollY),
			int(m_vPoint[i].x + 5.f),
			int(m_vPoint[i].y + 5.f + iScrollY));
	}

	LineTo(hDC, m_vPoint[0].x, m_vPoint[0].y + iScrollY);
}

void CItemScore::Release(void)
{
}
