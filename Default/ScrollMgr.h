#pragma once

#include "Define.h"

class CScrollMgr
{
private:
	CScrollMgr();
	~CScrollMgr();

public:
	void		Scroll_Lock(void);

public:
	static		CScrollMgr*		Get_Instance(void)
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CScrollMgr;

		return m_pInstance;
	}

	static		void			Destroy_Instance(void)
	{
		if (nullptr != m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

public:
	float		Get_ScrollX(void) { return m_fScrollX; }
	void		Set_ScrollX(float _x) { m_fScrollX += _x; }

	float		Get_ScrollY(void) { return m_fScrollY; }
	void		Set_ScrollY(float _y) {
		m_fScrollY += _y;
		m_fScrollY;
	}

	void		Set_MaxX(float _MaxX) { m_fMaxX = _MaxX; }
	void		Set_MaxY(float _MaxY) { m_fMaxY = _MaxY; }

	void		Reset() { m_fScrollX = 0.f; m_fScrollY = 0.f; }

private:
	static		CScrollMgr*		m_pInstance;

	float		m_fScrollX;
	float		m_fScrollY;
	float		m_fMaxX;
	float		m_fMaxY;
};

