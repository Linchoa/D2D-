#pragma once

#include "Obj.h"

class CColisionMgr
{
public:
	CColisionMgr();
	~CColisionMgr();

public:
	static void CollisionPlayerBlock(CObj* _pPlayer, list<CObj*>* _pBlock);
	static void CollisionPlayerScore(CObj* _pPlayer, list<CObj*>* _pItem);
};

