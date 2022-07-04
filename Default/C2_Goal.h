#pragma once
#include "SC_Obj.h"
class C2_Goal :
	public CSC_Obj
{
public:
	C2_Goal();
	virtual ~C2_Goal();
public:
	virtual		void	Initialize(void)	override;
	virtual		int		Update(void)		override;
	virtual		void	Late_Update(void)	override;
	virtual		void	Render(HDC hDC)		override;
	virtual		void	Release(void)		override;
};

