#pragma once

#include "Define.h"
#include "Player.h"
#include "Bullet.h"

class CMainGame
{
public:					// 생성자, 소멸자
	CMainGame();
	~CMainGame();

// public, protected, private 함수
 public:
	void		Initialize(void);
	void		Update(void);
	void		Late_Update(void);
	void		Render(void);
	void		Release(void);

// public, protected, private 변수
private:
	HDC			m_hDC;
	CObj*		m_pPlayer;
	CObj*		m_pMonster;

	list<CObj*>	m_BulletList;
};