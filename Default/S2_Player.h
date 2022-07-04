#pragma once
#include "SC_Obj.h"
class CS2_Player :
	public CSC_Obj
{
public:
#define PLAYER_X 20
#define	PLAYER_Y 50
	CS2_Player();
	virtual ~CS2_Player();
public:
	virtual		void	Initialize(void)	override;
	virtual		int		Update(void)		override;
	virtual		void	Late_Update(void)	override;
	virtual		void	Render(HDC hDC)		override;
	virtual		void	Release(void)		override;
public:
	void		SetZeroTime() { m_fTime = 0; }
	float		Get_Degree() { return m_fDegree; }
	int			Get_Score() { return m_iScore; }
	void		Zero_Score() { m_iScore = 0; }
private:
	void		Key_Input(void);
	void		Gravity(void);
private:
	float			m_fDegree;
	float			m_fPast_move;
	float			m_fTime;
	float			m_fPostX;
	float			m_fPostY;
private:
	INFO			m_vTarget;
private:
	int				m_iScore;
};



