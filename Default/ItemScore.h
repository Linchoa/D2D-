#pragma once
#include "Item.h"
class CItemScore :
	public CItem
{
public:
	CItemScore();
	virtual ~CItemScore();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	D3DXVECTOR3			m_vPoint[3];
	D3DXVECTOR3			m_vOriginPoint[3];

	float				m_fX;
	float				m_fY;
};

