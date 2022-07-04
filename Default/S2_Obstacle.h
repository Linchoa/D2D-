#pragma once
#include "SC_Obj.h"
class CS2_Obstacle :
	public CSC_Obj
{
public:
	CS2_Obstacle();
	virtual ~CS2_Obstacle();
public:
	virtual		void	Initialize(void)	override;
	virtual		int		Update(void)		override;
	virtual		void	Late_Update(void)	override;
	virtual		void	Render(HDC hDC)		override;
	virtual		void	Release(void)		override;
};


