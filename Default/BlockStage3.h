#pragma once
#include "Obj.h"
class CBlockStage3 :
	public CObj
{
public:
	CBlockStage3();
	virtual ~CBlockStage3();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void	Set_SizeX(float _fX) { m_fSizeX = _fX; }
	float	Get_SizeX() { return m_fSizeX * 0.5f; }
	float	Get_SizeY() { return m_fSizeY * 0.5f; }

private :
	float			m_fSizeX;
	float			m_fSizeY;
};

