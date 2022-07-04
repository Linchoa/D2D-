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
	static void Collision_Player_Monster_Stage1(list<CObj*> _Monster, CObj* _Player);
};

