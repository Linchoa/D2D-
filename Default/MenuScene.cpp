#include "stdafx.h"
#include "MenuScene.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "MyButton.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Player.h"


CMenuScene::CMenuScene()
{
}

CMenuScene::~CMenuScene()
{
	Release();
}

void CMenuScene::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Background/Menu.bmp", L"Menu");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Button/Menu_Button1.bmp", L"Stage1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Button/Menu_Button2.bmp", L"Stage2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Button/Menu_Button3.bmp", L"Stage3");

	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create());

	CObj*	pObj = CAbstractFactory<CMyButton>::Create(250.f, 300.f);
	pObj->Set_FrameKey(L"Stage1");
	CObjMgr::Get_Instance()->Add_Object(OBJ_BUTTON, pObj);

	pObj = CAbstractFactory<CMyButton>::Create(250.f, 450.f);
	pObj->Set_FrameKey(L"Stage2");
	CObjMgr::Get_Instance()->Add_Object(OBJ_BUTTON, pObj);

	pObj = CAbstractFactory<CMyButton>::Create(250.f, 600.f);
	pObj->Set_FrameKey(L"Stage3");
	CObjMgr::Get_Instance()->Add_Object(OBJ_BUTTON, pObj);
}

void CMenuScene::Update(void)
{
	CObjMgr::Get_Instance()->Update();
}

void CMenuScene::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CMenuScene::Render(HDC hDC)
{
	HDC	hMenuDC;

	hMenuDC = CBmpMgr::Get_Instance()->Find_Image(L"Menu");

	BitBlt(hDC, 0, 0, WINCX, WINCY, hMenuDC, 0, 0, SRCCOPY);

	CObjMgr::Get_Instance()->Render(hDC);
}

void CMenuScene::Release(void)
{
	CObjMgr::Get_Instance()->Delete_ID(OBJ_BUTTON);
}
