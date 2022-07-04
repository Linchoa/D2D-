#pragma once
#include "Obj.h"
class CSC_Obj :
	public CObj
{
public:
	enum OBJID { OBJ_PLAYER, OBJ_MONSTER, OBJ_ITEM, OBJ_END };
	CSC_Obj();
	virtual ~CSC_Obj();
public:
	void		Add_PosY(float _fY)
	{

		m_tInfo.vPos.y += _fY;
	}
	void		Add_posX(float _fX)
	{
		m_tInfo.vPos.x += _fX;
	}

public:
	virtual		void	Initialize(void)	PURE;
	virtual		int		Update(void)		PURE;
	virtual		void	Late_Update(void)	PURE;
	virtual		void	Render(HDC hDC)		PURE;
	virtual		void	Release(void)		PURE;
protected:
	D3DXVECTOR3			m_vPoint[4];
	D3DXVECTOR3			m_vOriginPoint[4];

	D3DXVECTOR3			m_vGunPoint;
	D3DXVECTOR3			m_vOriginGunPoint;
};

//class CObj
//{
//public:
//	CObj();
//	virtual ~CObj();
//
//public:
//	void		Set_Pos(float _fX, float _fY)
//	{
//		m_tInfo.vPos.x = _fX;
//		m_tInfo.vPos.y = _fY;
//	}
//
//	const INFO&		Get_Info(void)const { return m_tInfo; }
//
//public:
//	virtual		void	Initialize(void)	PURE;
//	virtual		int	Update(void)		PURE;
//	virtual		void	Late_Update(void)	PURE;
//	virtual		void	Render(HDC hDC)		PURE;
//	virtual		void	Release(void)		PURE;
//
//protected:
//	INFO		m_tInfo;
//	float		m_fAngle = 0.f;
//	float		m_fSpeed;
//
//	CObj*		m_pTarget;
//};
