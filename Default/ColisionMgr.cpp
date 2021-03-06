#include "stdafx.h"
#include "ColisionMgr.h"
#include "BlockStage3.h"
#include "Player.h"


CColisionMgr::CColisionMgr()
{
}

CColisionMgr::~CColisionMgr()
{
}

void CColisionMgr::CollisionPlayerBlock(CObj * _pPlayer, list<CObj*>* _pBlock)
{
	for (auto& Block : *_pBlock) {
		if ((Block->Get_Info().vPos.x - static_cast<CBlockStage3*>(Block)->Get_SizeX()) <= _pPlayer->Get_Info().vPos.x 
			&& (Block->Get_Info().vPos.x + static_cast<CBlockStage3*>(Block)->Get_SizeX()) >= _pPlayer->Get_Info().vPos.x) {
			if (Block->Get_Info().vPos.y - static_cast<CBlockStage3*>(Block)->Get_SizeY() * 2 <= _pPlayer->Get_Info().vPos.y + 5
				&& Block->Get_Info().vPos.y + static_cast<CBlockStage3*>(Block)->Get_SizeY() * 2 >= _pPlayer->Get_Info().vPos.y 
				&& static_cast<CPlayer*>(_pPlayer)->Get_Collision()) {
				static_cast<CPlayer*>(_pPlayer)->Set_YPos(Block->Get_Info().vPos.y - static_cast<CBlockStage3*>(Block)->Get_SizeY() - 25.f);
				static_cast<CPlayer*>(_pPlayer)->Set_JumpTrue();
			}
		}
	}
}

void CColisionMgr::CollisionPlayerScore(CObj * _pPlayer, list<CObj*>* _pItem)
{
	for (auto& Item : *_pItem) {
		float fWidth = Item->Get_Info().vPos.x - _pPlayer->Get_Info().vPos.x;
		float fHeight = Item->Get_Info().vPos.y - _pPlayer->Get_Info().vPos.y;

		float fLength = sqrtf(fWidth * fWidth + fHeight * fHeight);

		if (fLength < 13 + static_cast<CPlayer*>(_pPlayer)->Get_Size()) {
			Item->Set_Dead();
			static_cast<CPlayer*>(_pPlayer)->Set_Score(2, 100);
		}
	}
}

void CColisionMgr::Collision_Player_Monster_Stage1(list<CObj*> _Monster, CObj* _Player)
{
	RECT rc{};

	for (auto& Monster : _Monster)
	{
		RECT Monster_Rect{ Monster->Get_Info().vPos.x - 30.f, Monster->Get_Info().vPos.y - 30.f,
			Monster->Get_Info().vPos.x + 30.f, Monster->Get_Info().vPos.y + 30.f };

		RECT Player_Rect{ _Player->Get_Info().vPos.x - 25.f, _Player->Get_Info().vPos.y - 25.f,
			_Player->Get_Info().vPos.x + 25.f, _Player->Get_Info().vPos.y + 25.f };

		if (IntersectRect(&rc, &Monster_Rect, &Player_Rect))
		{
			Monster->Set_Dead();
			_Player->Set_Dead();
		}
	}
}