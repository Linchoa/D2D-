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
	void		Set_FrameKey(TCHAR* _pFrameKey) { m_pFrameKey = _pFrameKey; }
	void		Set_Dead() { m_bDead = true; }

	const INFO&		Get_Info(void)const { return m_tInfo; }
	const bool&		Get_Dead(void)const { return m_bDead; }

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

	bool		m_bDead;

	CObj*		m_pTarget;

	TCHAR*		m_pFrameKey;
};

