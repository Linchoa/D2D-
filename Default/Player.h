#pragma once

#include "Obj.h"

class CPlayer :	public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	virtual void Initialize(void) override;
	virtual int	 Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void	Set_YPos(float _fY) { m_tInfo.vPos.y = _fY; }
	void	Set_JumpTrue() { 
		m_bJump = false;
		m_fTime = 0.f;
	}
	void	Set_Score(int _iNum, int _iScore) { m_iScore[_iNum] += _iScore; }
	void	Set_OriginPos(){ m_vOriginPos = m_tInfo.vPos; }

	bool	Get_Collision() { return m_bCollision; }
	float	Get_Size() { return m_fSize; }
	bool	Get_Win() { return m_bWin; }
	int		Get_Score(int _iNum) { return m_iScore[_iNum]; }
	void	Set_Reset() {
		m_iScore[2] = 0;
		m_bWin = false;
		m_bDead = false;
	}

private:
	void		Key_Input(void);
	void		Jumping(void);
	void		Offset(void);

private:
	bool		m_bJump;
	bool		m_bCollision;

	float		m_fSize;
	float		m_fJumpPower;
	float		m_fTime;

	int			m_iScore[3];

	bool		m_bWin;

	D3DXVECTOR3		m_vOriginPos;
};
