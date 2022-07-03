#pragma once
#include "Scene.h"
#include "Enum.h"
class CLogo :
	public CScene
{
public:
	CLogo();
	virtual ~CLogo();

public:
	void	Initialize(void);
	void	Update(void);
	void	Late_Update(void);
	void	Render(HDC hDC);
	void	Release(void);
};

