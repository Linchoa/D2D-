#pragma once

#include "Include.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	void		Set_Pos(float _fX, float _fY) 
	{
		m_tInfo.vPos.x = _fX;
		m_tInfo.vPos.y = _fY;
	}

	const INFO&		Get_Info(void)const { return m_tInfo; }

public:
	virtual		void	Initialize(void)	PURE;
	virtual		int	Update(void)		PURE;
	virtual		void	Late_Update(void)	PURE;
	virtual		void	Render(HDC hDC)		PURE;
	virtual		void	Release(void)		PURE;
	
protected:
	INFO		m_tInfo;
	float		m_fAngle = 0.f;
	float		m_fSpeed;

	CObj*		m_pTarget;
};

